//̰���㷨---��������������
//���㷨���ۣ��ڶ��棩��16.3
//Author����������
//Email��xiajunhust@gmail.com

#include <iostream>
#include <queue>//�����ȼ��������洢��Ԫ�ؽڵ�
#include <string>

using namespace std;

//��������������Ӧ�Ķ������Ľڵ����ݽṹ
typedef struct structHuffmanTreeNode{
	int data;//�ڵ�Ԫ��ֵ
	struct structHuffmanTreeNode *lCild,*rChild;//���Һ���ָ��
}HuffmanTreeNode;

//���ȼ�������Ԫ�����ݽṹ
typedef struct structQueueNode{
	int elem;//Ԫ��ֵ
	HuffmanTreeNode *node;//��Ӧ�Ĺ��������ڵ�
}QueueNode;

//�Զ������ȼ�������Ԫ�رȽ�׼��
class QueneNodeLess{//�º�������
public:
	bool operator()(QueueNode *a,QueueNode *b)
	{
		return a->elem > b->elem;
	}
};

//����ĳֵ�����µĹ��������ڵ�
HuffmanTreeNode *newHuffmanTreeNode(int elem)
{
	HuffmanTreeNode *node = new HuffmanTreeNode;
	node->data = elem;
	node->lCild = node->rChild = NULL;//Ĭ��Ϊ��

	return node;
}

//����ĳֵ�������ȼ����нڵ�
QueueNode *newQueneNode(int elem)
{
	QueueNode *node = new QueueNode;
	node->elem = elem;
	node->node = NULL;//Ĭ��Ϊ��

	return node;
}

//�������������Ӧ�ĸ��ַ��Ĺ���������
void printHuffmanCode(HuffmanTreeNode *T,string code)
{
	//��Ϊ��
	if(NULL == T)
		return;
	//����Ҷ�ӽڵ㣬�������������
	if(NULL == T->lCild && NULL == T->rChild)
	{
		cout << T->data << " : " << code << endl;
		return;
	}

	//������������������������
	string lcode = code + '0';
	printHuffmanCode(T->lCild,lcode);
	string rcode = code + '1';
	printHuffmanCode(T->rChild,rcode);
}

int main()
{
	const int n = 6;//��Ҫ���б�����ַ���Ŀ
	int frequncy[n] = {45,13,12,16,9,5};//���ַ����ֵ�Ƶ��
	priority_queue<QueueNode*,vector<QueueNode*>,QueneNodeLess> intQueue;//���ȼ�����

	for(int i = 0;i < n;++i)
	{
		QueueNode *node = newQueneNode(frequncy[i]);
		intQueue.push(node);
	}

	HuffmanTreeNode *T;//�������ɵĹ��������ĸ��ڵ�
	while(!intQueue.empty())
	{
		QueueNode *a = intQueue.top();
		intQueue.pop();
		if (intQueue.empty())//������ֻʣ��һ��Ԫ��
		{
			T = a->node;
			break;
		}
		QueueNode *b = intQueue.top();
		intQueue.pop();
		HuffmanTreeNode *lchild,*rchild,*t;

		if(NULL == a->node)
			lchild = newHuffmanTreeNode(a->elem);
		else 
			lchild = a->node;
		if(NULL == b->node)
			rchild = newHuffmanTreeNode(b->elem);
		else 
			rchild = b->node;

		t = newHuffmanTreeNode(a->elem + b->elem);
		t->lCild = lchild;
		t->rChild = rchild;

		QueueNode *newedQueueNode = newQueneNode(t->data);
		newedQueueNode->node = t;

		intQueue.push(newedQueueNode);
	}

	cout << "��Ƶ���ַ���������������" << endl;
	printHuffmanCode(T,"");

	return 0;
}

