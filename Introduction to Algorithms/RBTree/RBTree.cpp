#include "RBTree.h"

#include <iostream>

using namespace std;

RBTree::RBTree()
{
	NullNode = (rb_node_t *)malloc(sizeof(struct rb_node_t));
	//�����ڴ�ʧ��
	if (!NullNode)
	{
		cout << "malloc failed!" << endl;
		exit(-1);
	}
	NullNode ->left = NullNode ->right = NullNode ->parent = NULL;
	NullNode ->color = BLACK;

	//�����Ĭ�ϳ�ʼ������
	root = NullNode;
}

RBTree::~RBTree()
{
	//ɾ��������ڵ���ռ�Ŀռ�
	__freeRBTree(root);
}

//�������в����½ڵ�ĺ���
//�������ͣ�
//key���½ڵ�ļ�ֵ
void RBTree::insert(key_t key)
{
	rb_node_t *y = NullNode,*x = root;
	rb_node_t *node = __newNode(key);
	//����������������Ѱ���½ڵ�Ĳ���λ��
	while(x != NullNode)
	{
		y = x;
		if(key < x ->key)
			x = x ->left;
		else 
			x = x ->right;
	}
	node ->parent = y;

	//���ԭ��Ϊ�գ���Ҫ���ø��ڵ�
	if(NullNode == y)
		root = node;
	else{
		//�޸�ָ�룬���½ڵ��������ȷ��λ����
		if (key < y ->key)
			y ->left = node;
		else
			y ->right = node;
	}

	//�������Ա��ֺ��������
	__insertFixUp(node);
}

//������ɾ���������ָ���ڵ�
void RBTree::deleteNode(key_t key)
{
	rb_node_t *node = searchNode(key);
	if (NullNode == node)
	{
		cout << "Warnning�� the node that has the key value not exist��Delete failed��" << endl;
		return;
	}
	//ɾ���ڵ��˼�룺
	//�����ɾ���ڵ㲻���������ǿպ��ӣ���ֱ��ɾ������ڵ㣬����λ���ӽڵ������λ�ã�
	//����������ǿպ��ӣ����ð�����ֱ�Ӻ�̽ڵ����ݸ��Ƶ�����λ�ã�Ȼ����ͬ���ķ�ʽɾ�������̽ڵ�
	//ע�⣺�ڵ�ĺ�̽ڵ㲻�����������ǿպ��ӣ���˴˴��ݹ������ֻ����һ�Ρ�
	rb_node_t *nodeDeleted;//ָ��ʵ�ʽ�Ҫ��ɾ���Ľڵ�
	//�ڵ�node��һ�����ӽڵ�Ϊ�գ�ʵ��Ҫ��ɾ���Ľڵ㼴��ǰ�ڵ�
	if(NullNode == node ->left || NullNode == node ->right)
		nodeDeleted = node;
	else
		//����ʵ��Ҫ��ɾ���Ľڵ�Ϊ��ǰ�ڵ��ֱ�Ӻ�̽ڵ�
		nodeDeleted = getTreeSuccessor(node);

	rb_node_t *x;//ִ��ʵ��Ҫ��ɾ���ڵ�ĺ��ӽڵ㣬�����滻ʵ�ʱ�ɾ���ڵ��λ��
	if(nodeDeleted ->left != NullNode)
		x = nodeDeleted ->left;
	else
		x = nodeDeleted ->right;

	x ->parent = nodeDeleted ->parent;
	//ʵ�ʱ�ɾ���Ľڵ��Ǹ��ڵ�
	if(NullNode == nodeDeleted ->parent)
		root = x;//�޸ĸ��ڵ�
	else if(nodeDeleted == nodeDeleted ->parent ->left)
		nodeDeleted ->parent ->left = x;//�޸�ʵ�ʱ�ɾ���ڵ�ĸ��ڵ�ĺ���ָ��
	else
		nodeDeleted ->parent ->right= x;

	//���ʵ�ʱ�ɾ���Ľڵ��ǵ�ǰ�ڵ�ĺ�̽ڵ㣬����Ҫ����Ԫ�ؿ�������
	if(nodeDeleted != node)
		node ->key = nodeDeleted ->key;

	//ʵ�ʱ�ɾ���ڵ��Ǻڽڵ㣬��������ʱ��ƻ�������е���
	if(BLACK == nodeDeleted ->color)
		__deleteNodeFixUp(x);
}

//������������ֵΪĳһ�ض�ֵ�Ľڵ�
//����ֵΪ�ڱ��ڵ��ʾ��Ѱʧ��
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
			cout << "OK��find the node valued " << key << " in the RBTree��" << endl;
			return node;
		}
	}

	cout << "Warning�� cannot find the node valued " << key << " ��" << endl;
	return NullNode;
}

//����ת��������
//�������ͣ�
//x����Ҫ������ת�����Ľڵ�
void RBTree::rotateLeft(rb_node_t *x)
{
	rb_node_t *y = x ->right;//����y�ڵ�Ϊx���Һ���
	x ->right = y ->left;//x���Һ���ָ��ָ��y�ڵ������
	//���y�ڵ�����ӷǿգ�����Ҫ�޸�y�ڵ����ӽڵ�ĸ��ڵ�ָ��
	if (y ->left != NullNode)
		y ->left ->parent = x;

	y ->parent = x ->parent;//�޸�y�ڵ�ĸ�ָ��
	if (NullNode == x ->parent)//x�Ǹ��ڵ㣬����Ҫ�޸ĸ��ڵ�
		root = y;
	else
	{
		//�޸�x�ڵ�ĸ��ڵ�ĺ���ָ��
		if (x == x ->parent ->left)
			x ->parent ->left = y;
		else
			x ->parent ->right = y;
	}

	//��x��Ϊy������
	y ->left = x;
	x ->parent = y;
}

//����ת��������
//�������ͣ�
//x����Ҫ������ת�����Ľڵ�
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

	//�����ڴ�ʧ��
	if (!node)
	{
		cout << "malloc failed!" << endl;
		exit(-1);
	}

	node ->key = key;
	node ->color = RED;//�²���Ľڵ㱻�����ɫ
	node ->left = node ->right = NullNode;
	node ->parent = NullNode;

	return node;
}

//���������������ɵ������Ա��ֺ��������
void RBTree::__insertFixUp(rb_node_t *node)
{
	//����һ���½ڵ�֮��Ψһ���ܱ��ƻ��������ǣ�2���ͣ�4��
	//�����ڵ����Ϊ��ɫ�Լ���ڵ���Ů����Ϊ��ɫ
	//��������ֻ��һ�����ʱ��ƻ�
	while(RED == node ->parent->color)//�ڵ�node�ĸ��ڵ�Ϊ��ڵ�ʱ����ѭ��
	{
		//������Է�Ϊ����������������໥�ԳƵ�
		if(node ->parent == node ->parent ->parent ->left)//�ڵ�node�ĸ��ڵ������ӽڵ�
		{
			rb_node_t *y = node ->parent ->parent ->right;//�ڵ�node������ڵ�
			//���1���ڵ�node�������Ǻ�ڵ�
			if (RED == y ->color)
			{
				//���ڵ�node�ĸ��ڵ����������Ϊ��ɫ�����游�ڵ�����Ϊ��ɫ
				//Ȼ��ָ��node����Ϊ���游�ڵ㣬�ظ�whileѭ��
				node ->parent ->color = BLACK;
				y ->color = BLACK;
				node ->parent ->parent ->color = RED;
				node = node ->parent ->parent;
			}			
			else 
			{
				//���2���ڵ�node�������Ǻ�ɫ�ڵ㣬��node���Һ���
				if (node == node ->parent ->right)
				{
					//���������������Ϊ���3
					node = node ->parent;
					rotateLeft(node);
				}
				//���3���ڵ�node�������Ǻ�ɫ�ڵ㣬��node������
				//�޸ĵ�ǰ�ڵ�ĸ��ڵ㼰�游�ڵ����ɫ����ִ��һ������ת
				node ->parent ->color = BLACK;
				node ->parent ->parent ->color = RED;
				rotateRight(node ->parent ->parent);
			}
		}
		else{
			rb_node_t *y = node ->parent ->parent ->left;//�ڵ�node������ڵ�
			//���1���ڵ�node�������Ǻ�ڵ�
			if (RED == y ->color)
			{
				//���ڵ�node�ĸ��ڵ����������Ϊ��ɫ�����游�ڵ�����Ϊ��ɫ
				//Ȼ��ָ��node����Ϊ���游�ڵ㣬�ظ�whileѭ��
				node ->parent ->color = BLACK;
				y ->color = BLACK;
				node ->parent ->parent ->color = RED;
				node = node ->parent ->parent;
			}			
			else 
			{
				//���2���ڵ�node�������Ǻ�ɫ�ڵ㣬��node���Һ���
				if (node == node ->parent ->left)
				{
					//���������������Ϊ���3
					node = node ->parent;
					rotateRight(node);
				}
				//���3���ڵ�node�������Ǻ�ɫ�ڵ㣬��node������
				//�޸ĵ�ǰ�ڵ�ĸ��ڵ㼰�游�ڵ����ɫ����ִ��һ������ת
				node ->parent ->color = BLACK;
				node ->parent ->parent ->color = RED;
				rotateLeft(node ->parent ->parent);
			}
		}
	}

	root ->color = BLACK;//���ø��ڵ���ɫ
}

void RBTree::__deleteNodeFixUp(rb_node_t *node)
{
	//�����ɾ���Ľڵ��Ǻڽڵ㣬�������ʱ��ƻ������ȵķ����ǽ����ɫ���������ӽڵ㣬������ӽڵ���Ϊ
	//���ж����һ�غ�ɫ������ɫӦ���ǡ���ڡ����ߡ��ںڡ���

	//whileѭ���У�node����ָ��˫�غ�ɫ�ڵ�
	//ѭ����Ŀ���ǽ���ɫ��������
	while(node != root && node ->color == BLACK)
	{
		//Case 1����ǰ�ڵ�������
		if (node == node ->parent ->left)
		{
			rb_node_t *brother = node ->parent ->right;//�ֵܽڵ�
			//���1���ֵܽڵ�Ϊ��ڵ�
			if (RED == brother ->color)
			{
				//�ı��ֵܽڵ�͸��ڵ����ɫ����ִ��һ������ת��ʹ���1��Ϊ���2��3��4
				brother ->color = BLACK;
				node ->parent ->color = RED;
				rotateLeft(node ->parent);
				brother = node ->parent ->right;
			}
			//���2���ֵܽڵ�Ϊ�ڽڵ㣬���ֵܽڵ���������Ӷ��Ǻڽڵ�
			if (BLACK == brother ->left ->color && BLACK == brother ->right ->color)
			{
				brother ->color = RED;
				//�������õ�ǰ�ڵ㣬��ʼwhileѭ��
				node = node ->parent;
			}
			else{
				//���3���ֵܽڵ�Ϊ�ڽڵ㣬���ֵܽڵ�������Ǻ�ڵ㣬�Һ����Ǻڽڵ�
				if (BLACK == brother ->right ->color)
				{
					//�ı�ڵ���ɫ�ͽ�����ת�����������3��Ϊ���4
					brother ->left ->color = BLACK;
					brother ->color = RED;
					rotateRight(brother);
					brother = node ->parent ->right;
				}
				//���4���ֵܽڵ��Ǻڽڵ㣬�ֵܽڵ���Һ����Ǻ�ڵ�
				brother ->color = node ->parent ->color;
				node ->parent ->color = BLACK;
				brother ->right ->color = BLACK;
				rotateLeft(node ->parent);
				node = root;//����ǰ�ڵ���Ϊ���ڵ�
			}
		}
		//Case 2����ǰ�ڵ����Һ��ӣ���������һ���������
		else{
			rb_node_t *brother = node ->parent ->left;//�ֵܽڵ�
			//���1���ֵܽڵ�Ϊ��ڵ�
			if (RED == brother ->color)
			{
				//�ı��ֵܽڵ�͸��ڵ����ɫ����ִ��һ������ת��ʹ���1��Ϊ���2��3��4
				brother ->color = BLACK;
				node ->parent ->color = RED;
				rotateRight(node ->parent);
				brother = node ->parent ->left;
			}
			//���2���ֵܽڵ�Ϊ�ڽڵ㣬���ֵܽڵ���������Ӷ��Ǻڽڵ�
			if (BLACK == brother ->left ->color && BLACK == brother ->right ->color)
			{
				brother ->color = RED;
				node = node ->parent;
			}
			else{
				//���3���ֵܽڵ�Ϊ�ڽڵ㣬���ֵܽڵ�������Ǻ�ڵ㣬�Һ����Ǻڽڵ�
				if (BLACK == brother ->left ->color)
				{
					brother ->right ->color = BLACK;
					brother ->color = RED;
					rotateLeft(brother);
					brother = node ->parent ->left;
				}
				//���4���ֵܽڵ��Ǻڽڵ㣬�ֵܽڵ���Һ����Ǻ�ڵ�
				brother ->color = node ->parent ->color;
				node ->parent ->color = BLACK;
				brother ->left ->color = BLACK;
				rotateRight(node ->parent);
				node = root;//����ǰ�ڵ���Ϊ���ڵ�
			}
		}
	}

	node ->color = BLACK;
}

//�������õ�ָ���ڵ�ĺ�̽ڵ�
rb_node_t* RBTree::getTreeSuccessor(rb_node_t *node)
{
	rb_node_t *tempNode = node;

	//�ڵ��Һ��ӷǿ�
	if(tempNode ->right != NullNode)
		return getMinNode(tempNode ->right);

	rb_node_t *y = tempNode ->parent;
	//�����ǰ�ڵ����Һ��ӣ�����
	while(y != NullNode && tempNode == y ->right)
	{
		tempNode = y;
		y = y ->parent;
	}

	return y;
}

//�������õ�������ֵ��С�Ľڵ�
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

//�������ͷź�����ڵ���ռ�Ŀռ�
void RBTree::__freeRBTree(rb_node_t *t)
{
	if (NullNode == t)//��Ϊ��
		return;
	//�ڵ������������Ϊ�ڱ��ڵ㣬��ֱ���ͷŽڵ���ռ�ռ�
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