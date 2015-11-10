/* Javier Ramirez
 * UFID: 58400106
 * Discussion: 13A8
 * COP3530
 * Program Assignment 3
 * 
 * Templetad-MinHeafp and Leftist tree 
 * 
 * */


#include <iostream>
#include <sstream>
using namespace std;


template <class T>
class Node{
public:	
	T val;
	int s;
	int ID;
	Node<T> * left;
	Node<T> * right;

};

template <class T>
class HBLTree {
private:	
	Node<T> * root;
	int numOfElem;
	
public:
	HBLTree(){
		root = NULL;
		numOfElem = 0;
	}
	
	~HBLTree(){
		delete root;
	}
	
	bool empty(){
		if (root == NULL)
			return true;
		else
			return false;
	}
	
	int size(){
		return numOfElem;
	}
	

	Node<T>* meld(Node<T> * &x, Node<T> * &y)	{
		
		if(x == NULL)
			return y;
		if(y == NULL){
			return x;
		}	
		
		if( x->val > y->val){ //you want to keep smaller root in x, else swap
			Node<T> * temp = x;
			x = y;
			y = temp;
		}
		
		x->right = meld(x->right, y); //recusively meld right subtree of x with y
		
		if(!x->left){ //left subtree empty
			x->left = x->right;
			x->right = NULL;
			x->s = 1;
		} else {
			if(x->left->s < x->right->s){ //keep larger s value on left, otherwise swap
				Node<T> * temp = x->right;
				x->right = x->left;
				x->left = temp;
				
			}
			x->s = x->right->s +1; //increment s value
			
		}
		 return x;
		
	}
	
	void push(T value, int nID){
		Node<T> * temp = new Node<T>();
		temp->left = NULL;
		temp->right = NULL;
		temp->val = value;
		temp->ID = nID;
		
		if(empty())
			root = temp;
		else
			root = meld(root, temp);
		++numOfElem;	
	}
	
	void pop(){
		root = meld(root->left, root->right);
		--numOfElem;		
	}
	 
	T top(){
		return root->val;
	}
	
	T topID(){
		return root->ID;
	}
	
}; 


/*
* parent n has children at 2n + 1 and 2n+2
* child n has parent (n-1)/2
*
*	must have constructor, destructor, empty, size, push, top, and pop functions.
*
*/

template <class T>
class HeapNode{
public:
	T value;
	int ID;
	
	HeapNode(T val, int nID){
		value = val;
		ID = nID;
	}
};

template <class T>
class MinHeap {
private:
	HeapNode<T> ** data;
	int heapSize;
	int arraySize;

public:
	MinHeap(int size) {
		data = new HeapNode<T>*[size];
		heapSize = 0;
		arraySize = size;
	}

	~MinHeap() {
		delete[] data;
	}

	bool empty() { 
		if (heapSize == 0)
			return true;
		else
			return false;
	}

	int size() { return heapSize; }

	/*
	void doubleSize() {
		T * dubArr = new T[arraySize * 2];
		for (int i = 0; i < arraySize; i++) {
			dubArr[i] = data[i];
		}

		data = dubArr;
		arraySize *= 2;
	}
*/

	int parent(int i) { //index of parent returned
		return (i - 1) / 2;
	}

	void push( T elem, int ID ) {
		/*if (heapSize == arraySize - 1) {
			doubleSize();
		}*/
		
		/*cout << "here1 \n";
		HeapNode<T> * temp;
		cout << "here2 \n";
		cout << "temp->value is: " << temp->value << endl;
		cout << "elem is: " << elem << endl;
		temp->value = 0;
		cout << "did I make it here?\n";
		temp->value = elem;
		temp->ID = ID;
		*/
		
		int curr = heapSize++; //first open index
		
		if (curr != 0) { // on first insertion, should just go straight into index 0

			while (curr != 0 && (data[parent(curr)]->value > elem)) {
				
				data[curr] = data[parent(curr)];
				curr = parent(curr);
			}
		}

		data[curr] = new HeapNode<T>(elem, ID);

	
	}

	T top(){

		return data[0]->value;
	
	}
	
	int topID(){
		
		return data[0]->ID;
	}


	void pop() {
		if (empty()) {
			cout << "empty heap" << endl;
			return;
		}
		

		//remove first elem
		delete data[0];

		
		//take last element
		HeapNode<T> * lastLeaf;
		--heapSize;
		lastLeaf = new HeapNode<T>(data[heapSize]->value, data[heapSize]->ID);


		int curr = 0, child = 1;


		while (child <= heapSize) {

			if (child < heapSize && data[child + 1]->value < data[child]->value)
				child++;

			if (lastLeaf->value <= data[child]->value)
				break;

			data[curr] = data[child];
			curr = child;
			child = (curr * 2) + 1;
		}


		data[curr] = lastLeaf;
	
	}

};

//sort the array after being given the numbers
void BubbleSort(int * nums, int length ){
	int i,j, flag = 1;
	int temp;
	for(i = 1; (i <= length) && flag; i++) {
			
		flag = 0;
		
		for (j = 0; j < length-1; j++){
			if (nums[j+1] > nums[j]){
				temp = nums[j];
				nums[j] = nums[j+1];
				nums[j+1] = temp;
				flag = 1;
				
			}
			
		}
		
	}
	
	return;
	
	
}
int main() {
	//check to test
	int length, machines;
	cout << "Enter the number of job(s)" << endl;
	cin >> length;
	int process[length]; 
	cout << "Enter the number of machine(s)" << endl;
	cin >> machines;
	cout << "Enter Processing Time(s)\n" << endl;
	for (int i = 0; i < length; i++){
		cin >> process[i];
	}
	
	
	int *procptr = process;
	BubbleSort(procptr, length);
	
	string loadOrders[machines];
	
	
	clock_t t1, t2;

	///MinHeap calculations-------------------------------------------
	
	//time start
	t1 = clock();
	
	MinHeap<int> mach1 = MinHeap<int>(length);
	
	for (int i = 0; i < machines; i++) {
		mach1.push(process[i], i+1);
		
		//string array each have at least one process time in each index
		stringstream ss;
		ss << process[i];
		string str;
		ss >> str;
		loadOrders[i] = str;
	}
	
	//Where the magic happens
	for(int i = machines; i < length; i++){
		
		int emptiestMach = mach1.topID(); //take note of machine with most space
		int newTotal = mach1.top() + process[i]; // time to that machine
		mach1.pop(); //remove that machine
		
		// concatenate next process time to respective machine
		string str1 = loadOrders[emptiestMach - 1];
		stringstream ss;
		ss << process[i];
		string str2;
		ss >> str2;
		str1 = str1 + ", " + str2;
		loadOrders[emptiestMach - 1] = str1;
		
		//reinsert the new total with the same machine ID as before
		mach1.push(newTotal, emptiestMach);
	}
	
	//calculate longest process time
	int max = 0;
	while (!mach1.empty()) {
		
		if(mach1.top() > max)
			max = mach1.top();
		mach1.pop();
	}
	
	
	cout << "Min Heap Finishing Time: " << max << endl;
	for(int i = 0; i < machines; i++){
		cout << "Machine " << i +1 << ": " << loadOrders[i] << endl;
		
	}
	
	//stop clock
	t2 = clock();
	float diff = ((float)t2 - (float)t1)/CLOCKS_PER_SEC;
	cout << "Execution time is " << diff << endl;
	cout << "\n";
	
	///------------------------------------------------------------------------
	
	for(int i = 0; i < machines; i++){
		loadOrders[i] = "";		
	}
	
	///HBLTree analysis **********************************************************
	t1 = clock();
	HBLTree<int> mach2 = HBLTree<int>();
	
	// keep track of the orders
	//holds value order of insertion into certain machines in designated format 

	
	
	//fill in the empty machines with the largest values
	for (int i = 0; i < machines; i++) {
		mach2.push(process[i], i+1);
		
		//string array each have at least one process time in each index
		stringstream ss;
		ss << process[i];
		string str;
		ss >> str;
		loadOrders[i] = str;
	}
	
	//Where the magic happens
	for(int i = machines; i < length; i++){
		
		int emptiestMach = mach2.topID(); //take note of machine with most space
		int newTotal = mach2.top() + process[i]; // time to that machine
		mach2.pop(); //remove that machine
		
		// concatenate next process time to respective machine
		string str1 = loadOrders[emptiestMach - 1];
		stringstream ss;
		ss << process[i];
		string str2;
		ss >> str2;
		str1 = str1 + ", " + str2;
		loadOrders[emptiestMach - 1] = str1;
		
		//reinsert the new total with the same machine ID as before
		mach2.push(newTotal, emptiestMach);
	}
	
	//calculate longest process time
	max = 0;
	while (!mach2.empty()) {
		
		if(mach2.top() > max)
			max = mach2.top();
		mach2.pop();
	}
	
	
	cout << "Height Biased Leftist Tree Finishing Time: " << max << endl;
	for(int i = 0; i < machines; i++){
		cout << "Machine " << i +1 << ": " << loadOrders[i] << endl;
		
	}
	
	t2 = clock();
	diff = ((float)t2 - (float)t1)/CLOCKS_PER_SEC;
	cout << "Execution time is " << diff << endl;

	
	///***************************************************************************
	
	
	return 0;
}
