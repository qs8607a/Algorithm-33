//红黑树C++编程实现
//Author：江南烟雨（xiajunhust@gmail.com）
//Date：2013-02-22

//参考资料：《算法导论（第二版）》第163页，第十三章《红黑树》

#ifndef RBTREE_H
#define RBTREE_H

typedef int key_t;//红黑树节点键值类型

//红黑树颜色值类型定义
typedef enum color_t{
	RED = 0,
	BLACK = 1
}color_t;

//红黑树节点数据结构定义（节点包括五个域）
typedef struct rb_node_t{
	struct rb_node_t *left,*right,*parent;//节点左右孩子指针以及父节点指针
	key_t key;//键值
	color_t color;//节点颜色
}rb_node_t;

//红黑树类封装
class RBTree{
private:
	rb_node_t *root;

	rb_node_t *NullNode;//空节点（哨兵节点）

public:
	RBTree();
	~RBTree();

	void insert(key_t key);//插入新节点
	void deleteNode(key_t key);//删除指定节点
	rb_node_t* searchNode(key_t key);//搜索键值为某特定值的节点

	void rotateLeft(rb_node_t *x);//左旋转操作
	void rotateRight(rb_node_t *y);//右旋转操作

	//一些辅助函数
	rb_node_t* __newNode(key_t key);//生成新的红黑树节点
	void __insertFixUp(rb_node_t *node);//插入节点调整，以保持红黑树的性质
	void __deleteNodeFixUp(rb_node_t *node);//删除节点调整，以保持红黑树性质
	rb_node_t *getTreeSuccessor(rb_node_t *node);//得到指定节点的后继节点
	rb_node_t *getMinNode(rb_node_t *t);//得到子树中值最小的节点
	rb_node_t *getMaxNode(rb_node_t *t);//得到子树中值最大的节点
	void __freeRBTree(rb_node_t *t);//释放红黑树节点所占空间
};

#endif