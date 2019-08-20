#include "Sorting.h"
#include "Timer.h"

void Test()
{
	Sort<int>a(600);
	Sort<int>b(600,Sort<int>::NEARLY_SORTED);	//copy test
	Draw(a);
	{
		Timer t;
		a.QuickSort();
	}
	closegraph();
	Draw(b);
	{
		Timer t;
		b.InsertionSort();
	}
}

int main()
{
	Test();
}
