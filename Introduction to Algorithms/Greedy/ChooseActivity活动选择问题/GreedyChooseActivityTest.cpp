//̰���㷨---�ѡ������
//���㷨���ۣ��ڶ��棩��16.1
//Author����������
//Email��xiajunhust@gmail.com

#include <iostream>
#include <algorithm>

using namespace std;

//����ݽṹ
typedef struct s_f_time{
	int index;//�����
	int s_time;//���ʼʱ��
	int f_time;//�����ʱ��
}time;

//����Ƚ�׼�򣺰���Ľ���ʱ���������
bool comp(struct s_f_time a,struct s_f_time b)
{
	return a.f_time < b.f_time;
}

//�ݹ�̰���㷨���
void RecursiveActivitySelector(struct s_f_time *times,const int n)
{
	int maxActivityNum = 0;//��������Ӽ��Ļ����
	int *maxActivity = new int[n];//�洢����Ӽ�
	maxActivity[maxActivityNum++] = times[1].index;
	int temp = maxActivityNum;//��ǰ�����ݻ�Ӽ��е����һ�������
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

	//�Ը�����ս���ʱ���������
	sort(times + 1,times + 12,comp);

	RecursiveActivitySelector(times,n);

	return 0;
}