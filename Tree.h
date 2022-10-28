#pragma once

#include <string>
#include <sstream>

class Tree {
private:
	class Node {
		friend class Tree;
		friend class iterator;
	public:
		Node(int value);
		~Node();
	private:
		Node* Left;
		Node* Right;
		Node* Previous;
		int Value;
	};
public:
	class iterator {
		friend class Tree;
	private:
		iterator(Node* n, bool isend);
	public:
		const iterator operator++(int);
		const iterator operator--(int);
		
		bool operator==(const iterator&) const;
		bool operator!=(const iterator&) const;

		std::string operator*();
	private:
		Node* Cur;
		bool isEnd;
	};

	Tree();
	~Tree();

	void add(int value);
	unsigned int size() const;

	iterator begin() const;
	iterator end() const;
private:
	Node* Top;
	Node* Begin;
	Node* End;
	unsigned int Size;
};

