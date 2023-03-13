#include "undoredo.h"

template <typename T>

undoredo<T>::undoredo(unsigned int depth)
{
	_p = depth;
	_depth = depth;
	vector<T> _stack{};
	for (int i = 0; i < depth; i++)
	{
		T default_element{};
		_stack.push_back(default_element);
	}
#ifdef DEBUG
	std :: cout << _stack.size();
	std::cout << _depth;
#endif // DEBUG

}

