/* Javier Ramirez
 * COP3530
 * Program Assignment 1
 * 
 * Templetad-Circular-Singly-Linkedlist 
 * 
 * */


#include <iostream>
#include <string>
using namespace std;

//always let your friend know you're there for them :)
template <class T> class CircLinkedList;

template <class T>
class Node {	
	friend class  CircLinkedList<T>;
	T data;
	Node <T> * next;

public:
	//constructor for node	
	Node<T>() { data = NULL; next = NULL; }
		
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
		head = 0; //initialize head pointer to NULL
		listSize = 0; //set size to empty 
	}

	~CircLinkedList() {
		//systematic deletion along the loop
		if( listSize >0){		
			Node<T> *temp = head->next;
			Node<T> *nextNode;
			while (temp != head) {	
				nextNode	= temp->next;
				delete temp;
				temp		= nextNode;
			}
		}
	}

	int size() const {
		return listSize;
	}
	
	T& get(int theIndex) {
	//return <T> value of index
		Node<T>* current = head;
		for (int i = 0; i < theIndex; i++)
			current = current->next;

		return current->data;
	}
	
	void printI(int index) {
		// use returned value to print to screen 
		T result = get(index);
		cout << result << endl;
	}

	void printL() {
		if( listSize == 0){
			cout << "[list is empty]" <<endl;
			return;
		}
		//print content of list with formatting
		cout << "[";
		Node<T>* current = head;
		for (int i = 0; i < listSize -1; i++) {
			cout << current->data << ",";
			current = current->next;
		}//stop at 2nd-to-last node 

		cout << current->data << "]\n";//last node printed
	}

	
	void addNode(const T& item, int index) {
		if (index < 0 || index > listSize) {
			cout << index << " not a valid index" << endl;
			return;
		}

		if (head  == 0) { //insert to empty list
			head = new Node<T>(item, NULL);
			head->next = head;//makes it circular
		}
		else if (index == 0) {//insert at beginning
			Node<T>* temp = head;
			Node<T>* temp2 = new Node<T>(head->data, head->next);//copy of orig head
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
		
		//if list is empty, should return.
		if (listSize == 0){
			cout << "Can't delete from empty list" <<endl;
			return;
		}
		if (index >= listSize || index < 0) {
			cout <<  index << " not a valid index" <<endl;
			return;
		}	

		Node<T>* trashMe;
		if (index == 0) {
			//get last node, 
			Node<T>* lastNode = getNode(listSize - 1);
			trashMe = head;
			head = head->next;     //move head to second node
			lastNode->next = head; //maintain circular link

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

		delete trashMe;
		listSize--;
	}
	
	//modularized function to return pointer to node
	Node<T>* getNode(int index) const{
		Node<T> *temp = head;
		int count = 0;
		while (count != index) {
			temp = temp->next;
			count++;
		}
		return temp;
	}
	
	//handle n insertion in main
	// k >= 1
	//listSize >=1
	void josephus(int k){
		if(listSize == 0){
			cout << "Can't run josephus on empty stomach- I mean, list\n";
			return; 
		}
		
		Node<T>* track = getNode(listSize - 1); // folow node starts behind head (last node)
		Node<T>* kill = head; //leading node start at head
		 
		cout << "[";
		 
		int counter = 1;
		while(listSize != 1){
			
			//target in site
			if(counter == k){
				counter = 1; //reset
				if( kill == head){
					head = head->next; // move head over so you don't lose track of head					
				} 
				//any other node k
				cout << kill->data << ",";
				track->next = kill->next;
				delete kill;
				listSize--;
				kill = track->next;					 
								 
			} else {
			track = kill;
			kill= kill->next;
			counter++;
			}
		}
		
		cout << head->data << "]" << endl;
		 
		 
	}


};

int main() {

	cout << "Insert number of commands" << endl;

	CircLinkedList<int> Object1;
	int tests = 0;
	
	cin >> tests;
	
	int value, index, n, k;
	char com;
	while( tests >0){
		cin >> com;
		switch (com) {
			case 'I':
				cin >> value;
				cin >> index;
				Object1.addNode(value, index);
				break;
			case 'D':
				cin >> index;
				Object1.remove(index);
				break;
			case 'S':
				Object1.printL();
				break;
			case 'P':
				cin >> index;
				Object1.printI(index);
				break;
			case 'J':
				cin >> n;
				cin >> k;
				for(int i = 0; i < n; i++){
					cin >> value;
					Object1.addNode(value, 0);
				}
				Object1.josephus(k);
				break;
			default:
				cout << "bad input: " << com << endl;
				break;
		}
		
		tests--;
		
	}
	


	return 0;
}
