#pragma once
#define UNDOREDO_DEPTH 4

template <typename T>
class undoredo
{
private:
	int _p,_rest,_depth;
	T* _stack;
public:
	undoredo(unsigned int depth);
	~undoredo();
	const int push(T& element);
	const int undo(T& element);				//modify by input instead of return value
	const int redo(T& element);
	//bool end();
};

