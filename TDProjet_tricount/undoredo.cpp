#include "undoredo.h"


template <typename T>
undoredo<T>::undoredo(unsigned int depth)
{
	_p = 0;
	if (depth > 0) _depth = depth;
	else _depth = 3;

	T[_depth] _stack;
	for (int i = 0; i < depth; i++)
	{
		T default_element{};
		_stack[i] = default_element;
	}
#ifdef DEBUG
	//std :: cout << _stack.size();
	std::cout << _depth;
#endif // DEBUG

}


template<typename T>
int undoredo<T>::push(const T element)
{
	_stack[_depth - 1] = element;

	if (_p == _depth - 1)
	{
		for (int i = 0; i < _depth - 1; i++)
		{
			_stack[i] = _stack[i + 1];
		}
	}
	else if (_p < _depth - 1 && _p >= 0)
	{
		int i = _p, j = _depth - 2;
		for (; j >= 0; j--)
		{
			if (i >= 0)
			{

				i--;
			}
			else 
		}
	}
	else return 1;
	return 0;
}

template<typename T>
int undoredo<T>::redo(T& element)
{
	if (_p >= _depth - 1)return 1;
	_p++;
	element = _stack[_p];
	return 0;
}

template<typename T>
int undoredo<T>::undo(T& element)
{
	if (_p <= 0)return 1;
	_p--;
	element = _stack[_p];
	return 0;
}



