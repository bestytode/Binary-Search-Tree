#include <iostream>
#include "BST.h"

/*	Test BST Structure
		 5
	   /   \
	  2     8
	 / \   / \
	1   3 6   9
		 \ \
		  4 7
*/

int main()
{
	// Init tree with initilizer list
	BinarySearchTree<int> tree = { 5, 8, 6, 7, 2, 3, 1, 9, 4 };

	// 1. expect to print 5 2 1 3 4 8 6 7 9
	tree.pre_order();
	std::cout << "\n";

	// 2. expect to print 1 2 3 4 5 6 7 8 9
	std::cout << tree << "\n"; // same as tree.in_order();

	// 3. expect to print 1 4 3 2 7 6 9 8 5
	tree.post_order();
	std::cout << "\n";

	// 4. expect to print 5 2 8 1 3 6 9 4 7 
	tree.level_order();
	std::cout << "\n";
	
	tree.erase(5);
	tree.insert(10);

	// 5. expect to print 1 2 3 4 6 7 8 9 10
	std::cout << tree << "\n";

	std::cout << "min value is: " << tree.minValue() << "\n";
	std::cout << "max value is: " << tree.maxValue() << "\n";

	
}