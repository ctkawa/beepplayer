#ifndef BEEP_H
#define BEEP_H

#include <windows.h>
#include <iostream>

#include "bancodenotas.h"
#include "nota.h"

using namespace std;

class BEEP {
private:
    BANCODENOTAS* banco;
    NOTA* nota;
    void som();             //interpreta e toca
public:
    BEEP(BANCODENOTAS*);
    void tocar();
    void tocar(NOTA*, bool print);
    void tocar(NOTA*);
};

#endif
