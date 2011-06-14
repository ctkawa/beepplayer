#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <iostream>
#include <fstream>

#include "beep.h"
#include "musica.h"
#include "arvore.h"

/**
    BIBLIOTECA é ARVORE de NO com info MUSICA
**/

using namespace std;

class BIBLIOTECA : public ARVORE<MUSICA*>{
private:
    BANCODENOTAS* banco;
    BEEP* beep;
    MUSICA* minhaMusica;
    string bibdir;
    string bibfile;
    LISTA<string> bibfiles;
    void getMusicasR(NO2<MUSICA*>*, LISTA<string>*);
    bool estaNaBibliotecaR(string, NO2<MUSICA*>*);
public:
    string normalizaNome(string);
    BIBLIOTECA(BANCODENOTAS*, BEEP*);
    BANCODENOTAS* getBanco();
    BEEP* getBeep();
    MUSICA* getMinhaMusica();
    void setMinhaMusica(MUSICA*);
    void recarregar();
    void salvarBib();
    void tocar(string, bool&);
    MUSICA* getMusica(string, bool&);
    bool salvar();
    bool abrir(string);
    bool desejaSalvar();
    void moveMinhaMusicaPBib();
    void getMusicas(LISTA<string>*);
    void busca(string, NO2<MUSICA*>*, NO2<MUSICA*>* &, bool&);
    ~BIBLIOTECA();
    void imprimeAll();
    void imprimeAllR(NO2<MUSICA*> *no);
    bool estaNaBiblioteca(string);
};


#endif
