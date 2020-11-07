#include "node.h"

int main(int argc, char** argv) {
	string huh = "huh?";
	
	Node<string> *n = new Node<string>(huh);
	
	cout << n->data << endl;
	
	return 0;
}
