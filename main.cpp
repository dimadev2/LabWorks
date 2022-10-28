#define CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Tree.h"

int main(void) {
	Tree t = Tree();
	
	t.add(0);
	t.add(2);
	t.add(-2);
	t.add(1);
	t.add(-1);
	t.add(3);
	t.add(-3);

	std::cout << t.size() << std::endl;

	Tree::iterator b = t.begin();
	Tree::iterator e = t.end();

	std::cout << (b == e) << std::endl;
	std::cout << (b != e) << std::endl;

	for (auto iter = t.begin(); iter != t.end(); iter++) {
		std::cout << *iter << " ";
	}
	std::cout << std::endl;

	for (auto iter = t.end(); iter != t.begin(); iter--) {
		std::cout << *iter << " ";
	}
	std::cout << "\nExcept situation: not get the begin - " << *b << "\n\n";

	std::cout << "Begin: " << *b << "\tEnd: " << *e << std::endl;
	std::cout << "Add to tree -8 and 8\n";
	t.add(-8);
	t.add(8);
	std::cout << "Begin: " << *b << "\tEnd: " << *e << std::endl;
	std::cout << "b--	e++" << std::endl;
	b--;
	e++;
	std::cout << "Begin: " << *b << "\tEnd: " << *e << std::endl;

	return 0;
}