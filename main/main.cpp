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

	cout << a << endl;

	cout << a.max_amount() << endl;
	cout << a.max_elem() << endl;
	a.pop(2);
	a.push(2, 100);
	cout << a.max_elem() << endl;
}