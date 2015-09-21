#include <iostream>
#include <string>
using namespace std;

template <class T> class CircLinkedList;

//problem with insert function:
//not adding to the front properly
//check to make sure its circular

template <class T>
class Node {	
	friend class  CircLinkedList<T>;
	T data;
	Node <T> * next;

public:
	//constructor for node	
	Node<T>() { data = NULL; next = NULL }
		
	Node<T>(const T& item, Node<T>* next)
	{
		this->data = item;
		this->next = next;
	}

};

template <class T> class CircLinkedList {
protected:
	Node<T> * head;
	int listSize; //value for easy checking

public:

	CircLinkedList() {
		head = NULL; //initialize head pointer to NULL
		listSize = 0; //set size to empty 
	}

	~CircLinkedList() {
		//systematic deletion along the loop
		Node<T>* temp = head->next;
		Node<T>* afterNode = NULL;
		while (temp != head) {
			afterNode = temp->next;
			delete temp;
			temp = afterNode;
		}

		delete afterNode;
		delete temp;
		delete head;

	}

	int size() const {
		return listSize;
	}

	bool empty() const {
		if (listSize == 0)
			return true;
		else
			false;
	}

	/*
	void checkIndex(int index) {
		if (empty() || index > listSize - 1 ) {
			string s = "illegal Index";
			throw illegalIndex(s);
		}
	}
	*/
	
	T& get(int theIndex) {

		Node<T>* current = head;
		for (int i = 0; i < theIndex; i++)
			current = current->next;

		return current->data;
	}
	
	void printI(int index) {
		T result = get(index);
		cout << result << endl;
	}

	void printL() {
		Node<T>* current = head;
		for (int i = 0; i < listSize; i++) {
			cout << current->data << " ";
			current = current->next;
		}

		cout << "\n";
	}

	void printC(int steps) {
		Node<T>* current = head;
		for (int i = 0; i < steps; i++) {
			cout << current->data << " ";
			current = current->next;
		}

		cout << "\n";
	}


	///May not need this 
	///doesn't work, current should never = NULL if List is circular
	///------------------------------------------------------------------
	int indexOf(const T& element) const {
		
		//set up to itterate through list
		Node<T>* current = firstNode;
		int index = 0;
		//go through list, break out if item found with index 
		// saved or at end of list  
		while (index < listSize && currentNode->element != element) {
			current = current->next;
			index++;
		}

		if (current == NULL)
			return -1;
		else
			return index;
	}
	///----------------------------------------------------------------
	//

	void addNode(const T& item, int index) {
		if (index < 0 || index > listSize) {
			cout << index << " not a valid index" << endl;
			return;
		}

		if (head  == NULL) { //insert to begining list
			head = new Node<T>(item, head);
		}
		else if (index == 0) {
			Node<T>* temp = head;
			Node<T>* temp2 = new Node<T>(head->data, head->next);
			temp->data = item;
			temp->next = temp2;
			head = temp;
		}
		else { //insert within list
			Node<T>* temp = head;
			for (int i = 0; i < index - 1; i++) {
				temp = temp->next;
			}

			Node<T>* temp2 = new Node<T>(item, temp->next);
			temp->next = temp2;

		}

		listSize++;

	}

	void remove(int index) {

		Node<T>* trashMe;
		if (index == 0) {
			//take what head is pointing to, reassign to second
			//node, delete original head node
			trashMe = head;
			head = head->next;

		}
		else {
			//go to before node
			Node<T>* temp = head;
			for (int i = 0; i < index - 1; i++) {
				temp = temp->next;
			}

			// grab what before node points to
			trashMe = temp->next;
			//point before node to "after"-node
			temp->next = temp->next->next;

		}

		listSize--;
		delete trashMe;
	}

	void test() {
		T result = head->next->data;
		cout << result << endl;
	}

};

int main() {

	cout << "Hello World " << endl;

	CircLinkedList<int> Object1;

	Object1.addNode(7, 0);
	Object1.addNode(12, 0);

	Object1.printL();

	Object1.addNode(1, 1);
	Object1.printL();
	Object1.addNode(32, 3);
	Object1.printL();


	cout << Object1.size() << endl;

	

	//cout << "the value at 0 is " << endl;
	//Object1.printI(0);
	//cout << "the value of test is " << endl;
	//Object1.test();


	return 0;
}
