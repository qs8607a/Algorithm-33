#include <iostream>
#include <ctime>//time
#include <cstdlib>//rand
#include <algorithm>//swap

using namespace std;

//划分-普通版本
template <class KeyType>
int partition(KeyType *a,int low,int high)
{
	//int pivotKey = *(a + high);
	//int i = low;
	//int j = high - 1;
	//while(i < j)
	//{
	//	while(i < j && pivotKey > *(a + i))
	//		++i;
	//	while(i < j && pivotKey < *(a + j))
	//		--j;
	//	if(i < j)
	//		swap(*(a + i),*(a + j));
	//}

	////将枢轴放到正确的位置
	//if(*(a + i) > *(a + high))
	//	swap(*(a + i),*(a + high));

	//版本2
	int pivotKey = *(a + low);
	while(low < high)
	{
		while(low < high && *(a + high) > pivotKey)
			--high;
		*(a + low) = *(a + high);
		while(low < high && *(a + low) < pivotKey)
			++low;
		*(a + high) = *(a + low);
	}
	*(a + low) = pivotKey;

	//return i;

	return low;
}

//划分-随机化版本
template <class KeyType>
int partitionRandomized(KeyType *a,int low,int high)
{
	//随机选取一个数作为枢轴
	//随机生成[low,high]中的一个数，作为枢轴的索引
	srand(time(NULL));
	int pivotKeyIndex = rand() % (high - low + 1) + low;
	
	//交换数组中最后一个元素与枢轴
	swap(*(a + high),*(a + pivotKeyIndex));

	return partition(a,low,high);
}

//快排-普通版本
template <class KeyType>
void QuickSort(KeyType *a,int low,int high)
{
	if (low < high)
	{
		int mid = partition(a,low,high);
		QuickSort(a,low,mid - 1);
		QuickSort(a,mid + 1,high);
	}
}

//快排-随机化版本
template <class KeyType>
void QuickSortRandomize(KeyType *a,int low,int high)
{
	if (low < high)
	{
		int mid = partitionRandomized(a,low,high);
		QuickSort(a,low,mid - 1);
		QuickSort(a,mid + 1,high);
	}
}

int main()
{
	const int num = 7;
	int a[num] = {4,2,7,9,3,0,6};

	/*QuickSort(a,0,num - 1);*/

	QuickSortRandomize(a,0,num - 1);
	
	for(int i = 0;i < num;++i)
		cout << *(a + i) << " ";
	cout << endl;
}