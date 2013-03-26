#include <iostream>
#include <cmath>

using namespace std;

//注意：下表都以1开始，而不是0
//得到父节点索引
int getParent(int i)
{
	return i>>1;
}

//得到左子树索引
int getLeftSon(int i)
{
	return i<<1;
}

//得到右子树索引
int getRightSon(int i)
{
	return ((i<<1) + 1);
}

//调整以某个节点i为根节点的子树为大根堆
void MaxHeapify(int A[],int i,int HeapSize)
{
	int left = getLeftSon(i);
	int right = getRightSon(i);
	int largest = i;//记录值最大的元素的索引

	if (left <= HeapSize && A[left] > A[i])
	{
		largest = left;
	}

	if (right <= HeapSize && A[right] > A[largest])
	{
		largest = right;
	}

	if (largest != i)//此子树不满足大根堆的性质，需要进行调整
	{
		//进行交换
		int temp = A[i];
		A[i] = A[largest];
		A[largest] = temp;
		
		MaxHeapify(A,largest,HeapSize);//递归调用，继续调整子树
	}
}

//输出数组元素
void printHeap(int A[],int HeapSize)
{
	for(int i = 1;i <= HeapSize;++i)
	{
		cout << A[i] << " ";
	}
	cout << endl;
}

//建堆
void buildMaxHeap(int A[],int HeapSize)
{
	for (int i = (int)floor((float)HeapSize / 2);i > 0;--i)
	{
		MaxHeapify(A,i,HeapSize);
	}

	cout << "建成的大根堆：" << endl;
	printHeap(A,HeapSize);
}

//堆排序
void heapSort(int A[],int HeapSize)
{
	buildMaxHeap(A,HeapSize);
	for (int i = HeapSize;i > 0;--i)
	{
		int temp = A[1];
		A[1] = A[i];
		A[i] = temp;
		MaxHeapify(A,1,i - 1);
	}
}

int main()
{
	const int length = 11;
	//堆元素下班从1开始
	int A[length] = {0,4,1,3,2,16,9,10,14,8,7};
	int HeapSize = length - 1;
	heapSort(A,HeapSize);
	cout << "堆排序之后：" << endl;
	printHeap(A,HeapSize);
}