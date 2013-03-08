//0-1����������֣����㷨���ۣ��ڶ��棩��ϰ��16.2-3��
//���յ����������ŵ���Ʒ�Ĵ���Ͱ��յݼ���ֵ���ŵĴ���һ��
//Author����������
//Email��xiajunhust@gmail.com

#include <iostream>
#include <algorithm>

using namespace std;

//����̰���㷨���������

//��Ʒ�������ͼ�ֵ
typedef struct ThingStruct{
	int w;
	int v;
}Thing;

//����Ƚ�׼��
bool comp(Thing thing1,Thing thing2)
{
	return thing1.w < thing2.w;
}

int ZeroOneBagModified(const int n,const int maxW,Thing *things)
{
	int maxV = 0;//�������ɵ���Ʒ������ֵ
	int wCurrent = 0;//��ǰ��װ�뱳������Ʒ��������
	int i;
	//����Ʒ����������С�������У�����ѡȡ��ֱ������ѡ����Ʒװ�뱳��Ϊֹ
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
	const int n = 6;//��Ʒ����
	const int maxW = 40;//�����������ɵ��������
	//����Ʒ�����ͼ�ֵ�б�
	Thing things[n] = {{3,30},{5,28},{8,24},{11,17},{14,14},{19,6}}; 

	sort(things,things + n,comp);

	int maxV = ZeroOneBagModified(n,maxW,things);

	cout << "The max value of the things that the bag can contain : " << maxV << endl;

	return 0;
}