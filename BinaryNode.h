#pragma once
#include<iostream>
using namespace std;
enum { black, red };

template<class T>
class BinaryNode {
private:
	T key;
public:
	BinaryNode<T>* left;
	BinaryNode<T>* right;
	BinaryNode<T>* parent;
	int color; // 0 : black, 1 : red
public:
	BinaryNode(T k, BinaryNode<T>* l, BinaryNode<T>* r, BinaryNode<T>* p)
		:key(k), left(l), right(r), parent(p) {}

	BinaryNode(T k, int c, BinaryNode<T>* l, BinaryNode<T>* r, BinaryNode<T>* p)
		:key(k), color(c), left(l), right(r), parent(p) {}

	void setLeft(BinaryNode<T> l) { left = l; }
	void setRight(BinaryNode<T> r) { right = r; }
	void setParent(BinaryNode<T> p) { parent = p; }
	void setColor(int c) { color = c; }

	BinaryNode<T>* getLeft() { return left; }
	BinaryNode<T>* getRight() { return right; }
	BinaryNode<T>* getParent() { return parent; }
	T getKey() { return key; }
	bool isLeaf() { return left == nullptr && right == nullptr; }
};
