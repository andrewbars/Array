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
	//возвращает длину массива
	int Length();
	//возвращает истину, если длина массива 0
	bool IsEmpty();
	//увеличивает массив до указанной величины
	Array& Resize(int size);
	//добавляет элемент в конец массива
	Array& Add(T newItem);
	//добавляет элемент в указанную позицию
	Array& Insert(T newItem, int ind);
	//удаляет последний элемент массива
	Array& RemoveLast();
	//Удаляет указанным элемент массива
	Array& Remove(int ind);
	//Сортирует массив по возрастанию
	Array& Sort();
	//Меняет порядок элементов в массиве на обратный
	Array& Reverse();
	//Перемешивает элементы массива
	Array& Shuffle();
	//Возвращает индекс первого вхождения указанного элемента в массив
	int IndexOf(T item);
	// Возвращает индекс последнего вхождения указанного элемента в массив
	int LastIndexOf(T item);
	//Возвращает индекс первого элемента в массиве, удовлетворяющего указанному условию
	int IndexWhere(Condition f);
	//Доступ к элементу массива по индексу в []
	T& operator[](int index);
	//Проверяет, совпадают ли два массива
	bool operator==(Array<T> that);
	//Возвращает новый массив, состоящий из тех элементов исходного массива, которые удовлетворяю указанному условию
	Array filter(Condition f);
	//Возвращает новый массив, состоящий из тех элементов исходного массива, которые не удовлетворяю указанному условию
	Array filterNot(Condition f);
	//Проверяет, существует ли в массиве элемент, удовлетворяющий указанному условию
	bool Exists(Condition f);
	//Проверяет, выполняется ли указанное условие для всех элементов массива
	bool ForAll(Condition f);
	//Возвращает новый массив типа U, полученный в резальтате применения ко всем элементам исходного массива заданной функции
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


