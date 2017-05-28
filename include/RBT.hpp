#include <iostream>

const bool BLACK = 1;
const bool RED = 0;


template<typename T> 
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
	bool _color(const T&) const;
	Node<T>* _root()const;
	Node<T>* _NIL()const;
	void rotateLeft(Node<T>* current);
	void rotateRight(Node<T> *current);
	void insertFixup(Node<T>* current);
	void insert(const T& added);
	Node<T>* search(const T& value)const;
};
template<typename T>
	RBT<T>::RBT()
	{
		NIL = new Node<T>;
		NIL->left = NIL->parent = NIL->right = nullptr;
		NIL->color = BLACK;
		root = NIL;
	}

	template<typename T>
	bool RBT<T>::_color(const T& value)const
	{
		return search(value)->color;
	}
	template<typename T>
	Node<T>* RBT<T>::_root()const
	{
		return root;
	}

	template<typename T>
	Node<T>* RBT<T>::_NIL()const
	{
		return NIL;
	}

	template<typename T>
	void RBT<T>::rotateLeft(Node<T>* current)
	{
		Node<T>* temp = current->right;
		current->right = temp->left;
		if (temp->left != NIL)
			temp->left->parent = current;
		if (temp != NIL)
			temp->parent = current->parent;
		if (current->parent != NIL)
		{
			if (current == current->parent->left)
				current->parent->left = temp;
			else
				current->parent->right = temp;
		}
		else
		{
			root = temp;
		}
		temp->left = current;
		if (current != NIL)
			current->parent = temp;
	}

	template<typename T>
	void RBT<T>::rotateRight(Node<T> *current)
	{
		Node<T> *temp = current->left;
		current->left = temp->right;
		if (temp->right != NIL)
			temp->right->parent = current;
		if (temp != NIL)
			temp->parent = current->parent;
		if (current->parent != NIL)
		{
			if (current == current->parent->right)
				current->parent->right = temp;
			else
				current->parent->left = temp;
		}
		else
		{
			root = temp;
		}
		temp->right = current;
		if (current != NIL)
			current->parent = temp;
	}

	template<typename T>
	void RBT<T>::insertFixup(Node<T>* current)
	{
		while (current != root && current->parent->color == RED)
		{
			if (current->parent == current->parent->parent->left)
			{
				Node<T>* temp = current->parent->parent->right;
				if (temp->color == RED)
				{
					current->parent->color = BLACK;
					temp->color = BLACK;
					current->parent->parent->color = RED;
					current = current->parent->parent;
				}

				else
				{
					if (current == current->parent->right)
					{
						current = current->parent;
						rotateLeft(current);
					}
					current->parent->color = BLACK;
					current->parent->parent->color = RED;
					rotateRight(current->parent->parent);
				}
			}

			else
			{
				Node<T>* temp = current->parent->parent->left;
				if (temp->color == RED)
				{
					current->parent->color = BLACK;
					temp->color = BLACK;
					current->parent->parent->color = RED;
					current = current->parent->parent;
				}
				else
				{
					if (current == current->parent->left)
					{
						current = current->parent;
						rotateRight(current);
					}
					current->parent->color = BLACK;
					current->parent->parent->color = RED;
					rotateLeft(current->parent->parent);
				}
			}
		}
		root->color = BLACK;
	}

	template<typename T>
	void RBT<T>::insert(const T& added)
	{
		if (search(added))
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
				return;

			parent = temp;
			if (added < temp->value)
				temp = temp->left;
			else
				temp = temp->right;
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
	Node<T>* RBT<T>::search(const T& value)const
	{
		Node<T>* current = root;
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
