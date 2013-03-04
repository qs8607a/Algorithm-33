//˫��ŷ���������������
//���㷨���ۣ��ڶ��棩��˼����15-1
//PKU 2677

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const int n = 7;//�����Ŀ
const int MaxVal = 999999;
const int MaxLen = 201;

struct tagPoint{
	double x,y;
};

//�����i�͵�j֮���ֱ�߾���
double distance(tagPoint *points,int i,int j)
{
	return sqrt((points[i].x - points[j].x) * (points[i].x - points[j].x) +
		(points[i].y - points[j].y) * (points[i].y - points[j].y));
}

double DP(tagPoint *points,int n)
{
	double b[MaxLen][MaxLen];//��¼���·���ĳ���
	//������������µ�b[i][j]��1 <= i <= j
	//��ʼ��
	b[1][2] = distance(points,1,2);
	for (int j = 3;j <= n;++j)
	{
		//i < j-1
		for (int i = 1;i <= j - 2;++i)
		{
			b[i][j] = b[i][j - 1] + distance(points,j - 1,j);
		}
		//i = j - 1,b[i][j] = min(b[k][j - 1] + distance(k,j));
		b[j - 1][j] = MaxVal;
		for (int k = 1;k <= j - 2;++k)
		{
			double temp = b[k][j - 1] + distance(points,k,j);
			if (temp < b[j - 1][j])
			{
				b[j - 1][j] = temp;
			}
		}
	}

	b[n][n] = b[n - 1][n] + distance(points,n - 1,n);

	return b[n][n];
}

int main()
{
	int NUM;
	while(cin >> NUM)
	{
		tagPoint *points = new tagPoint[NUM + 1];
		for (int i = 1;i <= NUM;++i)
		{
			cin >> points[i].x;
			cin >> points[i].y;
		}
		double minDis = DP(points,NUM);
		//���������ʽ����ȷ��С�����2λ
		cout.setf(ios::fixed);
		cout << setprecision(2) << minDis << endl;
	}
}