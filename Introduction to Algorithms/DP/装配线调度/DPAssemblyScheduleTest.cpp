//��̬�滮---װ���ߵ�������
//���㷨���ۣ������棩����15�¶�̬�滮 15.1װ���ߵ�������
//Author���������꣨xiajunhust@gmail.com��
//Date��2013-03-02

#include <iostream>

using namespace std;

//��������
const int numAssemblyLine = 2;//װ��������
const int numAssemblyStation = 6;//ÿ��װ���ߵ�װ��վ����
int e[numAssemblyLine] = {2,4};//���̽���װ��վʱ��
int x[numAssemblyLine] = {3,2};//װ����������뿪װ����ʱ��
//ÿ��װ��վ������ʱ��
int a[numAssemblyLine][numAssemblyStation] = {{7,9,3,4,8,4},{8,5,6,4,5,7}};
//���Ѿ�ͨ��װ��վSi,j�ĵ��̴�װ����i����������ʱ��
int t[numAssemblyLine][numAssemblyStation] = {{2,3,1,3,4},{2,1,2,2,1}};

//���������װ�����Լ�װ��վ�������Ϣ
void printStations(int **l,int lEnd,int n);

//����������ͨ�����������ʱ��
//�������������ȫ�ֱ���������ͬ
int FastestWay(int a[numAssemblyLine][numAssemblyStation],int t[numAssemblyLine][numAssemblyStation],
			   int *e,int *x,const int numAssemblyLine,const int numAssemblyStation);

int main(){
	int leastTime = FastestWay(a,t,e,x,numAssemblyLine,numAssemblyStation);

	cout << "Least time = " << leastTime << endl;
}

//����������ͨ�����������ʱ��
//�������������ȫ�ֱ���������ͬ
int FastestWay(int a[numAssemblyLine][numAssemblyStation],int t[numAssemblyLine][numAssemblyStation],
			   int *e,int *x,const int numAssemblyLine,const int numAssemblyStation)
{
	//��¼�м�����ע���ά����ռ���䣩
	int **f;
	f = new int *[numAssemblyLine];
	for (int i = 0;i < numAssemblyLine;++i)
		f[i] = new int[numAssemblyStation];
	int fEnd;//�������ʱ��

	//��¼����ǰװ��վ�����·��ʹ����ǰ������װ�����ϵ�װ��վ
	int **l;
	l = new int*[numAssemblyLine];
	for(int i = 0;i < numAssemblyLine;++i)
		l[i] = new int[numAssemblyStation];

	int lEnd;
	//��ʼ��
	f[0][0] = e[0] + a[0][0];
	f[1][0] = e[1] + a[1][0];

	//��С������װ��վ���˳�����μ���
	for (int i = 1;i < numAssemblyStation;++i)
	{
		int temp1 = f[0][i - 1] + a[0][i];
		int temp2 = f[1][i - 1] + t[1][i - 1] + a[0][i];
		if (temp1 < temp2)
		{
			l[0][i] = 0;
			f[0][i] = temp1;
		}
		else{
			l[0][i] = 1;
			f[0][i] = temp2;
		}

		int temp3 = f[1][i - 1] + a[1][i];
		int temp4 = f[0][i - 1] + t[0][i - 1] + a[1][i];
		if (temp3 < temp4)
		{
			l[1][i] = 1;
			f[1][i] = temp3;
		}
		else{
			l[1][i] = 0;
			f[1][i] = temp4;
		}
	}

	if (f[0][numAssemblyStation - 1] + x[0] < f[1][numAssemblyStation - 1] + x[1])
	{
		lEnd = 0;
		fEnd = f[0][numAssemblyStation - 1] + x[0];
	}
	else{
		lEnd = 1;
		fEnd = f[1][numAssemblyStation - 1] + x[1];
	}

	printStations(l,lEnd,numAssemblyStation);

	//��ά���鶯̬�ռ��ͷ�
	for (int i = 0;i < numAssemblyLine;++i)
		delete[] f[i];
	delete[] f;

	for (int i = 0;i < numAssemblyLine;++i)
		delete[] l[i];
	delete[] l;

	return fEnd;
}

void printStations(int **l,int lEnd,int n)
{
	cout << "Stations :" << endl;
	int i = lEnd;
	cout << "Line " << i + 1 << " Station " << n << endl;
	for(int j = n - 1;j > 0;--j)
	{
		i = l[i][j];
		cout << "Line " << i  + 1 << " Station " << j << endl;
	}
}