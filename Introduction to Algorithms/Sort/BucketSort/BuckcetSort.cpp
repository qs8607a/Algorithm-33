//桶排序
//《算法导论（第二版）》P102 8.4 桶排序
//Author：江南烟雨（2013-03027）
//E-Mail:xiajunhust@gmail.com

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

//桶中链表节点数据结构
typedef struct StructLinkNode{
	double elem;
	struct StructLinkNode *next;
}LinkNode,*LinkNodePtr;

//桶排序
void BucketSort(double *a,int n);
//删除一条链表
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

//桶排序
void BucketSort(double *a,int n)
{
	//存放链表的数组
	LinkNodePtr *linkListArr = new LinkNodePtr[n];
	//初始化
	for (int i = 0;i < n;++i)
	{
		linkListArr[i] = new LinkNode;
		linkListArr[i]->elem = -1;
		linkListArr[i]->next = NULL;
	}

	//将n个输入元素依次放入n个桶中
	for (int i = 0;i < n;++i)
	{
		LinkNodePtr newNode = new LinkNode;
		newNode->elem = *(a + i);
		newNode->next = NULL;

		//将新元素插入对应桶的链表的正确位置
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

//删除一条链表
void deleteLinkList(LinkNodePtr head)
{
	if (NULL == head)
	{
		return;
	}
	deleteLinkList(head->next);
	delete head;
}