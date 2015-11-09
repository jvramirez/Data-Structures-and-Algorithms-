#include <iostream>
using namespace std;

/*
* parent n has children at 2n + 1 and 2n+2
* child n has parent (n-1)/2
*
*	must have constructor, destructor, empty, size, push, top, and pop functions.
*
*/

template <class T>
class MinHeap {
private:
	T * data;
	int heapSize;
	int arraySize;

public:
	MinHeap(int size) {
		data = new T[size];
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

	int size() { return heapsize; }

	void doubleSize() {
		T * dubArr = new T[arraySize * 2];
		for (int i = 0; i < arraySize; i++) {
			dubArr[i] = data[i];
		}

		data = dubArr;
		arraySize *= 2;
	}

	int parent(int i) { //index of parent returned
		return (i - 1) / 2;
	}

	void push(const T& elem ) {
		if (heapSize == arraySize - 1) {
			doubleSize();
		}
		
		int curr = heapSize++; //first open index
		
		if (curr != 0) { // on first insertion, should just go straight into index 0
			while (curr != 0 && (data[parent(curr)] > elem)) {

				data[curr] = data[parent(curr)];
				curr = parent(curr);
			}
		}

		data[curr] = elem;

	
	}

	T top() {

		if (!empty())
			return data[0];
	
	}


	void pop() {
		if (empty()) {
			cout << "empty heap" << endl;
			return;
		}

		//remove first elem
		data[0] = 0;

		//take last element
		T lastLeaf = data[--heapSize];

		int curr = 0, child = 1;

		while (child <= heapSize) {

			if (child < heapSize && data[child + 1] < data[child])
				child++;

			if (lastLeaf <= data[child])
				break;

			data[curr] = data[child];
			curr = child;
			child = (curr * 2) + 1;
		}

		data[curr] = lastLeaf;
	
	}

};

int main() {
	//check to test
	const int length = 7;
	int bins[length] = {14,10,7,6,5,3,2};
	
	MinHeap<int> mach1 = MinHeap<int>(length);

	for (int i = 0; i < length; i++) {
		mach1.push(bins[i]);
	}

	while (!mach1.empty()) {
		
		cout << mach1.top() << ",";
		mach1.pop();
	}

	return 0;
}
