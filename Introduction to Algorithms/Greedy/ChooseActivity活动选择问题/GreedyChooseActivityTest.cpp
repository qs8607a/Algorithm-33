//贪心算法---活动选择问题
//《算法导论（第二版）》16.1
//Author：江南烟雨
//Email：xiajunhust@gmail.com

#include <iostream>
#include <algorithm>

using namespace std;

//活动数据结构
typedef struct s_f_time{
	int index;//活动索引
	int s_time;//活动起始时间
	int f_time;//活动结束时间
}time;

//排序比较准则：按活动的结束时间递增排序
bool comp(struct s_f_time a,struct s_f_time b)
{
	return a.f_time < b.f_time;
}

//递归贪心算法求解
void RecursiveActivitySelector(struct s_f_time *times,const int n)
{
	int maxActivityNum = 0;//最大活动兼容子集的活动个数
	int *maxActivity = new int[n];//存储最大活动子集
	maxActivity[maxActivityNum++] = times[1].index;
	int temp = maxActivityNum;//当前最大兼容活动子集中的最后一个活动索引
	for (int i = 2;i <= n;++i)
	{
		if(times[i].s_time > times[temp].f_time)
		{
			maxActivity[maxActivityNum++] = times[i].index;
			temp = i;
		}
	}

	cout << "Max num of Activities = " << maxActivityNum << endl;
	cout << "The activities : " << endl;
	for(int i = 0;i < maxActivityNum;++i)
		cout << "a" << maxActivity[i] << " ";
	cout << endl;
}

int main()
{
	const int n = 11;
	struct s_f_time times[n + 1] = {{-1,-1,-1},{1,1,4},{2,3,5},{3,0,6},{4,5,7},{5,3,8},
	{6,5,9},{7,6,10},{8,8,11},{9,8,12},{10,2,13},{11,12,14}};

	//对各活动按照结束时间递增排序
	sort(times + 1,times + 12,comp);

	RecursiveActivitySelector(times,n);

	return 0;
}