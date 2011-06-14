#include "musica.h"

MUSICA::MUSICA(BEEP* b) :
    LISTA<NOTA*>(){
    beep = b;
    nome = "Nome padrao";
}

MUSICA::MUSICA(BEEP* b, string s) :
    LISTA<NOTA*>(){
    beep = b;
    nome = s;
}

string MUSICA::getNome(){
    return nome;
}

void MUSICA::setNome(string s){
    //cout<< "F";
    nome = "";
    //cout<< "L";
    nome = s;
    //cout<< "A";
}

void MUSICA::tocar(){
    NO2<NOTA*>* ptr;
    //NOTA* n;
    ptr = getPtrHeader()->getDir();
    //cout << getPtrHeader() << " <-HEADER" << endl;
    while(ptr != getPtrHeader()){
        //n = ptr->getInfo();
        //      cout << n->getNome() << " " << n->getTempo() << "<- NOTA* DA MUSICA" << endl;
        //      cout << ptr->getDir() << " " << "<- Proxima nota" << endl;
        beep->tocar(ptr->getInfo());
        ptr = ptr->getDir();
    }
}

void MUSICA::tocar(bool print){
    NO2<NOTA*>* ptr;
    ptr = getPtrHeader()->getDir();
    while(ptr != getPtrHeader()){
        beep->tocar(ptr->getInfo(), print);
        ptr = ptr->getDir();
    }
}

bool MUSICA::operator==(MUSICA const &dir){
    return (nome==dir.nome);
};/*
bool MUSICA::operator<(MUSICA const &dir){
    cout << nome << "<" << dir.nome << endl;
    return (nome<dir.nome);
};
bool MUSICA::operator>(MUSICA const &dir){
    cout << nome << ">" << dir.nome << endl;
    return (nome>dir.nome);
};*/
