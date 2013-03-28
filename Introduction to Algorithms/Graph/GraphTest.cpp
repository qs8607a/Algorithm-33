#include "Graph.h"

using namespace std;

int main()
{
	//���㷨���ۣ��ڶ��棩��P322 ͼ22-1����ͼ��������
	//const int n = 5;
	//int a[n] = {1,2,3,4,5};
	//char matrix[n * n] = {0,1,0,0,1,
	//								1,0,1,1,1,
	//								0,1,0,1,0,
	//								0,1,1,0,1,
	//								1,1,0,1,0};

	//���㷨���ۣ��ڶ��棩��P322 ͼ22-2����ͼ��������
	const int n = 6;
	int a[n] = {1,2,3,4,5,6};
	char matrix[n * n] = {0,1,0,1,0,0,
									0,0,0,0,1,0,
									0,0,0,0,1,1,
									0,1,0,0,0,0,
									0,0,0,1,0,0,
									0,0,0,0,0,1};

	GraphClass<int> *graphObj = new GraphClass<int>;
	graphObj->createGraph(a,n,matrix);
	graphObj->__printAdjacencyList();
	graphObj->BFSGraph();
	graphObj->DFSGraph();

	return 0;
}