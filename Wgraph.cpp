#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stack>
#include<queue>
#define INF 9999
#define MAX 20
using namespace std;


class Wgraph {
protected:
	char vertices[MAX];
	int matrix[MAX][MAX];
	int size;
	bool visited[MAX];
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
};

int main() {
	Wgraph g;
	g.load("graph.txt");
	g.display();
	cout << endl;
	cout << "DFS : "; g.DFS('A');
	cout << endl;
	cout << "BFS : "; g.BFS('A');
}