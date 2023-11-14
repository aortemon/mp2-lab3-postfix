#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

template <class T>
class Stack {

	T* _begin;
	T* _end;
	int size;

public:

	Stack() : size(100) {
		_begin = new T[size]{};
		_end = _begin;
	}

	Stack(int _size) : size(_size) {
		if (_size < 0) throw invalid_argument("Length should be non-negative integer");
		_begin = new T[size]{};
		_end = _begin;
	}


	~Stack() { delete[] _begin; }


	void push(T x) {
		if ((_end - _begin) == size) {
			size *= 2;
			T* tmp = new T[size]{};
			std::copy(_begin, _end, tmp);
			_end = tmp + (_end - _begin);
			delete[] _begin;
			_begin = tmp;
		}
		*_end = x;
		_end++;
	}


	T top() {
		if (!isEmpty()) return *(_end - 1);
		else throw out_of_range("Stack is empty");
	}


	T pop() {
		if (!isEmpty()) {
			T last = *(_end - 1);
			_end--;
			return last;
		}
		else throw out_of_range("Stack is empty");
	}

	bool isEmpty() { return _begin == _end; }


	int getSize() { return _end - _begin; }


	T* begin() { return _begin; }

	T* end() { return _end; } 


	bool operator==(const Stack& other) {
		if ((_end - _begin) != (other._end - other._begin)) return false;
		int s = _end - _begin;
		for (int i = 0; i < s; i++)
			if (_begin[i] != other._begin[i]) return false;
		return true;
	}


	friend ostream& operator<<(ostream& out, const Stack<T>& v) {
		out << "{ ";
		int s = v._end - v._begin;
		for (int i = s - 1; i >= 0; i--) out << v._begin[i] << " ";
		out << "}";
		return out;
	}
};

#endif // STACK_H