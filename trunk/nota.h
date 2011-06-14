#ifndef NOTA_H
#define NOTA_H

#include <iostream>
#include "bancodenotas.h"
class BANCODENOTAS; // solução para include recursivo

using namespace std;

/*
    Nota guarda uma nota= frequencia/tempo em formato "musical"
*/
class NOTA{
private:
    BANCODENOTAS* banco;
    string nome;        // =>frequencia
    float tempo;
    void criaNomes();
public:
    // para compatibilidade
    //NOTA();
    //void setBancoDeNotas(BANCODENOTAS*);

    NOTA(BANCODENOTAS*);
    NOTA(BANCODENOTAS*, string);
    NOTA(BANCODENOTAS*, float);
    NOTA(BANCODENOTAS*, string, float);
    NOTA(BANCODENOTAS*, NOTA&);
    string getNome();
    void setNome(string, bool&);        // receive & set tinbre, com validacao
    float getTempo();
    void setTempo(float, bool&);        // receive & set Time
    void setNota(string, float, bool&, bool&);
    void setNota(string, bool&);
    void setNota(float, bool&);
    NOTA operator=(NOTA);
    bool operator==(NOTA);
    bool operator>(NOTA);
};

#endif
