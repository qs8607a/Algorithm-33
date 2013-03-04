//动态规划---装配线调度问题
//《算法导论（第三版）》第15章动态规划 15.1装配线调度问题
//Author：江南烟雨（xiajunhust@gmail.com）
//Date：2013-03-02

#include <iostream>

using namespace std;

//变量定义
const int numAssemblyLine = 2;//装配线条数
const int numAssemblyStation = 6;//每条装配线的装配站数量
int e[numAssemblyLine] = {2,4};//底盘进入装配站时间
int x[numAssemblyLine] = {3,2};//装配完的汽车离开装配线时间
//每个装配站上所需时间
int a[numAssemblyLine][numAssemblyStation] = {{7,9,3,4,8,4},{8,5,6,4,5,7}};
//把已经通过装配站Si,j的底盘从装配线i移走所花的时间
int t[numAssemblyLine][numAssemblyStation] = {{2,3,1,3,4},{2,1,2,2,1}};

//函数：输出装配线以及装配站的相关信息
void printStations(int **l,int lEnd,int n);

//函数：计算通过工厂的最快时间
//参数含义和上述全局变量定义相同
int FastestWay(int a[numAssemblyLine][numAssemblyStation],int t[numAssemblyLine][numAssemblyStation],
			   int *e,int *x,const int numAssemblyLine,const int numAssemblyStation);

int main(){
	int leastTime = FastestWay(a,t,e,x,numAssemblyLine,numAssemblyStation);

	cout << "Least time = " << leastTime << endl;
}

//函数：计算通过工厂的最快时间
//参数含义和上述全局变量定义相同
int FastestWay(int a[numAssemblyLine][numAssemblyStation],int t[numAssemblyLine][numAssemblyStation],
			   int *e,int *x,const int numAssemblyLine,const int numAssemblyStation)
{
	//记录中间结果（注意多维数组空间分配）
	int **f;
	f = new int *[numAssemblyLine];
	for (int i = 0;i < numAssemblyLine;++i)
		f[i] = new int[numAssemblyStation];
	int fEnd;//最终最短时间

	//记录到当前装配站的最快路线使用了前面哪条装配线上的装配站
	int **l;
	l = new int*[numAssemblyLine];
	for(int i = 0;i < numAssemblyLine;++i)
		l[i] = new int[numAssemblyStation];

	int lEnd;
	//初始化
	f[0][0] = e[0] + a[0][0];
	f[1][0] = e[1] + a[1][0];

	//从小到大按照装配站编号顺序依次计算
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

	//多维数组动态空间释放
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