#pragma once
#include <cstdlib>
template<typename T>
class Array
{
	T** array;
	int length;
	void Sorting(int bot, int top);
	typedef bool(*Condition)(T);
public:
	Array();
	Array(int len);
	Array(const Array<T> &that);
	~Array();
	//Returns the length of the array
	int Length();
	//Returns, if array is empty
	bool IsEmpty();
	//Enlarge array to given size
	Array& Resize(int size);
	//Adds new item in the end of array
	Array& Add(T newItem);
	//Adds new item to the given pos
	Array& Insert(T newItem, int ind);
	//Removes last elemen
	Array& RemoveLast();
	//Removes given elem
	Array& Remove(int ind);
	//Sorts array in acsending order
	Array& Sort();
	//Reverses order of elements in array
	Array& Reverse();
	//Shuffles array
	Array& Shuffle();
	//Returns index of first occurrence of some element in Array
	int IndexOf(T item);
	// Returns index of last occurrence of some element in Array
	int LastIndexOf(T item);
	//Finds index of first element satisfying some conition.
	int IndexWhere(Condition f);
	T& operator[](int index);
	bool operator==(Array<T> that);
	//Returns a new array, which contains all elements of the original array, which satisfy some condition
	Array filter(Condition f);
	//Returns a new array, which contains all elements of the original array, which dont satisfy some condition
	Array filterNot(Condition f);
	//Checks if any element in array satisfy some condition
	bool Exists(Condition f);
	//Checks if all elements in array satisfy some condition
	bool ForAll(Condition f);
	//Creates a new array by applying givven function to original array
	template<typename U>
	Array<U> Map(U(*MapFunc)(T));
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
	if (length)
	{
		array = new T*[length];
		for (int i = 0; i < length; i++)
		{
			array[i] = new T;
		}
	}
}

template <typename T>
Array<T>::Array(const Array<T> &that)
{
	length = that.length;
	if (length)
	{
		array = new T*[length];
		for (int i = 0; i < length; i++)
		{
			array[i] = new T;
			*array[i] = *that.array[i];
		}
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
bool Array<T>::IsEmpty()
{
	return length==0;
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
template <typename T>
Array<T> Array<T>::filter(Condition f)
{
	int k = 0;
	for (int i = 0; i < length; i++)
	{
		if (!f(*array[i]))
			k++;
	}
	Array<T> tmp(length-k);
	k = 0;
	for (int i = 0; i < tmp.length; i++)
	{
		while(!f(*array[i+k]))
			k++;
		*tmp.array[i] = *array[i + k];
	}
	return tmp;
}
template <typename T>
Array<T> Array<T>::filterNot(Condition f)
{
	int k = 0;
	for (int i = 0; i < length; i++)
	{
		if (f(*array[i]))
			k++;
	}
	Array<T> tmp(length - k);
	k = 0;
	for (int i = 0; i < tmp.length; i++)
	{
		while (f(*array[i + k]))
			k++;
		*tmp.array[i] = *array[i + k];
	}
	return tmp;
}

template <typename T>
bool Array<T>::Exists(Condition f)
{
	for (int i = 0; i < length; i++)
	{
		if (f(array[i]))
			return true;
	}
	return false;
}

template <typename T>
bool Array<T>::ForAll(Condition f)
{
	for (int i = 0; i < length; i++)
	{
		if (!f(array[i]))
			return false;
	}
	return true;
}

template <typename T>
int Array<T>::IndexWhere(Condition f)
{
	for (int i = 0; i < length; i++)
	{
		if (f(array[i]))
			return i;
	}
	return -1;
}

template <typename T>
template <typename U>
Array<U> Array<T>::Map(U(*MapFunc)(T))
{
	Array<U> tmp(length);
	for (int i = 0; i < length; i++)
	{
		tmp[i] = MapFunc(*array[i]);
	}
	return tmp;
}


