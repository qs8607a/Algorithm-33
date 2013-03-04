//�����C++���ʵ��
//Author���������꣨xiajunhust@gmail.com��
//Date��2013-02-22

//�ο����ϣ����㷨���ۣ��ڶ��棩����163ҳ����ʮ���¡��������

#ifndef RBTREE_H
#define RBTREE_H

typedef int key_t;//������ڵ��ֵ����

//�������ɫֵ���Ͷ���
typedef enum color_t{
	RED = 0,
	BLACK = 1
}color_t;

//������ڵ����ݽṹ���壨�ڵ���������
typedef struct rb_node_t{
	struct rb_node_t *left,*right,*parent;//�ڵ����Һ���ָ���Լ����ڵ�ָ��
	key_t key;//��ֵ
	color_t color;//�ڵ���ɫ
}rb_node_t;

//��������װ
class RBTree{
private:
	rb_node_t *root;

	rb_node_t *NullNode;//�սڵ㣨�ڱ��ڵ㣩

public:
	RBTree();
	~RBTree();

	void insert(key_t key);//�����½ڵ�
	void deleteNode(key_t key);//ɾ��ָ���ڵ�
	rb_node_t* searchNode(key_t key);//������ֵΪĳ�ض�ֵ�Ľڵ�

	void rotateLeft(rb_node_t *x);//����ת����
	void rotateRight(rb_node_t *y);//����ת����

	//һЩ��������
	rb_node_t* __newNode(key_t key);//�����µĺ�����ڵ�
	void __insertFixUp(rb_node_t *node);//����ڵ�������Ա��ֺ����������
	void __deleteNodeFixUp(rb_node_t *node);//ɾ���ڵ�������Ա��ֺ��������
	rb_node_t *getTreeSuccessor(rb_node_t *node);//�õ�ָ���ڵ�ĺ�̽ڵ�
	rb_node_t *getMinNode(rb_node_t *t);//�õ�������ֵ��С�Ľڵ�
	rb_node_t *getMaxNode(rb_node_t *t);//�õ�������ֵ���Ľڵ�
	void __freeRBTree(rb_node_t *t);//�ͷź�����ڵ���ռ�ռ�
};

#endif