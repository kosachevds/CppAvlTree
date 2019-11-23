#ifndef NODE_H

#include <memory>
#include <algorithm>

template <typename T>
class Node;

template <typename T>
using NodePtr = std::shared_ptr<Node<T>>;

template <typename T>
class Node
{
public:
	explicit Node(T key);
	static NodePtr<T> insert(NodePtr<T>& root, T key);
	static NodePtr<T> remove(NodePtr<T>& root, T key);
	static NodePtr<T> find(NodePtr<T> root, T key);
	static uint8_t heightOrZero(const NodePtr<T>& node);
private:
	T key;
	uint8_t height;
	NodePtr<T> left;
	NodePtr<T> right;

	int bfactor() const;
	void fixHeight();
	static NodePtr<T> rotateRight(NodePtr<T>& p);
	static NodePtr<T> rotateLeft(NodePtr<T>& q);
	static NodePtr<T> balance(NodePtr<T>& p);
	static NodePtr<T> findMin(NodePtr<T> root);
	static NodePtr<T> removeMin(NodePtr<T>& root);
};

////////////////////////////////////////////////////////////////////////////////

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
		// TODO: ?
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

#endif // !NODE_H
