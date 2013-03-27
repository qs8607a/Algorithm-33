//基数排序
//《算法导论（第二版）》P100 8.3 基数排序
//Author：江南烟雨
//E-Mail:xiajunhust@gmail.com

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//得到某个整数第i位的数值
int getDigitNun(int a,int digit);
//按位排序
void DigitSort(int *a,int n,int digit,int *result);
//基数排序算法
void RadixSort(int *a,int n,int d);

int main()
{
	int n = 7,i;
	int *a = new int[n];
	srand(time(NULL));
	for(i = 0;i < n;++i)
		*(a + i) = rand();
	//判断最大的数的位数
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

//基数排序算法
void RadixSort(int *a,int n,int d)
{
	int *result = new int[n + 5];
	//循环执行按位排序操作
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

//得到某个整数第i位的数值
int getDigitNun(int a,int digit)
{
	while(--digit)
	{
		a /= 10;
	}

	return a % 10;
}

//按位排序
//这里采用选择排序
void DigitSort(int *a,int n,int digit,int *result)
{
	//记录中间结果
	const int num = 15;
	int *tempResult = new int[num];
	for(int i = 0;i < num;++i)
		*(tempResult + i) = 0;//初始化

	//tempResult[i]记录数组中等于i的数的个数
	for(int i = 0;i < n;++i)
		*(tempResult + getDigitNun(*(a + i),digit)) = *(tempResult + getDigitNun(*(a + i),digit)) + 1;

	//tempResult[i]记录数组中小于等于i的数的个数
	for(int i = 1;i < num;++i)
		*(tempResult + i) = *(tempResult + i) + *(tempResult + i - 1);

	//将个元素直接放入正确的位置
	for(int i = n - 1;i >= 0;--i)
	{
		*(result + *(tempResult + getDigitNun(*(a + i),digit))) = *(a + i);
		*(tempResult + getDigitNun(*(a + i),digit)) = *(tempResult + getDigitNun(*(a + i),digit)) - 1;
	}

	delete[] tempResult;
}