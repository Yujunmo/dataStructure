#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stack>
#include<queue>
#include<functional>
#define INF 9999
#define MAX 20
using namespace std;

//find union 클래스
class VertexSets {
private:
	int* parent;
	int nSets;
public:
	VertexSets(int size) :nSets(size) {
		parent = new int[size];
		for (int i = 0; i < size; ++i) {
			parent[i] = i;
		}
	}
	~VertexSets() {
		delete[] parent;
	}

	// 소속 집합의 루트를 찾아줌
	int findSet(int vertexIndex) {
		while (parent[vertexIndex] != vertexIndex) { vertexIndex = parent[vertexIndex]; }
		return vertexIndex;
	}

	// 하나의 집합으로 통합. 작은 루트로 통합함.
	void unionSet(int Smallv1, int Bigv2) {
		parent[Bigv2] = Smallv1;
		nSets--;
	}

};

// 최소 힙에 푸시하기 위해 새로운 객체를 구현함.
class Edge {
	int weight;
	int start;
	int end;
public:
	Edge(int s, int e, int w) :start(s), end(e), weight(w) {}
	int getStart() { return start; }
	int getEnd() { return end; }
	int getWeight() { return weight; }
};

class cmp {
public:
	bool operator()(Edge a, Edge b) {
		return  a.getWeight() > b.getWeight();
	}
};

class primVertex {
public:
	int from;
	int weight;

	primVertex() {
		from = 0;
		weight = INF;
	}
};

class Wgraph {
protected:
	char vertices[MAX];
	int matrix[MAX][MAX];
	int size;
	bool visited[MAX];
	primVertex distance[MAX];
public:
	Wgraph() { reset(); }
	void reset() {
		for (int i = 0; i < MAX; ++i) {
			for (int j = 0; j < MAX; ++j) {
				matrix[i][j] = INF;
			}
		}
		for (int i = 0; i < MAX; ++i) {
			visited[i] = false;
		}
		size = 0;
	}

	void visitedReset() {
		for (int i = 0; i < size; ++i) {
			visited[i] = false;
		}
	}

	bool isFull() {
		return size == MAX;
	}
	bool isEmpty() {
		return size == 0;
	}
	int getVertexNumber(char v) {
		for (int index = 0; index < size; ++index) {
			if (vertices[index] == v) {
				return index;
			}
		}
		return -1;
	}

	void getEdge(char v1, char v2, int &edge) {
		int index1 = getVertexNumber(v1);
		int index2 = getVertexNumber(v2);
		if (index1 == -1 || index2 == -1) {
			cout << "unavailable vertex" << endl;
			return;
		}
		else {
			if (matrix[index1][index2] == INF) {
				cout << "no edge" << endl;
				return;
			}
			edge = matrix[index1][index2];
		}
	}

	// kruskal에 쓰일 함수. 시작 정점, 끝 정점, 가중치를 필드로 갖는 객체를 반환.
	Edge GETEDGE(int v1, int v2) {
		int weight = matrix[v1][v2];
		Edge edge(v1, v2, weight);
		return edge;
	}

	
	void insertVertex(char v) {
		if (isFull()) {
			cout << "matrix is full" << endl;
			return;
		}
		else {
			vertices[size++] = v;
			cout << v << " is inserted" << endl;
		}
	}
	void deleteVertex(char v) {
		if (isEmpty()) {
			cout << "martix is empty" << endl;
			return;
		}
		else {
			int index = getVertexNumber(v);
			for (int i = index; i < size-1; ++i) {
				for (int j = 0; j < size; ++j) {
					matrix[j][i] = matrix[j][i + 1];
					matrix[i][j] = matrix[i + 1][j];
				}
				matrix[i][i] = matrix[i + 1][i + 1];
			}

			for (int i = index; i < size - 1; ++i) {
				vertices[i] = vertices[i + 1];
			}

			size--;
			cout << v << " is deleted" << endl;
		}	
	}

	void insertEdge(char v1, char v2, int weight) {
		int index1 = getVertexNumber(v1);
		int index2 = getVertexNumber(v2);
		if (index1 == -1 || index2 == -1) {
			cout << "unavailabe vertex" << endl;
			return;
		}
		else {
			matrix[index1][index2] = weight;
			matrix[index2][index1] = weight;
		}
	}

	void deleteEdge(char v1, char v2) {
		int index1 = getVertexNumber(v1);
		int index2 = getVertexNumber(v2);
		if (index1 == -1 || index2 == -1) {
			cout << "unavailabe vertex" << endl;
			return;
		}
		else {
			matrix[index1][index2] = INF;
			matrix[index2][index1] = INF;
		}
	}

	void display() {
		if (isEmpty()) {
			cout << "matrix is empty" << endl;
			return;
		}
		else {
			cout << "size : " << size << endl << "\t";
			for (int i = 0; i < size; ++i) {
				cout << vertices[i] << "\t";
			}
			cout << endl;
			for (int i = 0; i < size; ++i) {
				cout << vertices[i] << "\t";
				for (int j = 0; j < size; ++j) {
					if (matrix[i][j] == INF) {
						cout << "" << "\t";
						continue;
					}
					cout << matrix[i][j] << "\t";
				}
				cout << endl;
			}
		}
	}

	void load(const char* filename) {
		FILE* fp = fopen(filename, "r");
		if (fp == nullptr) {
			cout << "open failure" << endl;
			return;
		}
		cout << "file successfully opened" << endl;
		char v1, v2;
		int weight;
		int number;
		
		fscanf(fp, "%d", &number);
		while ((v1=fgetc(fp)) != '\n') {}
		for (int i = 0; i < number; ++i) {
			v1 = fgetc(fp);
			v2 = fgetc(fp); //공백 받기용
			insertVertex(v1);
		}

		char check;
		while (true) {
			check = fgetc(fp);
			if (check == EOF) {
				return;
			}
			fscanf(fp,"%c %c %d", &v1, &v2, &weight);
			insertEdge(v1, v2, weight);
		}
	}

	void DFS(char v) {
		visitedReset();
		stack<int> stack;
		int Firstindex = getVertexNumber(v);
		//첫번째 정점의 인덱스 스택에 추가
		stack.push(Firstindex);
		visited[Firstindex] = true;
		cout << v << " ";
		
		while (stack.empty() == false) {
			int index = stack.top();
			if(visited[index]==false)	//방문되지 않은 정점이라면 출력 (정점 중복 출력 방지)
				cout << vertices[index] << " ";
			visited[index] = true;		//가장 위에 있는건 방문 처리
			stack.pop();
			for (int i = 0; i < size; ++i) {
				if (matrix[index][i] != INF && visited[i] == false) {
					stack.push(i);	
				}
			}
		}
	}

	void BFS(char v) {
		visitedReset();
		queue<int> queue;
		int FirstIndex = getVertexNumber(v);
		queue.push(FirstIndex);
		visited[FirstIndex] = true;

		while (queue.empty() == false) {
			int index = queue.front();
			cout << vertices[index] << " ";
			queue.pop();
			for (int i = 0; i < size; ++i) {

				if (matrix[index][i] != INF && visited[i] == false) {
					visited[i] = true;
					queue.push(i);
					
				}
			}
		}
	}

	void Kruskal() {
		//최소 힙
		priority_queue<Edge, vector<Edge>, cmp > minheap;

		
		for (int i = 0; i < size - 1; ++i) {
			for (int j = i + 1; j < size; ++j) {
				if (matrix[i][j] != INF) {  //두 정점간 간선이 존재하면
					minheap.push(GETEDGE(i, j)); //힙에 넣는다. 객체에 담아서 넣는다.
				}
			}
		}

		VertexSets set(size);
		int numberSelected = 0;
		while (numberSelected < size - 1) {
			Edge e = minheap.top();
			minheap.pop();
			int p1 = set.findSet(e.getStart()); //시작 정점의 루트
			int p2 = set.findSet(e.getEnd());   //끝 정점의 루트

			//두 정점의 루트가 같으면 이미 같은 집합임. 이 두 정점을 이으면 싸이클이 생기므로 간선을 추가하지 않음.
			if (p1 == p2) {
				continue;
			}
			// 두 정점의 루트가 다르다. 서로 다른 집합이다.
			else {
				//루트가 작은걸로 통합함.
				if (p1 > p2) {
					cout << vertices[e.getStart()] << " " << vertices[e.getEnd()] << " : " << matrix[e.getStart()][e.getEnd()] << endl;
					set.unionSet(p2, p1);
					numberSelected++;
				}
				else {
					cout << vertices[e.getStart()] << " " << vertices[e.getEnd()] << " : " << matrix[e.getStart()][e.getEnd()] << endl;
					set.unionSet(p1, p2);
					numberSelected++;
				}
			}
		}
	}

	void Prim(char v) {
		//초기화
		visitedReset();
		for (int i = 0; i < size; ++i) {
			distance[i].weight = INF;
		}

		int count = 0;
		int Firstindex = getVertexNumber(v);
		distance[Firstindex].weight = 0;

		//정점 개수만큼
		while (count != size) {
			int closestIndex = getClosestVertexIndex();
			visited[closestIndex] = true;

			if (distance[closestIndex].weight == INF) {
				cout << "unavilable to make a spanning tree" << endl;
				return;
			}

			if (!(closestIndex == distance[closestIndex].from)) {
				cout << vertices[closestIndex] << "-" << vertices[distance[closestIndex].from] <<
					" : " << distance[closestIndex].weight << endl;
			}

			//새로 추가된 정점에 대해 distance 갱신
			for (int i = 0; i < size; ++i) {
				if (visited[i] == false && matrix[closestIndex][i] != INF) {
					if (matrix[closestIndex][i] < distance[i].weight) {
						distance[i].weight = matrix[closestIndex][i];
					}
				}
			}

			count++;
		}
		puts("");
	}

	int getClosestVertexIndex() {
		int min = INF;
		int index;
		for (int i = 0; i < size; ++i) {
			if (visited[i] == false) {
				if (distance[i].weight < min) {
					min = distance[i].weight;
					index = i;
				}
			}
		}
		return index;
	}


};



int main() {
	Wgraph graph;
	graph.load("graph.txt");
	graph.display();
	puts("");

	cout << "DFS : "; graph.DFS('A'); puts("");
	cout << "BFS : "; graph.BFS('A'); puts("");
	puts("");

	cout << "Kruskal " << endl;
	graph.Kruskal();

	cout << "Prim" << endl;
	graph.Prim('A');
	return 0;
}