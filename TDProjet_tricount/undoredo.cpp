#include "undoredo.h"


template <typename T>
undoredo<T>::undoredo(unsigned int depth)
{
	_depth = UNDOREDO_DEPTH;
	_p = 0;
	_rest = 0;
	if (depth > 0) _depth = depth;

	_stack = new T[_depth];
	/*
	for (int i = 0; i < _depth; i++)
	{
		T default_element{};
		_stack[i] = default_element;
	}*/
#ifdef DEBUG
	//std :: cout << _stack.size();
	std::cout << _depth;
#endif // DEBUG

}

template<typename T>
undoredo<T>::~undoredo()
{
	delete[] _stack;
	return;
}

template<typename T>
const int undoredo<T>::push(T& element) //use const T element cause a unexpect problem, that T::T(const) has been delete. dont know y.
{
	if (_p == 0)
	{
		_rest = 1;
		_p = _depth - 1;
		_stack[_depth - 1] = element;
	}
	else if (_p == _depth - 1)
	{
		for (int i = 0; i < _depth - 1; i++) _stack[i] = _stack[i + 1];
		if (_rest < _depth - 1)_rest++;
		_stack[_depth - 1] = element;
	}
	else if (_p < _depth - 1 && _p >= 0)
	{
		const int shift = _depth - 2 - _p;
		for (int j = _depth - 2; j >= 0; j--)
		{
			if (j - shift >= 0) _stack[j] = _stack[j - shift];
			//else _stack[j] = T{};
		}
		_rest = _depth - shift;
		_p = _depth - 1;
		_stack[_depth - 1] = element;
	}
	else return 1;
	return 0;
}

template<typename T>
const int undoredo<T>::redo(T& element)
{
	if (_p >= _depth - 1)return 1;
	_p++;
	element = _stack[_p];
	return 0;
}

template<typename T>
const int undoredo<T>::undo(T& element)
{
	if (_p <= _depth - _rest)return 1;
	//else if (_stack[_p - 1] == T{}) return 2;
	_p--;
	element = _stack[_p];
	return 0;
}



