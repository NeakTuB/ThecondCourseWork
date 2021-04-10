#pragma once
#include <iostream>

template<class T>
class List {
	T** arr;
	size_t _size;
public:
	List() {
		arr = new T *[_size = 0];
	}

	void push(T* obj) {
		arr = (T * *)realloc(arr, (++_size) * sizeof(T*));
		arr[_size - 1] = obj;
	}

	void resize(size_t new_size) {
		arr = (T * *)realloc(arr, (_size = new_size) * sizeof(T*));
	}

	size_t size() {
		return _size;
	}

	T*& operator [](size_t ind) {
		_ASSERT(ind < _size);
		if (0 <= ind && ind < _size)
			return arr[ind];
	}

	void erase(size_t ind) {
		if (ind >= this->size())
			return;

		for (size_t i = ind; i < this->size() - 1; ++i) {
			arr[i] = arr[i + 1];
			arr[i]->num = i;
		}

		resize(_size - 1);
	}

	int find(std::string name) {
		for (size_t i = 0; i < _size; ++i) {
			if (arr[i]->full_name == name)
				return (int)i;
		}

		return -1;
	}

	T** begin() {
		return arr;
	}

	T** end() {
		return arr + _size;
	}

};
