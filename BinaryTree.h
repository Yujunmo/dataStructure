#pragma once
#include"BinaryNode.h"

template<class T>
class BinaryTree {
protected:
	BinaryNode<T>* root;
	int height;

private:
	int getHeightSub(BinaryNode<T>* node) {
		if (node == nullptr) {
			return 0;
		}
		else {
			int left = getHeightSub(node->getLeft());
			int right = getHeightSub(node->getRight());
			return left > right ? left + 1 : right + 1;
		}
	}
	void printSub(BinaryNode<T>* node) {
		if (node == nullptr) {
			return;
		}
		else {
			printSub(node->getLeft());
			cout << node->getKey() << " ";
			printSub(node->getRight());
		}
	}
	void erase(BinaryNode<T>* n) {
		if (n == nullptr) {
			return;
		}
		else {
			erase(n->getLeft());
			erase(n->getRight());
			delete n;
		}
	}

public:
	BinaryTree<T>() {}
	BinaryTree<T>(BinaryNode<T>* myR) : root(myR), height(0) {}

	BinaryNode<T>* getRoot() { return root; }
	void setRoot(BinaryNode<T>* myR) { root = myR; }
	bool isEmpty() { return root == nullptr; }
	int getHeight() { return getHeightSub(root); }
	void print() {
		if (isEmpty()) { cout << "tree is empty " << endl; }
		printSub(root); \
	}
	~BinaryTree() { 
		//erase(root); 
	}

};
