#pragma once
#include <cstdlib>
template<typename T>
class Array
{
	T** array;
	int length;
	void Sorting(int bot, int top);
public:
	Array();
	Array(int len);
	Array(const Array<T> &that);
	~Array();
	int Length();
	Array& Resize(int size);
	Array& Add(T newItem);
	Array& Insert(T newItem, int ind);
	Array& RemoveLast();
	Array& Remove(int ind);
	Array& Sort();
	Array& Reverse();
	Array& Shuffle();
	int IndexOf(T item);
	int LastIndexOf(T item);
	T& operator[](int index);
	bool operator==(Array<T> that);
};

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
		for (int i = 0; i < length;i++)
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
Array<T>& Array<T>::Resize(int size)
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
	return *this;
}

template <typename T>
Array<T>& Array<T>::Add(T newItem)
{
	Resize(length + 1);
	*array[length - 1] = newItem;
	return *this;
}
template <typename T>
Array<T>& Array<T>::Insert(T newItem, int ind)
{
	T** tmp = new T*[length + 1];
	int k = 0;
	for (int i = 0; i < length; i++)
	{
		if (i == ind)
		{
			tmp[i] = new T;
			*tmp[i] = newItem;
			k++;
		}
		tmp[i + k] = array[i];
	}
	delete[]array;
	array = tmp;
	length += 1;
	return *this;
}

template <typename T>
Array<T>& Array<T>::Remove(int ind)
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
	return *this;
}

template <typename T>
Array<T>& Array<T>::RemoveLast()
{
	return Remove(length - 1);
}

template <typename T>
Array<T>& Array<T>::Sort()
{
	Sorting(0, length - 1);
	return *this;
}

template <typename T>
void Array<T>::Sorting(int down, int up)
{
	int i = down, j = up;
	int m = (up - down) / 2 + down;

	while (i <= j)
	{
		while (*array[i] < *array[m])
			i++;
		while (*array[j] > *array[m])
			j--;

		if (i <= j)
		{
			T* tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;
			i++; j--;
		}
	}
	if (m < up)
		Sorting(m + 1, up);
	if (m>down)
		Sorting(down, m);
}

template <typename T>
Array<T>& Array<T>::Reverse()
{
	T** tmp=new T*[length];
	for (int i = 0; i < length; i++)
	{
		tmp[i] = array[length - 1 - i];
	}
	delete[]array;
	array = tmp;
	return *this;
}
template <typename T>
Array<T>& Array<T>::Shuffle()
{
	for (int i = 0; i < length; i++)
	{
		int pick = rand() % length;
		T* tmp = array[i];
		array[i] = array[pick];
		array[pick] = tmp;
	}
	return *this;
}

template <typename T>
int Array<T>::IndexOf(T item)
{
	for (int i = 0; i < length; i++)
	{
		if (*array[i] == item)
		{
			return i;
		}
	}
	return -1;
}

template <typename T>
int Array<T>::LastIndexOf(T item)
{
	for (int i = length-1; i >= 0; i--)
	{
		if (*array[i] == item)
		{
			return i;
		}
	}
	return -1;
}

template <typename T>
T& Array<T>::operator[](int index)
{
	if (index > length - 1 || index<0)
	{
		throw "Index out of bonds!!!";
	}
	else
	{
		return *array[index];
	}
}

template <typename T>
bool Array<T>::operator==(Array<T> that)
{
	if (length != that.length)
		return false;
	else
	{
		for (int i = 0; i < lengthi++)
		{
			if (array[i] != that.array[i])
				return false
		}
		return true;
	}
}
