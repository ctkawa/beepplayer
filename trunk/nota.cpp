#include "nota.h"

NOTA::NOTA(BANCODENOTAS* b){
    banco = b;

    nome = banco->getNomePadrao();
    tempo = banco->getTempoPadrao();
}

NOTA::NOTA(BANCODENOTAS* b, string s){
    banco = b;

    bool okn;

    setNome(s, okn);
    tempo = banco->getTempoPadrao();
}

NOTA::NOTA(BANCODENOTAS* b, float t){
    banco = b;

    bool okt;

    nome = banco->getNomePadrao();
    setTempo(t, okt);
}

NOTA::NOTA(BANCODENOTAS* b, string s, float t){
    banco = b;

    bool okn, okt;

    setNome(s, okn);
    setTempo(t, okt);
}

NOTA::NOTA(BANCODENOTAS* b, NOTA& n){
    banco = b;

    bool okn, okt;

    setNome(n.getNome(), okn);
    setTempo(n.getTempo(), okt);
}

string NOTA::getNome(){
    return nome;
}

void NOTA::setNome(string n, bool& okn){
    nome = banco->certificaNome(n);
    okn = (nome == n);
}

float NOTA::getTempo(){
    return tempo;
}

void NOTA::setTempo(float t, bool& okt){
    tempo = banco->certificaTempo(t);
    okt = (tempo == t);
}

void NOTA::setNota(string s, float t, bool& okn, bool& okt){
    setNome(s, okn);
    setTempo(t, okt);
}

void NOTA::setNota(string s, bool& okn){
    setNome(s, okn);
}

void NOTA::setNota(float t, bool& okt){
    setTempo(t, okt);
}

NOTA NOTA::operator=(NOTA n){
    nome = n.getNome();
    tempo = n.getTempo();
    return *this;
}

bool NOTA::operator==(NOTA n){
    bool okn, okt;
    okn = (nome == n.getNome());
    okt = (tempo == n.getTempo());
    return (okn && okt);
}

bool NOTA::operator>(NOTA n){
    return banco->maiorQue(this, &n);
}
