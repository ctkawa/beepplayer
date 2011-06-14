#include "beep.h"

BEEP::BEEP(BANCODENOTAS* b){
    banco = b;
    nota = banco->getNotaPadrao();
}

void BEEP::som(){   // interpreta e toca

    int freq = banco->getFrequencia(nota);
    int tempo = banco->getTempo(nota);

    //cout << "\t" << nota->getNome() << " " << nota->getTempo() << endl;
    Beep(freq,tempo);                   // toca efetivamente, funcao do sistema
}

void BEEP::tocar(){
    som();
}

void BEEP::tocar(NOTA* n, bool print){
    nota = n;
    cout << nota->getNome() << " " << nota->getTempo() << endl;
    som();
}

void BEEP::tocar(NOTA* n){
    nota = n;
    som();

}

//void BEEP::tocar2(NOTA n){
//    int freq = 0;
//    int tempo = 0;
//    if(n.getNome() == "0do") freq = 440;
//    else if(n.getNome() == "0re") freq = 494;
//    else if(n.getNome() == "0mi") freq = 554;
//    else if(n.getNome() == "0fa") freq = 587;
//    else if(n.getNome() == "0sol") freq = 659;
//    else if(n.getNome() == "0la") freq = 740;
//    else if(n.getNome() == "0si") freq = 830;
//    else if(n.getNome() == "1do") freq = 880;
//    else if(n.getNome() == "pausa") freq = 0;
//    else freq = 440;
//    if(n.getTempo() == 1) tempo = 400;
//    else if(n.getTempo() == 2) tempo = 800;
//    else if(n.getTempo() == 0.5) tempo = 200;
//    else if(n.getTempo() == 0.25) tempo = 100;
//    else if(n.getTempo() == 0.75) tempo = 300;
//    else if(n.getTempo() == 3) tempo = 1200;
//    else if(n.getTempo() == 4) tempo = 1600;
//    else tempo = 400;
//    Beep(freq,tempo);                   // toca efetivamente, funcao do sistema
//}
