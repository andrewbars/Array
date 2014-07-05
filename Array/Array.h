#pragma once
template<typename T>
class Array
{
	T** array;
	int length;
public:
	Array();
	Array(int len);
	Array(const Array<T> &that);
	~Array();
	int Length();
	void Resize(int size);
	void Add(T newItem);
	void Insert(T newItem, int ind);
	void RemoveLast();
	void Remove(int ind);
	int IndexOf(T item);
	int LastIndexOf(T item);
	T& operator[](int index);
};

