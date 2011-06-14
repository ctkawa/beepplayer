#ifndef MUSICA_H
#define MUSICA_H

#include "nota.h"
#include "lista.h"
#include "beep.h"
#include "no2.h"

/**
    MUSICA é LISTA de NO de NOTA
**/

//class MUSICA : public LISTA<NO1<NOTA> >{  //  MUSICA eh lista de NO com info NOTA

class MUSICA : public LISTA<NOTA*>{      // MUSICA eh lista de notas
private:
    string nome;
    BEEP * beep;
public:
    MUSICA(BEEP*);
    MUSICA(BEEP*, string);
    string getNome();
    void setNome(string);

    void tocar();

    bool operator==(MUSICA const &dir);
//    bool operator<(MUSICA const &dir);
//    bool operator>(MUSICA const &dir);
};

#endif
