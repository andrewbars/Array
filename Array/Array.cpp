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
