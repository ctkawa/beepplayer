#ifndef LISTA_H
#define LISTA_H

#include <iostream>

#include "no2.h"

using namespace std;

template<class T>
class LISTA{
protected:
    T* elemento;
    int tamanhoAtual;
    NO2<T> header;
public:
    LISTA();
    ~LISTA();
    T* getElemento();
    void setElemento(T*);

    int getTamanhoAtual(){return tamanhoAtual;}
    bool vazia();
    void esvaziar();
    void adicionar(T, bool&);
    bool estaNaLista(const T&);
    void retirar(T&, bool&);
    void retirar(NO2<T> *, bool &);
    bool insereADireita(T, NO2<T>&);
    bool insereAEsquerda(T, NO2<T>&);
    NO2<T> *getPtrHeader(){return &header;}
    bool estaNaLista(const NO2<T>*);
    void printAll();

//    elemento info(no2&, bool&);   // A final, o que era isso?

};

template<class T>
LISTA<T>::LISTA(){
    elemento = NULL;

    header.setDir(&header);
    header.setEsq(&header);
    tamanhoAtual = 0;
}
template<class T>
LISTA<T>::~LISTA(){
    //retirar e liberar todo elemento
    bool ok;
    while (header.getDir() != &header){
        retirar(header.getDir(),ok);
        if (!ok)
            cout << "TEVE PROBLEMAS NO DESTRUTOR LISTA AVANCADA" << endl;
    }
}

template<class T>
T* LISTA<T>::getElemento(){
    return elemento;
}

template<class T>
void LISTA<T>::setElemento(T* ele){
    elemento = ele;
}

template<class T>
bool LISTA<T>::vazia(){
    return tamanhoAtual==0 ? true : false;
}

template<class T>
void LISTA<T>::esvaziar(){
    bool ok;
    while(!vazia())
        retirar(header.getDir(), ok);
}

template<class T>
void LISTA<T>::adicionar(T ele, bool& ok){
    NO2<T> *ptrNovo;
    ptrNovo = new NO2<T>();
    ptrNovo->setInfo(ele);
    ptrNovo->setDir(header.getDir());
    ptrNovo->setEsq(&header);
    header.setDir(ptrNovo);
    ptrNovo->getDir()->setEsq(ptrNovo);
    tamanhoAtual++;
    ok = true;
}

template<class T>
bool LISTA<T>::estaNaLista(const T& ele){
    NO2<T> *ptr;
    ptr = header.getDir();
    while(ptr != &header){
        if(ptr->getInfo() == ele)
            return true;
        ptr = ptr->getDir();
    }
    return false;
}

template<class T>
void LISTA<T>::retirar(NO2<T> *noRetir, bool &ok){
    NO2<T> *ptr;
    ptr = header.getDir();
    while(ptr != &header){
        if(ptr == noRetir){
            ptr->getDir()->setEsq(ptr->getEsq());
            ptr->getEsq()->setDir(ptr->getDir());
            delete ptr;
            ok = true;
            tamanhoAtual--;
            return;
        }
        ptr = ptr->getDir();
    }
    ok = false;
    return;
}
template<class T>
void LISTA<T>::retirar(T& ele, bool& ok){
    ok = false;
    if (estaNaLista(ele)){  // talvez nao tenha sentido fazer isso, vai percorrer 2x
        NO2<T> *ptr;
        ptr = header.getDir();
        while(ptr != &header){
            if(ptr->getInfo() == ele){
                ptr->getDir()->setEsq(ptr->getEsq());
                ptr->getEsq()->setDir(ptr->getDir());
                delete ptr;
                ok = true;
                tamanhoAtual--;
                return;
            }
            ptr = ptr->getDir();
        }
        ok = false;
        return;
    }
    return;
}

template<class T>
bool LISTA<T>::insereADireita(T ele, NO2<T> &no){   // inserir no com ELEMENTO na direita do NO2 passado
    if(estaNaLista(&no)){
        NO2<T> *ptrNovo;
        ptrNovo = new NO2<T>();
        ptrNovo->setInfo(ele);
        ptrNovo->setDir(no.getDir());
        ptrNovo->setEsq(&no);
        no.setDir(ptrNovo);
        ptrNovo->getDir()->setEsq(ptrNovo);
        tamanhoAtual++;
        return true;
    }
    return false;
}
template<class T>
bool LISTA<T>::insereAEsquerda(T ele, NO2<T> &no){
    if(estaNaLista(&no)){
        NO2<T> *ptrNovo;
        ptrNovo = new NO2<T>();
        ptrNovo->setInfo(ele);
        ptrNovo->setEsq(no.getEsq());
        ptrNovo->setDir(&no);
        no.setEsq(ptrNovo);
        ptrNovo->getEsq()->setDir(ptrNovo);
        tamanhoAtual++;
        return true;
    }
    return false;
}

template<class T>
bool LISTA<T>::estaNaLista(const NO2<T> *no){ // verifica se o no apontado esta sendo encadeado na lista
    if(tamanhoAtual==0 && no!=&header)
        return false;

    NO2<T> *ptr;
    ptr = &header;
    do{
        if(ptr==no){        //poderia verificar se no.esq aponta para anterior, etc...
            return true;
        }
        ptr = ptr->getDir();
    }while(ptr != &header);
    return false;
}

template<class T>
void LISTA<T>::printAll(){
    NO2<T> *ptr;
    ptr = header.getDir();
    while(ptr!=&header){
        cout << ptr->getInfo() << ", ";
        ptr = ptr->getDir();
    }
    cout << "Fim da lista" << endl;
    return;
}

#endif
