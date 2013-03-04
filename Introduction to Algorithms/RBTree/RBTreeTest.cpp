#include "RBTree.h"

#include <iostream>

using namespace std;

int main()
{
	//²âÊÔÊý¾ÝÀ´×ÔJuly£¨http://blog.csdn.net/v_JULY_v/article/details/6284050£©
	//´ý²åÈëÊý¾Ý
	const int num = 20;
	key_t datas[num] = {12,1,9,2,0,11,7,19,4,15,18,5,14,13,10,16,6,3,8,17};
	RBTree *rbTree = new RBTree;

	//ºìºÚÊ÷²åÈë²Ù×÷²âÊÔ
	rbTree ->insert(datas[0]);
	rbTree ->insert(datas[1]);
	rbTree ->insert(datas[2]);
	rbTree ->insert(datas[3]);
	rbTree ->insert(datas[4]);
	rbTree ->insert(datas[5]);
	rbTree ->insert(datas[6]);
	rbTree ->insert(datas[7]);
	rbTree ->insert(datas[8]);
	rbTree ->insert(datas[9]);
	rbTree ->insert(datas[10]);
	rbTree ->insert(datas[11]);
	rbTree ->insert(datas[12]);
	rbTree ->insert(datas[13]);
	rbTree ->insert(datas[14]);
	rbTree ->insert(datas[15]);
	rbTree ->insert(datas[16]);
	rbTree ->insert(datas[17]);
	rbTree ->insert(datas[18]);
	rbTree ->insert(datas[19]);

	//ºìºÚÊ÷ËÑÑ°²Ù×÷²âÊÔ
	rb_node_t *searchedNode = rbTree ->searchNode(15);
	searchedNode = rbTree ->searchNode(11);
	searchedNode = rbTree ->searchNode(105);

	//ºìºÚÊ÷É¾³ý²Ù×÷²âÊÔ
	rbTree ->deleteNode(datas[0]);
	rbTree ->deleteNode(datas[1]);
	rbTree ->deleteNode(datas[2]);
	rbTree ->deleteNode(datas[3]);
	rbTree ->deleteNode(datas[4]);
	rbTree ->deleteNode(datas[5]);
	rbTree ->deleteNode(datas[6]);
	rbTree ->deleteNode(datas[7]);
	rbTree ->deleteNode(datas[8]);
	rbTree ->deleteNode(datas[9]);
	rbTree ->deleteNode(datas[10]);
	rbTree ->deleteNode(datas[11]);
	rbTree ->deleteNode(datas[12]);
	rbTree ->deleteNode(datas[13]);
	rbTree ->deleteNode(datas[14]);
	rbTree ->deleteNode(datas[15]);
	rbTree ->deleteNode(datas[16]);
	rbTree ->deleteNode(datas[17]);
	rbTree ->deleteNode(datas[18]);
	rbTree ->deleteNode(datas[19]);

	delete rbTree;
}