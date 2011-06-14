#include "beep.h"

BEEP::BEEP(BANCODENOTAS* b){
    banco = b;
    nota = banco->getNotaPadrao();
}

void BEEP::som(){   // interpreta e toca

    int freq = banco->getFrequencia(nota);
    int tempo = banco->getTempo(nota);
    Beep(freq,tempo);    // toca efetivamente, funcao do sistema
}

void BEEP::tocar(){
    som();
}

void BEEP::tocar(NOTA* n, bool print){
    nota = n;
    if (print) cout << nota->getNome() << " " << nota->getTempo() << endl;
    som();
}

void BEEP::tocar(NOTA* n){
    nota = n;
    som();

}
