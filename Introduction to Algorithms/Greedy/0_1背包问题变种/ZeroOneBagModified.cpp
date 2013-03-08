//0-1背包问题变种（《算法导论（第二版）》习题16.2-3）
//按照递增重量所排的物品的次序和按照递减价值所排的次序一样
//Author：江南烟雨
//Email：xiajunhust@gmail.com

#include <iostream>

using namespace std;

//采用贪心算法解决此问题

int ZeroOneBagModified(const int n,const int maxW,int *w,int *v)
{
	int maxV = 0;//所能容纳的物品的最大价值
	int wCurrent = 0;//当前已装入背包的物品的总重量
	int i;
	//将物品按照重量从小到大排列，依次选取，直至不能选择物品装入背包为止
	for (i = 0;i < n;++i)
	{
		if(wCurrent < maxW)
		{
			maxV += v[i];
			wCurrent += w[i];
		}
		else break;
	}
	if(wCurrent > maxW)
		maxV -= v[i - 1];

	return maxV;
}

int main()
{
	const int n = 6;//物品件数
	const int maxW = 40;//背包所能容纳的最大重量
	//各物品重量和价值列表
	int w[n] = {3,5,8,11,14,19};
	int v[n] = {30,28,24,17,14,6};

	int maxV = ZeroOneBagModified(n,maxW,w,v);

	cout << "The max value of the things that the bag can contain : " << maxV << endl;

	return 0;
}