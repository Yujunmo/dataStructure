#include<iostream>
#include<queue>
#include<vector>
#define BUF_SIZE 20

using namespace std;

class node {
private:
	char ch;
	int freq;
	node* left;
	node* right;
	int seq;

public:
	node(char myCh, int myFreq, int mySeq) :
		ch(myCh), freq(myFreq), seq(mySeq), left(nullptr), right(nullptr) {
	}

	void setLeft(node* l) { left = l; }
	void setRight(node* r) { right = r; }

	char getChar() { return ch; }
	int getFreq() const { return freq; }
	int getSeq() const { return seq; }
	node*& getLeft() { return left; }
	node*& getRight() { return right; }

	bool isLeaf() { return left == nullptr && right == nullptr; }


	vector<char> code;

};

class cmp {
public:
	bool operator()(node* a, node* b) {
		return  a->getFreq() > b->getFreq();
	}
};

class Huffman {
private:
	node* root;
	priority_queue<node*, vector<node*>, cmp > minheap;
	int nodeCnt;

	void printSub(node* n) {
		if (n->isLeaf()) {
			printf("%c : ", n->getChar());
			for (int i = 0; i < n->code.size(); ++i) {
				printf("%c", n->code[i]);
			}
			puts("");
		}
		else {
			printSub(n->getLeft());
			printSub(n->getRight());
		}
	}

public:
	Huffman() :root(nullptr) {}

	void makeTree(char* data, int* freq, int* seq, int size) {
		for (int i = 0; i < size; ++i) {
			minheap.push(new node(data[i], freq[i], seq[i]));
		}
		nodeCnt = minheap.size();

		while (minheap.size() > 1) {
			node* n1 = minheap.top();
			minheap.pop();
			node* n2 = minheap.top();
			minheap.pop();

			//순서 유지하기 위해 seq 사용
			node* newNode = new node('-', n1->getFreq() + n2->getFreq(), n1->getSeq());
			if (n1->getSeq() < n2->getSeq()) {
				newNode->setLeft(n1);
				newNode->setRight(n2);
			}
			else {
				newNode->setLeft(n2);
				newNode->setRight(n1);
			}
			minheap.push(newNode);
		}
		root = minheap.top();
	}


	void makeCode() {
		root->code.push_back('b');
		makeCodeSub(root);
	}

	void makeCodeSub(node* n) {
		if (n->isLeaf()) {
			return;
		}
		else {
			node*& left = n->getLeft();
			node*& right = n->getRight();

			if (left != nullptr) {
				//부모 노드 가변코드 복사
				left->code.assign(n->code.begin(), n->code.end());
				left->code.push_back('1');
				makeCodeSub(left);
			}
			if (right != nullptr) {
				//부모 노드 가변코드 복사
				right->code.assign(n->code.begin(), n->code.end());
				right->code.push_back('0');
				makeCodeSub(right);
			}
		}
	}

	void print() { printSub(root); }

	void doHuffman(char* data, int* freq, int* seq, int size) {
		makeTree(data, freq, seq, size);
		makeCode();
		print();
	}
};


int main()
{
	char data[] = { 'a','b','c','d','e' };
	int freq[] = { 4,6,8,12,15 };
	int seq[] = { 1,2,3,4,5 };
	int size = sizeof(data) / sizeof(char);

	Huffman huff;
	huff.doHuffman(data, freq, seq, size);

}