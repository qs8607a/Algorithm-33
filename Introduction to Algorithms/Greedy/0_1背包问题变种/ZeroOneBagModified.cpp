//0-1����������֣����㷨���ۣ��ڶ��棩��ϰ��16.2-3��
//���յ����������ŵ���Ʒ�Ĵ���Ͱ��յݼ���ֵ���ŵĴ���һ��
//Author����������
//Email��xiajunhust@gmail.com

#include <iostream>

using namespace std;

//����̰���㷨���������

int ZeroOneBagModified(const int n,const int maxW,int *w,int *v)
{
	int maxV = 0;//�������ɵ���Ʒ������ֵ
	int wCurrent = 0;//��ǰ��װ�뱳������Ʒ��������
	int i;
	//����Ʒ����������С�������У�����ѡȡ��ֱ������ѡ����Ʒװ�뱳��Ϊֹ
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
	const int n = 6;//��Ʒ����
	const int maxW = 40;//�����������ɵ��������
	//����Ʒ�����ͼ�ֵ�б�
	int w[n] = {3,5,8,11,14,19};
	int v[n] = {30,28,24,17,14,6};

	int maxV = ZeroOneBagModified(n,maxW,w,v);

	cout << "The max value of the things that the bag can contain : " << maxV << endl;

	return 0;
}