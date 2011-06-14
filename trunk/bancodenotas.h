#ifndef BANCODENOTAS_H
#define BANCODENOTAS_H

#include <math.h>

#include "arvore.h"

#include "nota.h"
class NOTA; // solução para include recursivo

typedef struct {
    string nome;    //Nome da frequencia ex: do re mi...
    int valor;      //Valor real da frequencia
} tipoFREQUENCIA;

typedef struct{
    float tempo;    //Tempo usado na nota
    int valor;      //Valor real do tempo ... ms
} tipoTEMPO;

class BANCODENOTAS : public ARVORE<NOTA*>{
private:
    tipoFREQUENCIA* nomes;
    int qtdFreq;
    tipoTEMPO* tempos;
    int qtdTemp;
    NOTA* notaPadrao;
    void criaNomes();
    void criaTempos();
    void criaNotaPadrao();
    void buscaNota(NO2<NOTA*>*, NOTA*, NOTA&, bool&);
public:
    BANCODENOTAS();
    ~BANCODENOTAS();
    string getNomePadrao();
    string certificaNome(string);
    float getTempoPadrao();
    float certificaTempo(float);
    NOTA* getNotaPadrao();
    NOTA* getNota(NOTA);
    int getFrequencia(NOTA*);
    int getTempo(NOTA*);
    bool maiorQue(NOTA*, NOTA*);
};

#endif
