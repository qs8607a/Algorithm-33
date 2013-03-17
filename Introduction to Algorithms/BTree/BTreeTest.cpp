#include "BTree.h"

#include <iostream>

using namespace std;

int main()
{
	typedef char KeyType;
	const int NUM = 20;
	KeyType keyVals[NUM] = {'a','b','f','g','k','d','h','m','j','e','s','i','r','x','c','l','n','t','u','p'};
	BTree<KeyType> *BTreeObj = new BTree<KeyType>(3);
	BTreeObj->insertBTreeNode(keyVals[0]);
	cout << "Current B-Tree------------------------------------ : " << endl;
	BTreeObj->printBTreeBFS(BTreeObj->getRoot());
	BTreeObj->insertBTreeNode(keyVals[1]);
	cout << "Current B-Tree------------------------------------ : " << endl;
	BTreeObj->printBTreeBFS(BTreeObj->getRoot());
	BTreeObj->insertBTreeNode(keyVals[2]);
	cout << "Current B-Tree------------------------------------ : " << endl;
	BTreeObj->printBTreeBFS(BTreeObj->getRoot());
	BTreeObj->insertBTreeNode(keyVals[3]);
	cout << "Current B-Tree------------------------------------ : " << endl;
	BTreeObj->printBTreeBFS(BTreeObj->getRoot());
	BTreeObj->insertBTreeNode(keyVals[4]);
	cout << "Current B-Tree------------------------------------ : " << endl;
	BTreeObj->printBTreeBFS(BTreeObj->getRoot());
	BTreeObj->insertBTreeNode(keyVals[5]);
	cout << "Current B-Tree------------------------------------ : " << endl;
	BTreeObj->printBTreeBFS(BTreeObj->getRoot());
	BTreeObj->insertBTreeNode(keyVals[6]);
	cout << "Current B-Tree------------------------------------ : " << endl;
	BTreeObj->printBTreeBFS(BTreeObj->getRoot());
	BTreeObj->insertBTreeNode(keyVals[7]);
	cout << "Current B-Tree------------------------------------ : " << endl;
	BTreeObj->printBTreeBFS(BTreeObj->getRoot());
	BTreeObj->insertBTreeNode(keyVals[8]);
	cout << "Current B-Tree------------------------------------ : " << endl;
	BTreeObj->printBTreeBFS(BTreeObj->getRoot());
	BTreeObj->insertBTreeNode(keyVals[9]);
	cout << "Current B-Tree------------------------------------ : " << endl;
	BTreeObj->printBTreeBFS(BTreeObj->getRoot());
	BTreeObj->insertBTreeNode(keyVals[10]);
	cout << "Current B-Tree------------------------------------ : " << endl;
	BTreeObj->printBTreeBFS(BTreeObj->getRoot());
	BTreeObj->insertBTreeNode(keyVals[11]);
	cout << "Current B-Tree------------------------------------ : " << endl;
	BTreeObj->printBTreeBFS(BTreeObj->getRoot());
	BTreeObj->insertBTreeNode(keyVals[12]);
	cout << "Current B-Tree------------------------------------ : " << endl;
	BTreeObj->printBTreeBFS(BTreeObj->getRoot());
	BTreeObj->insertBTreeNode(keyVals[13]);
	cout << "Current B-Tree------------------------------------ : " << endl;
	BTreeObj->printBTreeBFS(BTreeObj->getRoot());
	BTreeObj->insertBTreeNode(keyVals[14]);
	cout << "Current B-Tree------------------------------------ : " << endl;
	BTreeObj->printBTreeBFS(BTreeObj->getRoot());
	BTreeObj->insertBTreeNode(keyVals[15]);
	cout << "Current B-Tree------------------------------------ : " << endl;
	BTreeObj->printBTreeBFS(BTreeObj->getRoot());
	BTreeObj->insertBTreeNode(keyVals[16]);
	cout << "Current B-Tree------------------------------------ : " << endl;
	BTreeObj->printBTreeBFS(BTreeObj->getRoot());
	BTreeObj->insertBTreeNode(keyVals[17]);
	cout << "Current B-Tree------------------------------------ : " << endl;
	BTreeObj->printBTreeBFS(BTreeObj->getRoot());
	BTreeObj->insertBTreeNode(keyVals[18]);
	cout << "Current B-Tree------------------------------------ : " << endl;
	BTreeObj->printBTreeBFS(BTreeObj->getRoot());
	BTreeObj->insertBTreeNode(keyVals[19]);
	cout << "Current B-Tree------------------------------------ : " << endl;
	BTreeObj->printBTreeBFS(BTreeObj->getRoot());


	return 0;
}