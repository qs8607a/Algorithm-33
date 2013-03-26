//��������-���㷨���ۣ��ڶ��棩��P98 8.2��������
//Author����������
//E-Mail��xiajunhust@gmail.com

#include <iostream>
#include <cstdlib>

using namespace std;

void CountSort(int *a,const int num,int *result)
{
	int MaxVal = -99999;
	for(int i = 0;i < num;++i)
	{
		if(MaxVal < *(a + i))
			MaxVal = *(a + i);
	}
	int *tempResult = new int[MaxVal + 5];//��¼�м���
	for(int i = 0;i < MaxVal  + 5;++i)
		*(tempResult + i) = 0;
	//result[i]��¼������ֵ����i��Ԫ�صĸ���
	for(int i = 0;i < num;++i)
		*(tempResult + *(a + i)) = *(tempResult + *(a + i)) + 1;
	//result[i]��¼������ֵС�ڵ���i��Ԫ�صĸ���
	for(int i = 1;i < MaxVal + 5;++i)
		*(tempResult + i) = *(tempResult + i) + *(tempResult + i - 1);
	//ע�⣬�����п��ܴ�����ȵ�Ԫ��
	//�������и�Ԫ��ֱ�ӷ�����ȷ��λ��
	for (int i = num - 1;i >= 0;--i)
	{
		*(result + *(tempResult + *(a + i))) = *(a + i);
		*(tempResult + *(a + i)) = *(tempResult + *(a + i)) - 1;
	}

	delete[] tempResult;
}

int main()
{
	 int num = 7;
	int *a = new int[num];
	for(int i = 0;i < num;++i)
		*(a + i) = rand();

	cout << "Before sort: " << endl;
	for(int i = 0;i < num;++i)
		cout << *(a + i) << " ";
	cout << endl;

	int *result = new int[num + 5];

	CountSort(a,num,result);

	cout << "After sort: " << endl;
	for(int i = 1;i <= num;++i)
		cout << *(result + i) << " ";
	cout << endl;

	delete[] a;
	delete[] result;
}