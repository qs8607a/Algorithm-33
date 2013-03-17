//B-树编程实现
//《算法导论（第二版）》第18章 B树
//Author：江南烟雨
//E-Mail：xiajunhust@gmail.com

#include <iostream>

//B-Tree节点数据结构定义
template <class KeyT>
struct BTreeNode{
	int n;//当前节点中存储的关键字数
	KeyT *keys;//指向所有关键字的指针
	bool isLeaf;//标识当前节点是否是叶子
	struct BTreeNode **childs;//指向所有指向子女的指针
};

//B-Tree类封装
template <class KeyT>
class BTree{
private:
	typedef struct BTreeNode<KeyT> * BTreeNodeLink;//指向节点类型的指针类型定义

	BTreeNodeLink T;//根节点
	//每个非根节点至少有t-1个关键字，至多2t-1个关键字
	int t;//B树的最小度数

public:
	BTree(int tVal = 2);
	BTreeNodeLink searchBTree(KeyT k);//搜索B树
	BTreeNodeLink getRoot();//返回当前B树的根节点
	void insertBTreeNode(KeyT k);//向B树中插入关键字
	void createBTree(KeyT *keyValues);//创建B树
	void printBTreeBFS(BTreeNodeLink t);//层次遍历输出以t为根的子树B树

	void splitChild(BTreeNodeLink x,int i,BTreeNodeLink y);//分裂满的子节点
	void insertBTreeNonFull(BTreeNodeLink x,KeyT k);//将关键字插入到以该非满节点为根的树中
	BTreeNodeLink __allocateNode();//产生一个新的节点
};

//构造函数
template <class KeyT>
BTree<KeyT>::BTree(int tVal = 2)
{
	t = tVal;

	typename BTree<KeyT>::BTreeNodeLink x = __allocateNode();
	x->isLeaf = true;
	x->n = 0;
	T = x;
}

//函数：依据一组关键字值，创建一棵B树
template <class KeyT>
void BTree<KeyT>::createBTree(KeyT *keyValues)
{

}

//函数：返回当前B树的根节点
template <class KeyT>
typename BTree<KeyT>::BTreeNodeLink BTree<KeyT>::getRoot()
{
	return T;
}

//函数：向B树中插入关键字
template <class KeyT>
void BTree<KeyT>::insertBTreeNode(KeyT k)
{
	typename BTree<KeyT>::BTreeNodeLink r = T;
	if (2 * t - 1 == r->n)//根节点满
	{
		typename BTree<KeyT>::BTreeNodeLink s = __allocateNode();
		T = s;//新根节点
		s->isLeaf = false;
		s->n = 0;
		s->childs[0] = r;
		splitChild(s,0,r);//分裂原根节点
		insertBTreeNonFull(s,k);
	}
	else
		insertBTreeNonFull(r,k);
}

//函数：层次遍历输出以t为根的子树
template <class KeyT>
void BTree<KeyT>::printBTreeBFS(typename BTree<KeyT>::BTreeNodeLink t)
{
	if(NULL == t)
		return;

	//输出当前节点所有关键字
	cout << "[";
	for(int i = 0;i < t->n;++i)
	{
		cout << t->keys[i];
		if(t->n - 1 != i)
			cout << " ";
	}
	cout << "]" << endl;

	//递归输出所有子树
	for(int i = 0;i <= t->n;++i)
		printBTreeBFS(t->childs[i]);
}

//函数：分裂满的子节点
//参数解释：
//x：一个非满的内节点
//y：x的一个满子节点
//i；y的下标
template <class KeyT>
void BTree<KeyT>::splitChild(typename BTree<KeyT>::BTreeNodeLink x, int index,typename BTree<KeyT>::BTreeNodeLink y)
{
	typename BTree<KeyT>::BTreeNodeLink z = __allocateNode();//分裂产生的新节点

	z->isLeaf = y->isLeaf;
	z->n = t - 1;
	//关键字赋值
	for(int i = 0;i < t - 1;++i)
		z->keys[i] = y->keys[t + i];
	//非叶节点，子女节点指针赋值
	if(!y->isLeaf)
	{
		for(int i = 0;i < t;++i)
			z->childs[i] = y->childs[t + i];
	}

	//调整原节点的参数
	y->n = t - 1;
	//向后移动子女指针，便于增加一个子女节点指针
	for(int i = x->n;i >= index + 1;--i)
		x->childs[i + 1] = x->childs[i];
	x->childs[index + 1] = z;//插入新子女指针，指向增加的节点z

	//向后移动关键字，便于将子女的一个关键字上升至父节点
	for(int i = x->n - 1;i >= index;--i)
		x->keys[i + 1] = x->keys[i];
	x->keys[index] = y->keys[t - 1];//关键字上移
	x->n = x->n + 1;
}

//函数：将关键字插入到根节点非满的子树中
template <class KeyT>
void BTree<KeyT>::insertBTreeNonFull(typename BTree<KeyT>::BTreeNodeLink x, KeyT k)
{
	int i = x->n;

	//要插入的节点是叶子节点，直接插入
	if (x->isLeaf)
	{
		//空节点
		if(!i)
		{
			x->keys[0] = k;
			x->n = x->n + 1;
			return;
		}
		//搜寻插入位置,并将关键字向后移
		while(i >= 0 && k < x->keys[i - 1])
		{
			x->keys[i] = x->keys[i - 1];
			--i;
		}
		x->keys[i] = k;
		x->n = x->n + 1;
	}
	else{
		//要插入的节点是非叶节点，需要向下递归到子树，将其插入到子树中适当的叶节点中去
		//寻找要插入的子树
		while(i > 0 && k < x->keys[i - 1])
			--i;

		//判断要下降的子节点是否满
		if (2 * t - 1 == x->childs[i]->n)
		{
			//如果要下降的子树满，则分裂
			splitChild(x,i,x->childs[i]);
			//判断需要下降至哪个子树上
			if(k > x->keys[i])
				++i;//需要下降至右子树上
		}
		insertBTreeNonFull(x->childs[i],k);
	}
}

//函数：生成一个新的节点
//返回值：返回指向新节点的指针
template <class KeyT>
typename BTree<KeyT>::BTreeNodeLink BTree<KeyT>::__allocateNode()
{
	typename BTree<KeyT>::BTreeNodeLink newNode = new struct BTreeNode<KeyT>;
	newNode->n = 0;
	newNode->keys = new KeyT[2 * t - 1];//一次性分配2 * t - 1的空间
	newNode->isLeaf = true;
	newNode->childs = new typename BTree<KeyT>::BTreeNodeLink[2 * t];
	//子女指针初始化
	for(int i = 0;i < 2 * t;++i)
		newNode->childs[i] = NULL;

	return newNode;
}

