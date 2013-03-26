#include <iostream>
#include <cmath>

using namespace std;

//ע�⣺�±���1��ʼ��������0
//�õ����ڵ�����
int getParent(int i)
{
	return i>>1;
}

//�õ�����������
int getLeftSon(int i)
{
	return i<<1;
}

//�õ�����������
int getRightSon(int i)
{
	return ((i<<1) + 1);
}

//������ĳ���ڵ�iΪ���ڵ������Ϊ�����
void MaxHeapify(int A[],int i,int HeapSize)
{
	int left = getLeftSon(i);
	int right = getRightSon(i);
	int largest = i;//��¼ֵ����Ԫ�ص�����

	if (left <= HeapSize && A[left] > A[i])
	{
		largest = left;
	}

	if (right <= HeapSize && A[right] > A[largest])
	{
		largest = right;
	}

	if (largest != i)//���������������ѵ����ʣ���Ҫ���е���
	{
		//���н���
		int temp = A[i];
		A[i] = A[largest];
		A[largest] = temp;
		
		MaxHeapify(A,largest,HeapSize);//�ݹ���ã�������������
	}
}

//�������Ԫ��
void printHeap(int A[],int HeapSize)
{
	for(int i = 1;i <= HeapSize;++i)
	{
		cout << A[i] << " ";
	}
	cout << endl;
}

//����
void buildMaxHeap(int A[],int HeapSize)
{
	for (int i = (int)floor((float)HeapSize / 2);i > 0;--i)
	{
		MaxHeapify(A,i,HeapSize);
	}

	cout << "���ɵĴ���ѣ�" << endl;
	printHeap(A,HeapSize);
}

//������
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
	//��Ԫ���°��1��ʼ
	int A[length] = {0,4,1,3,2,16,9,10,14,8,7};
	int HeapSize = length - 1;
	heapSort(A,HeapSize);
	cout << "������֮��" << endl;
	printHeap(A,HeapSize);
}