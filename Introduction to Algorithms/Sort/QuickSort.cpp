//Quick Sort

#include <iostream>

using namespace std;

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
	int n,temp;
	cout<<"please input the number of the values that need to sort:"<<endl;
	cin>>n;
	int *a = (int*)malloc(n * sizeof(int));
	cout<<"please input each value:"<<endl;
	for(int i = 0;i < n;++i)
	{
		cin>>temp;
		*(a + i) = temp;
	}
	QuickSort(a,0,n - 1);
	cout<<"the values after sort:"<<endl;
	for(int i = 0;i < n;++i)
		cout<<*(a + i)<<" ";
	free(a);
}