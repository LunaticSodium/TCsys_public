#pragma once

template <typename T>
class undoredo
{
private:
	unsigned int _p,_depth;
	T* _stack;
public:
	undoredo(unsigned int depth);
	int push(const T element);
	int undo(T& element);				//modify by input instead of return value
	int redo(T& element);
	bool end();
};

