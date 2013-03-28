#include "Graph.h"

using namespace std;

int main()
{
	//《算法导论（第二版）》P322 图22-1无向图测试例子
	//const int n = 5;
	//int a[n] = {1,2,3,4,5};
	//char matrix[n * n] = {0,1,0,0,1,
	//								1,0,1,1,1,
	//								0,1,0,1,0,
	//								0,1,1,0,1,
	//								1,1,0,1,0};

	//《算法导论（第二版）》P322 图22-2有向图测试例子
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