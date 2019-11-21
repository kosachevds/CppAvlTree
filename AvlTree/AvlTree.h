#ifndef AVLTREE_H
#define AVLTREE_H
#include <memory>

template <typename T>
struct Node;

template <typename T>
using NodePtr = std::shared_ptr<Node<T>>;

template <typename T>
struct Node
{
    T key;
    uint8_t height;
    NodePtr<T> left;
    NodePtr<T> right;

    explicit Node(T key);
    int bfactor() const;
    void fixHeight();

    static NodePtr<T> rotateRight(NodePtr<T>& p);
    static NodePtr<T> rotateLeft(NodePtr<T>& q);
    static NodePtr<T> balance(NodePtr<T>& p);
    static uint8_t heightOrZero(const NodePtr<T>& node);
    static NodePtr<T> insert(NodePtr<T>& root, T key);
    static NodePtr<T> findMin(NodePtr<T> root);
    static NodePtr<T> find(NodePtr<T> root, T key);
    static NodePtr<T> removeMin(NodePtr<T>& root);
    static NodePtr<T> remove(NodePtr<T>& root, T key);
};

class Tree final
{
public:
	using KeyType = int;
	Tree() = default;
    void add(KeyType key);
    void remove(KeyType key);
    bool isContains(KeyType key) const;
    int getHeight() const;
	template <typename InputIterator>
	static Tree create(InputIterator begin, InputIterator end);
private:
    NodePtr<KeyType> root { nullptr };
};

template<typename InputIterator>
inline Tree Tree::create(InputIterator begin, InputIterator end)
{
	Tree tree;
	for (auto it = begin; it != end; ++it) {
		tree.add(*it);
	}
	return tree;
}

#endif // AVLTREE_H
