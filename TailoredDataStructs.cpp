#include <iostream>
#include <exception>
using namespace std;


template <class T>
class Node {
public:
	T data;
	int index;
	Node<T>* next;
	Node(int loc, const T& data) {
		this->data = data;
		this->index = loc;
		this->next = NULL;
	}

	Node(int loc, const T& data, Node<T>* nxt) {
		this->data = data;
		this->index = loc;
		this->next = nxt;
	}

};

template <class T>
class SparseMatrix {
public:
	//make private later if you have time
	int rows;
	int columns;
	Node<T>** elem;

	SparseMatrix() {
		elem = NULL;
		rows = 0;
		columns = 0;
	}
	~SparseMatrix() {
		Node<T>* kill = NULL;
		Node<T>* curr = NULL;

		for (int i = 0; i < rows; i++) {

			curr = elem[i];
			if (curr != NULL) {
				while (curr != NULL) {
					kill = curr;
					curr = curr->next;
					delete kill;
				}
				delete curr;
			}

		}
	}
	void insert(int val, int nA, int loc) { //modularize insertion code

			if (elem[nA ] == NULL) {//first insertion
				elem[nA ] = new Node<T>(loc, val);
			}
			else {//traverse Nodes in row until at end
				Node<T>* curr = elem[nA ];

				if (loc == curr->index && val < curr->data) {
					elem[nA] = new Node<T>(loc, val, curr->next);
					delete curr;
				} else if(loc == curr->index && val >= curr->data){
					return;
				} else if (loc < curr->index) {
					elem[nA ] = new Node<T>(loc, val, curr);
				} else {
					Node<T>* aftr = curr->next;
					while (aftr != NULL) {
						if (loc < aftr->index){
							break;
						} else if (loc == aftr->index && val < aftr->data) { //case where edge already exists but is not smallest
							curr->next = new Node<T>(loc, val, aftr->next);
							delete aftr;
							return;
						} else if (loc == aftr->index && val >= aftr->data){ //case where edge already exists but new edge is more expensive
							return;
						}
						
						curr = aftr;
						aftr = aftr->next;
					}

					curr->next = new Node<T>(loc, val, aftr);

				}
			}


	}

	void insertF(int loc, int val, int r) {
		if (elem[r] == NULL) {//first insertion
			elem[r] = new Node<T>(loc, val);
		}
		else {//traverse Nodes in row until at end
			Node<T>* curr = elem[r];
			while (curr->next != NULL) {
				curr = curr->next;
			}
			curr->next = new Node<T>(loc, val);
		}

	}

	bool init(int dim) {
		if (dim < 1) {
			cout << "Error: Cannot have less than 1 node " << endl;
			return false;
		}
		
		// square adjacency matrix
		rows = dim;
		columns = dim;

		//initialize rows point to null
		elem = new Node<T>*[rows];
		for (int i = 0; i < rows; i++) {
			elem[i] = NULL;
		}

		return true;
	}

	void read(int NodeA, int NodeB, int edge) {
	
		if (edge > 0) {
			insert(edge, NodeA, NodeB);
			insert(edge, NodeB, NodeA);
		}	
	}

	void print() {
		if (rows == 0 || columns == 0) {
			cout << "Empty sparse matrix" << endl;
		}

		Node<T>* curr; // boiler plate ptr through list
		for (int i = 0; i < rows; i++) {
			cout << "Node " << i << "[";
			curr = elem[i];
			while (curr != NULL) {
				if (curr != elem[i]) //if not the first element, need to start with ','
					cout << ",";

				cout << " col:" << curr->index;
				cout << " val= " << curr->data;

				curr = curr->next;
			}
			cout << "]" << endl;
		}

		cout << "\n";


	}
};

template <class T>
class Edge {
public:
	T val;
	int NodeA;
	int NodeB;
	int s;
	Edge<T> * left;
	Edge<T> * right;

};

//HBL tree holding edges
template <class T>
class HBLTree {
private:
	Edge<T> * root;
	int numOfElem;

public:
	HBLTree() {
		root = NULL;
		numOfElem = 0;
	}

	~HBLTree() {
		delete root;
	}

	bool empty() {
		if (root == NULL)
			return true;
		else
			return false;
	}

	int size() {
		return numOfElem;
	}


	Edge<T>* meld(Edge<T> * &x, Edge<T> * &y) {

		if (x == NULL)
			return y;
		if (y == NULL) {
			return x;
		}

		if (x->val > y->val) { //you want to keep smaller root in x, else swap
			Edge<T> * temp = x;
			x = y;
			y = temp;
		}

		x->right = meld(x->right, y); //recusively meld right subtree of x with y

		if (!x->left) { //left subtree empty
			x->left = x->right;
			x->right = NULL;
			x->s = 1;
		}
		else {
			if (x->left->s < x->right->s) { //keep larger s value on left, otherwise swap
				Edge<T> * temp = x->right;
				x->right = x->left;
				x->left = temp;

			}
			x->s = x->right->s + 1; //increment s value

		}
		return x;

	}

	void push(T value, int nA, int nB) {
		Edge<T> * temp = new Edge<T>();
		temp->left = NULL;
		temp->right = NULL;
		temp->val = value;
		temp->NodeA = nA;
		temp->NodeB = nB;

		if (empty())
			root = temp;
		else
			root = meld(root, temp);
		++numOfElem;
	}

	void pop() {
		root = meld(root->left, root->right);
		--numOfElem;
	}

	T top() {
		return root->val;
	}

	T topA() {
		return root->NodeA;
	}

	T topB() {
		return root->NodeB;
	}

};
