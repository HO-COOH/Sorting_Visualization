#include "Sorting.h"
#include "Timer.h"

void Test()
{
	Sort<int>a(600);
	Sort<int>b(a);
	Draw(a);
	{
		Timer t;
		a.QuickSort();
	}
	closegraph();
	Draw(b);
	{
		Timer t;
		b.MergeSort();
	}
}

int main()
{
	Test();
}
