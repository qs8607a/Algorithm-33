//��������
//���㷨���ۣ��ڶ��棩��P100 8.3 ��������
//Author����������
//E-Mail:xiajunhust@gmail.com

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//�õ�ĳ��������iλ����ֵ
int getDigitNun(int a,int digit);
//��λ����
void DigitSort(int *a,int n,int digit,int *result);
//���������㷨
void RadixSort(int *a,int n,int d);

int main()
{
	int n = 7,i;
	int *a = new int[n];
	srand(time(NULL));
	for(i = 0;i < n;++i)
		*(a + i) = rand();
	//�ж���������λ��
	int MaxVal = -1,d = 0;
	cout << "Before sort : " << endl;
	for(i = 0;i < n;++i)
	{
		cout << *(a + i) << " ";
		MaxVal = MaxVal < *(a + i) ? *(a + i) : MaxVal;
	}
	cout << endl;
	while(MaxVal > 0)
	{
		++d;
		MaxVal /= 10;
	}

	RadixSort(a,n,d);

	cout << "After sort : " << endl;
	for(i = 0;i < n;++i)
		cout << *(a + i) << " ";
	cout << endl;
}

//���������㷨
void RadixSort(int *a,int n,int d)
{
	int *result = new int[n + 5];
	//ѭ��ִ�а�λ�������
	for (int i =1;i <= d;++i)
	{
		DigitSort(a,n,i,result);
		for (int j = 0;j < n;++j)
		{
			*(a + j) = *(result + j + 1);
		}
	}

	delete[] result;
}

//�õ�ĳ��������iλ����ֵ
int getDigitNun(int a,int digit)
{
	while(--digit)
	{
		a /= 10;
	}

	return a % 10;
}

//��λ����
//�������ѡ������
void DigitSort(int *a,int n,int digit,int *result)
{
	//��¼�м���
	const int num = 15;
	int *tempResult = new int[num];
	for(int i = 0;i < num;++i)
		*(tempResult + i) = 0;//��ʼ��

	//tempResult[i]��¼�����е���i�����ĸ���
	for(int i = 0;i < n;++i)
		*(tempResult + getDigitNun(*(a + i),digit)) = *(tempResult + getDigitNun(*(a + i),digit)) + 1;

	//tempResult[i]��¼������С�ڵ���i�����ĸ���
	for(int i = 1;i < num;++i)
		*(tempResult + i) = *(tempResult + i) + *(tempResult + i - 1);

	//����Ԫ��ֱ�ӷ�����ȷ��λ��
	for(int i = n - 1;i >= 0;--i)
	{
		*(result + *(tempResult + getDigitNun(*(a + i),digit))) = *(a + i);
		*(tempResult + getDigitNun(*(a + i),digit)) = *(tempResult + getDigitNun(*(a + i),digit)) - 1;
	}

	delete[] tempResult;
}