#include "Tree.h"

Tree::Node::Node(int value) {
	Left = nullptr;
	Right = nullptr;
	Previous = nullptr;
	Value = value;
}

Tree::Node::~Node() {
	delete Left;
	delete Right;
}

Tree::Tree() {
	Top = nullptr;
	Begin = nullptr;
	End = nullptr;
	Size = 0;
}

Tree::~Tree() {
	delete Top;
}

unsigned int Tree::size() const {
	return Size;
}

void Tree::add(int value) {
	Node* nw = new Node(value);
	if (Size == 0) {
		Top = nw;
		Begin = nw;
		End = nw;
	}
	else {
		Node* iter = Top;
		Node* prev = nullptr;
		while (iter != nullptr) {
			prev = iter;
			if (nw->Value >= iter->Value) {
				iter = iter->Right;
			}
			else {
				iter = iter->Left;
			}
		}

		if (nw->Value >= prev->Value) {
			prev->Right = nw;
		}
		else {
			prev->Left = nw;
		}

		nw->Previous = prev;

		Begin = Begin->Left ? Begin->Left : Begin;
		End = End->Right ? End->Right : End;
	}
	Size++;
}

Tree::iterator Tree::begin() const {
	return iterator(Begin, false);
}

Tree::iterator Tree::end() const {
	return iterator(End, true);
}

Tree::iterator::iterator(Node* n, bool isend) {
	Cur = n;
	isEnd = isend;
}

bool Tree::iterator::operator==(const Tree::iterator& iter) const {
	return (Cur == iter.Cur) && (isEnd == iter.isEnd);
}

bool Tree::iterator::operator!=(const Tree::iterator& iter) const {
	return !((*this) == iter);
}

const Tree::iterator Tree::iterator::operator++(int) {
	if (isEnd) {
		if (!Cur->Right) {
			return *this;
		}
		else {
			iterator ret = *this;
			isEnd = false;
			Cur = Cur->Right;
			while (Cur->Left) {
				Cur = Cur->Left;
			}
			return ret;
		}
	}

	iterator ret = *this;
	if (!Cur->Left && !Cur->Right && Cur->Previous) {
		if (Cur == Cur->Previous->Left) {
			Cur = Cur->Previous;
		}
		else {
			Node* iter = Cur;
			while (iter->Previous && iter != iter->Previous->Left) {
				iter = iter->Previous;				
			}
			if (!iter->Previous) {
				isEnd = true;				
			}
			else {
				Cur = iter->Previous;
			}
		}
	}
	else {
		if (!Cur->Right) {
			isEnd = true;
		}
		else {
			Cur = Cur->Right;
			while (Cur->Left) {
				Cur = Cur->Left;
			}
		}
	}

	return ret;
}

const Tree::iterator Tree::iterator::operator--(int) {
	if (isEnd) {
		isEnd = false;
		return *this;
	}
	
	iterator ret = *this;
	if (!Cur->Left && !Cur->Right && Cur->Previous) {
		if (Cur == Cur->Previous->Right) {
			Cur = Cur->Previous;
		}
		else {
			Node* iter = Cur;
			while (iter->Previous && iter != iter->Previous->Right) {
				iter = iter->Previous;
			}
			if (!iter->Previous) {
				// "Is begin" situation
			}
			else {
				Cur = iter->Previous;
			}
		}
	}
	else {
		if (!Cur->Left) {
			// "Is begin" situation
		}
		else {
			Cur = Cur->Left;
			while (Cur->Right) {
				Cur = Cur->Right;
			}
		}
	}

	return ret;
}

std::string Tree::iterator::operator*() {
	if (isEnd) {
		if (!Cur->Right) {
			return std::string("IS_END");
		}
		else {
			std::stringstream ss;
			ss << Cur->Value;
			std::string res;
			ss >> res;

			return res;
		}
	}
	else {
		std::stringstream ss;
		ss << Cur->Value;
		std::string res;
		ss >> res;
		
		return res;
	}
}
