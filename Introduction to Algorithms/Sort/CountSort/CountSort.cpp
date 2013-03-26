//计数排序-《算法导论（第二版）》P98 8.2计数排序
//Author：江南烟雨
//E-Mail：xiajunhust@gmail.com

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
	int *tempResult = new int[MaxVal + 5];//记录中间结果
	for(int i = 0;i < MaxVal  + 5;++i)
		*(tempResult + i) = 0;
	//result[i]记录数组中值等于i的元素的个数
	for(int i = 0;i < num;++i)
		*(tempResult + *(a + i)) = *(tempResult + *(a + i)) + 1;
	//result[i]记录数组中值小于等于i的元素的个数
	for(int i = 1;i < MaxVal + 5;++i)
		*(tempResult + i) = *(tempResult + i) + *(tempResult + i - 1);
	//注意，数组中可能存在相等的元素
	//将数组中各元素直接放入正确的位置
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