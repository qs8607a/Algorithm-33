//�����֮��������1.4����������ʵ��
//Author���������꣨Email��xiajunhust@gmail.com��
//Date��2013-02-28

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

//��ⷽ�����ݹ�

const double MaxValue = 999999.99;//һ���Ƚϴ�������������
const int price = 8;//ÿ����ĵ��ۣ���ͬ�������ͬ
const int num = 5;//��ľ���
double discount[num] = {0,0.05,0.1,0.2,0.25};//��ͬ��������ܵ��ۿ�

int countNum = 0;//�������

//�º�����sort�����Ƚ�׼�򡣰��մӴ�С��˳�����С�
bool myCmp(int i,int j)
{
	return i > j;
}

//���������������е���Сֵ
double minFiveValues(double a1,double a2,double a3,double a4,double a5)
{
	double values[num] = {a1,a2,a3,a4,a5};
	sort(values,values + num);

	return values[0];
}

//�������õ���ǰ״̬�����Ž⼴��ǰ���������С����
//�������������Եı���
double getMinCost(int y1,int y2,int y3,int y4,int y5)
{
	++countNum;

	int vals[num] = {y1,y2,y3,y4,y5};
	//ÿ�ζ���������С��ʾ
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
	//���蹺�����ĸ���ı���
	//���������������10���ڵ��������Ϊ10���������������Բ��Ϊ10�����ڵ����
	int booksNum[num] = {7,2,5,3,6};

	//����ĸ���������С��ʾ����
	//��(Y1,Y2,Y3,Y4,Y5)����Y1>=Y2>=Y3>=Y4>=Y5
	sort(booksNum,booksNum + num,myCmp);

	double minCost = getMinCost(booksNum[0],booksNum[1],booksNum[2],booksNum[3],booksNum[4]);
	cout << "The min cost is " << minCost << endl;
	//���н����152.2
	cout << "������� = " << countNum << endl;

	return 0;
}