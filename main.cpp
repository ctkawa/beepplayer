#include <iostream>
#include <conio.h>
#include <fstream>
#include <windows.h>

#include "biblioteca.h"

#include "no1.h"

#define SAIDA 0
#define ENTRADA 1
#define COMANDO 2
#define PLAYER 3
#define PIANO 4
#define TESTE 5
#define SOBRE 6

using namespace std;

// Prototipos
void tocarBib(BIBLIOTECA*);
void salvar(string, MUSICA &);
void salvarBib(BIBLIOTECA*);
void nova(MUSICA &mus, bool &ok);
//void abrir(BIBLIOTECA*);
void abrirBib(BIBLIOTECA*);
//void gravar(MUSICA &, BIBLIOTECA*);
void gravarBib(BIBLIOTECA*);
void piano(BIBLIOTECA*);
void teste();

/////////////////////////////////////////////////
////// TELA: ENTRADA
/////////////////////////////////////////////////

int telaEntrada(){
    system("CLS");
    cout << "\tUniversidade Federal de Sao Carlos" << endl;
    cout << "\tDepartamento de Computacao" << endl;
    cout << "\tBacharelado em Ciencias da Computacao" << endl;
    cout << "\tTrabalho de Estruturas de Dados" << endl;
    cout << "\n\n\n\n\n\n";
    cout << "\t\tBeep Player" << endl;
    cout << "\n\n\n";
    cout << "Cleber Takahito Kawamorita" << endl;
    cout << "Felipe Augusto de Salles Pupo" << endl;
    cout << "Joao C. S. de Oliveira" << endl;
    cout << "Willian Lira Cardoso" << endl;
    cout << "\n\n\n";
    cout << "[Tecle ENTER para continuar]" << endl;
    getche();
    return COMANDO;
}

/////////////////////////////////////////////////
////// TELA: SAÍDA
/////////////////////////////////////////////////

int telaSaida(){
    system("CLS");
    cout << "\tUniversidade Federal de Sao Carlos" << endl;
    cout << "\tDepartamento de Computacao" << endl;
    cout << "\tBacharelado em Ciencias da Computacao" << endl;
    cout << "\tTrabalho de Estruturas de Dados" << endl;
    cout << "\n\n\n\n\n\n";
    cout << "\t\tBeep Player" << endl;
    cout << "\n\n\n\n\n\n";
    Sleep(2000);
    return 0;
}

/////////////////////////////////////////////////
////// TELA: COMANDO
/////////////////////////////////////////////////

int telaComando(BIBLIOTECA* bib){
    system("CLS");
    BEEP* beep = bib->getBeep();
    //MUSICA minhaMusica(beep, "Minha música");
    bool sair = false;
    string cmd = "";

    while(!sair){
        system("CLS");
        if(bib->getMinhaMusica()!=NULL)
            cout << "Múica atual :" << bib->getMinhaMusica()->getNome() << endl;
        else
            cout << "Sem música aberta"<<endl;
        cout << "\nEntre com comando" << endl <<" {sair; tocar; teste; abrir; salvar; nova; piano; sobre}" << endl << "{tocarbib; abrirbib; salvarbib; gravarbib; player}" << endl << ">> ";
        cin >> cmd;
        if(cmd == "sair" || cmd == "exit" || cmd == "fechar" || cmd == "q" || cmd == "quit")
            return SAIDA;
        else if(cmd == "tocar"){
            bool ok;
            system("CLS");
            cout << "Múica atual :" << bib->getMinhaMusica()->getNome() << endl;
            cout << "Tamanho     :" << bib->getMinhaMusica()->getTamanhoAtual() << endl;
            bib->getMinhaMusica()->tocar();
            cout << "Fim da música. Aperte alguma tela para continuar ...";
            getche();
            //return COMANDO;
        } else if(cmd == "tocarbib"){
            tocarBib(bib);
        } else if(cmd == "teste" || cmd == "test"){
            return TESTE;
        } else if(cmd == "salvar" || cmd == "save"){
                string nomeP;
                cout << "Salvar em arquivo" << endl;
                cout << "Salvando: entre com nome do arquivo: ";
                cin >> nomeP;
                bib->getMinhaMusica()->setNome(nomeP);
                salvar(nomeP, *(bib->getMinhaMusica()));
            Sleep(500);
            //return COMANDO;
        } else if(cmd == "salvarbib"){
            salvarBib(bib);
            return COMANDO;

//        } else if(cmd == "abrir" || cmd == "open"){
//            abrir(bib);
//            Sleep(500);
//            //return COMANDO;

        } else if(cmd == "nova" || cmd == "new"){
            bool ok;
            nova(*bib->getMinhaMusica(), ok);
            if(!ok){
                cout << "!\tErro ao criar nova musica" << endl;
                Sleep(1000);
            }
        } else if(cmd == "abrirbib"){
            abrirBib(bib);
            Sleep(500);

//        } else if(cmd == "gravar"){
//            gravar(*bib->getMinhaMusica(), bib);
//            Sleep(500);
            //return COMANDO;

        } else if(cmd == "gravarbib"){
            gravarBib(bib);
        } else if(cmd == "piano"){
            return PIANO;
        } else if(cmd == "sobre"){
            return SOBRE;
        } else if(cmd == "player"){
            return PLAYER;
        } else {
            cout << "Comando desconhecido." << endl;
            Sleep(500);
            //return COMANDO;
        }
    }
    return COMANDO;
}

void tocarBib(BIBLIOTECA* bib){
    MUSICA* minhaMusica = bib->getMinhaMusica();
    if(minhaMusica != NULL)
        minhaMusica->tocar();
}

void salvarBib(BIBLIOTECA* bib){
    bib->salvar();
}

void nova(MUSICA &mus, bool &ok){
    ok=true;
    while((mus.getTamanhoAtual()!=0) && (ok)){ // retirar todos os elementos
        mus.retirar(mus.getPtrHeader()->getDir(), ok);
    }
    if(ok)
        mus.setNome("NovaMusica");
}

void salvar(string nomeP, MUSICA &mus){
    char* arqNome = new char[nomeP.length()+1];
    strcpy( arqNome, nomeP.c_str() );

    ofstream ofs(arqNome);
    NO2<NOTA*> *noPtr;
    noPtr = mus.getPtrHeader()->getDir();
    while(noPtr!=mus.getPtrHeader()){
        ofs << noPtr->getInfo()->getNome() << "," << noPtr->getInfo()->getTempo() << endl;
        noPtr = noPtr->getDir();
    }
    delete arqNome;
}

void abrirBib(BIBLIOTECA* bib){
    string nomeP;

    //if(bib->desejaSalvar());
    MUSICA* minhaMusica = bib->getMinhaMusica();
    if( minhaMusica != NULL){
        bool b = bib->desejaSalvar();
        if(b==false){
            cout << "Cancelado pelo usuario " << b << endl;
            return;
        }
    } else {
        delete minhaMusica; // ja deletedo no desejaSalvar();
        minhaMusica = new MUSICA(bib->getBeep(), "Sem nome");
    }
    bib->setMinhaMusica(minhaMusica);

    cout << "Abrindo: Entre com nome do arquivo: ";
    cin >> nomeP;
    if (bib->abrir(nomeP)){
        cout << endl << "Música aberta:" << bib->getMinhaMusica()->getNome() << endl << "Aperte alguma tela para continuar ...";
        getche();
    } else {
        cout << endl << "Abortado" << endl << "Aperte alguma tecla para continuar ...";
        getche();
    }


}

//void abrir(BIBLIOTECA* bib){
//    system("CLS");
//    string nomeP;
//
//    if(bib->getMinhaMusica()->getTamanhoAtual()!=0)
//        cout << "Música atual será descartada. (Digite nome inválido para cancelar)" << endl;
//
//    cout << "Entre com nome do arquivo: ";
//    cin >> nomeP;
//
//    char* arqNome = new char[nomeP.length()+1];
//    strcpy( arqNome, nomeP.c_str() );
//
//    int conf = GetFileAttributes(TEXT(arqNome));
//    if(conf == -1 || conf == FILE_ATTRIBUTE_DIRECTORY){
//        cout << "Arquivo nao existe"<<endl;
//        return;
//    }
//
//	ifstream ifs(arqNome);
//	string str,strTempo;
//	float tempo;
//    bool okn, okt;
//
//	NOTA minhaNota(bib->getBanco());
//	MUSICA minhaMusica(bib->getBeep(), nomeP);
//	ifs >> str;
//    while(!ifs.eof()){
//        cout << str << endl;
//        strTempo = str.substr(str.find(',')+1);
//        tempo = ::atof(strTempo.c_str());
//        minhaNota.setNota(str.substr(0,str.find(',')),tempo,okn,okt);
//        minhaMusica.insereAEsquerda(&minhaNota,*minhaMusica.getPtrHeader());
//        ifs >> str;
//    }
//    minhaMusica.tocar();
//
//    delete arqNome;
//}


void gravarBib(BIBLIOTECA* bib){
    BANCODENOTAS* banco = bib->getBanco();
    MUSICA* minhaMusica = bib->getMinhaMusica();

    if(minhaMusica != NULL){
        if(!bib->desejaSalvar()){
            return;
        }
    } else {
        delete minhaMusica;
        minhaMusica = new MUSICA(bib->getBeep(), "Minha Gravacao");
        bib->setMinhaMusica(minhaMusica);
    }

    system("CLS");
    cout << "Gravacao" << endl << "entre com nota e tempo separado com virgula (1do,1; 0re,0.25 ...) uma nota por linha." << endl << "fim para sair"<< endl << endl;
    NOTA minhaNota(banco);
	bool okn, okt;
	float tempo;
    string cmd="",strTempo, strNota;
    cin >> cmd;
    while(!(cmd=="fim"||cmd=="end")){
        strTempo = cmd.substr(cmd.find(',')+1);
        tempo = ::atof(strTempo.c_str());
        minhaNota.setNota(cmd.substr(0,cmd.find(',')),tempo,okn,okt);
        if (okn&&okt)
            minhaMusica->insereAEsquerda(banco->getNota(minhaNota),*minhaMusica->getPtrHeader());
        cout << "nota: " << (okn?minhaNota.getNome():"erro") << ", tempo: " << (okt?strTempo:"erro") << (okn&&okt?" gravado.":" => falha.") << endl;
        cin >> cmd;
    }
    //minhaMusica.tocar();
}

//void gravar(MUSICA &minhaMusica, BIBLIOTECA* bib){
//    BANCODENOTAS* banco = bib->getBanco();
//
//    system("CLS");
//    cout << "Gravacao" << endl << "entre com nota e tempo separado com virgula (1do,1; 0re,0.25 ...) uma nota por linha." << endl << "fim para sair"<< endl << endl;
//    NOTA minhaNota(banco);
//	bool okn, okt;
//	float tempo;
//    string cmd="",strTempo, strNota;
//    cin >> cmd;
//    while(!(cmd=="fim"||cmd=="end")){
//        strTempo = cmd.substr(cmd.find(',')+1);
//        tempo = ::atof(strTempo.c_str());
//        minhaNota.setNota(cmd.substr(0,cmd.find(',')),tempo,okn,okt);
//        if (okn&&okt)
//            minhaMusica.insereAEsquerda(banco->getNota(minhaNota),*minhaMusica.getPtrHeader());
//        cout << "nota: " << (okn?minhaNota.getNome():"erro") << ", tempo: " << (okt?strTempo:"erro") << (okn&&okt?" gravado.":" => falha.") << endl;
//        cin >> cmd;
//    }
//    //minhaMusica.tocar();
//}



/////////////////////////////////////////////////
////// TELA: PLAYER
/////////////////////////////////////////////////

int telaPlayer(BIBLIOTECA* bib){
    bool sair = false;
    string cmd;
    LISTA<string>* musicas = new LISTA<string>;
    NO2<string>* ptrMus = NULL;
    NO2<string>* ptrTocar = NULL;
    MUSICA* tmpMus;
    bool ok;

    musicas->esvaziar();
    bib->getMusicas(musicas);   // obter lista de musicas da biblioteca


    char c;
    if(!musicas->vazia()){
        ptrTocar = musicas->getPtrHeader()->getDir();
    }

//     system("CLS");
//        cout << "BEEP PLAYER" << endl;
//        if(musicas->vazia()){
//            cout << "A biblioteca está vazia." << endl;
//        } else {
//            ptrMus = musicas->getPtrHeader()->getDir();
//            while(ptrMus != musicas->getPtrHeader()){
//                if(ptrMus == ptrTocar) cout << ">> ";
//                else cout << "   ";
//                cout << ptrMus->getInfo() << endl;
//                ptrMus = ptrMus->getDir();
//            }
//        }

    do{
        system("CLS");
        cout << "BEEP PLAYER" << "\t [q] para sair." << endl;
        if(musicas->vazia()){
            cout << "A biblioteca está vazia." << endl;
        } else {
            ptrMus = musicas->getPtrHeader()->getDir();
            while(ptrMus != musicas->getPtrHeader()){
                if(ptrMus == ptrTocar) cout << ">> ";
                else cout << "   ";
                cout << ptrMus->getInfo() << endl;
                ptrMus = ptrMus->getDir();
            }
        }

        //if(kbhit){
           switch(c = getch()){
                case 'P':
                    if(ptrTocar != NULL && ptrTocar->getDir() != musicas->getPtrHeader())
                        ptrTocar = ptrTocar->getDir();
                    break;
                case 'H':
                    if(ptrTocar != NULL && ptrTocar->getEsq() != musicas->getPtrHeader())
                        ptrTocar = ptrTocar->getEsq();
                    break;
                case 29://[esc]
                case 'q':
                    sair = true;
                    break;
                case 13:
                    tmpMus = bib->getMusica(ptrTocar->getInfo(), ok);
                    if(tmpMus == NULL){
                        cout << "SELECTED: " << ptrTocar->getInfo() << endl;
                        cout << "FETCH ERR" << endl<<endl;
                        bib->imprimeAll();
                        getch();
                        break;
                    }
                    cout << "Múica atual :" << bib->getMusica(ptrTocar->getInfo(), ok)->getNome() << endl;
                    if(ok){
                        cout << "Tamanho     :" << bib->getMusica(ptrTocar->getInfo(), ok)->getTamanhoAtual() << endl;
                        if(ok){
                            bib->tocar(ptrTocar->getInfo(), ok);
                            if(!ok)
                                cout << "Erro ao tocar"<< endl;
                        }else cout << "Erro ao gettamanho"<< endl;
                    } else cout << "Erro ao getnome"<< endl;
                    cout << endl <<  "Aperte alguma tecla para continuar ...";
                    getch();
                    break;
            }
        //}
        Sleep(1);
    }while(!sair);

    return COMANDO;
}

/////////////////////////////////////////////////
////// TELA: PIANO
/////////////////////////////////////////////////

int telaPiano(BIBLIOTECA* bib){
    system("CLS");
    piano(bib);
    return COMANDO;
}


void piano(BIBLIOTECA* bib){
    BANCODENOTAS* banco = bib->getBanco();
    BEEP* bep = bib->getBeep();

    MUSICA* minhaMusica = bib->getMinhaMusica();
    if( minhaMusica != NULL){
        bool b = bib->desejaSalvar();
        if(b==false){
            cout << "Cancelado pelo usuario " << b << endl;
            return;
        } else {
            if(bib->getMinhaMusica()!=NULL){
                cout << "somethig wrong..." << endl;
            }
            minhaMusica = new MUSICA(bib->getBeep(), "Sem nome");
        }
    } else {
        delete minhaMusica;
        minhaMusica = new MUSICA(bib->getBeep(), "Sem nome");
    }
    bib->setMinhaMusica(minhaMusica);

    system("CLS");
    cout << "Piano" << endl << "[Esc] para sair" << endl << endl;
    bool ok;

    char key;
    int i;
    bool okn, okt;
    NOTA minhaNota(banco);
    do{
        if (kbhit()){
            key = getch();
            i =key;
            cout << key << " " << (int)key;
            switch(key){
                case(32):
                    minhaNota.setNota("pausa",0.5,okn,okt);
                    break;
                case(13):
                    okt = false;
                    okn = false;
                    cout << bib->getMinhaMusica()->getNome() << ", tamanho: " << bib->getMinhaMusica()->getTamanhoAtual() << endl;
                    bib->getMinhaMusica()->tocar();
                    break;

                case(122):
                    minhaNota.setNota("0do",0.25,okn,okt);
                    break;
                case(120):
                    minhaNota.setNota("0re",0.25,okn,okt);
                    break;
                case(99):
                    minhaNota.setNota("0mi",0.25,okn,okt);
                    break;
                case(118):
                    minhaNota.setNota("0fa",0.25,okn,okt);
                    break;
                case(109):
                    minhaNota.setNota("0sol",0.25,okn,okt);
                    break;
                case(44):
                    minhaNota.setNota("0la",0.25,okn,okt);
                    break;
                case(46):
                    minhaNota.setNota("0si",0.25,okn,okt);
                    break;
                case(47):
                    minhaNota.setNota("1do",0.25,okn,okt);
                    break;
                case(97):
                    minhaNota.setNota("0do",0.5,okn,okt);
                    break;
                case(115):
                    minhaNota.setNota("0re",0.5,okn,okt);
                    break;
                case(100):
                    minhaNota.setNota("0mi",0.5,okn,okt);
                    break;
                case(102):
                    minhaNota.setNota("0fa",0.5,okn,okt);
                    break;
                case(106):
                    minhaNota.setNota("0sol",0.5,okn,okt);
                    break;
                case(107):
                    minhaNota.setNota("0la",0.5,okn,okt);
                    break;
                case(108):
                    minhaNota.setNota("0si",0.5,okn,okt);
                    break;
                case(59):
                    minhaNota.setNota("1do",0.5,okn,okt);
                    break;

                case(113):
                    minhaNota.setNota("0do",1,okn,okt);
                    break;
                case(119):
                    minhaNota.setNota("0re",1,okn,okt);
                    break;
                case(101):
                    minhaNota.setNota("0mi",1,okn,okt);
                    break;
                case(114):
                    minhaNota.setNota("0fa",1,okn,okt);
                    break;
                case(117):
                    minhaNota.setNota("0sol",1,okn,okt);
                    break;
                case(105):
                    minhaNota.setNota("0la",1,okn,okt);
                    break;
                case(111):
                    minhaNota.setNota("0si",1,okn,okt);
                    break;
                case(112):
                    minhaNota.setNota("1do",1,okn,okt);
                    break;
                case(49):
                    minhaNota.setNota("0do",2,okn,okt);
                    break;
                case(50):
                    minhaNota.setNota("0re",2,okn,okt);
                    break;
                case(51):
                    minhaNota.setNota("0mi",2,okn,okt);
                    break;
                case(52):
                    minhaNota.setNota("0fa",2,okn,okt);
                    break;
                case(55):
                    minhaNota.setNota("0sol",2,okn,okt);
                    break;
                case(56):
                    minhaNota.setNota("0la",2,okn,okt);
                    break;
                case(57):
                    minhaNota.setNota("0si",2,okn,okt);
                    break;
                case(48):
                    minhaNota.setNota("1do",2,okn,okt);
                    break;

                default:
                    okt = false;
                    okn = false;
                    break;
            }
            if(okn&&okt){
                if(!bib->getMinhaMusica()->insereAEsquerda(banco->getNota(minhaNota), *bib->getMinhaMusica()->getPtrHeader()))
                   cout << "insert Error!" << endl;
                bep->tocar(&minhaNota);
                cout << " \t"  << minhaNota.getNome() << ", " << minhaNota.getTempo();
            } else if(key!=13&&key!=27)
                cout << "Nao reconhecido";
            cout << endl;
        }
    }while(key!=27);
}


/////////////////////////////////////////////////
////// TELA: TESTE
/////////////////////////////////////////////////

int telaTeste(){
    system("CLS");
    teste();
    return COMANDO;
}

void teste(){

    BANCODENOTAS* banco = new BANCODENOTAS;
    BEEP beep(banco);
    NOTA n(banco);
    NOTA* pn;

    bool okn, okt; //ok nota tempo
    cout << "Modulo de teste" << endl;

    Sleep(500);
    cout << "Teste de NOTA" << endl;
    cout << "\t" << n.getNome() << " " << n.getTempo() << endl;
    n.setNota("0sol", 0.5, okn, okt);

    Sleep(500);
    cout << "Teste do Beep do sistema" << endl;
    Beep(440, 200);
    Beep(494, 200);
    Beep(554, 200);
    Beep(587, 200);
    Beep(659, 200);
    Beep(740, 200);
    Beep(830, 200);
    Beep(880, 200);

    Sleep(500);
    cout << "Teste de BEEP" << endl;
    cout << "\tTocando nota ..." << endl;
    pn = banco->getNotaPadrao();
    beep.tocar(pn);
    pn = banco->getNota(n);
    beep.tocar(pn);
    beep.tocar();

    Sleep(500);
    NOTA* nota[8];
    for(int i=0; i<8; i++)
        nota[i] = new NOTA(banco);

    nota[0]->setNota("0do",0.5,okn,okt);
    nota[1]->setNota("0re",0.5,okn,okt);
    nota[2]->setNota("0mi",0.5,okn,okt);
    nota[3]->setNota("0fa",0.5,okn,okt);
    nota[4]->setNota("0sol",0.5,okn,okt);
    nota[5]->setNota("0la",0.5,okn,okt);
    nota[6]->setNota("0si",0.5,okn,okt);
    nota[7]->setNota("1do",0.5,okn,okt);
    for(int i=0; i<8; i++)
        beep.tocar(nota[i]);

    Sleep(500);
    cout << "Teste de BANCODENOTAS" << endl;

    pn = banco->getNota(n);
    beep.tocar(pn);

    n.setNota("0re", okn);
    pn = banco->getNota(n);
    beep.tocar(pn);

    n.setNota("erro", okn);
    pn = banco->getNota(n);
    beep.tocar(pn);

    pn = banco->getNotaPadrao();
    beep.tocar(pn);

    Sleep(500);
    cout << "Teste de NO1" << endl;
    NO1<NOTA*> no1;
    n.setNota("0la", 0.75, okn, okt);
    no1.setInfo(banco->getNota(n));
    cout << "\t" << no1.getInfo()->getNome() << " " << no1.getInfo()->getTempo() << endl;
    beep.tocar(no1.getInfo());

    Sleep(500);
    cout << "Teste de encadeamento de NO1" << endl;
    NO1<NOTA*> no12;
    n.setNota("0si", 0.5, okn, okt);
    no12.setInfo(banco->getNota(n));
    no1.setNext(&no12);

    NO1<NOTA*> no13;
    n.setNota("1do", 0.5, okn, okt);
    no13.setInfo(banco->getNota(n));
    no12.setNext(&no13);

    NO1<NOTA*> * pno1;
    pno1 = &no1;
    while(pno1 != NULL){
        beep.tocar(pno1->getInfo());
        pno1 = pno1->getNext();
    }

    Sleep(500);
    cout << "Teste de NO2" << endl;
    NO2<NOTA*> no2;
    n.setNota("0do", 2, okn, okt);
    no2.setInfo(banco->getNota(n));
    cout << "\t" << no2.getInfo()->getNome() << " " << no2.getInfo()->getTempo() << endl;
    beep.tocar(no2.getInfo());

    Sleep(500);
    cout << "Teste de encadeamento de NO2" << endl;
    NO2<NOTA*> no22;
    n.setNota("0re", 1, okn, okt);
    no22.setInfo(banco->getNota(n));
    no2.setDir(&no22);
    no22.setEsq(&no2);

    NO2<NOTA*> no23;
    n.setNota("0mi", 0.5, okn, okt);
    no23.setInfo(banco->getNota(n));
    no22.setDir(&no23);
    no23.setEsq(&no22);

    NO2<NOTA*> * pno2;
    pno2 = &no2;
    while(pno2 != NULL){
        beep.tocar(pno2->getInfo());
        pno2 = pno2->getDir();
    }

    pno2 = &no23;
    while(pno2 != NULL){
        beep.tocar(pno2->getInfo());
        pno2 = pno2->getEsq();
    }

    Sleep(500);
    cout << "Teste de MUSICA" << endl;
    cout << "teste 1" << endl;
    MUSICA mus(&beep);
    mus.setNome("Teste");
    n.setNota("0do", okn);
    mus.adicionar(banco->getNota(n), okn);
    n.setNota("0mi", okn);
    mus.adicionar(banco->getNota(n), okn);
    n.setNota("0sol", okn);
    mus.adicionar(banco->getNota(n), okn);
    n.setNota("1do", okn);
    mus.adicionar(banco->getNota(n), okn);
    n.setNota("0sol", okn);
    mus.adicionar(banco->getNota(n), okn);
    n.setNota("0mi", okn);
    mus.adicionar(banco->getNota(n), okn);
    n.setNota("0do", okn);
    mus.adicionar(banco->getNota(n), okn);

    mus.tocar();
    cout << "\t" << mus.getNome() << endl;

    Sleep(500);
    cout << "teste 2"<<endl;
    MUSICA minhaMus(&beep);
    for(int i=0; i<8; i++)
        minhaMus.insereADireita(nota[i], *minhaMus.getPtrHeader());
    minhaMus.tocar();

    Sleep(500);
    cout << "Teste de BIBLIOTECA" << endl;
    BIBLIOTECA bib(banco, &beep);
    bib.tocar("Teste", okn);

    Sleep(1000);
}


/////////////////////////////////////////////////
////// TELA: SOBRE
/////////////////////////////////////////////////

int telaSobre(){
    system("CLS");
    system("more sobre");
    cout << "[tecle ENTER para sair]";
    getche();
    return COMANDO;
}

/////////////////////////////////////////////////
////// MAIN
/////////////////////////////////////////////////


int main(){
    BANCODENOTAS* banco = new BANCODENOTAS;
    BEEP* beep = new BEEP(banco);
    BIBLIOTECA* bib = new BIBLIOTECA(banco, beep);
    MUSICA minhaMusica(beep, "NovaMusica");
    bib->setMinhaMusica(&minhaMusica);
    int status = ENTRADA;

    while(status){
        switch(status){
            case ENTRADA: status = telaEntrada(); break;
            case COMANDO: status = telaComando(bib); break;
            case PLAYER: status = telaPlayer(bib); break;
            case PIANO: status = telaPiano(bib); break;
            case TESTE: status = telaTeste(); break;
            case SOBRE: status = telaSobre(); break;
            default: status = 0;
        }
    }

    telaSaida();

    return 0;
}
