//《编程之美》问题1.4买书问题编程实现
//Author：江南烟雨（Email：xiajunhust@gmail.com）
//Date：2013-02-28

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

//求解方法：递归

const double MaxValue = 999999.99;//一个比较大的数，做标记用
const int price = 8;//每本书的单价，不同卷的书相同
const int num = 5;//书的卷数
double discount[num] = {0,0.05,0.1,0.2,0.25};//买不同卷的书享受的折扣

int countNum = 0;//计算次数

//仿函数：sort函数比较准则。按照从大到小的顺序排列。
bool myCmp(int i,int j)
{
	return i > j;
}

//函数：获得五个数中的最小值
double minFiveValues(double a1,double a2,double a3,double a4,double a5)
{
	double values[num] = {a1,a2,a3,a4,a5};
	sort(values,values + num);

	return values[0];
}

//函数：得到当前状态下最优解即买当前所需书的最小花费
//参数：五卷书各自的本数
double getMinCost(int y1,int y2,int y3,int y4,int y5)
{
	++countNum;

	int vals[num] = {y1,y2,y3,y4,y5};
	//每次都必须用最小表示
	sort(vals,vals + num,myCmp);
	y1 = vals[0];
	y2 = vals[1];
	y3 = vals[2];
	y4 = vals[3];
	y5 = vals[4];

	if(!y1 && !y2 && !y3 && !y4 && !y5)
		return 0;
	else if(y5 >= 1)
		return minFiveValues(num * price * (1 - discount[num - 1]) + getMinCost(y1 - 1,y2 - 1,y3 - 1,y4 - 1,y5 - 1),
		(num - 1) * price * (1 - discount[num - 2]) + getMinCost(y1 - 1,y2 - 1,y3 - 1,y4 - 1,y5),
		(num - 2) * price * (1 - discount[num - 3]) + getMinCost(y1 - 1,y2 - 1,y3 - 1,y4,y5),
		(num - 3) * price * (1 - discount[num - 4]) + getMinCost(y1 - 1,y2 - 1,y3,y4,y5),
		price + getMinCost(y1 - 1,y2,y3,y4,y5));
	else if(y4 >= 1)
		return minFiveValues(MaxValue,
		(num - 1) * price * (1 - discount[num - 2]) + getMinCost(y1 - 1,y2 - 1,y3 - 1,y4 - 1,y5),
		(num - 2) * price * (1 - discount[num - 3]) + getMinCost(y1 - 1,y2 - 1,y3 - 1,y4,y5),
		(num - 3) * price * (1 - discount[num - 4]) + getMinCost(y1 - 1,y2 - 1,y3,y4,y5),
		price + getMinCost(y1 - 1,y2,y3,y4,y5));
	else if(y3 >= 1)
		return minFiveValues(MaxValue,
		MaxValue,
		(num - 2) * price * (1 - discount[num - 3]) + getMinCost(y1 - 1,y2 - 1,y3 - 1,y4,y5),
		(num - 3) * price * (1 - discount[num - 4]) + getMinCost(y1 - 1,y2 - 1,y3,y4,y5),
		price + getMinCost(y1 - 1,y2,y3,y4,y5));
	else if(y2 >= 1)
		return min((num - 3) * price * (1 - discount[num - 4]) + getMinCost(y1 - 1,y2 - 1,y3,y4,y5),
		price + getMinCost(y1 - 1,y2,y3,y4,y5));
	else if(y1 >= 1)
		return price + getMinCost(y1 - 1,y2,y3,y4,y5);
}

int main()
{
	//所需购买的书的各卷的本数
	//这里仅考虑综述在10以内的情况，因为10本以外的情况都可以拆解为10本以内的组合
	int booksNum[num] = {7,2,5,3,6};

	//将书的各卷数量最小表示出来
	//即(Y1,Y2,Y3,Y4,Y5)满足Y1>=Y2>=Y3>=Y4>=Y5
	sort(booksNum,booksNum + num,myCmp);

	double minCost = getMinCost(booksNum[0],booksNum[1],booksNum[2],booksNum[3],booksNum[4]);
	cout << "The min cost is " << minCost << endl;
	//运行结果：152.2
	cout << "计算次数 = " << countNum << endl;

	return 0;
}