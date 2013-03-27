//Ͱ����
//���㷨���ۣ��ڶ��棩��P102 8.4 Ͱ����
//Author���������꣨2013-03027��
//E-Mail:xiajunhust@gmail.com

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

//Ͱ������ڵ����ݽṹ
typedef struct StructLinkNode{
	double elem;
	struct StructLinkNode *next;
}LinkNode,*LinkNodePtr;

//Ͱ����
void BucketSort(double *a,int n);
//ɾ��һ������
void deleteLinkList(LinkNodePtr head);

int main()
{
	srand(time(NULL));
	int n = 8;
	double *a = new double[n];
	for(int i = 0;i < n;++i)
		*(a + i) = rand() * 1.0 / RAND_MAX;

	cout << "Before sort : " << endl;
	for(int i = 0;i < n;++i)
		cout << *(a + i) << "  ";
	cout << endl;

	BucketSort(a,n);

	cout << "After sort : " << endl;
	for(int i = 0;i < n;++i)
		cout << *(a + i) << "  ";
	cout << endl;
}

//Ͱ����
void BucketSort(double *a,int n)
{
	//������������
	LinkNodePtr *linkListArr = new LinkNodePtr[n];
	//��ʼ��
	for (int i = 0;i < n;++i)
	{
		linkListArr[i] = new LinkNode;
		linkListArr[i]->elem = -1;
		linkListArr[i]->next = NULL;
	}

	//��n������Ԫ�����η���n��Ͱ��
	for (int i = 0;i < n;++i)
	{
		LinkNodePtr newNode = new LinkNode;
		newNode->elem = *(a + i);
		newNode->next = NULL;

		//����Ԫ�ز����ӦͰ���������ȷλ��
		int index = floor(n * *(a + i));
		LinkNodePtr loopPtr = linkListArr[index]->next;
		LinkNodePtr prevPtr = linkListArr[index];
		while(loopPtr != NULL && *(a + i) > loopPtr->elem)
		{
			prevPtr = loopPtr;
			loopPtr = loopPtr->next;
		}
		newNode->next = loopPtr;
		prevPtr->next = newNode;
	}

	int count = 0;
	for (int i = 0;i < n;++i)
	{
		LinkNodePtr loopPtr = linkListArr[i]->next;
		while(loopPtr != NULL)
		{
			*(a + count) = loopPtr->elem;
			++count;
			loopPtr = loopPtr->next;
		}
	}

	for (int i = 0;i < n;++i)
		deleteLinkList(linkListArr[i]);
}

//ɾ��һ������
void deleteLinkList(LinkNodePtr head)
{
	if (NULL == head)
	{
		return;
	}
	deleteLinkList(head->next);
	delete head;
}