#ifndef ARVORE_H
#define ARVORE_H

#include <iostream>
#include "no2.h"

using namespace std;

template<class T>
class ARVORE{
protected:
    T elemento;

    NO2<T> *raiz;
private:
    void copiaR(NO2<T> * const &arv);
    bool estaNaArvoreR(T, NO2<T>*);
    bool insereR(T &, NO2<T> *&);
    T removerR(NO2<T> *, NO2<T> *, bool &);
    void imprimeAllR(NO2<T>*);
    NO2<T>* maior(NO2<T> *);
protected:
    void destruir(NO2<T>*);
public:
    ARVORE();
    ARVORE(ARVORE &);
    ~ARVORE();
    T* getElemento();
    void setElemento(T);

    NO2<T> *getRaiz(){return raiz;};
    bool vazia();
    bool estaNaArvore(T);
    bool insere(T &);
    T remover(NO2<T> *, bool &);
    void imprimeAll();

    int altura(NO2<T> *);

};


template<class T>
ARVORE<T>::ARVORE(){
    raiz = NULL;
}

template<class T>
ARVORE<T>::ARVORE(ARVORE &arv){
    raiz = NULL;
    copiaR(arv.raiz);
}
template<class T>
void ARVORE<T>::copiaR(NO2<T> * const &arv){
    if(arv != NULL){
        T ele;
        ele = arv->getInfo();
        insere(ele);
        copiaR(arv->getDir());
        copiaR(arv->getEsq());
    }
}

template<class T>
ARVORE<T>::~ARVORE(){
    destruir(raiz);
}


template<class T>
void ARVORE<T>::destruir(NO2<T>* no){
    if(no == NULL)
        return;
    else {
        destruir(no->getEsq());
        destruir(no->getDir());
        delete no;
    }
}


template<class T>
T* ARVORE<T>::getElemento(){
    return elemento;
}

template<class T>
void ARVORE<T>::setElemento(T ele){
    elemento = ele;
}


template<class T>
bool ARVORE<T>::vazia(){
    if(raiz==NULL)
        return true;
    return false;
}

template<class T>
bool ARVORE<T>::estaNaArvore(T noInfo){
    return (estaNaArvoreR(noInfo,raiz));
}

template<class T>
bool ARVORE<T>::estaNaArvoreR(T e, NO2<T> *no){
    if(no==NULL){
        return false;
    } else if(*no->getInfo() == *e){
        return true;
    } else                                                              //if(no->getInfo() > e)......
        return (estaNaArvoreR(e,no->getDir()) || estaNaArvoreR(e,no->getEsq()));
}




template<class T>
bool ARVORE<T>::insere(T &e){
    if(estaNaArvore(e))
        return false;
    else
        return insereR(e, raiz);
}

template<class T>
bool ARVORE<T>::insereR(T &e, NO2<T> *&no){  //referencia de ponteiro
    if(no == NULL){
        no = new NO2<T>;
        no->setInfo(e);
        return true;
    } else if(no->getInfo() > e){   //insere a Esq se elemento < este no
        NO2<T> *temp;
        temp = no->getEsq();
        bool result = insereR(e, temp);
        if(result)
            no->setEsq(temp);
        if(altura(no->getDir()) - altura(no->getEsq()) < -1 ){   //detectar desbalanceamento
            if(altura(no->getEsq()->getDir()) - altura(no->getEsq()->getEsq()) > 0 ){
                //ED
                temp = no;
                no = no->getEsq()->getDir();
                temp->getEsq()->setDir(no->getEsq());
                no->setEsq(temp->getEsq());
                temp->setEsq(no->getDir());
                no->setDir(temp);
            } else{    //EE
                temp = no;
                no = no->getEsq();
                temp->setEsq(no->getDir());
                no->setDir(temp);
            }
        }
        return result;
    }else{                          //insere a Dir
        NO2<T> *temp;
        temp = no->getDir();
        bool result = insereR(e, temp);
        if(result)
            no->setDir(temp);
        if(altura(no->getDir()) - altura(no->getEsq()) > 1 ){   //detectar desbalanceamento
            if(altura(no->getDir()->getDir()) - altura(no->getDir()->getEsq()) > 0 ){
                //DD
                temp = no;
                no = no->getDir();
                temp->setDir(no->getEsq());
                no->setEsq(temp);
            } else{    //DE
                temp = no;
                no = no->getDir()->getEsq();
                temp->getDir()->setEsq(no->getDir());
                no->setDir(temp->getDir());
                temp->setDir(no->getEsq());
                no->setEsq(temp);
            }
        }
        return result;
    }
    return false;
}

template<class T>
T ARVORE<T>::remover(NO2<T> *no, bool &ok){
    return removerR(raiz, no, ok);
}
template<class T>
T ARVORE<T>::removerR(NO2<T> *arvore, NO2<T> *no, bool &ok){
    cout << "ops" << endl;

	T ele = NULL;
    if(arvore==NULL){
        ok = false;
    } else {
        if(arvore == no){
            if(arvore->getDir()==NULL && arvore->getEsq() == NULL){ //no sem descendente
                ele = arvore->getInfo();
                delete arvore;
                arvore = NULL;
                ok = true;
            } else if(arvore->getDir()!=NULL && arvore->getEsq() != NULL){ // no com 2 descendentes
                ele = arvore->getInfo();
                maior(arvore->getEsq())->setDir(arvore->getDir());
                arvore->setDir(NULL);
                NO2<T> *temp = arvore;
                arvore = arvore->getEsq();
                delete temp;
                ok = true;
            } else { // no com um descendente
                NO2<T> *temp;
                temp = arvore;
                if(arvore->getDir()!=NULL){
                    arvore = arvore->getDir();
                } else{
                    arvore = arvore->getEsq();
                }
                ele = arvore->getInfo();
                delete temp;
                ok = true;
            }
        } else {
            NO2<T> *temp;
            if(arvore->getInfo() > no->getInfo()){
                removerR(arvore->getEsq(),no,ok);
                //monitorar
                if(altura(arvore->getDir()) - altura(arvore->getEsq()) > 1 ){
                    if(altura(arvore->getEsq()->getDir()) - altura(arvore->getEsq()->getEsq()) < 0 ){
                        //EE
                        temp = arvore;
                        arvore = arvore->getEsq();
                        temp->setEsq(arvore->getDir());
                        arvore->setDir(temp);
                    } else {
                        //ED
                        temp = arvore;
                        arvore = arvore->getEsq()->getDir();
                        temp->getEsq()->setDir(arvore->getEsq());
                        arvore->setEsq(temp->getEsq());
                        temp->setEsq(arvore->getDir());
                        arvore->setDir(temp);
                    }
                }
            } else {
                removerR(arvore->getDir(),no,ok);
                //monitorar
                if(altura(arvore->getDir()) - altura(arvore->getEsq()) < -1 ){
                    if(altura(arvore->getDir()->getDir()) - altura(arvore->getDir()->getEsq()) > 0 ){
                        //DD
                        temp = arvore;
                        arvore = arvore->getDir();
                        temp->setDir(arvore->getEsq());
                        arvore->setEsq(temp);
                    } else {
                        //DE
                        temp =arvore;
                        arvore = arvore->getDir()->getEsq();
                        temp->getDir()->setEsq(arvore->getDir());
                        arvore->setDir(temp->getDir());
                        temp->setDir(arvore->getEsq());
                        arvore->setEsq(temp);
                    }
                }
            }

        }
    }

    return ele;
}

template<class T>
NO2<T>* ARVORE<T>::maior(NO2<T> *raiz){
    if(raiz==NULL)
        return NULL;
    else if(raiz->getDir()==NULL)
        return raiz;
    else
        return maior(raiz->getDir());
}

template<class T>
void ARVORE<T>::imprimeAll(){
    cout << "Imprimindo tudo, raiz = "<<raiz<<endl;
    imprimeAllR(raiz);
}
template<class T>
void ARVORE<T>::imprimeAllR(NO2<T> *no){
    if(no!=NULL){
        imprimeAllR(no->getEsq());
        cout << no << " possui " << no->getInfo() << ", Dir=" << no->getDir() << ", Esq=" << no->getEsq() << endl;
        imprimeAllR(no->getDir());
    } else
        return;
}

template<class T>
int ARVORE<T>::altura(NO2<T> *no){
    if(no==NULL)
        return 0;
    int d = altura(no->getDir());
    int e = altura(no->getEsq());
    return d>e ? d+1 : e+1;
}

#endif
