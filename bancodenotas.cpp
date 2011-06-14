#include "bancodenotas.h"

BANCODENOTAS::BANCODENOTAS(){
    criaNomes();
    criaTempos();
    criaNotaPadrao();
}

BANCODENOTAS::~BANCODENOTAS(){
    delete [] nomes;
    delete [] tempos;
}

void BANCODENOTAS::criaNomes(){
    qtdFreq = 9;
    nomes = new tipoFREQUENCIA[qtdFreq];
    nomes[0] = {"0do", 440};
    nomes[1] = {"0re", 494};
    nomes[2] = {"0mi", 554};
    nomes[3] = {"0fa", 587};
    nomes[4] = {"0sol", 659};
    nomes[5] = {"0la", 740};
    nomes[6] = {"0si", 830};
    nomes[7] = {"1do", 880};
    nomes[8] = {"pausa", 0};
}

string BANCODENOTAS::getNomePadrao(){
    return nomes[0].nome;
}

string BANCODENOTAS::certificaNome(string n){
    string resultado = getNomePadrao();

    int i=0;
    bool encontrado = false;

    while(i < qtdFreq && !encontrado){
        if(nomes[i].nome == n){
            resultado = nomes[i].nome;
            encontrado = true;
        } else {
            i++;
        }
    }

    return resultado;
}

void BANCODENOTAS::criaTempos(){
    qtdTemp = 10;
    tempos = new tipoTEMPO[qtdTemp];
    int unidade = 400;

    tempos[0] = {0.25, floor(0.25*unidade)};
    tempos[1] = {0.5, floor(0.5*unidade)};
    tempos[2] = {0.75, floor(0.75*unidade)};
    tempos[3] = {1, floor(1*unidade)};
    tempos[4] = {1.25, floor(1.25*unidade)};
    tempos[5] = {1.5, floor(1.5*unidade)};
    tempos[6] = {1.75, floor(1.75*unidade)};
    tempos[7] = {2, floor(2*unidade)};
    tempos[8] = {3, floor(3*unidade)};
    tempos[9] = {4, floor(4*unidade)};
}

float BANCODENOTAS::getTempoPadrao(){
    return tempos[3].tempo;
}

float BANCODENOTAS::certificaTempo(float t){
    float resultado = getTempoPadrao();

    int i=0;
    bool encontrado = false;

    while(i < qtdTemp && !encontrado){
        if(tempos[i].tempo == t){
            resultado = tempos[i].tempo;
            encontrado = true;
        } else {
            i++;
        }
    }

    return resultado;
}

void BANCODENOTAS::criaNotaPadrao(){
    string nome = getNomePadrao();

    float tempo = getTempoPadrao();
    NOTA* n = new NOTA(this, nome,tempo);
    notaPadrao = n;
    insere(n);
}

NOTA* BANCODENOTAS::getNotaPadrao(){
    return notaPadrao;
}

NOTA* BANCODENOTAS::getNota(NOTA n){
    bool ok = false;
    NOTA* resultado = NULL;
    buscaNota(raiz, resultado, n, ok);

    if(resultado == NULL){
        NOTA* tmp = new NOTA(this, n);
        insere(tmp);
        resultado = tmp;
    }

    return resultado;
}

void BANCODENOTAS::buscaNota(NO2<NOTA*>* no, NOTA* resultado, NOTA& n, bool& ok){
    if( no == NULL){
        ok = false;
        resultado = NULL;
    } else {
        if(*(no->getInfo()) == n){
            ok = true;
            resultado = no->getInfo();
        } else if( *(no->getInfo()) > n ) {
            buscaNota(no->getEsq(), resultado, n, ok);
        } else {
            buscaNota(no->getDir(), resultado, n, ok);
        }
    }
}

bool BANCODENOTAS::maiorQue(NOTA* n1, NOTA* n2){
    int i=0;
    int indice1=0;
    bool encontrado1 = false;
    int indice2=0;
    bool encontrado2 = false;

    while( i < qtdFreq && (!encontrado1 || !encontrado2) ){
        if(n1->getNome() == nomes[i].nome){
            encontrado1 = true;
            indice1 = i;
        }

        if(n2->getNome() == nomes[i].nome){
            encontrado2 = true;
            indice2 = i;
        }

        i++;
    }

    if(indice1>indice2)
        return true;

    if(indice1==indice2)
        return n1->getTempo() > n2->getTempo();

    return false;
}

int BANCODENOTAS::getFrequencia(NOTA* n){
    int resultado = 0;
    int i=0;
    bool encontrado = false;

    while(i<qtdFreq && !encontrado){
        if(nomes[i].nome == n->getNome()){
            resultado = nomes[i].valor;
            encontrado = true;
        } else {
            i++;
        }
    }

    return resultado;
}

int BANCODENOTAS::getTempo(NOTA* n){
    int resultado = 0;
    int i=0;
    bool encontrado = false;

    while(i < qtdTemp && !encontrado){
        if(tempos[i].tempo == n->getTempo()){
            resultado = tempos[i].valor;
            encontrado = true;
        } else {
            i++;
        }
    }

    return resultado;
}
