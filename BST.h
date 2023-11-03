#pragma once

#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <queue>

// Simple structure Node for creating tree data structure
template<typename T>
struct Node
{
	// Constructors
	Node() :left(nullptr), right(nullptr), value(0) {}
	Node(T _value) :left(nullptr), right(nullptr), value(_value) {}
	Node(T _value, Node<T>* _left, Node<T>* _right)
		:left(_left), right(_right), value(_value) {}
	
	// Destructor
	~Node() {
		delete left;
		delete right;
	}

	friend std::ostream& operator << (std::ostream& out, const Node& node) {
		return out << node.value;
	}

	// variables
	Node<T>* left;
	Node<T>* right;
	T value;
};

// Binary search tree data structure with insert, erase utility functions, etc.
template<typename T>
class BinarySearchTree
{
public:
	using pointer = BinarySearchTree<T>*;
	using const_pointer = const BinarySearchTree<T>;
	using reference = BinarySearchTree<T>&;
	using const_reference = const BinarySearchTree<T>&;

public:
	// Constructors
	BinarySearchTree() :root(nullptr) {}
	BinarySearchTree(std::initializer_list<T>list) {
		for (T _value : list) {
			insert(_value);
		}
	}

	void insert(T _value) {
		Node<T>* new_node = new Node<T>(_value);
		if (this->root == nullptr) {
			this->root = new_node;
			return;
		}

		Node<T>* current = this->root;
		while (true) {
			if (new_node->value <= current->value) {
				if (current->left == nullptr) {
					current->left = new_node;
					return;
				}
				else
					current = current->left;
			}
			else {
				if (current->right == nullptr) {
					current->right = new_node;
					return;
				}
				else
					current = current->right;
			}
		}
	}
	// Modify the erase function to inform the user about deletion.
	void erase(T _value) {
		// check if the value exists in the tree.
#ifdef _DEBUG
		bool found = is_contain(this->root, _value);
		if (found) {
			this->root = erase_recursive(this->root, _value);
			std::cout << _value << " has been removed from the tree.\n";
		}
		else 
			std::cout << _value << " not found in the tree.\n";
#else
        // In release mode, just perform the deletion without checks.
		this->root = erase_recursive(this->root, _value);
#endif
	}

	T minValue() const {
		if (this->root == nullptr)
			return -1;

		Node<T>* current = root;
		while (current && current->left) {
			current = current->left;
		}
		return current->value;
	}
	T maxValue() const {
		if (this->root == nullptr)
			return -1;

		Node<T>* current = root;
		while (current && current->right) {
			current = current->right;
		}
		return current->value;
	}

	void pre_order() const {
		pre_order_recursive(root);
	}
	void in_order() const {
		in_order_recursive(root);
	}
	void post_order() const {
		post_order_recursive(root);
	}
	void level_order() const {
		level_order_recursive(root);
	}

	friend std::ostream& operator << (std::ostream& out, const BinarySearchTree<T>& tree) {
		if (tree.root == nullptr)
			return out;

		tree.in_order();
		return out;
	}

private:
	void pre_order_recursive(Node<T>* node) const {
		if (node) {
			std::cout << *node << " ";  
			pre_order_recursive(node->left);
			pre_order_recursive(node->right);
		}
	}
	void in_order_recursive(Node<T>* node) const {
		if (node) {
			in_order_recursive(node->left);
			std::cout << *node << " ";
			in_order_recursive(node->right);
		}
	}
	void post_order_recursive(Node<T>* node) const {
		if (node) {
			post_order_recursive(node->left);
			post_order_recursive(node->right);
			std::cout << *node << " ";
		}
	}
	void level_order_recursive(Node<T>* node) const {
		if (root == nullptr)
			return;

		// A std::queue containing pointers and push the root to queue first
		std::queue<Node<T>*>q;
		q.push(root);

		while (!q.empty()) {
			int length = q.size();
			for (int i = 0; i < length; ++i) {
				auto node = q.front();
				q.pop();
				std::cout << *node << " ";

				if (node->left) q.push(node->left);
				if (node->right) q.push(node->right);
			}
		}
	}

	// the return node is about to change the state (which is vital here)
	Node<T>* erase_recursive(Node<T>* root, T _value)
	{
		if (root == nullptr) 
			return root;

		// Recursive case: first find the node to delete
		if (_value < root->value)
			root->left = erase_recursive(root->left, _value);
		else if (_value > root->value)
			root->right = erase_recursive(root->right, _value);
		else {
			// root->value is the value to be deleted

			// Case 1: Node with only one child or no child
			if (root->left == nullptr) {
				Node<T>* temp = root->right;
				delete root;
				return temp;
			}
			else if (root->right == nullptr) {
				Node<T>* temp = root->left;
				delete root;
				return temp;
			}

			// Case 2: Node with two children
			Node<T>* temp = min_value_node(root->right); // find the node with smallest value in right subtree of current node
			root->value = temp->value; // replace node with in_order successor
			root->right = erase_recursive(root->right, temp->value);  // remove the in-order successor node from the right subtree.
		}
		return root;
	}

	Node<T>* min_value_node(Node<T>* node) {
		Node<T>* current = node;
		while (current->left) {
			current = current->left;
		}
		return current;
	}

	// Function to check if a value exists in the BST.
	bool is_contain(Node<T>* root, T _value) {
		if (root == nullptr)
			return false;

		if (_value < root->value) 
			return is_contain(root->left, _value);
		else if (_value > root->value) 
			return is_contain(root->right, _value);
		else 
			return true;
	}

private:
	Node<T>* root;
};