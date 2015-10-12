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
	void insert(int n, int r) { //modularize insertion code
		cout << "Enter element's column, and value of each term in row " << r << endl;
		while (n > 0) {
			//take in values
			int loc, val;
			cin >>  loc;
			cin >>  val;

			if (elem[r - 1] == NULL) {//first insertion
				elem[r - 1] = new Node<T>(loc, val);
			}
			else {//traverse Nodes in row until at end
				Node<T>* curr = elem[r - 1];
				if (loc < curr->index) {
					elem[r - 1] = new Node<T>(loc, val, curr);
				}
				else {
					Node<T>* aftr = curr->next;
					while (aftr != NULL && loc > aftr->index) {
						curr = aftr;
						aftr = aftr->next;
					}
					curr->next = new Node<T>(loc, val, aftr);
					//curr = curr->next; //now on newly created node (may be able to replace with curr->next->next = aftr)
					//curr->next = aftr;
				}
			}

			n--;
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

	void read() {
		cout << "Enter the number of rows, columns" << endl;
		try{
			cin >> rows;
			cin >> columns;
		}
		catch (bad_typeid) { //error checkin to make sure rows and its type are correct 
			cout << "rows and columns must be ints" << endl;
		}
		if (rows < 1 || columns < 1) {
			cout << "Input cannot be < 1" << endl;
			return;
		}

		//initialize elem array with NULL ptr
		elem = new Node<T>* [rows];
		for (int i = 0; i < rows; i++) {
			elem[i] = NULL;
		}


		for (int i = 1; i <= rows; i++) {
			int nums = 0;
			cout << "Enter the number of terms in row " << i << endl;
			cin >> nums;
			//if value greater than 0, call insert
			while (nums < 0 || nums > columns) {
				cout << "Value must be between 0 and " << columns << endl;
				cout << "Enter the number of terms in row " << i << endl;
				cin >> nums;
			}
			if (nums != 0) {
				insert(nums, i); //i is whatever row you are currently inserting for
			}
			

		}		
	}

	void print() {
		if (rows == 0 || columns == 0) {
			cout << "Empty sparse matrix" << endl;
		}

		cout << "rows = " << rows << " columns = " << columns << endl;
		Node<T>* curr; // boiler plate ptr through list
		for (int i = 0; i < rows; i++){
			cout << "row " << i + 1 <<"[";
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

/* Better print that shows all elements in abstract representation
	void print() {
		
		Node<T>* curr;
		for (int i = 0; i < rows; i++) {
			curr = elem[i];
			for (int j = 0; j < columns; j++) {
			
				if (curr == NULL) {
					cout << "\t" << 0;
				}
				else if (curr->index == j + 1) {
					cout << "\t" << curr->data;
					curr = curr->next;
				}
				else {
					cout << "\t" << 0;
				}
	
			}

			cout << "\n";
		}
	
	}
*/

	void mask(SparseMatrix<T>  *b, SparseMatrix<bool> *c) {
	// b should be int; c should be bool

		if (b->rows != c->rows || b->columns != c->columns) { //check dimensions
			cout << "Matrices must be of equal dimensions" << endl;
			return;
		}

		this->columns = b->columns; //set rows and cols
		this->rows = b->rows;

		//array of Node<T>* that are all NULL
		elem = new Node<T>*[rows];
		for (int i = 0; i < rows; i++) {
			elem[i] = NULL;
		}

		for (int i = 0; i < rows; i++) {
			if (c->elem[i] != NULL) { //if nothing in bool sp row, go to next row
				
				Node<bool>* Cptr = c->elem[i];
				Node<T>* Bptr = b->elem[i];

				//move through bool and int spMat simult	runs:O(m+n)
				while ( Cptr != NULL) {
					while (Bptr != NULL && Bptr->index < Cptr->index) { //move through <int> row and stop when NULL or you are at an index >=  <bool> index
						Bptr = Bptr->next;
					}
					if (Bptr != NULL) { //if already at end of <int> row, no need to check
						if (Cptr->index == Bptr->index) {
							//insert Cptr index and bptr value
							insertF(Cptr->index, Bptr->data, i);

						}
					}
					Cptr = Cptr->next;

				}
			}
		
		}
	}
};

int main() {

	SparseMatrix<int>*	MatA = new SparseMatrix<int>();
	SparseMatrix<bool>*	MatB = new SparseMatrix<bool>();
	SparseMatrix<int>*	MatC = new SparseMatrix<int>();


	cout << "Reading Matrix A ..." << endl;
	MatA->read();
	cout << "\n Matrix A :" << endl;
	MatA->print();
	
	cout << "Reading Matrix B ..." << endl;
	MatB->read();
	cout << "\n Matrix B, the boolean mask matrix :" << endl;
	MatB->print();
	
	cout << "\n Matrix C Results :" << endl;
	MatC->mask(MatA, MatB);
	MatC->print();

	return 0;
}
