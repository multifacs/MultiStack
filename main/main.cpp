#include "MultiStack.h"

int main()
{
	MultiStack<int> a(3, 10);
	a.push(0, 99);
	a.push(0, 99);
	a.push(0, 99);

	a.push(1, 11);
	a.push(1, 11);

	a.push(2, 22);
	a.push(2, 22);

	a.push(0, 66);
	a.push(0, 9);
	
	a.push(1, 10);

	cout << a;
}