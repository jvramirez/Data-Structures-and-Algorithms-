#include <iostream>
#include <vector>
#include "TailoredDataStructs.cpp"
using namespace std;

//Kruskal's algorithm
// add shortest side that connects 2 nodes and does not make a cycle
void Kruskal(SparseMatrix<int>& graph, HBLTree<int>& edges, int size) {
	bool * visited = new bool[size];
	int totalWeight = 0;
	int edgesAdded = 0;
	vector<vector<int>> A;
	int node1, node2, node1Loc, node2Loc;

	for (int i = 0; i < size; i++)
		visited[i] = false;

	while (edgesAdded < size - 1) {
		node1 = edges.topA();
		node2 = edges.topB();
		node1Loc = -1;
		node2Loc = -1;
		bool node1Found = false;
		bool node2Found = false;

		if (A.empty()) {
			vector<int> comp;
			comp.push_back(node1);
			comp.push_back(node2);
			A.push_back(comp);
			totalWeight += edges.top();
			edges.pop();
			edgesAdded++;
			cout << "(" << node1 << ", " << node2 << ")" << endl;
		} else {
			for (int i = 0; i < A.size(); ++i) {
				for (int j = 0; j < A[i].size(); ++j) {
					if (A[i][j] == node1) {
						node1Found = true;
						node1Loc = i;
					}
					else if (A[i][j] == node2) {
						node2Found = true;
						node2Loc = i;
					}
				}
				if ( node1Loc == node2Loc && node1Found && node2Found) {
					edges.pop();
					break;
				}
			}

			if (node1Loc == node2Loc && node1Found && node2Found)
				continue;

			if (node1Loc == -1 && node2Loc == -1) {
				vector<int> comp;
				comp.push_back(node1);
				comp.push_back(node2);
				A.push_back(comp);
				totalWeight += edges.top();
				edges.pop();
				edgesAdded++;
				cout << "(" << node1 << ", " << node2 << ")" << endl;
			} else if (node1Loc == -1 || node2Loc == -1) {
				if (node1Loc == -1) {
					A[node2Loc].push_back(node1);
				} else {
					A[node1Loc].push_back(node2);
				}
				
				totalWeight += edges.top();
				edges.pop();
				edgesAdded++;
				cout << "(" << node1 << ", " << node2 << ")" << endl;
			}
			else {
				vector<int> comp;
				comp.reserve(A[node1Loc].size() + A[node2Loc].size() );
				comp.insert(comp.end(), A[node1Loc].begin(), A[node1Loc].end());
				comp.insert(comp.end(), A[node2Loc].begin(), A[node2Loc].end());
				A.push_back(comp);
				totalWeight += edges.top();
				edges.pop();
				edgesAdded++;
				cout << "(" << node1 << ", " << node2 << ")" << endl;	
			}
			
		
		}
	
	
	}

	cout << "Total Weight:" << endl;
	cout << totalWeight << endl;

}


//Prim's algorithm
// add node piece by piece, with a start node
void Prim(SparseMatrix<int>& graph, int start, int size) {
	bool * visited = new bool[size];
	int curr = start;
	Node<int> * ptr;
	int totalWeight = 0;

	for (int i = 0; i < size; i++) 
		visited[i] = false;


	for (int i = 0; i < size - 1; i++) {
		int min = INT_MAX, minIndex, startNode;

		visited[curr] = true;

		//find lowest edge to new node
		for (int j = 0; j < size; j++) {		
			if (visited[j]) {
				ptr = graph.elem[j];
				while (ptr != NULL) {
					if (ptr->data < min && !visited[ptr->index]) {
						min = ptr->data;
						minIndex = ptr->index;
						startNode = j;
					}
					
					ptr = ptr->next;
				}
									
			}
		}

		curr = minIndex;
		totalWeight += min;
		cout << "(" << startNode << ", " << minIndex << ")" << endl;
	
	}

	cout << "Total Weight:" << endl;
	cout << totalWeight << endl;

}

//Sollin's algorithm
//Load up nodes into a queue, every dequeue and find smallest edge
void Sollin(SparseMatrix<int>& graph, int size) {
	//use vector as modified Q
	vector<vector<int>> modQ;
	bool * visited = new bool[size];
	Node<int>* gptr;
	int totalWeight = 0;

	for (int i = 0; i < size; i++) {
		vector<int> comp;
		comp.push_back(i);
		modQ.push_back(comp);
		visited[i] = false;
	}

	for (int steps = 0; steps < size - 1; steps++) {
		int min = INT_MAX, minIndex = -1, startNode;
		vector<int> tmp = modQ.front();
		modQ.erase(modQ.begin());
		
		for (int i = 0; i < tmp.size(); i++) {
			visited[tmp[i]] = true;
		}


		for (int i = 0; i < tmp.size(); i++) {
			gptr = graph.elem[tmp[i]];
			while (gptr != NULL) {
				if (gptr->data < min && !visited[gptr->index]) {
					min = gptr->data;
					minIndex = gptr->index;
					startNode = tmp[i];
				}

				gptr = gptr->next;
			
			}
			
		}
	
		totalWeight += min;
		cout << "(" << startNode << ", " << minIndex << ")" << endl;

		for (int i = 0; i < size; i++)
			visited[i] = false;

				
		int listIndex = -1;
		for (int i = 0; i < modQ.size(); i++) {
			for (int j = 0; j < modQ[i].size(); j++) {
				if (modQ[i][j] == minIndex) {
					listIndex = i;
					break;
				}
			
			}	
		}

		vector<int> comp;
		comp.reserve(modQ[listIndex].size() + tmp.size());
		comp.insert(comp.end(), modQ[listIndex].begin(), modQ[listIndex].end());
		comp.insert(comp.end(), tmp.begin(), tmp.end());
		modQ.erase(modQ.begin() + listIndex);
		modQ.push_back(comp);
		
	}

	cout << "Total Weight:" << endl;
	cout << totalWeight << endl;

}


int main() {

	int nodeCount, edgeCount, startNode;
	SparseMatrix<int> oGraph;
	HBLTree<int> edgeTree;


	cout << "Enter number of Node and Edge(s): " << endl;
	cin >> nodeCount;
	cin >> edgeCount;
	oGraph.init(nodeCount);



	cout << "Enter Node A and Node B and Undirected Edge Weight(s): " << endl;
	for (int i = 0; i < edgeCount; i++) {
		int A, B, weight;
		cin >> A;
		cin >> B;
		cin >> weight;

		oGraph.read(A, B, weight);
		edgeTree.push(weight, A, B);
		
	
	}

	cout << "Enter the start Node: " << endl;
	cin >> startNode;

	cout << "\nPrim's Algorithm:" << endl;
	Prim(oGraph, startNode, nodeCount);

	cout << "\nKruskal's Algorithm" << endl;
	Kruskal(oGraph,edgeTree,nodeCount);

	cout << "\nSollin's Algorithm" << endl;
	Sollin(oGraph, nodeCount);


	return 0;
}
