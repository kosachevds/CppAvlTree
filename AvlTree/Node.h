#ifndef NODE_H

#include <memory>

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

#endif // !NODE_H
