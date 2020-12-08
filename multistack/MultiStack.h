#include <iostream>
using namespace std;

template<class T>
class MultiStack
{
private:
	T* x; // мультистек построен на одномерном массиве
	short size;
	short* heads;
	short* tails;
	unsigned int* sizes;
	unsigned short StackCount;

	bool comp(short* a, short* b) // функция сравнения двух массивов типа short, нужна для определения, закончено ли перераспределение
	{
		for (int i = 0; i < StackCount; i++)
			if (a[i] != b[i])
				return 0;
		return 1;
	}

	unsigned short get_free_cells() // функция получения количества свободных ячеек в массиве
	{
		unsigned short free_cells = 0;
		for (int i = 0; i < StackCount; i++)
			free_cells += (sizes[i] - tails[i] + heads[i]);
		return free_cells;
	}

	void calc_news(short* new_heads, short* new_tails, unsigned int* new_sizes, unsigned short for_each, unsigned short extra, int n)
	{
		if (n == 0)
			new_sizes[0] = sizes[0] - (sizes[0] - tails[0] + heads[0]) + for_each + extra;
		else
			new_sizes[0] = sizes[0] - (sizes[0] - tails[0] + heads[0]) + for_each;
		new_heads[0] = 0;
		new_tails[0] = tails[0];

		for (int i = 1; i < StackCount; i++)
		{
			if (i == n)
				new_sizes[i] = sizes[i] - (sizes[i] - tails[i] + heads[i]) + for_each + extra;

			else
				new_sizes[i] = sizes[i] - (sizes[i] - tails[i] + heads[i]) + for_each;

			new_heads[i] = new_heads[i - 1] + new_sizes[i - 1];
			new_tails[i] = new_heads[i] + (tails[i] - heads[i]);
		}
	}

	bool can_realloc(short* heads, short* tails, short* new_heads, short* new_tails, unsigned short counter)
	{
		return (((new_heads[counter] >= tails[counter - 1]) && (new_tails[counter] <= heads[counter + 1]) || (new_heads[counter] >= tails[counter - 1]) && (counter == StackCount - 1)) && (counter != 0));
	}

	void reallocate(unsigned short free_cells, int n) // функция перераспределения
	{
		unsigned short for_each = free_cells / StackCount;
		unsigned short extra = free_cells - for_each * StackCount;

		short* new_heads;
		new_heads = new short [StackCount];

		short* new_tails;
		new_tails = new short [StackCount];

		unsigned int* new_sizes;
		new_sizes = new unsigned int[StackCount];

		calc_news(new_heads, new_tails, new_sizes, for_each, extra, n);

		sizes[0] = new_sizes[0];

		unsigned short counter = 1;

		while (!comp(heads, new_heads))
		{
			if (can_realloc(heads, tails, new_heads, new_tails, counter))
			{
				unsigned short elems = tails[counter] - heads[counter];
				short diff = new_heads[counter] - heads[counter];

				if (new_heads[counter] < heads[counter])
					for (int i = heads[counter]; i < elems + heads[counter]; i++)
					{
						x[i + diff] = x[i];
						x[i] = 0;
					}
				else
					for (int i = elems - 1 + heads[counter]; i >= heads[counter]; i--)
					{
						x[i + diff] = x[i];
						x[i] = 0;
					}

				heads[counter] = new_heads[counter];
				tails[counter] = new_tails[counter];
				sizes[counter] = new_sizes[counter];
			}
			counter = (counter + 1) % StackCount;
		}

	}

public:
	MultiStack()
	{
		StackCount = 0;
		size = 0;
		x = new T[0];
		heads = new short [0];
		tails = new short [0];
		sizes = new unsigned int[0];
	}
	MultiStack(int _count, int _size)
	{
		if (_size / _count <= 0)
			throw logic_error("incorrect mem size");
		if (_size <= 0 || _count <= 0)
			throw logic_error("incorrect input");

		size = _size;
		StackCount = _count;
		heads = new short [_count];
		tails = new short [_count];
		sizes = new unsigned int[_count];
		
		x = new T[_size];
		for (int i = 0; i < _size; i++)
			x[i] = 0;


		int temp = round((double)_size / _count);
		for (int i = 0; i < StackCount - 1; i++)
		{
			heads[i] = temp * i;
			tails[i] = heads[i];
			sizes[i] = temp;
		}
		heads[_count - 1] = temp * (_count - 1);
		tails[_count - 1] = heads[_count - 1];
		sizes[_count - 1] = _size - temp * (_count - 1);
	}

	MultiStack(MultiStack<T>& copy)
	{
		StackCount = copy.StackCount;
		size = copy.size;

		x = new T[size];
		for (int i = 0; i < size; i++)
			x[i] = copy.x[i];

		heads = new short[StackCount];
		tails = new short[StackCount];
		sizes = new unsigned int[StackCount];
		for (int i = 0; i < StackCount; i++)
		{
			heads[i] = copy.heads[i];
			tails[i] = copy.tails[i];
			sizes[i] = copy.sizes[i];
		}
	}

	void push(int n, T elem)
	{
		if ((tails[n] - heads[n]) == sizes[n])
		{
			unsigned short free_cells = get_free_cells();
			if (free_cells > 0)
				reallocate(free_cells, n);
			else throw logic_error("multistack full");
		}
		x[tails[n]] = elem;
		tails[n]++;
	}

	T pop(int n)
	{
		if (IsEmpty(n))
			throw logic_error("stack empty");
		tails[n]--;
		return x[tails[n]];
	}

	bool IsFull(int n)
	{
		if (tails[n] - heads[n] == sizes[n])
			return 1;
		else
			return 0;
	}
	bool IsEmpty(int n)
	{
		if (tails[n] == heads[n])
			return 1;
		else
			return 0;
	}

	int get_size(int n)
	{
		return sizes[n];
	}

	template <class T1>
	friend ostream& operator << (ostream& ostr, const MultiStack<T1>& _m)
	{
		ostr << "(";

		for (int i = 0; i < _m.StackCount; i++)
		{
			ostr << "[";
			for (int j = _m.heads[i]; j < _m.heads[i] + _m.sizes[i]; j++)
				if (j != _m.heads[i] + _m.sizes[i] - 1)
					ostr << _m.x[j] << " ";
				else
					ostr << _m.x[j];
			if (i != _m.StackCount - 1)
				ostr << "], ";
			else
				ostr << "]";
		}

		ostr << ")";

		return ostr;
	}

	//extra

	int max_amount()
	{
		if (size == 0)
			throw logic_error("multistack empty");

		int result = 0;

		for (int i = 0; i < StackCount; i++)
			if (sizes[i] > sizes[result])
				result = i;

		return result;
	}

	int max_elem()
	{
		if (size == 0)
			throw logic_error("multistack empty");

		int result = 0;
		int temp = x[0];
		int counter = 0;

		for (int i = 0; i < StackCount; i++)
			for (int j = 0; j < sizes[i]; j++)
			{
				if (x[counter] > temp)
				{
					result = i;
					temp = x[counter];
				}
				counter++;
			}

		return result;
	}
};