//���㷨���ۣ������棩�� 15.4 P208 ��̬�滮---��������������⣨LCS��
//Author����������
//Email��xiajunhust@gmail.com

#include <iostream>

using namespace std;

enum{
	LIST_A = 0,
	LIST_BOTH,
	LIST_B
};//��Ǵ˴�ѡ���ĸ����е�Ԫ��

//��������������ַ����Ĺ��������еĳ���
//�����ֱ��������ַ������䳤��
int LCSLength(char *s1,int n1,char *s2,int n2);

//��������������������
void printLCS(int **b,char *s1,int i,int j);

int main()
{
	const int n1 = 5,n2 = 5;
	char *s1 = "ABCDE";
	char *s2 = "ABDFE";

	int lcs = LCSLength(s1,n1,s2,n2);

	cout << "LCS = " << lcs << endl;
}

int LCSLength(char *s1,int n1,char *s2,int n2)
{
	//ά��һ�������¼�м���
	int **c = new int *[n1 + 1];
	for(int i = 0;i <= n1;++i)
		c[i] = new int[n2 + 1];
	//����ֵ
	for(int i = 0;i <= n2;++i)
		c[0][i] = 0;
	for(int i = 0;i <= n1;++i)
		c[i][0] = 0;

	//Ϊ�˹������Ž�
	int **b = new int *[n1 + 1];
	for(int i = 0;i <= n1;++i)
		b[i] = new int[n2 + 1];
	//����ֵ
	for(int i = 0;i <= n2;++i)
		b[0][i] = 0;
	for(int i = 0;i <= n1;++i)
		b[i][0] = 0;

	for (int i = 1;i <= n1;++i)
	{
		for (int j = 1;j <= n2;++j)
		{
			if (s1[i - 1] == s2[j - 1])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = LIST_BOTH;
			}
			else if (c[i - 1][j] >= c[i][j - 1])
			{
				c[i][j] = c[i - 1][j];
				b[i][j] = LIST_B;
			}
			else{
				c[i][j] = c[i][j - 1];
				b[i][j] = LIST_A;
			}
		}
	}

	cout << "�����������Ϊ��";
	printLCS(b,s1,n1,n2);
	cout << endl;

	int lcs = c[n1][n2];

	//�ͷſռ�
	for (int i = 0;i <= n1;++i)
		delete[] c[i];
	delete[] c;

	for (int i = 0;i <= n1;++i)
		delete[] b[i];
	delete[] b;

	return lcs;
}

void printLCS(int **b,char *s1,int i,int j)
{
	if(!i || !j)
		return;

	if(LIST_BOTH == b[i][j])
	{
		printLCS(b,s1,i - 1,j - 1);
		cout << " " << s1[i - 1];
	}
	else if(LIST_A == b[i][j])
		printLCS(b,s1,i,j - 1);
	else
		printLCS(b,s1,i - 1,j);
}