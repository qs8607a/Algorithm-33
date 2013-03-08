//0-1背包问题变种（《算法导论（第二版）》习题16.2-3）
//按照递增重量所排的物品的次序和按照递减价值所排的次序一样
//Author：江南烟雨
//Email：xiajunhust@gmail.com

#include <iostream>
#include <algorithm>

using namespace std;

//采用贪心算法解决此问题

//物品的重量和价值
typedef struct ThingStruct{
	int w;
	int v;
}Thing;

//排序比较准则
bool comp(Thing thing1,Thing thing2)
{
	return thing1.w < thing2.w;
}

int ZeroOneBagModified(const int n,const int maxW,Thing *things)
{
	int maxV = 0;//所能容纳的物品的最大价值
	int wCurrent = 0;//当前已装入背包的物品的总重量
	int i;
	//将物品按照重量从小到大排列，依次选取，直至不能选择物品装入背包为止
	for (i = 0;i < n;++i)
	{
		if(wCurrent < maxW)
		{
			maxV += things[i].v;
			wCurrent += things[i].w;
		}
		else break;
	}
	if(wCurrent > maxW)
		maxV -= things[i - 1].v;

	return maxV;
}

int main()
{
	const int n = 6;//物品件数
	const int maxW = 40;//背包所能容纳的最大重量
	//各物品重量和价值列表
	Thing things[n] = {{3,30},{5,28},{8,24},{11,17},{14,14},{19,6}}; 

	sort(things,things + n,comp);

	int maxV = ZeroOneBagModified(n,maxW,things);

	cout << "The max value of the things that the bag can contain : " << maxV << endl;

	return 0;
}