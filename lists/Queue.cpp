#include <lists/node.h>

template <typename Data>
struct Queue{
	Node<Data> * tail;
	
	int length;
	
	// Constructores
	Queue(){
		tail = NULL;
		length = 0;
	}
	
	Queue(Data data){
		tail = new Node<Data>(data);
		length = 1;
	}
	
	// Funciones
	
	// Retorna true si la lista esta vacia
	bool isEmpty(){
		return length == 0;
	}
	
	// Encola un elemento
	void enqueue(Data data){
		Node<Data> * temp = new Node<Data>(data);
		
		if (!isEmpty()){
			temp->next = tail;
		
		}
		
		tail = temp;
		length++;
	}
	
	// Desencola un elemento
	Data dequeue(){
		if (isEmpty()) return NULL;
		
		if (length == 1){
			Data data = tail->data;
			tail = NULL;
			
			length--;
			
			return data;
		
		} else {
			Node<Data> * temp = tail;
			
			for (int i = 0; i < length - 2; i++){
				temp = temp->next;
			}
			
			Data data = temp->next->data;
			temp->next = NULL;
			
			length--;
			return data;
		}
		
	}
	
	// Retorna el primer elemento de la cola sin borrarlo
	Data peek(){
		if (isEmpty()) return NULL;
		
		Node<Data> * temp = tail;
		
		for (int i = 0; i < length - 1; i++){
			temp = temp->next;
		}
		
		return temp->data;
	}
	
	// Imprime la cola
	void print(){
		cout << "[ ";
		
		Node<Data> * temp = tail;
		
		for (int i = 0; i < length; i++){
			temp->print();
			temp = temp->next;
		}
		
		cout << " ]" << endl;
	}
};
