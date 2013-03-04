//�������˷�����
//���㷨���ۣ������棩��15.2 �������˷�

#include <iostream>

using namespace std;

//�������������Ŵ���
int leastMultiplyNum(int n,int *dimension);
//������������Ž�
void printOptimalParens(int **s,int i,int j);

const int MaxValue = 99999;//һ�����ֵ����ʾ�ܴ�

int main()
{
	const int n = 6;//�������
	//����ά��dimension[i]��dimension[i + 1]�Ǿ���Ai��ά��
	int dimension[n + 1] = {30,35,15,5,10,20,25};

	int leastCost = leastMultiplyNum(n,dimension);

	cout << "Least cost = " << leastCost << endl;
}

int leastMultiplyNum(const int n,int *dimension)
{
	//�����м���������
	int **m = new int*[n];
	for(int i = 0;i < n;++i)
		m[i] = new int[n];
	//�������m[i][j]ʱȡ�����Ŵ��۴�k��ֵ�����������ѵ㣩
	int **s = new int*[n];
	for(int i = 0;i < n;++i)
		s[i] = new int[n];

	for (int i = 0;i < n;++i)
		m[i][i] = 0;//��ʼ������Ϊ1�ľ�����

	for (int l = 2;l <= n;++l)//l�Ǿ��������ȣ��Ե����ϼ��㣩
	{
		for (int i = 0;i <= n - l;++i)//���г���Ϊl�ľ������Ŀ�����ʼ��������
		{
			int j = i + l - 1;//������β����������
			m[i][j] = MaxValue;//��ʼ��Ϊһ���ܴ��ֵ
			for (int k = i;k <j;++k)//���ÿһ�ֿ��ܵľ������������
			{
				int temp = m[i][k] + m[k + 1][j] + dimension[i] * dimension[k + 1] * dimension[j + 1];
				if(temp < m[i][j])//�����м�ֵ�Լ����������ѵ��¼
				{
					m[i][j] = temp;
					s[i][j] = k;
				}
			}
		}
	}

	//�������Ž�
	cout << "���Ž⣺";
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