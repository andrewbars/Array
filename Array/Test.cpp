#include <iostream>
#include <cstdlib>
#include "Array.h"
#include <ctime>

using namespace std;

bool AboveFive(int c)
{
	return c>5;
}

void main()
{
	srand(int(time(0)));
	Array<int> a(15);
	for (int i = 0; i < a.Length(); i++)
	{
		a[i] = i;
	}

	for (int i = 0; i < a.Length(); i++)
		cout << a[i] << ' ';

	a[5] = 1;
	cout << endl;
	cout << a.LastIndexOf(1) << '\n';
	a.RemoveLast().Add(10);
	cout << a.LastIndexOf(10);
	try{
		cout << a[20];
	}
	catch (char* e)
	{
		cout << '\n' << e << '\n';
	}
	for (int i = 0; i < a.Length(); i++)
		cout << a[i] << ' ';
	a.Sort();
	cout << endl;
	for (int i = 0; i < a.Length(); i++)
		cout << a[i] << ' ';
	a.Reverse();
	cout << endl;
	for (int i = 0; i < a.Length(); i++)
		cout << a[i] << ' ';
	a.Shuffle();
	cout << endl;
	for (int i = 0; i < a.Length(); i++)
		cout << a[i] << ' ';
	Array<int>b=a.filter(AboveFive);
	cout << endl;
	for (int i = 0; i < b.Length(); i++)
		cout << b[i] << ' ';
	Array<int>c = a.filter([](int x){return x < 5; });
	cout << endl;
	for (int i = 0; i < c.Length(); i++)
		cout << c[i] << ' ';
	Array<bool>d = a.Map(AboveFive);
	cout << endl;
	for (int i = 0; i < d.Length(); i++)
		cout << d[i] << ' ';
}