//ͼ����㷨���ʵ�֡��㷨���ۣ��ڶ��棩��P322 ��22�� ͼ�Ļ����㷨
//Date��2013-03-27
//Author���������꣨E-Mail��xiajunhust@gmail.com��
#include <iostream>
#include <queue>

//ͼ�Ļ����㷨���װʵ��
//����ͼ���ڽӱ��ʾ�������ǲ���Ȩ������ͼ��
template <class ElemType>
class GraphClass{
public:
	//ͼ�ڽӱ��ʾ�нڵ����ݽṹ
	typedef struct StructGraphNode{
		ElemType elem;
		struct StructGraphNode *next;
	}GraphNode,*GraphNodeLink;

	//ͼ����ʱ�ڵ���ɫ���
	enum NodeColor{
		WHITE,//δ������
		GRAY,//�ѱ����ֵ���δ����
		BLACK//�ѱ�����
	};

	static const int MaxVal = 99999;

	GraphClass();//Ĭ�Ϲ��캯��
	~GraphClass();//��������
	//����ͼ�а����Ľڵ��Լ��ڽӾ��󴴽��ڽ������ʾ��ͼ
	void createGraph(ElemType *a,int n,char *matrix);
	void BFSGraph();//ͼ�Ĺ����������
	void DFSGraph();//ͼ�������������

	void __printAdjacencyList();//���ͼ�ĵ�ǰ�ڽӱ�

private:
	GraphNodeLink *root;//�ڽӱ������˶�Ӧ��ÿ���ڵ���б�
	int num_nodes;//ͼ�нڵ����

	int __getNodeIndex(GraphNodeLink node);//�õ�ĳ����������ɫ�������е�����
	void __DFSSubGraph(GraphNodeLink u,int &time,int *d,int *f,enum NodeColor *color,GraphNodeLink *parent);//��ĳ���ӽڵ㿪ʼ������ȱ���
	//ɾ���ڽӱ���ռ�ռ�
	void __deleteAdjacencyList();
	void __deleteSingleLinkList(GraphNodeLink head);//ɾ��һ��������
};

template <class ElemType>
GraphClass<ElemType>::GraphClass()
{
	root = NULL;
}

//��������
template <class ElemType>
GraphClass<ElemType>::~GraphClass()
{
	__deleteAdjacencyList();
}

//����������ͼ���ڽӾ����ʾ����ͼ���ٽ���ʾ
//������
//matrix��ͼ���ڽӾ��������ȣ���һά�����ʾ
template <class ElemType>
void GraphClass<ElemType>::createGraph(ElemType *a,int n,char *matrix)
{
	num_nodes = n;
	root = new GraphNodeLink[n];
	for (int i = 0;i < n;++i)
		root[i] = NULL;

	//�����ڽӱ��е�ÿ���б�ÿ���б��Ӧһ������
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
				//Ѱ�Ҳ������ȷλ��
				while(loopNode->next != NULL)
					loopNode = loopNode->next;
				loopNode->next = newNode;
			}
		}
	}
}

//ͼ�Ĺ�����ȱ���
template <class ElemType>
void GraphClass<ElemType>::BFSGraph()
{
	if (NULL == root)
	{
		cout << "The graph is empty!" << endl;
		return;
	}

	cout << "BFS :" << endl;
	//���ÿ���������ɫ����ʾ�Ƿ񱻷��ʹ���������
	enum NodeColor *color = new enum NodeColor[num_nodes];
	//��¼����ʱԴ���㵽��������ľ���
	int *d = new int[num_nodes];
	//��¼ÿ������ĸ��ڵ�
	GraphNodeLink *parentNode = new GraphNodeLink[num_nodes];
	for(int i = 0;i < num_nodes;++i)
	{
		*(color + i) = WHITE;
		*(d + i) = MaxVal;
		*(parentNode + i) = NULL;
	}

	//��Դ���㣨�ڽӱ��е�һ���б��׽ڵ㿪ʼ������
	int index = __getNodeIndex(*(root + 0));
	*(color + index) = GRAY;
	*(d + index) = 0;
	*(parentNode + index) = NULL;

	std::queue<GraphNodeLink> BFSQueue;//�������ݽṹ������
	BFSQueue.push(*(root + 0));//Դ�ڵ������
	while(!BFSQueue.empty())
	{
		GraphNodeLink tempNode = BFSQueue.front();
		cout << tempNode->elem << " ";
		BFSQueue.pop();
		int tempIndex = __getNodeIndex(tempNode);
		*(color + tempIndex) = BLACK;
		GraphNodeLink loopNode = (*(root + tempIndex))->next;//�ҵ��ڽӱ��ж�Ӧ���б�
		while(loopNode)
		{
			int index = __getNodeIndex(loopNode);
			if (WHITE == *(color + index))//��ǰ�ڵ�δ������
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

//ͼ��������ȱ���
template <class ElemType>
void GraphClass<ElemType>::DFSGraph()
{
	if (NULL == root)
	{
		cout << "The graph is empty!" << endl;
		return;
	}

	cout << "DFS :" << endl;
	//���ÿ���������ɫ����ʾ�Ƿ񱻷��ʹ���������
	enum NodeColor *color = new enum NodeColor[num_nodes];
	//��¼ÿ������ĸ��ڵ�
	GraphNodeLink *parentNode = new GraphNodeLink[num_nodes];
	//ʱ����������һ�α����ֵ�ʱ���Լ������ʵ�ʱ��
	int *d = new int[num_nodes];
	int *f = new int[num_nodes];
	for(int i = 0;i < num_nodes;++i)
	{
		*(color + i) = WHITE;
		*(parentNode + i) = NULL;
	}

	int time = 0;//��Ƿ���ʱ���
	//��ͼ��δ�����ֵĽڵ㿪ʼ���������������������
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

//��ĳ���ӽڵ㿪ʼ�����������
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
		//�뵱ǰ�ڵ����ڵĽڵ�δ������
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

//�ռ��ͷţ�ɾ���ڽӱ���ռ�ռ�
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

//ɾ��һ����������ռ�ռ�
template <class ElemType>
void GraphClass<ElemType>::__deleteSingleLinkList(typename GraphClass<ElemType>::GraphNodeLink head)
{
	if(NULL == head)
		return;

	__deleteSingleLinkList(head->next);
	delete head;
}