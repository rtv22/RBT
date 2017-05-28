#include <iostream>

using namespace std;

const bool BLACK = 1;
const bool RED = 0;

template <typename T>
struct Node
{
	T value;
	bool color;
	Node* left;
	Node* right;
	Node* parent;
};

template<typename T> 
class RBT
{
private:
	Node<T>* root;
	Node<T>* NIL;
public:
	RBT();
	~RBT();
	bool _color(const T&) const;
	Node<T>* _root()const;
	Node<T>* _NIL*()const;
	Node<T>* findNode(const T&);
	void deleteNode(Node<T>*);
	void rotateLeft(Node<T>*);
	void rotateRight(Node<T>*);
	void insert(const T&);
	void insertFixup(Node<T>*);
};

template <typename T>
RBT<T>::RBT()
{
	NIL = new Node<T>;
	NIL->parent = nullptr;
	NIL->left = nullptr;
	NIL->right = nullptr;
	NIL->color = BLACK;
	root = NIL;
}

template<typename T>
RBT<T>::~RBT()
{
	deleteNode(root);
}

template <typename T>
void RBT<T>::deleteNode(Node<T>* temp)
{
	if (!temp){
		return 0;
	}
	deleteNode(temp->left);
	deleteNode(temp->right);
	delete temp;
}

template<typename T>
bool RBT<T>::_color(const T& value)const
{
	return search(value)->color;
}

template <typename T>
Node<T>* _root()const
{
	return root;
}

template <typename T>
Node<T>* _NIL()const
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
	if (search(added))
	{
		std::cout << "This value's already added in the tree\n";
		return 0;
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
		return 0;
	}
	while (temp != NIL)
	{
		if (daughter->value == temp->value)
		{
			return 0;
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
	insertFix(daughter);
}

template<typename T>
void RBT<T>::insertFixup(Node<T> *x) 
{
	while (x != root && x->parent->color == RED) 
	{
		if (x->parent == x->parent->parent->left) 
		{
			Node *y = x->parent->parent->right;
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
				if (x == x->parent->right) {
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
				if (x == x->parent->left) {
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
		if (value == current->value)
			return current;
		else
		{
			if (value < current->value)
				current = current->left;
			else current = current->right;
		}
	}
	return 0;
}
