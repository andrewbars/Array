#include <iostream>
#include <cstdlib>
#include "Array.h"
#include <ctime>

using namespace std;

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
}