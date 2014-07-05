#include "Array.h"

template <typename T>
Array<T>::Array()
{
	length = 10;
	array = new T*[length];
	for (int i = 0; i < length; i++)
	{
		array[i] = new T;
	}
}
template <typename T>
Array<T>::Array(int len)
{
	length = len;
	array = new T*[length];
	for (int i = 0; i < length; i++)
	{
		array[i] = new T;
	}
}

template <typename T>
Array<T>::Array(const Array<T> &that)
{
	length = that.length;
	array = new T*[length];
	for (int i = 0; i < length; i++)
	{
		array[i] = new T;
		*array[i] = *that.array[i];
	}
}

template <typename T>
Array<T>::~Array()
{
	if (array)
	{
		for (int i = 0; i < length)
		{
			if (array[i])
				delete array[i];
		}
		delete[]array;
	}
}

template <typename T>
int Array<T>::Length()
{
	return length;
}

template <typename T>
void Array<T>::Resize(int size)
{
	if (size>length)
	{
		T** tmp = new T*[size];
		for (int i = 0; i < length; i++)
		{
			tmp[i] = array[i];
		}
		for (int i = length; i < size; i++)
		{
			tmp[i] = new T;
		}
		delete[]array;
		array = tmp;
		length = size;
	}
}

template <typename T>
void Array<T>::Add(T newItem)
{
	Resize(length + 1);
	*array[length - 1] = newItem;
}

template <typename T>
void Array<T>::Remove(int ind)
{
	T** tmp = new T*[length - 1];
	int k = 0;
	for (int i = 0; i < length; i++)
	{
		if (i == ind)
		{
			delete array[i];
			k++;
		}
		tmp[i] = array[i + k];
	}
	delete[]array;
	array = tmp;
	length -= 1;
}

template <typename T>
void Array<T>::RemoveLast()
{
	Remove(length - 1);
}
