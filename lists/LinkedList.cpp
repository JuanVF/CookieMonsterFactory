#include <lists/node.h>

template <typename Data>
struct LinkedList{
	Node<Data> * firstNode;
	Node<Data> * lastNode;
	
	int length;
	
	// Constructores
	LinkedList(){
		firstNode = NULL;
		lastNode = NULL;
		length = 0;
	}
	
	LinkedList(Data data){
		firstNode = lastNode = new Node<Data>(data);
		
		length = 1;
	}
	
	// Funciones
	
	// Returna true si la lista esta vacia
	bool isEmpty(){
		return length == 0;
	}
	
	// Inserta en la ultima posicion
	void add(Data data){
		Node<Data> * temp = new Node<Data>(data);
		
		temp->prev = lastNode;
		
		if (!isEmpty()){
			lastNode->next = temp;
			lastNode = temp;
		
		}else{
			firstNode = lastNode = temp;
		}
		
		length++;
	}
	
	// Inserta en la primera posicion
	void addFirst(Data data){
		Node<Data> * temp = new Node<Data>(data);
		
		if (!isEmpty()){
			temp->next = firstNode;
			firstNode->prev = temp;
		
		} else {
			lastNode = temp;
		}
		
		firstNode = temp;
		
		length++;
	}
	
	// Inserta en la posicion n
	void add(Data data, int n){
		if (n >= length || isEmpty()){
			add(data);
			
		} else if (n <= 0){
			addFirst(data);
		
		} else {
			
			Node<Data> * newNode = new Node<Data>(data);
			Node<Data> * temp = firstNode;
			
			for (int i = 0; i < (n-1); i++){
				temp = temp->next;
			}
			
			newNode->next = temp->next;
			newNode->prev = temp;
			
			temp->next->prev = newNode;
			temp->next = newNode;
			
			length++;	
		}
	}
	
	// Cambia el valor del nodo n
	void set(Data data, int n){
		// Restricciones para tener todo en la misma funcion
		if (n < 0) n = 0;
		if (n >= length) n = length - 1;
		
		if (isEmpty()) return;
		
		Node<Data> * temp = firstNode;
		
		for (int i = 0; i < n; i++){
			temp = temp->next;
		}
		
		temp->data = data;
	}
	
	// Remueve el de la ultima posicion y retorna su valor
	Data remove(){
		if (isEmpty()) return NULL;
		
		Node<Data> * removed = lastNode;
		
		lastNode = removed->prev;
		
		if (length != 1){
			lastNode->next = NULL;
			removed->prev = NULL;
		}
		
		length--;
		
		return removed->data;
	}
	
	// Remueve el primero de la lista
	Data removeFirst(){
		if (isEmpty()) return NULL;
		
		Node<Data> * removed = firstNode;
		
		firstNode = removed->next;
		
		if (length != 1){
			firstNode->prev = NULL;
			removed->next = NULL;
		}
		
		length--;
		
		return removed->data;
	}
	
	// Remueve el nodo de una posicion n
	Data remove(int n){
		if (n <= 0){
			return removeFirst();
		
		} else if (n >= (length-1)){
			return remove();
		
		}
		
		Node<Data> * removed = firstNode;
			
		for (int i = 0; i < n; i++){
			removed = removed->next;
		}
		
		removed->prev->next = removed->next;
		removed->next->prev = removed->prev;
		
		removed->next = NULL;
		removed->prev = NULL;
		
		length--;
		
		return removed->data;
	}
	
	// Retorna el ultimo de la lista
	Data get(){
		if (isEmpty()) return NULL;
		
		return lastNode->data;
	}
	
	// Retorna el primero de la lista
	Data getFirst(){
		if (isEmpty()) return NULL;
		
		return firstNode->data;
	}
	
	// Retorna el de una posicion n
	Data get(int n){
		if (n <= 0) return getFirst();
		
		if (n >= length - 1) return get();
		
		Node<Data> * temp = firstNode;
		
		for (int i = 0; i < n; i++){
			temp = temp->next;
		}
		
		return temp->data;
	}
	
	// Retorna la lista al reves
	LinkedList<Data> * reverse(){
		LinkedList<Data> * rev = new LinkedList<Data>();
		Node<Data> * temp = lastNode;
		
		for (int i = 0; i < length; i++){
			rev->add(temp->data);
			temp = temp->prev;
		}
		
		return rev;
	}
	
	// Imprime la lista
	void print(){
		Node <Data> * temp = firstNode;
		
		cout << "[ ";
		
		for (int i = 0; i < length; i++){
			temp->print();
			temp = temp->next;
		}	
		
		cout << "]" << endl;
	}
};
