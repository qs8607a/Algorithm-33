#include "RBTree.h"

#include <iostream>

using namespace std;

RBTree::RBTree()
{
	NullNode = (rb_node_t *)malloc(sizeof(struct rb_node_t));
	//分配内存失败
	if (!NullNode)
	{
		cout << "malloc failed!" << endl;
		exit(-1);
	}
	NullNode ->left = NullNode ->right = NullNode ->parent = NULL;
	NullNode ->color = BLACK;

	//红黑树默认初始化操作
	root = NullNode;
}

RBTree::~RBTree()
{
	//删除红黑树节点所占的空间
	__freeRBTree(root);
}

//向红黑树中插入新节点的函数
//参数解释：
//key：新节点的键值
void RBTree::insert(key_t key)
{
	rb_node_t *y = NullNode,*x = root;
	rb_node_t *node = __newNode(key);
	//从树根往下搜索，寻找新节点的插入位置
	while(x != NullNode)
	{
		y = x;
		if(key < x ->key)
			x = x ->left;
		else 
			x = x ->right;
	}
	node ->parent = y;

	//如果原树为空，需要设置根节点
	if(NullNode == y)
		root = node;
	else{
		//修改指针，将新节点插入在正确的位置上
		if (key < y ->key)
			y ->left = node;
		else
			y ->right = node;
	}

	//调整，以保持红黑树性质
	__insertFixUp(node);
}

//函数：删除红黑树中指定节点
void RBTree::deleteNode(key_t key)
{
	rb_node_t *node = searchNode(key);
	if (NullNode == node)
	{
		cout << "Warnning： the node that has the key value not exist！Delete failed！" << endl;
		return;
	}
	//删除节点的思想：
	//如果被删除节点不具有两个非空孩子，则直接删除这个节点，用其位移子节点替代其位置；
	//如果有两个非空孩子，则用把它的直接后继节点内容复制到它的位置，然后以同样的方式删除这个后继节点
	//注意：节点的后继节点不可能有两个非空孩子，因此此传递过程最多只进行一次。
	rb_node_t *nodeDeleted;//指向实际将要被删除的节点
	//节点node有一个孩子节点为空，实际要被删除的节点即当前节点
	if(NullNode == node ->left || NullNode == node ->right)
		nodeDeleted = node;
	else
		//否则，实际要被删除的节点为当前节点的直接后继节点
		nodeDeleted = getTreeSuccessor(node);

	rb_node_t *x;//执行实际要被删除节点的孩子节点，用它替换实际被删除节点的位置
	if(nodeDeleted ->left != NullNode)
		x = nodeDeleted ->left;
	else
		x = nodeDeleted ->right;

	x ->parent = nodeDeleted ->parent;
	//实际被删除的节点是根节点
	if(NullNode == nodeDeleted ->parent)
		root = x;//修改根节点
	else if(nodeDeleted == nodeDeleted ->parent ->left)
		nodeDeleted ->parent ->left = x;//修改实际被删除节点的父节点的孩子指针
	else
		nodeDeleted ->parent ->right= x;

	//如果实际被删除的节点是当前节点的后继节点，则需要进行元素拷贝操作
	if(nodeDeleted != node)
		node ->key = nodeDeleted ->key;

	//实际被删除节点是黑节点，红黑树性质被破坏，需进行调整
	if(BLACK == nodeDeleted ->color)
		__deleteNodeFixUp(x);
}

//函数：搜索键值为某一特定值的节点
//返回值为哨兵节点表示搜寻失败
rb_node_t* RBTree::searchNode(key_t key)
{
	rb_node_t *node = root,*parent = NullNode;
	while(node != NullNode)
	{
		parent = node;
		if (key < node ->key)
			node = node ->left;
		else if(key > node ->key)
			node = node ->right;
		else
		{
			cout << "OK：find the node valued " << key << " in the RBTree！" << endl;
			return node;
		}
	}

	cout << "Warning： cannot find the node valued " << key << " ！" << endl;
	return NullNode;
}

//左旋转操作函数
//参数解释：
//x：需要做左旋转操作的节点
void RBTree::rotateLeft(rb_node_t *x)
{
	rb_node_t *y = x ->right;//设置y节点为x的右孩子
	x ->right = y ->left;//x的右孩子指针指向y节点的左孩子
	//如果y节点的左孩子非空，则需要修改y节点左孩子节点的父节点指针
	if (y ->left != NullNode)
		y ->left ->parent = x;

	y ->parent = x ->parent;//修改y节点的父指针
	if (NullNode == x ->parent)//x是根节点，则需要修改根节点
		root = y;
	else
	{
		//修改x节点的父节点的孩子指针
		if (x == x ->parent ->left)
			x ->parent ->left = y;
		else
			x ->parent ->right = y;
	}

	//让x成为y的左孩子
	y ->left = x;
	x ->parent = y;
}

//右旋转操作函数
//参数解释：
//x：需要做右旋转操作的节点
void RBTree::rotateRight(rb_node_t *y)
{
	rb_node_t *x = y ->left;
	y ->left = x ->right;
	if(x ->right != NullNode)
		x ->right ->parent = y;

	x ->parent = y ->parent;
	if (NullNode == y ->parent)
		root = x;
	else{
		if(y == y ->parent ->left)
			y ->parent ->left = x;
		else
			y ->parent ->right = x;
	}
	x ->right = y;
	y ->parent = x;
}

rb_node_t* RBTree::__newNode(key_t key)
{
	rb_node_t *node = (rb_node_t *)malloc(sizeof(struct rb_node_t));

	//分配内存失败
	if (!node)
	{
		cout << "malloc failed!" << endl;
		exit(-1);
	}

	node ->key = key;
	node ->color = RED;//新插入的节点被赋予红色
	node ->left = node ->right = NullNode;
	node ->parent = NullNode;

	return node;
}

//函数：调整新生成的树，以保持红黑树性质
void RBTree::__insertFixUp(rb_node_t *node)
{
	//插入一个新节点之后，唯一可能被破坏的性质是（2）和（4）
	//即根节点必须为黑色以及红节点子女必须为黑色
	//而且至多只有一个性质被破坏
	while(RED == node ->parent->color)//节点node的父节点为红节点时进入循环
	{
		//这里可以分为两种情况，而且是相互对称的
		if(node ->parent == node ->parent ->parent ->left)//节点node的父节点是左孩子节点
		{
			rb_node_t *y = node ->parent ->parent ->right;//节点node的叔叔节点
			//情况1：节点node的叔叔是红节点
			if (RED == y ->color)
			{
				//将节点node的父节点和叔叔设置为黑色，将祖父节点设置为红色
				//然后将指针node设置为其祖父节点，重复while循环
				node ->parent ->color = BLACK;
				y ->color = BLACK;
				node ->parent ->parent ->color = RED;
				node = node ->parent ->parent;
			}			
			else 
			{
				//情况2：节点node的叔叔是黑色节点，且node是右孩子
				if (node == node ->parent ->right)
				{
					//左旋操作，将其变为情况3
					node = node ->parent;
					rotateLeft(node);
				}
				//情况3：节点node的叔叔是黑色节点，且node是左孩子
				//修改当前节点的父节点及祖父节点的颜色，并执行一次右旋转
				node ->parent ->color = BLACK;
				node ->parent ->parent ->color = RED;
				rotateRight(node ->parent ->parent);
			}
		}
		else{
			rb_node_t *y = node ->parent ->parent ->left;//节点node的叔叔节点
			//情况1：节点node的叔叔是红节点
			if (RED == y ->color)
			{
				//将节点node的父节点和叔叔设置为黑色，将祖父节点设置为红色
				//然后将指针node设置为其祖父节点，重复while循环
				node ->parent ->color = BLACK;
				y ->color = BLACK;
				node ->parent ->parent ->color = RED;
				node = node ->parent ->parent;
			}			
			else 
			{
				//情况2：节点node的叔叔是黑色节点，且node是右孩子
				if (node == node ->parent ->left)
				{
					//左旋操作，将其变为情况3
					node = node ->parent;
					rotateRight(node);
				}
				//情况3：节点node的叔叔是黑色节点，且node是左孩子
				//修改当前节点的父节点及祖父节点的颜色，并执行一次右旋转
				node ->parent ->color = BLACK;
				node ->parent ->parent ->color = RED;
				rotateLeft(node ->parent ->parent);
			}
		}
	}

	root ->color = BLACK;//设置根节点颜色
}

void RBTree::__deleteNodeFixUp(rb_node_t *node)
{
	//如果被删除的节点是黑节点，则红黑性质被破坏。补救的方法是将其黑色下推至其子节点，把这个子节点视为
	//还有额外的一重黑色（其颜色应该是“红黑”或者“黑黑”）

	//while循环中，node总是指向双重黑色节点
	//循环的目标是将黑色沿树上移
	while(node != root && node ->color == BLACK)
	{
		//Case 1：当前节点是左孩子
		if (node == node ->parent ->left)
		{
			rb_node_t *brother = node ->parent ->right;//兄弟节点
			//情况1：兄弟节点为红节点
			if (RED == brother ->color)
			{
				//改变兄弟节点和父节点的颜色，并执行一次左旋转，使情况1变为情况2、3或4
				brother ->color = BLACK;
				node ->parent ->color = RED;
				rotateLeft(node ->parent);
				brother = node ->parent ->right;
			}
			//情况2：兄弟节点为黑节点，且兄弟节点的两个孩子都是黑节点
			if (BLACK == brother ->left ->color && BLACK == brother ->right ->color)
			{
				brother ->color = RED;
				//重新设置当前节点，开始while循环
				node = node ->parent;
			}
			else{
				//情况3：兄弟节点为黑节点，且兄弟节点的左孩子是红节点，右孩子是黑节点
				if (BLACK == brother ->right ->color)
				{
					//改变节点颜色和进行旋转操作，将情况3变为情况4
					brother ->left ->color = BLACK;
					brother ->color = RED;
					rotateRight(brother);
					brother = node ->parent ->right;
				}
				//情况4：兄弟节点是黑节点，兄弟节点的右孩子是红节点
				brother ->color = node ->parent ->color;
				node ->parent ->color = BLACK;
				brother ->right ->color = BLACK;
				rotateLeft(node ->parent);
				node = root;//将当前节点置为根节点
			}
		}
		//Case 2：当前节点是右孩子，操作与上一种情况类似
		else{
			rb_node_t *brother = node ->parent ->left;//兄弟节点
			//情况1：兄弟节点为红节点
			if (RED == brother ->color)
			{
				//改变兄弟节点和父节点的颜色，并执行一次左旋转，使情况1变为情况2、3或4
				brother ->color = BLACK;
				node ->parent ->color = RED;
				rotateRight(node ->parent);
				brother = node ->parent ->left;
			}
			//情况2：兄弟节点为黑节点，且兄弟节点的两个孩子都是黑节点
			if (BLACK == brother ->left ->color && BLACK == brother ->right ->color)
			{
				brother ->color = RED;
				node = node ->parent;
			}
			else{
				//情况3：兄弟节点为黑节点，且兄弟节点的左孩子是红节点，右孩子是黑节点
				if (BLACK == brother ->left ->color)
				{
					brother ->right ->color = BLACK;
					brother ->color = RED;
					rotateLeft(brother);
					brother = node ->parent ->left;
				}
				//情况4：兄弟节点是黑节点，兄弟节点的右孩子是红节点
				brother ->color = node ->parent ->color;
				node ->parent ->color = BLACK;
				brother ->left ->color = BLACK;
				rotateRight(node ->parent);
				node = root;//将当前节点置为根节点
			}
		}
	}

	node ->color = BLACK;
}

//函数：得到指定节点的后继节点
rb_node_t* RBTree::getTreeSuccessor(rb_node_t *node)
{
	rb_node_t *tempNode = node;

	//节点右孩子非空
	if(tempNode ->right != NullNode)
		return getMinNode(tempNode ->right);

	rb_node_t *y = tempNode ->parent;
	//如果当前节点是右孩子，上溯
	while(y != NullNode && tempNode == y ->right)
	{
		tempNode = y;
		y = y ->parent;
	}

	return y;
}

//函数：得到子树中值最小的节点
rb_node_t* RBTree::getMinNode(rb_node_t *t)
{
	rb_node_t *tempNode = t;
	while(tempNode ->left != NullNode)
		tempNode = tempNode ->left;

	return tempNode;
}

rb_node_t* RBTree::getMaxNode(rb_node_t *t)
{
	rb_node_t *tempNode = t;
	while(tempNode ->right != NullNode)
		tempNode = tempNode ->right;
	
	return tempNode;
}

//函数：释放红黑树节点所占的空间
void RBTree::__freeRBTree(rb_node_t *t)
{
	if (NullNode == t)//树为空
		return;
	//节点的左右子树均为哨兵节点，则直接释放节点所占空间
	if (NullNode == t ->left && NullNode == t ->right)
	{
		free(t);
		return;
	}
	if (t ->left != NullNode)
		__freeRBTree(t ->left);
	if (t ->right != NullNode)
		__freeRBTree(t ->right);
}