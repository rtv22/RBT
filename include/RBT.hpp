#include <iostream>

using namespace std;

const bool BLACK = 1;
const bool RED = 0;

template <typename T>
struct Node
{
	T value;
	bool color;
	Node<T>* left;
	Node<T>* right;
	Node<T>* parent;
};

template<typename T>
class RBT
{
private:
	Node<T>* root;
	Node<T>* NIL;
public:
	RBT();
	bool _color(const T&);
	Node<T>* _root();
	Node<T>* _NIL();
	Node<T>* findNode(const T&);
	void _delete(Node<T> *node);
	void DelNode(Node<T>*node);
	void rotateLeft(Node<T>*);
	void rotateRight(Node<T>*);
	void insert(const T&);
	void insertFixup(Node<T>*);
};

template <typename T>
RBT<T>::RBT()
{
	NIL = new Node<T>;
	NIL->left = NIL->parent = NIL->right = nullptr;
	NIL->color = black;
	root = NIL;
}

template<typename T>
bool RBT<T>::_color(const T& value)
{
	return findNode(value)->color;
}

template <typename T>
Node<T>* RBT<T>::_root()
{
	return root;
}

template <typename T>
Node<T>* RBT<T>::_NIL()
{
	return NIL;
}

template<typename T>
void RBT<T>::rotateLeft(Node<T> *x)
{
	Node<T> *y = x->right;
	x->right = y->left;
	if (y->left != NIL)
	{
		y->left->parent = x;
	}
	if (y != NIL)
	{
		y->parent = x->parent;
	}
	if (x->parent)
	{
		if (x == x->parent->left)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
	}
	else
	{
		root = y;
	}
	y->left = x;
	if (x != NIL)
	{
		x->parent = y;
	}
}

template<typename T>
void RBT<T>::rotateRight(Node<T> *x) {
	Node<T> *y = x->left;
	x->left = y->right;
	if (y->right != NIL)
	{
		y->right->parent = x;
	}
	if (y != NIL)
	{
		y->parent = x->parent;
	}
	if (x->parent)
	{
		if (x == x->parent->right)
		{
			x->parent->right = y;
		}
		else
		{
			x->parent->left = y;
		}
	}
	else
	{
		root = y;
	}
	y->right = x;
	if (x != NIL)
	{
		x->parent = y;
	}
}

template <typename T>
void RBT<T>::insert(const T& added)
{
	if (findNode(added))
	{
		std::cout << "This value's already added in the tree\n";
		return;
	}
	Node<T>* daughter = new Node<T>;
	daughter->value = added;
	daughter->color = RED;
	daughter->left = daughter->right = daughter->parent = NIL;
	Node<T>* parent = NIL;
	Node<T>* temp = root;
	if (root == NIL)
	{
		root = daughter;
		root->color = BLACK;
		return;
	}
	while (temp != NIL)
	{
		if (daughter->value == temp->value)
		{
			return;
		}
		parent = temp;
		if (added < temp->value)
		{
			temp = temp->left;
		}
		else
		{
			temp = temp->right;
		}
	}
	if (added < parent->value)
	{
		parent->left = daughter;
	}
	else
	{
		parent->right = daughter;

	}
	daughter->parent = parent;
	insertFixup(daughter);
}

template<typename T>
void RBT<T>::insertFixup(Node<T> *x)
{
	while (x != root && x->parent->color == RED)
	{
		if (x->parent == x->parent->parent->left)
		{
			Node<T> *y = x->parent->parent->right;
			if (y->color == RED)
			{
				/* uncle is RED */
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else
			{
				/* uncle is BLACK */
				if (x == x->parent->right) 
				{
					/* make x a left child */
					x = x->parent;
					rotateLeft(x);
				}
				/* recolor and rotate */
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				rotateRight(x->parent->parent);
			}
		}
		else
		{
			/* mirror image of above code */
			Node<T> *y = x->parent->parent->left;
			if (y->color == RED)
			{
				/* uncle is RED */
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else
			{
				/* uncle is BLACK */
				if (x == x->parent->left) 
				{
					x = x->parent;
					rotateRight(x);
				}
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				rotateLeft(x->parent->parent);
			}
		}
	}
	root->color = BLACK;
}

template <typename T>
Node<T>* RBT<T>::findNode(const T& data)
{

	/*******************************
	*  find node containing data  *
	*******************************/

	Node<T> *current = root;
	while (current != NIL)
	{
		if (data == current->value)
			return current;
		else
		{
			if (data < current->value)
			{
				current = current->left;
			}
			else
				current = current->right;
		}
	}
	return 0;
}
