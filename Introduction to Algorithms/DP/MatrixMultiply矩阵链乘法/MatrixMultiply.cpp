//矩阵链乘法问题
//《算法导论（第三版）》15.2 矩阵链乘法

#include <iostream>

using namespace std;

//函数：计算最优代价
int leastMultiplyNum(int n,int *dimension);
//函数：输出最优解
void printOptimalParens(int **s,int i,int j);

const int MaxValue = 99999;//一个标记值，表示很大

int main()
{
	const int n = 6;//矩阵个数
	//矩阵维数dimension[i]和dimension[i + 1]是矩阵Ai的维数
	int dimension[n + 1] = {30,35,15,5,10,20,25};

	int leastCost = leastMultiplyNum(n,dimension);

	cout << "Least cost = " << leastCost << endl;
}

int leastMultiplyNum(const int n,int *dimension)
{
	//保存中间结果：代价
	int **m = new int*[n];
	for(int i = 0;i < n;++i)
		m[i] = new int[n];
	//保存计算m[i][j]时取得最优代价处k的值（矩阵链分裂点）
	int **s = new int*[n];
	for(int i = 0;i < n;++i)
		s[i] = new int[n];

	for (int i = 0;i < n;++i)
		m[i][i] = 0;//初始化长度为1的矩阵链

	for (int l = 2;l <= n;++l)//l是矩阵链长度（自底向上计算）
	{
		for (int i = 0;i <= n - l;++i)//所有长度为l的矩阵链的可能起始矩阵索引
		{
			int j = i + l - 1;//矩阵链尾部矩阵索引
			m[i][j] = MaxValue;//初始化为一个很大的值
			for (int k = i;k <j;++k)//针对每一种可能的矩阵链分裂情况
			{
				int temp = m[i][k] + m[k + 1][j] + dimension[i] * dimension[k + 1] * dimension[j + 1];
				if(temp < m[i][j])//更新中间值以及矩阵链分裂点记录
				{
					m[i][j] = temp;
					s[i][j] = k;
				}
			}
		}
	}

	//构造最优解
	cout << "最优解：";
	printOptimalParens(s,0,n - 1);
	cout << endl;

	return m[0][n - 1];
}

void printOptimalParens(int **s,int i,int j)
{
	if(i == j)
		cout << "A" << i;
	else
	{
		cout << "(";
		printOptimalParens(s,i,s[i][j]);
		printOptimalParens(s,s[i][j] + 1,j);
		cout << ")";
	}
}