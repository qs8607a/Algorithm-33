#include <iostream>
#include <ctime>//time
#include <cstdlib>//rand
#include <algorithm>//swap

using namespace std;

//����-��ͨ�汾
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

	////������ŵ���ȷ��λ��
	//if(*(a + i) > *(a + high))
	//	swap(*(a + i),*(a + high));

	//�汾2
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

//����-������汾
template <class KeyType>
int partitionRandomized(KeyType *a,int low,int high)
{
	//���ѡȡһ������Ϊ����
	//�������[low,high]�е�һ��������Ϊ���������
	srand(time(NULL));
	int pivotKeyIndex = rand() % (high - low + 1) + low;
	
	//�������������һ��Ԫ��������
	swap(*(a + high),*(a + pivotKeyIndex));

	return partition(a,low,high);
}

//����-��ͨ�汾
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

//����-������汾
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