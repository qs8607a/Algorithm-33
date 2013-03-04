#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

const int NUM = 50005;

int main()
{
	char *s = new char[NUM];
	char *tempS = new char[NUM];
	string *words = new string[NUM];
	int index,len,start,end;
	while(gets(s))
	{
		index = 0;
		len = strlen(s);
		for (int i = 0;i < len;)
		{
			start = i;//单词起始位置
			while(i < len && s[i] != ' ')
				++i;//遍历完一个单词
			end = i - 1;//单词结束位置
			for (int j = start;j <= end;++j)
				tempS[j - start] = s[j];
			words[index++] = string(tempS).substr(0,end - start + 1);

			if (i < len)//紧接着是空格
			{
				while(' ' == s[i])
				{	
					++i;
					words[index] += ' ';
				}
				++index;
			}
		}

		for (int i = index - 1;i >= 0;--i)
		{
			cout << words[i];
		}
		cout << endl;

		//清空字符串
		memset(s,0,NUM * sizeof(char));
		memset(tempS,0,NUM * sizeof(char));
		for (int i = 0;i < NUM;++i)
			words[i] = "";
	}

	delete[] s;
	delete[] tempS;
	delete[] words;

	return 0;
}