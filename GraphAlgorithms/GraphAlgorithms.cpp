#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <queue>
using namespace std;
struct Node {
	int num;
	Node* next;

};
class LinkedList {
private:
	Node* head;

public:
	LinkedList() {
		head = NULL;
	}
	~LinkedList() {
		delete head;
	}
	void insertNode(int data) {
		Node* temp = head;
		Node* newNode = new Node;
		newNode->next = nullptr;
		newNode->num = data;
		bool indicator = true;

		if (head == nullptr) {
			head = newNode;
		}
		else {
			while (indicator) {
				if (temp->next == NULL) {
					temp->next = newNode;
					indicator = false;
				}
				else {
					temp = temp->next;
				}
			}
		}
	}
	void showListElems() {

		while (head != nullptr) {

			cout << head->num << "->";
			head = head->next;
		}
	}

	vector<Node*> getNeighbors() {
		vector<Node*> neighbors;
		head = head->next;
		while (head != nullptr) {
			neighbors.push_back(head);
			head = head->next;
			}
		return neighbors;
	}
	Node* getVertex(int headnode) {
		Node* vertex = head;
		while (vertex != nullptr) {
			if (vertex->num == headnode) return vertex;
			
			vertex = vertex->next;
		}
	}

};


class Graph {
	int vertices;
	LinkedList* l;
public:
	Graph(int V) {
		this->vertices = V; // constructor initializes number of vertices
		l = new LinkedList[vertices];
		for (int i = 0; i < vertices; i++) {
			l[i].insertNode(i);
		}
	}
	void addEdgeUndirected(int source, int dest) { //undirected graph implementation edges go from source to destination and back and forth
		l[source].insertNode(dest);
		l[dest].insertNode(source);
	}
	void addEdgeDirected(int source, int dest) { //directed graph implementation edges go from source to destination
		l[source].insertNode(dest);
	}
	void showGraph() {
		for (int i = 0; i < vertices; i++) {
			l[i].showListElems();
			cout << "\n";
		}
	}
	
	bool hasPath(int src, int dest) {
		vector <Node*> neighbors;
		stack<Node*> stack;
		Node* currVertex;
		set<int> visited;

		//LinkedList currPath;
		stack.push(l[src].getVertex(src));


		while (!stack.empty()) {
			currVertex = stack.top();
			stack.pop();

			//currPath.insertNode(currVertex->num);
			if (currVertex->num == dest) {
				cout << "Path has been found";
				return true;
			}
			else if (visited.find(currVertex->num) == visited.end()) {
				neighbors = l[currVertex->num].getNeighbors();
				visited.insert(currVertex->num);
				if (!neighbors.empty()) {
					for (int i = 0; i < neighbors.size(); i++) { //obtain neighbors
						stack.push(neighbors.at(i));
					}
				}
			}
		}
		cout << "No Path Found";
		return false;
	}

	void BFS(int start) {
		queue<Node*> q;
		set<int> visited;
		vector<Node*> neighbors;
		Node* currVertex;
		
		q.push(l[start].getVertex(start));
		while (!q.empty()) {
			currVertex = q.front();
			q.pop();
			if (visited.find(currVertex->num) == visited.end()) {
				cout << currVertex->num << endl;

				visited.insert(currVertex->num);
				neighbors = l[currVertex->num].getNeighbors();
				for (int i = 0; i < neighbors.size(); i++) {
					q.push(neighbors.at(i));
				}
			}
		}
	}

	void DFS(int start) {
		LinkedList path;
		stack<Node*> stack;
		set<int> visited;
		vector<Node*> neighbors;
		
		stack.push(l[0].getVertex(start));
		while (!stack.empty()) {
			Node* vertex = stack.top();
			stack.pop();

			if (visited.find(vertex->num) == visited.end()) {
				visited.insert(vertex->num);
				path.insertNode(vertex->num);
				neighbors = l[vertex->num].getNeighbors();

				for (int i = 0; i < neighbors.size(); i++) {
					stack.push(neighbors.at(i));
				}
			}
		}
		path.showListElems();
	}
};

	int main()
	{
		Graph g = Graph(9);
		Graph graph = Graph(13);
		graph.addEdgeUndirected(0,7);
		graph.addEdgeUndirected(0,9);
		graph.addEdgeUndirected(0,11);
		graph.addEdgeUndirected(3,2);
		graph.addEdgeUndirected(3,4);
		graph.addEdgeUndirected(3,7);
		graph.addEdgeUndirected(6,5);
		graph.addEdgeUndirected(7,6);
		graph.addEdgeUndirected(8,1);
		graph.addEdgeUndirected(8,12);
		graph.addEdgeUndirected(9,10);
		graph.addEdgeUndirected(9,8);
		graph.addEdgeUndirected(10,1);
		graph.addEdgeUndirected(11,7);
		graph.addEdgeUndirected(12,2);



		g.addEdgeDirected(0, 8);
		g.addEdgeDirected(0, 1);
		g.addEdgeDirected(0, 3);
		g.addEdgeDirected(1, 7);
		g.addEdgeDirected(2, 7);
		g.addEdgeDirected(2, 3);
		g.addEdgeDirected(2, 5);
		g.addEdgeDirected(3, 4);
		g.addEdgeDirected(4, 8);
		g.addEdgeDirected(5, 6);
		
		
		//g.showGraph();
		//g.DFS(0);
		//g.hasPath(2, 1);

		graph.BFS(0);
	}

