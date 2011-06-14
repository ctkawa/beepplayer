#include "biblioteca.h"

BIBLIOTECA::BIBLIOTECA(BANCODENOTAS* ba, BEEP* be) :
    ARVORE<MUSICA*>(){

    minhaMusica = NULL;
    banco = ba;
    beep = be;
    bibdir = "bib/";
    bibfile = "bib/biblioteca.bib";
    recarregar();
}

BANCODENOTAS* BIBLIOTECA::getBanco(){
    return banco;
}

BEEP* BIBLIOTECA::getBeep(){
    return beep;
}

MUSICA* BIBLIOTECA::getMinhaMusica(){
    return minhaMusica;
}

void BIBLIOTECA::setMinhaMusica(MUSICA* mus){
    minhaMusica = mus;
}

void BIBLIOTECA::recarregar(){
    // Abrindo arquivo biblioteca.bib

    char* bibfilec = new char[bibfile.length()+1];
    strcpy( bibfilec, bibfile.c_str() );

    int conf = GetFileAttributes(TEXT(bibfilec));
    if(conf == -1 || conf == FILE_ATTRIBUTE_DIRECTORY){
        cout << "Arquivo nao existe"<<endl;
        return;
    }

    ifstream ifs(bibfilec);
	string str;
	bool ok;

    // Copiando endereços das músicas
	ifs >> str;
    while(!ifs.eof()){
        //cout << str << endl;
        abrir(str);
        moveMinhaMusicaPBib();
        bibfiles.adicionar(str, ok);
        ifs >> str;
    }

    delete bibfilec;

}

void BIBLIOTECA::moveMinhaMusicaPBib(){
    if(minhaMusica != NULL){
        minhaMusica->setNome(normalizaNome(minhaMusica->getNome()));
        while( estaNaArvore(minhaMusica) ){
            string novoNome;
            cout << "Este nome ja existe na biblioteca." << endl;
            cout << "Digite outro nome: ";
            cin >> novoNome;
            minhaMusica->setNome(normalizaNome(novoNome));
        }

        insere(minhaMusica);
        minhaMusica = NULL;
    }
}

void BIBLIOTECA::tocar(string s, bool& ok){
    NO2<MUSICA*>* noMus = NULL;
    bool encontrado = false;
    busca(s, raiz, noMus, encontrado);
    if(encontrado){
        ok = true;
        noMus->getInfo()->tocar();
    } else {
        ok = false;
    }
}

MUSICA* BIBLIOTECA::getMusica(string s, bool &ok){
    NO2<MUSICA*>* noMus = NULL;
    bool encontrado = false;
    busca(s, raiz, noMus, encontrado);
    if(encontrado){
        ok = true;
        return noMus->getInfo();
    } else {
        ok = false;
        return NULL;
    }
}

string BIBLIOTECA::normalizaNome(string s){
    for(unsigned int i=0; i<s.length(); i++){
        if(s[i] == ' ')
            s[i] = '_';
    }
    return s;
}

bool BIBLIOTECA::salvar(){
    // Pedindo o nome do arquivo
    string nomeP;
    cout << "Salvando: entre com nome do arquivo: ";
    cin >> nomeP;
    nomeP = normalizaNome(nomeP);
    while(bibfiles.estaNaLista(nomeP)){
        cout << "Este arquivo ja existe." << endl;
        cout << "Digite outro nome de arquivo: ";
        cin >> nomeP;
        nomeP = normalizaNome(nomeP);
        if(nomeP == "")
            return false;
    }

    // Verificando se o nome da música já existe
    string novoNome;
    while(estaNaArvore(minhaMusica)){
        cout << "Este nome de musica ja existe." << endl;
        cout << "Digite outro nome: ";
        cin >> novoNome;
        normalizaNome(novoNome);
        if(novoNome == "")
            return false;
        minhaMusica->setNome(novoNome);
    }

    // Adicionando a biblioteca
//    cout << "Adicionando a biblioteca" << endl;
    bool ok;
    bibfiles.adicionar(nomeP, ok);
    salvarBib();

    nomeP = bibdir + nomeP;
    char* arqNome = new char[nomeP.length()+1];
    strcpy( arqNome, nomeP.c_str() );

    ofstream ofs(arqNome);

    // Salvando nome
//    cout << "Salvando nome" << endl;
    ofs << "nome," << normalizaNome(minhaMusica->getNome()) << endl;

    // Salvando notas
//    cout << "Salvando notas" << endl;
    NO2<NOTA*> *noPtr;
    noPtr = minhaMusica->getPtrHeader()->getDir();
    while(noPtr!=minhaMusica->getPtrHeader()){
        ofs << noPtr->getInfo()->getNome() << "," << noPtr->getInfo()->getTempo() << endl;
        noPtr = noPtr->getDir();
    }

    //cout << "insert" << endl;
    insere(minhaMusica);
    minhaMusica = NULL;

    delete arqNome;

    return true;
}

void BIBLIOTECA::salvarBib(){

    if(!bibfiles.vazia()){
        char* bibfilec = new char[bibfile.length()+1];
        strcpy( bibfilec, bibfile.c_str() );
        ofstream ofsbib(bibfilec);

        NO2<string>* ptrMus = bibfiles.getPtrHeader()->getDir();
        while(ptrMus != bibfiles.getPtrHeader()){
            ofsbib << ptrMus->getInfo() << endl;
            ptrMus = ptrMus->getDir();
        }

        delete bibfilec;
    }

}


bool BIBLIOTECA::abrir(string nomeP){
    nomeP = bibdir + nomeP;

    char* arqNome = new char[nomeP.length()+1];
    strcpy( arqNome, nomeP.c_str() );

    //cout << "VERIFICANDO EXISTENCIA DO ARQUIVO: " << arqNome <<endl;
    int conf = GetFileAttributes(TEXT(arqNome));
    if(conf == -1 || conf == FILE_ATTRIBUTE_DIRECTORY){
        cout << "Arquivo nao existe"<<endl;
        return false;
    }

    //
    string entrada;
    //cout << "VERIFICANDO OVERWRITE"<<endl;
    if(minhaMusica != NULL){
        bool b = desejaSalvar();
        if(b==false){
            cout << "Cancelado pelo usuario " << b << endl;
            return false;
        }

        minhaMusica = new MUSICA(beep);
    } else {
        minhaMusica = new MUSICA(beep);
    }

//    cout << "ABRINDO IFS"<<endl;
	ifstream ifs(arqNome);
	string str,strTempo;
	float tempo;
    bool okn, okt;

	NOTA minhaNota(banco);

//    cout << "LENDO DO IFS"<<endl;
	ifs >> str;
	string arg1 = "";
	string arg2 = "";
    while(!ifs.eof()){
//        cout << "Linha=>" << str << endl;
            if(str!=""){
            arg1 = str.substr(0,str.find(','));
            arg2 = str.substr(str.find(',')+1);
            if(arg1 == "nome"){
//                cout << "Nome=>" << arg2 << " -> " << normalizaNome(arg2);
                minhaMusica->setNome(normalizaNome(arg2));
//                cout << "  Nome mudado" << endl;
            } else {

                tempo = ::atof(arg2.c_str());
                minhaNota.setNota(arg1,tempo,okn,okt);
                if(! minhaMusica->insereAEsquerda(banco->getNota(minhaNota),*minhaMusica->getPtrHeader()))
                    cout << "Erro, Nota nao reconhecida: " << str << endl;
            }
        }
//        cout << "[END OF LINE]" << endl;
        ifs >> str;
    }
    //minhaMusica->tocar();

    delete arqNome;

    return true;
}

bool BIBLIOTECA::desejaSalvar(){
    string entrada;
    if(minhaMusica != NULL && minhaMusica->getTamanhoAtual()!=0){
        do{
            cout << "Existe uma musica aberta. Deseja salvar? (Sim/Nao/Cancelar): ";
            cin >> entrada;
        }while(entrada!="S" && entrada!="N" && entrada!="C");
        if(entrada == "C"){
            return false;
        } else if(entrada == "N"){
            delete minhaMusica;
            minhaMusica = NULL;
            return true;
        } else {
            salvar();
            if(minhaMusica != NULL)
                return false;
            else return true;
        }
    } else {
        return true;
    }
}

void BIBLIOTECA::getMusicas(LISTA<string>* musicas){
    getMusicasR(raiz, musicas);
}

void BIBLIOTECA::getMusicasR(NO2<MUSICA*>* no, LISTA<string>* musicas){
    if( no == NULL){
        return;
    } else {
        bool ok;
        musicas->adicionar(no->getInfo()->getNome(), ok);
        getMusicasR(no->getEsq(), musicas);
        getMusicasR(no->getDir(), musicas);
    }
}

void BIBLIOTECA::busca(string s, NO2<MUSICA*>* no, NO2<MUSICA*>* &resultado, bool& encontrado){
    if(no == NULL || encontrado){
        return;
    } else {
        if(no->getInfo()->getNome() == s){
            resultado = no;
            encontrado = true;
            return;
        } else if(no->getInfo()->getNome() < s){
            busca(s, no->getEsq(), resultado, encontrado);
                                                                        if(!encontrado){
                                                                            busca(s, no->getDir(), resultado, encontrado);
                                                                            if(encontrado)
                                                                                cout << "WRONG SEARCH 1 : "<<no->getInfo()->getNome() <<" not < "<< s<<endl;
                                                                        }
        } else {
            busca(s, no->getDir(), resultado, encontrado);
                                                                        if(!encontrado){
                                                                            busca(s, no->getEsq(), resultado, encontrado);
                                                                            if(encontrado)
                                                                                cout << "WRONG SEARCH 2 : "<<no->getInfo()->getNome() <<" not >= "<< s<<endl;
                                                                        }
        }
    }
}

BIBLIOTECA::~BIBLIOTECA(){
    delete beep;
}


void BIBLIOTECA::imprimeAll(){
    cout << "Imprimindo tudo, raiz = "<<raiz<<endl;
    imprimeAllR(raiz);
}
void BIBLIOTECA::imprimeAllR(NO2<MUSICA*> *no){
    if(no!=NULL){
        imprimeAllR(no->getEsq());
        cout << no << " possui " << no->getInfo()->getNome() << ", Dir=" << no->getDir() << ", Esq=" << no->getEsq() << endl;
        imprimeAllR(no->getDir());
    } else
        return;
}
