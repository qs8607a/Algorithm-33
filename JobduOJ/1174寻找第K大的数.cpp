#include <iostream>

using namespace std;

const int NUM = 1010;

//Quick sort
int Partition(int *a,int low,int high)
{
	int pivotKey = *(a + high);
	int i = low - 1;
	for(int j = low;j <= high - 1;++j)
	{
		if (*(a + j) < pivotKey)
		{
			++i;
			int tmp = *(a + i);
			*(a + i) = *(a + j);
			*(a + j) = tmp;
		}
	}

	int tmp = *(a + i + 1);
	*(a + i + 1) = *(a + high);
	*(a + high) = tmp;

	return (i + 1);
}

void QuickSort(int *a,int low,int high)
{
	if(low < high)
	{
		int PivotLoc = Partition(a,low,high);
		QuickSort(a,low,PivotLoc - 1);
		QuickSort(a,PivotLoc + 1,high);
	}
}

int main()
{
	int a[NUM];
	int n,k,i;
	while(cin >> n)
	{
		int temp = 0,count;
		int m = n;
		while(m--)
		{
			cin >> a[temp];
			++temp;
		}
		cin >> k;

		//sort the array
		QuickSort(a,0,n - 1);

		i = 1;
		count = 1;
		for (;i < n;++i)
		{
			if(count == k)
				break;
			if (*(a + i) != *(a + i - 1))
			{
				++count;
			}
		}
		cout << *(a + i - 1) << endl;
	}

	return 0;
}