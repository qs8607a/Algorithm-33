//B-�����ʵ��
//���㷨���ۣ��ڶ��棩����18�� B��
//Author����������
//E-Mail��xiajunhust@gmail.com

#include <iostream>

//ע�⣺�ڴ���ͷŲ���

//B-Tree�ڵ����ݽṹ����
template <class KeyT>
struct BTreeNode{
	int n;//��ǰ�ڵ��д洢�Ĺؼ�����
	KeyT *keys;//ָ�����йؼ��ֵ�ָ��
	bool isLeaf;//��ʶ��ǰ�ڵ��Ƿ���Ҷ��
	struct BTreeNode **childs;//ָ������ָ����Ů��ָ��
	struct BTreeNode *parent;//ָ�򸸽ڵ��ָ��
};

//B-Tree���װ
template <class KeyT>
class BTree{
public:
	
private:
	typedef struct BTreeNode<KeyT>* BTreeNodeLink;//ָ��ڵ����͵�ָ�����Ͷ���

	BTreeNodeLink T;//���ڵ�
	//ÿ���Ǹ��ڵ�������t-1���ؼ��֣�����2t-1���ؼ���
	int t;//B������С����

public:
	BTree(int tVal = 2);
	BTreeNodeLink searchBTree(BTreeNodeLink T,KeyT k,int &index);//��B��������ĳ�ؼ���
	BTreeNodeLink getRoot();//���ص�ǰB���ĸ��ڵ�
	void insertBTreeNode(KeyT k);//��B���в���ؼ���
	void deleteBTreeKey(BTreeNodeLink T,KeyT k);//��B����ɾ���ض��ؼ���
	void createBTree(KeyT *keyValues);//����B��
	void printBTreeBFS(BTreeNodeLink t);//��α��������tΪ��������B��

	void splitChild(BTreeNodeLink x,int i,BTreeNodeLink y);//���������ӽڵ�
	void insertBTreeNonFull(BTreeNodeLink x,KeyT k);//���ؼ��ֲ��뵽�Ը÷����ڵ�Ϊ��������
	BTreeNodeLink __allocateNode();//����һ���µĽڵ�
	void deleteNode(BTreeNodeLink node);//�ͷ�һ���ڵ���ռ�Ŀռ䣨����������Ů�ڵ���ռ�ռ䣩
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
	//�ݹ����ؼ���ʵ��
}

//��������B���������ض��ؼ���
//�������ͣ�
//T��Ҫ�����������ĸ�
//k��Ҫ�����Ĺؼ���
//index������ؼ������ڽڵ��йؼ��������е�����
//����ֵ���ؼ������ڵĽڵ�
template <class KeyT>
typename BTree<KeyT>::BTreeNodeLink BTree<KeyT>::searchBTree(BTreeNodeLink T,KeyT k,int &index)
{
	int i = 0;
	//�������ڵ�
	while(i < T->n && k > T->keys[i])
		++i;
	//�ڸ��ڵ�������������Ӧ�Ĺؼ���
	if(i < T->n && k == T->keys[i])
	{
		index = i;
		//cout << "OK : search the key " << k << " successfully ! " << endl;
		//cout << "The index : " << index << endl;
		return T;
	}

	//�����������еݹ�����
	if(T->isLeaf)//��ǰ�������ڵ��Ѿ���Ҷ�ӣ�������ʧ��
	{
		//cout << "Warnning : search the key " << k << "  failed ! " << endl;
		index = -1;
		return NULL;
	}
	else
	{
		return searchBTree(T->childs[i],k,index);
	}
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

//������ɾ���ض��ؼ���
//�������ͣ�
//K��Ҫɾ���Ĺؼ���
//TSubTree��Ҫɾ���Ĺؼ������ڽڵ�ָ��
template <class KeyT>
void BTree<KeyT>::deleteBTreeKey(BTreeNodeLink TSubTree,KeyT k)
{
	if(NULL == TSubTree)
		return;

	//�ж���Ҫɾ���Ĺؼ����Ƿ�������B����
	int searchedIndex;
	BTreeNodeLink searchedNode = searchBTree(TSubTree,k,searchedIndex);
	if(NULL == searchedNode)
	{
		cout << "The keyword to be deleted not exist in this B-tree!" << endl;
		return;
	}

	//�ж�Ҫ��ɾ���Ĺؼ����Ƿ��ڵ�ǰ�ڵ�TSubTree��
	int keyIndex = -1;
	for(int j = 0;j < TSubTree->n;++j)
	{
		if(k == TSubTree->keys[j])
		{
			keyIndex = j;
			break;
		}
	}

	//���Ҫ��ɾ���Ĺؼ��ִ��ڵ�ǰ�ڵ����ҵ�ǰ�ڵ���Ҷ�ڵ�
	if(keyIndex != -1 && TSubTree->isLeaf == true)
	{
		//ֱ��ɾ��
		for(int j = keyIndex;j < TSubTree->n - 1;++j)
			TSubTree->keys[j] = TSubTree->keys[j + 1];
		TSubTree->n = TSubTree->n - 1;

		return;
	}
	//���Ҫ��ɾ���Ĺؼ��ִ��ڵ�ǰ�ڵ����ҵ�ǰ�ڵ㲻��Ҷ�ڵ�
	else if (keyIndex != -1 && TSubTree->isLeaf == false)
	{
		//��ɾ���ؼ������ڽڵ����ڽڵ㣬�������²���
		//Ѱ��ǰ��
		BTreeNodeLink predecessorNode = TSubTree->childs[keyIndex];
		//Ѱ�Һ��
		BTreeNodeLink succeedNode = TSubTree->childs[keyIndex + 1];
		//���ǰ���ڵ��йؼ�����Ŀ����t-1������ǰ��y�����ؼ��������ɾ���Ĺؼ��֣�Ȼ��ɾ��ǰ�������ؼ���
		if(predecessorNode->n > t - 1)
		{
			KeyT predecessorKey = predecessorNode->keys[predecessorNode->n - 1];
			TSubTree->keys[keyIndex] = predecessorKey;
			deleteBTreeKey(predecessorNode,predecessorKey);
		}
		//�����̽ڵ��йؼ�����Ŀ����t-1�����Ժ��z����С�ؼ��������ɾ���Ĺؼ��֣�Ȼ��ɾ���������С�ؼ���
		else if (succeedNode->n > t - 1)
		{
			KeyT succeedKey = succeedNode->keys[0];
			TSubTree->keys[keyIndex] = succeedKey;
			deleteBTreeKey(succeedNode,succeedKey);
		}
		//ǰ��y�ͺ��z�ڵ��йؼ�����Ŀ��������Ҫ��
		else
		{
			//��Ҫ����ɾ���Ĺؼ��ֺ�z�ϲ���y��ʹ��TSubTreeʧȥk�Լ�ָ��z��ָ�룬Ȼ���y��ɾ��k
			predecessorNode->keys[predecessorNode->n] = k;
			for(int j = 0;j < t - 1;++j)
				predecessorNode->keys[t + j] = succeedNode->keys[j];
			predecessorNode->n = 2 * t - 1;
			//�޸Ľڵ�TSubTree
			for(int j = keyIndex;j < TSubTree->n - 1;++j)
				TSubTree->keys[j] = TSubTree->keys[j + 1];
			for(int j = keyIndex + 1;j < TSubTree->n;++j)
				TSubTree->childs[j] = TSubTree->childs[j + 1];
			TSubTree->n = TSubTree->n - 1;

			//����ϲ��ڵ��TSubTree�йؼ�����С��t - 1��ֻ������TSubTree�Ǹ��ڵ�
			if(0 == TSubTree->n)//���ڵ��йؼ�����Ϊ0�����߶��½�
				T = TSubTree->childs[keyIndex];

			//�ͷŽڵ�z��ռ�ռ�
			deleteNode(succeedNode);

			deleteBTreeKey(TSubTree->childs[keyIndex],k);
		}
	}
	//���Ҫ��ɾ���Ĺؼ��ֲ����ڵ�ǰ�ڵ���
	else
	{
		//����ȷ������Ҫ��ɾ���Ĺؼ��ֵ������ĸ�
		int subTreeIndex;
		BTreeNodeLink searchedNode;
		BTreeNodeLink deletedKeySubT;//����Ҫ��ɾ���Ĺؼ��ֵ������ĸ�
		for (int j = 0;j < TSubTree->n + 1;++j)
		{
			searchedNode = searchBTree(TSubTree->childs[j],k,subTreeIndex);
			if(searchedNode != NULL)
			{
				deletedKeySubT = TSubTree->childs[j];
				break;
			}
		}

		//����Ҫ��ɾ���Ĺؼ��ֵ������ĸ��ڵ�ؼ���������t������Ҫ���е���
		//�Ա�֤���ǽ���һ���������ٹؼ�����Ϊt�Ľڵ㣬Ȼ��ݹ����ɾ������
		if (deletedKeySubT->n < t)
		{
			int index;//��ǰ�������ڵ�ָ���ڸ��ڵ�ָ�������е�����
			for (int i = 0;i < TSubTree->n + 1;++i)
			{
				if(TSubTree->childs[i] == deletedKeySubT)
				{
					index = i;
					break;
				}
			}

			//�����һ�������ֵܰ�������t���ؼ���
			BTreeNodeLink leftBrotherNode = TSubTree->childs[index - 1];//���ֵܽڵ�
			BTreeNodeLink rightBrotherNode = TSubTree->childs[index + 1];//���ֵܽڵ�
			//������ֵܽڵ����ж���Ĺؼ��֣��������²���
			//�����ֵܽڵ������ؼ���������˫�׽ڵ㣬����˫�׽ڵ��д��ڸ����ƹؼ��ֵĹؼ�����������ɾ���ؼ������ڽڵ���
			if(index >= 1 && leftBrotherNode->n > t - 1)
			{
				//˫�׽ڵ��йؼ�������
				for(int j = deletedKeySubT->n - 1;j >= 0 ;--j)
					deletedKeySubT->keys[j + 1] = deletedKeySubT->keys[j];
				deletedKeySubT->keys[0] = TSubTree->keys[index - 1];
				deletedKeySubT->n = deletedKeySubT->n + 1;
				//���ֵܽڵ��йؼ�������
				TSubTree->keys[index - 1] = leftBrotherNode->keys[leftBrotherNode->n - 1];
				leftBrotherNode->n = leftBrotherNode->n - 1;
			}
			//������ֵܽڵ����ж���Ĺؼ��֣��������ƵĲ���
			else if(index < TSubTree->n + 1 && rightBrotherNode->n > t - 1)
			{
				//˫�׽ڵ��йؼ�������
				deletedKeySubT->keys[deletedKeySubT->n] = TSubTree->keys[index];
				deletedKeySubT->n = deletedKeySubT->n + 1;
				//���ֵܽڵ��йؼ�������
				TSubTree->keys[index] = rightBrotherNode->keys[0];
				for(int j = 0;j < rightBrotherNode->n - 1;++j)
					rightBrotherNode->keys[j] = rightBrotherNode->keys[j + 1];
				rightBrotherNode->n = rightBrotherNode->n - 1;
			}
			//�����ֵܽڵ�Ĺؼ�������������Ҫ����Ҫ���кϲ�����
			else
			{
				//����ǰ�ڵ㡢���ڵ��е�һ���ؼ��ֺϲ���һ���ֵܽڵ㣨ע���п���û�����ֵܽڵ�������ֵܽڵ�������
				if (index >= 1)//�����ֵܣ���ϲ������ֵ�
				{
					leftBrotherNode->keys[t - 1] = TSubTree->keys[index - 1];//���ڵ��еĹؼ���
					for(int j = 0;j < t - 1;++j)
						leftBrotherNode->keys[t + j] = deletedKeySubT->keys[j];
					leftBrotherNode->n = 2 * t - 1;//�ϲ�֮�����ֵܽڵ�ؼ�����Ϊ2t-1
					for(int j = 0;j < t;++j)
						leftBrotherNode->childs[t + j] = deletedKeySubT->childs[j];
					//���¸��ڵ�ؼ��ּ���Ůָ������
					for(int j = index - 1;j < TSubTree->n - 1;++j)
						TSubTree->keys[j] = TSubTree->keys[j + 1];
					TSubTree->n = TSubTree->n - 1;
					for(int j = index;j < TSubTree->n;++j)
						TSubTree->childs[j] = TSubTree->childs[j + 1];

					deleteNode(deletedKeySubT);

					deletedKeySubT = leftBrotherNode;//�ݹ�ɾ����������һ������

					////�ݹ�ɾ��ԭ�ڵ����ֵܽڵ��еĹؼ���k
					//deleteBTreeKey(leftBrotherNode,k);
				}
				else//���򣬺ϲ������ֵ�
				{
					deletedKeySubT->keys[t - 1] = TSubTree->keys[index - 1];//���ڵ��еĹؼ���
					for(int j = 0;j < t - 1;++j)
						deletedKeySubT->keys[t + j] = rightBrotherNode->keys[j];
					deletedKeySubT->n = 2 * t - 1;//�ϲ�֮�����ֵܽڵ�ؼ�����Ϊ2t-1
					for(int j = 0;j < t;++j)
						deletedKeySubT->childs[t + j] = rightBrotherNode->childs[j];
					//���¸��ڵ�ؼ��ּ���Ůָ������
					for(int j = index;j < TSubTree->n - 1;++j)
						TSubTree->keys[j] = TSubTree->keys[j + 1];
					TSubTree->n = TSubTree->n - 1;
					for(int j = index + 1;j < TSubTree->n;++j)
						TSubTree->childs[j] = TSubTree->childs[j + 1];

					deleteNode(rightBrotherNode);
					////�ݹ�ɾ��ԭ�ڵ����ֵܽڵ��еĹؼ���k
					//deleteBTreeKey(TSubTree,k);
				}
			}
		}
		
		//�ݹ��������н���ɾ������
		deleteBTreeKey(deletedKeySubT,k);
	}
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
	z->parent = x;

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
	newNode->parent = NULL;
	//��Ůָ���ʼ��
	for(int i = 0;i < 2 * t;++i)
		newNode->childs[i] = NULL;

	return newNode;
}

//�������ͷ�һ���ڵ���ռ�ռ�
template <class KeyT>
void BTree<KeyT>::deleteNode(typename BTree<KeyT>::BTreeNodeLink node)
{
	delete[] node->keys;
}