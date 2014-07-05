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
};

