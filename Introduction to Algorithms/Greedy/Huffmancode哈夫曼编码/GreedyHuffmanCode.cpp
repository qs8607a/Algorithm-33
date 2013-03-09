//贪心算法---哈夫曼编码问题
//《算法导论（第二版）》16.3
//Author：江南烟雨
//Email：xiajunhust@gmail.com

#include <iostream>
#include <queue>//用优先级队列来存储各元素节点
#include <string>

using namespace std;

//哈夫曼编码所对应的二叉树的节点数据结构
typedef struct structHuffmanTreeNode{
	int data;//节点元素值
	struct structHuffmanTreeNode *lCild,*rChild;//左右孩子指针
}HuffmanTreeNode;

//优先级队列中元素数据结构
typedef struct structQueueNode{
	int elem;//元素值
	HuffmanTreeNode *node;//对应的哈夫曼树节点
}QueueNode;

//自定义优先级队列中元素比较准则
class QueneNodeLess{//仿函数定义
public:
	bool operator()(QueueNode *a,QueueNode *b)
	{
		return a->elem > b->elem;
	}
};

//依据某值生成新的哈夫曼树节点
HuffmanTreeNode *newHuffmanTreeNode(int elem)
{
	HuffmanTreeNode *node = new HuffmanTreeNode;
	node->data = elem;
	node->lCild = node->rChild = NULL;//默认为空

	return node;
}

//依据某值生成优先级队列节点
QueueNode *newQueneNode(int elem)
{
	QueueNode *node = new QueueNode;
	node->elem = elem;
	node->node = NULL;//默认为空

	return node;
}

//输出哈夫曼树对应的各字符的哈夫曼编码
void printHuffmanCode(HuffmanTreeNode *T,string code)
{
	//树为空
	if(NULL == T)
		return;
	//遇到叶子节点，输出哈夫曼编码
	if(NULL == T->lCild && NULL == T->rChild)
	{
		cout << T->data << " : " << code << endl;
		return;
	}

	//继续向左子树和右子树遍历
	string lcode = code + '0';
	printHuffmanCode(T->lCild,lcode);
	string rcode = code + '1';
	printHuffmanCode(T->rChild,rcode);
}

int main()
{
	const int n = 6;//需要进行编码的字符数目
	int frequncy[n] = {45,13,12,16,9,5};//各字符出现的频数
	priority_queue<QueueNode*,vector<QueueNode*>,QueneNodeLess> intQueue;//优先级队列

	for(int i = 0;i < n;++i)
	{
		QueueNode *node = newQueneNode(frequncy[i]);
		intQueue.push(node);
	}

	HuffmanTreeNode *T;//最终生成的哈夫曼树的根节点
	while(!intQueue.empty())
	{
		QueueNode *a = intQueue.top();
		intQueue.pop();
		if (intQueue.empty())//队列中只剩下一个元素
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

	cout << "各频数字符哈夫曼编码结果：" << endl;
	printHuffmanCode(T,"");

	return 0;
}

