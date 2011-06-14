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
void tocar(BIBLIOTECA*);
void salvar(string, MUSICA &);
void salvar(BIBLIOTECA*);
void nova(MUSICA &mus, bool &ok);
void abrir(BIBLIOTECA*);
void gravar(BIBLIOTECA*);
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
    cout << "\n\n\n\n\n";
    cout << "\t\tBeep Player" << endl;
    cout << "\n\n\n\n\n";
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
    bool sair = false;
    string cmd = "";
    int escolha = 0;
    int escolhaMin = 0;
    int escolhaMax = 9;
    char c;

    do{
        system("CLS");
        if(bib->getMinhaMusica() != NULL)
            cout << "Musica atual: " << bib->getMinhaMusica()->getNome() << endl;
        else
            cout << "Nenhuma musica aberta" << endl;
        cout << endl;

        if(escolha == 0) cout << ">> ";
        else cout << "   ";
        cout << "Player" << endl;

        if(escolha == 1) cout << ">> ";
        else cout << "   ";
        cout << "Piano" << endl;

        cout << endl;

        if(escolha == 2) cout << ">> ";
        else cout << "   ";
        cout << "Tocar musica atual" << endl;

        if(escolha == 3) cout << ">> ";
        else cout << "   ";
        cout << "Nova musica vazia" << endl;

        if(escolha == 4) cout << ">> ";
        else cout << "   ";
        cout << "Abrir arquivo de musica" << endl;

        if(escolha == 5) cout << ">> ";
        else cout << "   ";
        cout << "Salvar musica atual" << endl;

        if(escolha == 6) cout << ">> ";
        else cout << "   ";
        cout << "Gravar musica" << endl;

        cout << endl;

        if(escolha == 7) cout << ">> ";
        else cout << "   ";
        cout << "Teste" << endl;

        if(escolha == 8) cout << ">> ";
        else cout << "   ";
        cout << "Sobre" << endl;

        if(escolha == 9) cout << ">> ";
        else cout << "   ";
        cout << "Sair" << endl;

        cout << "\n\n\n";

        switch(c = getch()){
            case 'P':
                escolha++;
                if(escolha>escolhaMax) escolha = escolhaMin;
                break;
            case 'H':
                escolha--;
                if(escolha<escolhaMin) escolha = escolhaMax;
                break;
            case 27:
                return SAIDA;
                break;
            case 13:
                switch(escolha){
                    case 0: return PLAYER;
                    case 1: return PIANO;
                    case 2: tocar(bib); break;
                    case 3: bib->novaMusica(); break;
                    case 4: abrir(bib); break;
                    case 5: salvar(bib); break;
                    case 6: gravar(bib); break;
                    case 7: return TESTE;
                    case 8: return SOBRE;
                    case 9: return SAIDA;
                }
        }
    } while(!sair);

    return COMANDO;

}

void tocar(BIBLIOTECA* bib){
    system("CLS");
    MUSICA* minhaMusica = bib->getMinhaMusica();
    if(minhaMusica == NULL)
        cout << "Nao ha uma musica atual. ";
    else{
        cout << "Musica atual : " << minhaMusica->getNome() << endl;
        cout << "Tamanho      : " << minhaMusica->getTamanhoAtual() << " notas" << endl;
        minhaMusica->tocar(true);
        cout << endl << "Fim da musica. ";
    }

    cout << "Aperte alguma tecla pra continuar... ";
    getche();

}

void salvar(BIBLIOTECA* bib){
    if(bib->getMinhaMusica()->getTamanhoAtual()==0){
        cout << "Musica sem nota" << endl;
        getch();
        return;
    }
    string novoNome;
    cout << "Digite nome para a musica: ";
    cin >> novoNome;
    bib->normalizaNome(novoNome);
    bib->getMinhaMusica()->setNome(novoNome);
    bib->salvar();
}

void abrir(BIBLIOTECA* bib){
    string nomeP;
    MUSICA* minhaMusica = bib->getMinhaMusica();

    bool b = bib->desejaSalvar();
    if(b==false){
        cout << "Cancelado pelo usuario " << b << endl;
        return;
    }

    minhaMusica = new MUSICA(bib->getBeep(), "Sem nome");
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

void gravar(BIBLIOTECA* bib){
    BANCODENOTAS* banco = bib->getBanco();
    MUSICA* minhaMusica = bib->getMinhaMusica();

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

}


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
    bib->getMusicas(musicas);   // obtem lista de musicas da biblioteca


    char c;
    if(!musicas->vazia()){
        ptrTocar = musicas->getPtrHeader()->getDir();
    }

    do{
        system("CLS");
        cout << "BEEP PLAYER" << "\t [q] para sair." << endl;
        if(musicas->vazia()){
            cout << "A biblioteca esta vazia." << endl;
            getch();
            return COMANDO;
        } else {
            cout << "\n\n\n";
            ptrMus = musicas->getPtrHeader()->getDir();
            while(ptrMus != musicas->getPtrHeader()){
                if(ptrMus == ptrTocar) cout << "\t((( ";
                else cout << "\t    ";

                cout << ptrMus->getInfo();

                if(ptrMus == ptrTocar) cout << " )))";
                cout << endl;
                ptrMus = ptrMus->getDir();
            }
        }

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
                    cout << endl << endl << "\tMusica atual : " << bib->getMusica(ptrTocar->getInfo(), ok)->getNome() << endl;
                    if(ok){
                        cout << "\tTamanho     : " << bib->getMusica(ptrTocar->getInfo(), ok)->getTamanhoAtual() << endl << endl;
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
    cout << "PIANO" << endl << "[Esc] para sair, [bksp] para voltar,"<<endl<<"SHIFT+L para limpar a tela, SHIFT+N para ver notas da musica" << endl << endl;

    char key = ' ';
    int i;
    bool okn, okt;
    NOTA minhaNota(banco);
    NO2<NOTA*> *ptrN2;
    do{
        okn =false;
        okt =false;
        if (kbhit()){
            key = getch();
            i =key;

            switch(key){
                case(78):   //N shift+N
                    cout << " - - - - - - - - - - - - -" << endl;
                    ptrN2 = bib->getMinhaMusica()->getPtrHeader()->getDir();
                    while(ptrN2 != bib->getMinhaMusica()->getPtrHeader()){
                        for(int i=0; i<banco->getPosicaoNota(*ptrN2->getInfo()); i++) cout << "   ";
                        cout << ptrN2->getInfo()->getNome() << endl;
                        for(int i=0; i<banco->getPosicaoNota(*ptrN2->getInfo()); i++) cout << "   ";
                        cout << ptrN2->getInfo()->getTempo()<< endl;
                        ptrN2 = ptrN2->getDir();
                    }
                    cout << " - - - - - - - - - - - - -" << endl;
                    okn =false;
                    break;
                case(76):   //L shift+l
                    system("CLS");
                    cout << "Piano" << endl << "[Esc] para sair, [bksp] para voltar,"<<endl<<"SHIFT+L para limpar a tela, SHIFT+N para ver notas da musica" << endl << endl;
                    okn =false;
                    okt =false;
                    break;
                case(8):    //backspace
                    if(bib->getMinhaMusica()->getPtrHeader()->getDir() == bib->getMinhaMusica()->getPtrHeader()){
                        cout << "Musica vazia!" << endl;
                        break;
                    }
                    cout << "Removendo ultima nota. (";
                    cout << bib->getMinhaMusica()->getPtrHeader()->getEsq()->getInfo()->getNome();
                    cout << "," << bib->getMinhaMusica()->getPtrHeader()->getEsq()->getInfo()->getTempo() << ")";
                    bib->getMinhaMusica()->retirar(bib->getMinhaMusica()->getPtrHeader()->getEsq(), okn);
                    if(!okn)
                        cout << "Erro ao retirar!" << endl;
                    okt = false;
                    break;
                case(32):   //espaço
                    minhaNota.setNota("pausa",0.5,okn,okt);
                    break;
                case(13):   //enter
                    okt = false;
                    okn = false;
                    cout << bib->getMinhaMusica()->getNome() << ", tamanho: " << bib->getMinhaMusica()->getTamanhoAtual();
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
                case(98):
                    minhaNota.setNota("pausa",0.25,okn,okt);
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
                case(103):
                    minhaNota.setNota("pausa",0.5,okn,okt);
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
                case(116):
                    minhaNota.setNota("pausa",1,okn,okt);
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
                case(53):
                    minhaNota.setNota("pausa",2,okn,okt);
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
                int i;
                for(i=0; i<banco->getPosicaoNota(minhaNota); i++) cout << "   ";
                cout << minhaNota.getNome() << endl;
                for(i=0; i<banco->getPosicaoNota(minhaNota); i++) cout << "   ";
                cout << minhaNota.getTempo()<< endl;
            } else if(key!=13&&key!=27&&key!=8&&key!=76&&key!=78)
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
    cout << "FIM DO TESTE"<<endl;
    getch();
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

    delete banco;
    Sleep(1000);
    return;
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
