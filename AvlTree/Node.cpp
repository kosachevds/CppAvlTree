#include "Node.h"

#include <algorithm>

template <typename T>
Node<T>::Node(T key)
	: key(key), height(1), left(nullptr), right(nullptr) { }

template <typename T>
uint8_t Node<T>::heightOrZero(const NodePtr<T>& node)
{
	if (node == nullptr) {
		return 0;
	}
	return node->height;
}

template <typename T>
NodePtr<T> Node<T>::find(NodePtr<T> root, T key)
{
	if (root == nullptr) {
		return nullptr;
	}
	if (key < root->key) {
		return find(root->left, key);
	}
	if (key > root->key) {
		return find(root->right, key);
	}
	return root;
}

template <typename T>
NodePtr<T> Node<T>::remove(NodePtr<T>& root, T key)
{
	// TODO: check function
	if (root == nullptr) {
		return nullptr;
	}
	if (key < root->key) {
		root->left = remove(root->left, key);
	}
	else if (key > root->key) {
		root->right = remove(root->right, key);
	}
	else {
		if (root->right == nullptr) {
			return root->left;
		}
		auto q = root->left;
		auto r = root->right;
		auto min_node = findMin(r);
		min_node->right = removeMin(r);
		min_node->left = q;
		return balance(min_node);
	}
	return balance(root);
}

template <typename T>
NodePtr<T> Node<T>::insert(NodePtr<T>& root, T key)
{
	if (root == nullptr) {
		root = std::make_shared<Node>(key);
		return root;
	}
	if (key < root->key) {
		root->left = insert(root->left, key);
	}
	else {
		root->right = insert(root->right, key);
	}
	return balance(root);
}

template <typename T>
NodePtr<T> Node<T>::findMin(NodePtr<T> root)
{
	// TODO: ?
	if (root->left == nullptr) {
		return root;
	}
	return findMin(root->left);
}

template <typename T>
NodePtr<T> Node<T>::removeMin(NodePtr<T>& root)
{
	if (root->left == nullptr) {
		return root->right;
	}
	root->left = removeMin(root->left);
	return balance(root);
}

template <typename T>
NodePtr<T> Node<T>::balance(NodePtr<T>& p)
{
	p->fixHeight();
	if (p->bfactor() == 2) {
		// Big Left rotate
		if (p->right->bfactor() < 0) {
			p->right = rotateRight(p->right);
		}
		return rotateLeft(p);
	}
	if (p->bfactor() == -2) {
		// Big Right rotate
		if (p->left->bfactor() > 0) {
			p->left = rotateLeft(p->left);
		}
		return rotateRight(p);
	}
	return p;
}

template <typename T>
int Node<T>::bfactor() const
{
	return heightOrZero(this->right) - heightOrZero(this->left);
}

template <typename T>
void Node<T>::fixHeight()
{
	auto left_height = heightOrZero(this->left);
	auto right_height = heightOrZero(this->right);
	this->height = std::max(left_height, right_height) + 1;
}

template <typename T>
NodePtr<T> Node<T>::rotateRight(NodePtr<T>& p)
{
	auto q = p->left;
	p->left = q->right;
	q->right = p;
	p->fixHeight();
	q->fixHeight();
	return q;
}

template <typename T>
NodePtr<T> Node<T>::rotateLeft(NodePtr<T>& q)
{
	auto p = q->right;
	q->right = p->left;
	p->left = q;
	q->fixHeight();
	p->fixHeight();
	return p;
}

template class Node<int>;
