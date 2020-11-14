#include <lists/node.h>

template <typename Data>
struct CircularList{
	Node<Data> * firstNode;
	
	int length;
	
	// Constructores
	CircularList(){
		firstNode = NULL;
		length = 0;
	}
	
	CircularList(Data data){
		firstNode = new Node<Data>(data);
		
		firstNode->next = firstNode;
		firstNode->prev = firstNode;
		
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
		
		if (!isEmpty()){
			temp->prev = firstNode->prev;
			temp->next = firstNode;
			
			firstNode->prev->next = temp;
			firstNode->prev = temp;
		}else{
			firstNode = temp;
			
			firstNode->next = firstNode;
			firstNode->prev = firstNode;
		}
		
		length++;
	}
	
	// Inserta en la primera posicion
	void addFirst(Data data){
		Node<Data> * temp = new Node<Data>(data);
		
		if (isEmpty()){
			firstNode = temp;
			
			firstNode->next = firstNode;
			firstNode->prev = firstNode;
		
		} else {
			temp->prev = firstNode->prev;
			temp->next = firstNode;
			
			firstNode->prev->next = temp;
			firstNode->prev = temp;
			
			firstNode = temp;			
		}
		
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
		
		Node<Data> * removed = firstNode->prev;
		
		removed->prev->next = firstNode;
		firstNode->prev = removed->prev;
		
		removed->next = NULL;
		removed->prev = NULL;
		
		length--;
		
		return removed->data;
	}
	
	// Remueve el primero de la lista
	Data removeFirst(){
		if (isEmpty()) return NULL;
		
		Node<Data> * removed = firstNode;
		
		removed->prev->next = removed->next;
		removed->next->prev = removed->prev;
		
		removed->prev = NULL;
		removed->next = NULL;
		
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
		
		return firstNode->prev->data;
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
	CircularList<Data> * reverse(){
		CircularList<Data> * rev = new CircularList<Data>();
		Node<Data> * temp = firstNode->prev;
		
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
