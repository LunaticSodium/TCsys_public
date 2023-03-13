#pragma once
#include <vector>

template <typename T>

class undoredo
{
private:
	unsigned int _p,_depth;
	vector<T> _stack;
public:
	undoredo(unsigned int depth);
	int push(const T element);
	int undo(T& element);
	int redo(T& element);
	bool end();
};

