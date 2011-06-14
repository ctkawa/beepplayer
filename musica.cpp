#include "musica.h"

MUSICA::MUSICA(BEEP* b) :
    LISTA<NOTA*>(){
    beep = b;
    nome = "Sem nome";
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
    nome = s;
}

void MUSICA::tocar(){
    NO2<NOTA*>* ptr;
    ptr = getPtrHeader()->getDir();

    while(ptr != getPtrHeader()){
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
};
