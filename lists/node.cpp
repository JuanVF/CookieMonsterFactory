#ifndef IOSSTREAM
#define IOSSTREAM
#include <iostream>
using namespace std;
#endif


template <typename Data>
struct Node{
	Data data;
	Node<Data> * next;
	Node<Data> * prev;
	
	// Constructores
	Node(Data _data){
		data = _data;
		next = NULL;
		prev = NULL;	
	}
	
	Node(Data _data, Node<Data> * _next){
		data = _data;
		next = _next;
		prev = NULL;
	}
	
	Node(Data _data, Node<Data> * _next, Node<Data> * _prev){
		data = _data;
		next = _next;
		prev = _prev;	
	}
	
	// Funciones
	
	void print(){
		cout << "[ " << data << " ] ";
	}
};
