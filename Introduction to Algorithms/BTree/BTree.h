//B-�����ʵ��
//���㷨���ۣ��ڶ��棩����18�� B��
//Author����������
//E-Mail��xiajunhust@gmail.com

#include <iostream>

//B-Tree�ڵ����ݽṹ����
template <class KeyT>
struct BTreeNode{
	int n;//��ǰ�ڵ��д洢�Ĺؼ�����
	KeyT *keys;//ָ�����йؼ��ֵ�ָ��
	bool isLeaf;//��ʶ��ǰ�ڵ��Ƿ���Ҷ��
	struct BTreeNode **childs;//ָ������ָ����Ů��ָ��
};

//B-Tree���װ
template <class KeyT>
class BTree{
private:
	typedef struct BTreeNode<KeyT> * BTreeNodeLink;//ָ��ڵ����͵�ָ�����Ͷ���

	BTreeNodeLink T;//���ڵ�
	//ÿ���Ǹ��ڵ�������t-1���ؼ��֣�����2t-1���ؼ���
	int t;//B������С����

public:
	BTree(int tVal = 2);
	BTreeNodeLink searchBTree(KeyT k);//����B��
	BTreeNodeLink getRoot();//���ص�ǰB���ĸ��ڵ�
	void insertBTreeNode(KeyT k);//��B���в���ؼ���
	void createBTree(KeyT *keyValues);//����B��
	void printBTreeBFS(BTreeNodeLink t);//��α��������tΪ��������B��

	void splitChild(BTreeNodeLink x,int i,BTreeNodeLink y);//���������ӽڵ�
	void insertBTreeNonFull(BTreeNodeLink x,KeyT k);//���ؼ��ֲ��뵽�Ը÷����ڵ�Ϊ��������
	BTreeNodeLink __allocateNode();//����һ���µĽڵ�
};

//���캯��
template <class KeyT>
BTree<KeyT>::BTree(int tVal = 2)
{
	t = tVal;

	typename BTree<KeyT>::BTreeNodeLink x = __allocateNode();
	x->isLeaf = true;
	x->n = 0;
	T = x;
}

//����������һ��ؼ���ֵ������һ��B��
template <class KeyT>
void BTree<KeyT>::createBTree(KeyT *keyValues)
{

}

//���������ص�ǰB���ĸ��ڵ�
template <class KeyT>
typename BTree<KeyT>::BTreeNodeLink BTree<KeyT>::getRoot()
{
	return T;
}

//��������B���в���ؼ���
template <class KeyT>
void BTree<KeyT>::insertBTreeNode(KeyT k)
{
	typename BTree<KeyT>::BTreeNodeLink r = T;
	if (2 * t - 1 == r->n)//���ڵ���
	{
		typename BTree<KeyT>::BTreeNodeLink s = __allocateNode();
		T = s;//�¸��ڵ�
		s->isLeaf = false;
		s->n = 0;
		s->childs[0] = r;
		splitChild(s,0,r);//����ԭ���ڵ�
		insertBTreeNonFull(s,k);
	}
	else
		insertBTreeNonFull(r,k);
}

//��������α��������tΪ��������
template <class KeyT>
void BTree<KeyT>::printBTreeBFS(typename BTree<KeyT>::BTreeNodeLink t)
{
	if(NULL == t)
		return;

	//�����ǰ�ڵ����йؼ���
	cout << "[";
	for(int i = 0;i < t->n;++i)
	{
		cout << t->keys[i];
		if(t->n - 1 != i)
			cout << " ";
	}
	cout << "]" << endl;

	//�ݹ������������
	for(int i = 0;i <= t->n;++i)
		printBTreeBFS(t->childs[i]);
}

//���������������ӽڵ�
//�������ͣ�
//x��һ���������ڽڵ�
//y��x��һ�����ӽڵ�
//i��y���±�
template <class KeyT>
void BTree<KeyT>::splitChild(typename BTree<KeyT>::BTreeNodeLink x, int index,typename BTree<KeyT>::BTreeNodeLink y)
{
	typename BTree<KeyT>::BTreeNodeLink z = __allocateNode();//���Ѳ������½ڵ�

	z->isLeaf = y->isLeaf;
	z->n = t - 1;
	//�ؼ��ָ�ֵ
	for(int i = 0;i < t - 1;++i)
		z->keys[i] = y->keys[t + i];
	//��Ҷ�ڵ㣬��Ů�ڵ�ָ�븳ֵ
	if(!y->isLeaf)
	{
		for(int i = 0;i < t;++i)
			z->childs[i] = y->childs[t + i];
	}

	//����ԭ�ڵ�Ĳ���
	y->n = t - 1;
	//����ƶ���Ůָ�룬��������һ����Ů�ڵ�ָ��
	for(int i = x->n;i >= index + 1;--i)
		x->childs[i + 1] = x->childs[i];
	x->childs[index + 1] = z;//��������Ůָ�룬ָ�����ӵĽڵ�z

	//����ƶ��ؼ��֣����ڽ���Ů��һ���ؼ������������ڵ�
	for(int i = x->n - 1;i >= index;--i)
		x->keys[i + 1] = x->keys[i];
	x->keys[index] = y->keys[t - 1];//�ؼ�������
	x->n = x->n + 1;
}

//���������ؼ��ֲ��뵽���ڵ������������
template <class KeyT>
void BTree<KeyT>::insertBTreeNonFull(typename BTree<KeyT>::BTreeNodeLink x, KeyT k)
{
	int i = x->n;

	//Ҫ����Ľڵ���Ҷ�ӽڵ㣬ֱ�Ӳ���
	if (x->isLeaf)
	{
		//�սڵ�
		if(!i)
		{
			x->keys[0] = k;
			x->n = x->n + 1;
			return;
		}
		//��Ѱ����λ��,�����ؼ��������
		while(i >= 0 && k < x->keys[i - 1])
		{
			x->keys[i] = x->keys[i - 1];
			--i;
		}
		x->keys[i] = k;
		x->n = x->n + 1;
	}
	else{
		//Ҫ����Ľڵ��Ƿ�Ҷ�ڵ㣬��Ҫ���µݹ鵽������������뵽�������ʵ���Ҷ�ڵ���ȥ
		//Ѱ��Ҫ���������
		while(i > 0 && k < x->keys[i - 1])
			--i;

		//�ж�Ҫ�½����ӽڵ��Ƿ���
		if (2 * t - 1 == x->childs[i]->n)
		{
			//���Ҫ�½����������������
			splitChild(x,i,x->childs[i]);
			//�ж���Ҫ�½����ĸ�������
			if(k > x->keys[i])
				++i;//��Ҫ�½�����������
		}
		insertBTreeNonFull(x->childs[i],k);
	}
}

//����������һ���µĽڵ�
//����ֵ������ָ���½ڵ��ָ��
template <class KeyT>
typename BTree<KeyT>::BTreeNodeLink BTree<KeyT>::__allocateNode()
{
	typename BTree<KeyT>::BTreeNodeLink newNode = new struct BTreeNode<KeyT>;
	newNode->n = 0;
	newNode->keys = new KeyT[2 * t - 1];//һ���Է���2 * t - 1�Ŀռ�
	newNode->isLeaf = true;
	newNode->childs = new typename BTree<KeyT>::BTreeNodeLink[2 * t];
	//��Ůָ���ʼ��
	for(int i = 0;i < 2 * t;++i)
		newNode->childs[i] = NULL;

	return newNode;
}

