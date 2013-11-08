#include <iostream>
#include <stdint.h>

const int max_value = 0x7FFFFFFFFFFFFFFF;

void heap_make(int *a, int n)
{
	for (int i = n/2; i >= 1; --i)
	{
		for(int j = i; j <= n/2; )
		{
			int k = j*2;
			if ((k+1 <= n) && (a[k] < a[k+1]))
				++k;
			if ( a[j] < a[k] )
			{
				std::swap(a[k], a[j]);
				j = k;
			}
			else
				break;
		}
	}
}

void heap_pop( int *a, int n )
{
	std::swap (a[n], a[1]);
	for (int i = 1; 2*i < n; )
	{
		i *= 2;
		if((i+1 < n) && (a[i] < a[i+1]))
			i +=1 ;
		if (a[i/2] < a[i])
			std::swap(a[i/2] , a[i]);
	}
}
void heap_sort_fast (int *data, int n)
{
	heap_make(data-1, n);
	for (int i = 0; i < n; ++i)
		heap_pop(data - 1, n - i);
}

int* merge (int *a, int ab_len, int *b)
{
	int* c = new int[ab_len];
	int i = 0;
	int j = 0;
	for (; i < ab_len && j < ab_len && (i+j) < ab_len; )
	{
		if (a[i] < b[j])
		{ 
			c[i+j] = a[i];
			++i;
		}
		else
		{
			c[i+j] = b[j];
			++j;
		}
	}
	delete[] a;
	return c;
}

int main()
{
	int size;
	int k;

	std::cin >> size >> k;
	int* arr = new int[k];
	int* merge_arr = new int[k];
	
	if (k < size)
	{
		for (int j=0; j<k; j++)
			std::cin >> arr[j];
	}
	heap_sort_fast (arr, k);

	int i = k;
	while (i < size)
	{
		int rest = 0;
		if ((i+k) < size)
		{
			i += k;
			for (int j=0; j<k; j++)
				std::cin >> merge_arr[j];
		}
		else 
		{
			rest = size-i;
			for (int j=0; j<k; j++)
			{
				if (j < rest)
					std::cin >> merge_arr[j];
				else
					merge_arr[j] = max_value;
			i = size;
			}
		}
		(i != size) ? (heap_sort_fast (merge_arr, k)) : (heap_sort_fast (merge_arr, rest));

		arr = merge(arr, k, merge_arr);
	}

	for (int j=0; j<k; j++)
		std::cout << arr[j] << " ";
	
	delete[] merge_arr;
	delete[] arr;

    system("pause");
	return 0;
}