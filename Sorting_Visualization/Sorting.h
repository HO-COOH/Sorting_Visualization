#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <easyx.h>
#include <algorithm>
#include <string>
#include <fstream>

template<typename T>
bool Compare(T* data, size_t i, size_t j)
{
	auto previousColor = getlinecolor();
	setlinecolor(RED);
	line(i, 0, i, -data[i]);
	line(j, 0, j, -data[j]);
	Sleep(1);
	setlinecolor(previousColor);
	line(i, 0, i, -data[i]);
	line(j, 0, j, -data[j]);
	return data[i] >= data[j];
}

template<typename T>
void Swap(T* data, size_t i, size_t j)
{
	auto previousColor = getlinecolor();
	setlinecolor(BLACK);
	line(i, 0, i, -480);
	line(j, 0, j, -480);
	T temp = data[i];
	data[i] = data[j];
	data[j] = temp;
	setlinecolor(WHITE);
	line(i, 0, i, -data[i]);
	line(j, 0, j, -data[j]);
	setlinecolor(previousColor);
}

template<typename T>
T Get(T* data, size_t index)
{
	auto previousColor = getlinecolor();
	setlinecolor(GREEN);
	line(index, 0, index, -data[index]);
	setlinecolor(previousColor);
	line(index, 0, index, -data[index]);
	//Sleep(1);
	return data[index];
}

template<typename T>
void Insert(T* data, size_t index, T value)
{
	auto previousColor = getlinecolor();
	setlinecolor(BLACK);
	line(index, 0, index, -480);
	setlinecolor(RED);
	data[index] = value;
	line(index, 0, index, -value);
	setlinecolor(WHITE);
	line(index, 0, index, -value);
	Sleep(1);
}

template<typename T> class Sort;
template <class T>
void Draw(Sort<T>& t);

template<typename T>
class Sort
{
	T* data;
	size_t numberOfElements;
	
public:
	enum _mode{RANDOM,REVERSE,NEARLY_SORTED};
	Sort(size_t numbers, _mode mode=RANDOM);
	Sort(const std::string filePath);	//Read data from a txt file
	Sort(const T array[], size_t numbers);
	Sort(const Sort<T>& t):numberOfElements(t.numberOfElements)
	{
		data = new T[t.numberOfElements];
		std::copy(t.data, &t.data[t.numberOfElements], data);
	}
	template<typename T>
	friend void Draw(Sort<T>& t);
	~Sort()
	{
		delete[] data;
	}
	void Show();

	/*Sorting Algorithm*/
	void BubbleSort();
	void QuickSort();
	void MergeSort();
	void SelectionSort();
	void CountingSort();
	void InsertionSort();
	void ShellSort();

	/*Performance*/
};

//default constructor: create an array of size and generate random numbers
//parameter: numbers-size of the array
template<typename T>
Sort<T>::Sort(size_t numbers, _mode mode) :numberOfElements(numbers)
{
	std::srand(static_cast<unsigned int>(time(NULL)));			
	data = new T[numbers];
	for (size_t i = 0; i < numbers; ++i)
		data[i] = rand()%480;
	switch (mode)
	{
		case REVERSE:
		{
			std::sort(data, data + numbers);
			T* newData = new T[numbers];
			std::reverse_copy(data, data + numbers, newData);
			delete[] data;
			data = newData;
			break;
		}
		case NEARLY_SORTED:
		{
			std::sort(data, data + numbers);
			size_t index1 = rand() % (numbers - 1);
			size_t index2 = rand() % (numbers - 1);
			std::swap(data[index1], data[index2]);
			break;
		}
		default: 
		{
		}
	}
};

template<typename T>
Sort<T>::Sort(const std::string filePath)
{
	using namespace std;
	ifstream inFile(filePath.c_str());
	if (inFile.is_open())
	{
		size_t number = 0;
		data = new T[640];
		string temp;
		while (getline(inFile, temp))
		{
			data[number++] = stoi(temp, 0, 10);
		}
		numberOfElements = number;
	}
	cout << "The file:" << filePath << " doesn't exist!\n";
}

template<typename T>
inline Sort<T>::Sort(const T array[], size_t numbers):numberOfElements(numbers)
{
	data = new T[numbers];
	std::copy(array, array + numbers, data);
}

template<typename T>
void Sort<T>::Show()
{
	std::cout << "All the numbers:\n";
	for (size_t i = 0; i < numberOfElements; ++i)
	{
		if (i % 6 == 5)
			std::cout << std::endl;
		std::cout << data[i] << " ";
	}
}

template<typename T>
void Sort<T>::BubbleSort()
{
	//Draw(*this);
	//int temp;
	for (size_t i = 1; i < numberOfElements - 1; ++i)
	{
		for (size_t j = 0; j < numberOfElements - i; ++j)
		{
			//std::cin.get();
			//setlinecolor(RED);
			//line(j, 0, j, -data[j]);
			//line(j + 1, 0, j + 1, -data[j + 1]);
			if (Compare(data,j,j+1))
			{
				Swap(data, j, j + 1);
			}
			//setlinecolor(BLACK);
			//line(j, 0, j, -480);
			//line(j + 1, 0, j + 1, -480);
			//setlinecolor(WHITE);
			//line(j, 0, j, -data[j]);
			//line(j + 1, 0, j + 1, -data[j + 1]);
			//Sleep(1);
		}
	}
	std::cin.get();
	closegraph();
}

template<typename T>
int Partition(T* data, int p, int r)
{
	
	int i = p - 1;
	for (int j = p; j < r; ++j)
	{
		if (Compare(data,r,j))
		{
			++i;
			Swap(data, i, j);
		}
	}
	Swap(data, i + 1, r);
	return i + 1;
}

template<typename T>
void _QuickSort(T* data, int p, int r)
{
	if (p < r)
	{
		int q = Partition(data, p, r);
		_QuickSort(data, p, q - 1);
		_QuickSort(data, q + 1, r);
	}
}

template<typename T>
void Sort<T>::QuickSort()
{
	//Draw(*this);
	RECT r = { 0,-480,300,-300 };
	drawtext(_T("Quick Sort"), &r, DT_CENTER);
	_QuickSort(data, 0, numberOfElements - 1);
}

template<typename T>
void Merge(T a[], size_t p, size_t q, size_t r)
{
	size_t left = q - p + 1;
	size_t right = r - q;

	T* L = new T[left+1];
	T* R=new T[right+1];
	L[left] = 99999999;
	R[right] = 99999999;

	for (size_t i = 0; i < left; ++i)
	{
		L[i] = Get(a,p+i) ;//a[p + i];
	}

	for (size_t i = 0; i < right; ++i)
	{
		R[i] = Get(a, q + i + 1); //a[q + i + 1];
	}

	for (size_t i = 0, j = 0, k = p; k <= r; ++k)
	{
		if (L[i] <= R[j])
			Insert(a, k, L[i++]); //= L[i++];
		else
			Insert(a, k, R[j++]);
	}

	delete[] L;
	delete[] R;
}

template<typename T>
void _MergeSort(T* a, size_t l, size_t r)
{
	if (l < r)
	{
		size_t m = (l + r) / 2;
		_MergeSort(a, l, m);
		_MergeSort(a, m + 1, r);
		Merge(a, l, m, r);
	}
}

template<typename T>
void Sort<T>::MergeSort()
{
	_MergeSort(data,0, numberOfElements-1);
}

inline void Init(int width, int height)
{
	initgraph(width, height,SHOWCONSOLE);
	setorigin(0, height);
	setlinecolor(WHITE);
};

template<typename T>
void Draw(Sort<T>& t)
{
	Init(640, 480);

	for (size_t i = 0; i < t.numberOfElements; ++i)
		line(i, 0, i, -t.data[i]);
	std::cin.get();
	//closegraph();
}

template<>
void Sort<double>::CountingSort()
{
	std::cout << "Counting Sort is not available for <double> types!\n";
}

template<>
void Sort<float>::CountingSort()
{
	std::cout << "Counting Sort is not available for <float> types!\n";
}

template<typename T>
void Sort<T>::CountingSort()
{
	T max = 0;
	for (size_t i = 0; i < numberOfElements; ++i)
	{
		if (Get(data, i) > max)
			max = data[i];
	}
	T* range = new T[max+1];
	for (T i = 0; i < max+1; ++i)
		range[i] = 0;
	for (size_t i = 0; i < numberOfElements; ++i)
	{
		++range[Get(data, i)];
	}
	size_t index = 0;
	for (T i = 0; i < max + 1; ++i)
	{
		while (range[i]--)
		{
			Insert(data, index++, i);
		}
	}
	delete[] range;
}


template<typename T>
void Sort<T>::SelectionSort()
{
	for (size_t i = 0; i < numberOfElements - 1; ++i)
	{
		T min = data[i];
		size_t min_index = i;
		for (size_t j = i + 1; j < numberOfElements; ++j)
		{
			if (Compare(data, min_index, j))
			{
				min = Get(data, j);
				min_index = j;
			}
		}
		//Insert(data, min_index, data[i]);
		//Insert(data,i,min);
		Swap(data, i, min_index);
	}
}

template<typename T>
void Sort<T>::InsertionSort()
{
	for (size_t i = 1; i < numberOfElements; ++i)
	{
		size_t j = i - 1;
		size_t current = i;
		while (j >= 0&&Compare(data, j, current))
		{
			Swap(data, j--, current--);
		}
	}
}

template<typename T>
void Sort<T>::ShellSort()
{

}