#pragma once
#include"BinaryTree.h"

template<class T>
class RBtree : public BinaryTree<T> {
private:
	BinaryNode<T>* nil = nullptr;

	BinaryNode<T>*& left_rotate(BinaryNode<T>* x) {
		BinaryNode<T>* y = x->right;
		
		x->right = y->left;
		y->left->parent = x;
		y->parent = x->parent;
		if (isRoot(x)) {
			this->root = y;
		}
		else {
			if (x == x->parent->left) {
				x->parent->left = y;
			}
			else {
				x->parent->right = y;
			}
		}
		y->left = x;
		x->parent = y;
		return y;
	}

	BinaryNode<T>*& right_rotate(BinaryNode<T>* y) {
		BinaryNode<T>* x = y->left;

		y->left = x->right;
		x->right->parent = y;
		x->parent = y->parent;
		if (isRoot(y)) {
			this->root = x;
		}
		else {
			if (y == y->parent->left) {
				y->parent->left = x;
			}
			else {
				y->parent->right = x;
			}
		}
		x->right = y;
		y->parent = x;
		return x;
	}

	void RB_fixup(BinaryNode<T>*& node) {
		//node has no uncle
		if (node->parent == nil) {
			node->setColor(black);
			return;
		}
		else if (node->parent->parent == nil) {
			return;
		}
		//node has an uncle
		else {
			BinaryNode<T>* uncle;
			//parent is left child
			if (node->parent == node->parent->parent->left) {
				uncle = node->parent->parent->right;
				//uncle is red
				if (uncle->color == red) {
					if (node->parent->parent->parent == nil) {
						node->parent->color = black;
						uncle->color = black;
					}
					else {
						node->parent->color = black;
						uncle->color = black;
						node->parent->parent->color = red;
						RB_fixup(node->parent->parent);
					}
				}
				//uncle is black
				else {
					if (node == node->parent->right) {
						BinaryNode<T>* r = left_rotate(node->parent);
						r->color = black;
						r->parent->color = red;
						right_rotate(r->parent);
					}
					else {
						node->parent->color = black;
						node->parent->parent->color = red;
						right_rotate(node->parent->parent);
					}
				}
			}
			//parent is right child
			else {
				uncle = node->parent->parent->left;
				//uncle is red
				if (uncle->color == red) {
					if (node->parent->parent->parent == nil) {
						node->parent->color = black;
						uncle->color = black;
					}
					else {
						node->parent->color = black;
						uncle->color = black;
						node->parent->parent->color = red;
						RB_fixup(node->parent->parent);
					}
				}
				//uncle is black
				else {
					if (node == node->parent->left) {
						BinaryNode<T>* r = right_rotate(node->parent);
						r->color = black;
						r->parent->color = red;
						left_rotate(r->parent);
					}
					else {
						node->parent->color = black;
						node->parent->parent->color = red;
						left_rotate(node->parent->parent);
					}
				}
			}
		}
	}

	bool isRoot(BinaryNode<T>* node) {
		return node->parent==nil;
	}

	void printSub(BinaryNode<T>* node) {
		if (node == nil) {
			return;
		}
		else {
			printSub(node->getLeft());
			cout << node->getKey() << ":"<<node->color<<"    ";
			printSub(node->getRight());
		}
	}

	BinaryNode<T>* insertSub(BinaryNode<T>*& p, BinaryNode<T>*& n, T key) {
		if (n == nil) {
			n = new BinaryNode<T>(key, red, nil, nil, p);
			return n;
		}
		else {
			if (n->getKey() == key) {
				cout << "can't insert the same key" << endl;
			}
			else if (n->getKey() > key) {
				return insertSub(n, n->left, key);
			}
			else {
				return insertSub(n, n->right, key);
			}
		}

	}

	void erase(BinaryNode<T>* node) {
		if (node == nil) {
			return;
		}
		else {
			erase(node->left);
			erase(node->right);
			delete node;
		}
	}

public:
	RBtree<T>() {
		nil = new BinaryNode<T>(-1, black, nullptr, nullptr, nullptr);
		this->root = nil;
	}
	void print() {printSub(this->root);}
	
	void search(T key) {
		if (this->isEmpty()) {
			cout << "empty" << endl;
		}
		else {
			BinaryNode<T>*& node = this->root;
			while (node != nil) {
				if (node->getKey() == key) {
					cout << "key exists" << endl;
					return;
				}
				else if (node->getKey() > key) {
					node = node->left;
				}
				else {
					node = node->right;
				}
			}
			cout << "doesn't exist" << endl;
		}
	}

	/*void insert(T key) {
		BinaryNode<T>* p = nil;
		BinaryNode<T>* node = this->root;
		while (node != nil) {
			if (node->getKey() == key) {
				cout << "key exists" << endl;
				return;
			}
			else if (node->getKey() > key) {
				p = node;
				node = node->left;
			}
			else {
				p = node;
				node = node->right;
			}
		}
		node = new BinaryNode<T>(key,red,nil, nil, p);
		if (this->root == nil) {
			this->root = node;
		}
		RB_fixup(node);
	}*/

	void insert(T key) {
		BinaryNode<T>* x = insertSub(nil, this->root, key);
		RB_fixup(x);
	}

	~RBtree() {
		erase(this->root);
	}
};