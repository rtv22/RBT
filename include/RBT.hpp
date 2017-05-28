#include <iostream> 
#include <string> 
#include <fstream> 
#include <cstdint> 

using namespace std;

template <typename T>
struct Node
{
	Node *left;
	Node *right;
	T data;
};

template <typename T>
class BinaryTree;

template <typename T>
std::ostream& operator<<(std::ostream&, const BinaryTree<T>&);

template <typename T>
class BinaryTree
{
private:
	Node<T>*root;
	int count = 0;
public:
	BinaryTree();
	~BinaryTree();
	Node<T>* root_();
	unsigned int getCount()const;
	void insert_node(const T&x);
	void deleteNode(Node<T>* temp);
	Node<T> *find_node(const T&, Node<T>*)const;
	bool remove_element(Node<T>* parent, Node<T>* current, const T& val);
	bool deleteVal(const T& value);
	void writing(const std::string& filename)const;
	friend std::ostream& operator<<<>(std::ostream&, const BinaryTree<T>&);
};

template <typename T>
BinaryTree<T>::BinaryTree()
{
	root = nullptr;
}

template<typename T>
Node<T>* BinaryTree<T>::root_()
{
	return root;
}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
	deleteNode(root);
}

template <typename T>
unsigned int BinaryTree<T>::getCount()const
{
	return count;
}


template<typename T>
void BinaryTree<T>::insert_node(const T&x)
{
	if (find_node(x, root_())) return;
	Node<T>* MyTree = new Node<T>;
	MyTree->data = x;
	MyTree->left = MyTree->right = 0;
	Node<T>* buff = root;
	Node<T>* temp = root;
	while (temp)
	{
		buff = temp;
		if (x < temp->data)
			temp = temp->left;
		else
			temp = temp->right;
	}
	if (!buff)
		root = MyTree;
	else
	{
		if (x < buff->data)
			buff->left = MyTree;
		else
			buff->right = MyTree;
	}
	++count;
}

template<typename T>
Node<T>* BinaryTree<T>::find_node(const T& data, Node<T>* temp) const
{
	if (temp == 0 || data == temp->data)
		return temp;
	if (data > temp->data)
		return find_node(data, temp->right);
	else
		return find_node(data, temp->left);
}

template<typename T>
void BinaryTree<T>::writing(const std::string& filename)const
{
	ofstream file_1(filename);
	file_1 << count << "\t";
	output(file_1, root);
	file_1.close();
}

template<typename T>
void BinaryTree<T>::deleteNode(Node<T>* temp)
{
	if (!temp)
		return;
	if (temp->left)
	{
		deleteNode(temp->left);
		temp->left = nullptr;
	}

	if (temp->right)
	{
		deleteNode(temp->right);
		temp->right = nullptr;
	}
	delete temp;
}

template <typename T>
std::ostream& output(std::ostream& ost, const Node<T>* node, unsigned int level)
{
	if (!node)
		return ost;
	output(ost, node->right, level + 1);
	for (unsigned int i = 0; i < level; i++)
		ost << "\t";
	ost << node->data << std::endl;
	output(ost, node->left, level + 1);
	return ost;
}

template<typename T>
bool BinaryTree<T>::remove_element(Node<T>* parent, Node<T>* current, const T& val)
{
	if (!current) return false;
	if (current->data == val)
	{
		if (current->left == NULL || current->right == NULL) {
			Node<T>* temp = current->left;
			if (current->right) temp = current->right;
			if (parent) {
				if (parent->left == current) {
					parent->left = temp;
				}
				else {
					parent->right = temp;
				}
			}
			else {
				this->root = temp;
			}
		}
		else {
			Node<T>* validSubs = current->right;
			while (validSubs->left) {
				validSubs = validSubs->left;
			}
			T temp = current->data;
			current->data = validSubs->data;
			validSubs->data = temp;
			return remove_element(current, current->right, temp);
		}
		delete current;
		count--;
		return true;
	}
	if (current->data > val)
		return remove_element(current, current->left, val);
	else
		return remove_element(current, current->right, val);
}

template<typename T>
bool BinaryTree<T>::deleteVal(const T& value)
{
	return this->remove_element(NULL, root, value);
}


template <typename T>
std::ostream& operator<<(std::ostream& ost, const BinaryTree<T>& temp)
{
	output(ost, temp.root, 0);
	return ost;
}
