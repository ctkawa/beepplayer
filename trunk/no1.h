#ifndef NO1_H
#define NO1_H
#include <iostream>

template <class T>
class NO1
{
	private:
		T info;
		NO1 *next;
	public:
		NO1();
		NO1(T);
		T getInfo();
		void setInfo(T);
		NO1* getNext();
		void setNext(NO1 *);
};

template <class T>
NO1<T>::NO1(){
    next = NULL;
}

template <class T>
NO1<T>::NO1(T e){
    info = e;
    next = NULL;
}

template <class T>
T NO1<T>::getInfo(){
	return info;
}

template <class T>
void NO1<T>::setInfo(T e){
	info = e;
}

template <class T>
NO1<T>* NO1<T>::getNext(){
	return next;
}

template <class T>
void NO1<T>::setNext(NO1<T>* no){
	next = no;
}

#endif // NO1_H
