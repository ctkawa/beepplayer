#ifndef NO2_H
#define NO2_H
#include <iostream>

template <class T>
class NO2{
	private:
		T info;
		NO2 *dir;
		NO2 *esq;

	public:
		NO2();
		NO2(T);
		NO2(const NO2&);
		T getInfo();
		void setInfo(T);
		NO2* getDir();
		void setDir(NO2*);
		NO2* getEsq();
		void setEsq(NO2*);
};

template <class T>
NO2<T>::NO2(){
    dir = NULL;
    esq = NULL;
}

template <class T>
NO2<T>::NO2(T e){
	info = e;
}

template <class T>
NO2<T>::NO2(const NO2 &original){
    info = original.info;
    dir = original.dir;
    esq = original.esq;
}

template <class T>
T NO2<T>::getInfo(){
    return info;
}

template <class T>
void NO2<T>::setInfo(T e){
	info = e;
}

template <class T>
NO2<T>* NO2<T>::getDir(){
	return dir;
}

template <class T>
void NO2<T>::setDir(NO2<T>* no){
	dir = no;
}

template <class T>
NO2<T>* NO2<T>::getEsq(){
	return esq;
}

template <class T>
void NO2<T>::setEsq(NO2<T>* no){
	esq = no;
}

#endif // NO2_H

