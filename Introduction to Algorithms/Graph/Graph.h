//图相关算法编程实现《算法导论（第二版）》P322 第22章 图的基本算法
//Date：2013-03-27
//Author：江南烟雨（E-Mail：xiajunhust@gmail.com）
#include <iostream>
#include <queue>

//图的基本算法类封装实现
//这里图用邻接表表示法（且是不带权的无向图）
template <class ElemType>
class GraphClass{
public:
	//图邻接表表示中节点数据结构
	typedef struct StructGraphNode{
		ElemType elem;
		struct StructGraphNode *next;
	}GraphNode,*GraphNodeLink;

	//图遍历时节点颜色标记
	enum NodeColor{
		WHITE,//未被发现
		GRAY,//已被发现但是未访问
		BLACK//已被访问
	};

	static const int MaxVal = 99999;

	GraphClass();//默认构造函数
	~GraphClass();//析构函数
	//依据图中包含的节点以及邻接矩阵创建邻接链表表示的图
	void createGraph(ElemType *a,int n,char *matrix);
	void BFSGraph();//图的广度优先搜索
	void DFSGraph();//图的深度优先搜索

	void __printAdjacencyList();//输出图的当前邻接表

private:
	GraphNodeLink *root;//邻接表，包含了对应于每个节点的列表
	int num_nodes;//图中节点个数

	int __getNodeIndex(GraphNodeLink node);//得到某个顶点在颜色等数组中的索引
	void __DFSSubGraph(GraphNodeLink u,int &time,int *d,int *f,enum NodeColor *color,GraphNodeLink *parent);//从某个子节点开始深度优先遍历
	//删除邻接表所占空间
	void __deleteAdjacencyList();
	void __deleteSingleLinkList(GraphNodeLink head);//删除一个单链表
};

template <class ElemType>
GraphClass<ElemType>::GraphClass()
{
	root = NULL;
}

//析构函数
template <class ElemType>
GraphClass<ElemType>::~GraphClass()
{
	__deleteAdjacencyList();
}

//函数：依据图的邻接矩阵表示创建图的临界表表示
//参数：
//matrix：图的邻接矩阵，行优先，以一维数组表示
template <class ElemType>
void GraphClass<ElemType>::createGraph(ElemType *a,int n,char *matrix)
{
	num_nodes = n;
	root = new GraphNodeLink[n];
	for (int i = 0;i < n;++i)
		root[i] = NULL;

	//创建邻接表中的每个列表，每个列表对应一个顶点
	for (int i = 0;i < n;++i)
	{
		root[i] = new GraphNode;
		root[i]->elem = *(a + i);
		root[i]->next = NULL;
		GraphNodeLink loopNode = root[i];
		for (int j = 0;j < n;++j)
		{
			if (*(matrix + i * n + j) == 1)
			{
				GraphNodeLink newNode = new GraphNode;
				newNode->elem = *(a + j);
				newNode->next = NULL;
				//寻找插入的正确位置
				while(loopNode->next != NULL)
					loopNode = loopNode->next;
				loopNode->next = newNode;
			}
		}
	}
}

//图的广度优先遍历
template <class ElemType>
void GraphClass<ElemType>::BFSGraph()
{
	if (NULL == root)
	{
		cout << "The graph is empty!" << endl;
		return;
	}

	cout << "BFS :" << endl;
	//标记每个顶点的颜色，表示是否被访问过、被发现
	enum NodeColor *color = new enum NodeColor[num_nodes];
	//记录遍历时源顶点到其他顶点的距离
	int *d = new int[num_nodes];
	//记录每个顶点的父节点
	GraphNodeLink *parentNode = new GraphNodeLink[num_nodes];
	for(int i = 0;i < num_nodes;++i)
	{
		*(color + i) = WHITE;
		*(d + i) = MaxVal;
		*(parentNode + i) = NULL;
	}

	//从源顶点（邻接表中第一个列表首节点开始遍历）
	int index = __getNodeIndex(*(root + 0));
	*(color + index) = GRAY;
	*(d + index) = 0;
	*(parentNode + index) = NULL;

	std::queue<GraphNodeLink> BFSQueue;//辅助数据结构：队列
	BFSQueue.push(*(root + 0));//源节点入队列
	while(!BFSQueue.empty())
	{
		GraphNodeLink tempNode = BFSQueue.front();
		cout << tempNode->elem << " ";
		BFSQueue.pop();
		int tempIndex = __getNodeIndex(tempNode);
		*(color + tempIndex) = BLACK;
		GraphNodeLink loopNode = (*(root + tempIndex))->next;//找到邻接表中对应的列表
		while(loopNode)
		{
			int index = __getNodeIndex(loopNode);
			if (WHITE == *(color + index))//当前节点未被发现
			{
				*(d + index) = *(d + tempIndex) + 1;
				*(parentNode + index) = tempNode;
				*(color + index) = GRAY;
				BFSQueue.push(loopNode);
			}
			loopNode = loopNode->next;
		}
	}

	cout << endl;
	cout << "distance from the source node : " << endl;
	for(int i = 0;i < num_nodes;++i)
	{
		if(MaxVal == *(d + i))
			cout << "The node cannot be visited from the source node!" << endl;
		else
		cout << "node " << (*(root + i))->elem << " has distance :" << *(d + i) << " from the source node"<< endl;
	}
}

//图的深度优先遍历
template <class ElemType>
void GraphClass<ElemType>::DFSGraph()
{
	if (NULL == root)
	{
		cout << "The graph is empty!" << endl;
		return;
	}

	cout << "DFS :" << endl;
	//标记每个顶点的颜色，表示是否被访问过、被发现
	enum NodeColor *color = new enum NodeColor[num_nodes];
	//记录每个顶点的父节点
	GraphNodeLink *parentNode = new GraphNodeLink[num_nodes];
	//时间戳：顶点第一次被发现的时间以及被访问的时间
	int *d = new int[num_nodes];
	int *f = new int[num_nodes];
	for(int i = 0;i < num_nodes;++i)
	{
		*(color + i) = WHITE;
		*(parentNode + i) = NULL;
	}

	int time = 0;//标记访问时间戳
	//从图中未被发现的节点开始，调用深度优先搜索函数
	for (int i = 0;i < num_nodes;++i)
	{
		GraphNodeLink currentNode = *(root + i);
		while(currentNode)
		{
			int tempIndex = __getNodeIndex(currentNode);
			if(WHITE == *(color + tempIndex))
				__DFSSubGraph(currentNode,time,d,f,color,parentNode);

			currentNode = currentNode->next;
		}
	}

	cout << endl;

	cout << "time of nodes :(first find the node,end of checking) " << endl;
	for (int i = 0;i < num_nodes;++i)
	{
		cout << "(" << *(d + i) << ", " << *(f + i) << ")  ";
	}
	cout << endl;
}

//从某个子节点开始深度优先搜索
template <class ElemType>
void GraphClass<ElemType>::__DFSSubGraph(typename GraphClass<ElemType>::GraphNodeLink u,int &time,int *d,int *f,
										 enum NodeColor *color,typename GraphClass<ElemType>::GraphNodeLink *parent)
{
	cout << u->elem << " ";
	++time;
	int currentIndex = __getNodeIndex(u);
	*(color + currentIndex) = GRAY;
	*(d + currentIndex) = time;
	GraphNodeLink loopNodeLink = (*(root + currentIndex))->next;
	while(loopNodeLink)
	{
		int tempIndex = __getNodeIndex(loopNodeLink);
		//与当前节点相邻的节点未被发现
		if (WHITE == *(color + tempIndex))
		{
			*(parent + tempIndex) = u;
			__DFSSubGraph(loopNodeLink,time,d,f,color,parent);
		}
		loopNodeLink = loopNodeLink->next;
	}
	
	*(color + currentIndex) = BLACK;
	*(f + currentIndex) = ++time;
}

template <class ElemType>
int GraphClass<ElemType>::__getNodeIndex(GraphNodeLink node)
{
	for (int i = 0;i <num_nodes;++i)
	{
		if((*(root + i))->elem == node->elem)
			return i;
	}

	return -1;
}

template <class ElemType>
void GraphClass<ElemType>::__printAdjacencyList()
{
	for (int i = 0;i < num_nodes;++i)
	{
		GraphNodeLink loopNode = *(root + i);
		while(loopNode)
		{
			cout << loopNode->elem << " ";
			loopNode = loopNode->next;
		}
		cout << endl;
	}
}

//空间释放：删除邻接表所占空间
template <class ElemType>
void GraphClass<ElemType>::__deleteAdjacencyList()
{
	if(NULL == root)
		return;
	for(int i = 0;i < num_nodes;++i)
	{
		GraphNodeLink head= *(root + i);
		if(head)
			__deleteSingleLinkList(head);
	}
}

//删除一个单链表所占空间
template <class ElemType>
void GraphClass<ElemType>::__deleteSingleLinkList(typename GraphClass<ElemType>::GraphNodeLink head)
{
	if(NULL == head)
		return;

	__deleteSingleLinkList(head->next);
	delete head;
}