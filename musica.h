#ifndef MUSICA_H
#define MUSICA_H

#include "nota.h"
#include "lista.h"
#include "beep.h"
#include "no2.h"

/**
    MUSICA é LISTA de NO de NOTA
**/

class MUSICA : public LISTA<NOTA*>{      // MUSICA eh lista de NOTA
private:
    string nome;
    BEEP * beep;
public:
    MUSICA(BEEP*);
    MUSICA(BEEP*, string);
    string getNome();
    void setNome(string);

    void tocar();
    void tocar(bool print); //imprimir notas tocadas

    bool operator==(MUSICA const &dir);
};

#endif
