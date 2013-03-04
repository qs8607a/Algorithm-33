#include <iostream>
#include <limits>

using namespace std;

const long int NUM = 100005;

int main()
{
	long *a = new long[NUM],n;
	long currentNum,currentVal;

	//cout << "max of long=" << numeric_limits<long int>::max() << endl;

	while(cin >> n)
	{
		for (int i = 0;i < n;++i)
			cin >> a[i];

		currentNum = 0;
		for (int i = 0;i < n;++i)
		{
			if (!currentNum)
			{
				currentVal = a[i];
				currentNum = 1;
			}
			else{
				if (currentVal ==a[i])
					++currentNum;
				else
					--currentNum;
			}
		}

		//currentVal最终存储的是出现奇数次的数
		currentNum = 0;
		for (int i = 0;i < n;++i)
			if(currentVal == a[i])
				++currentNum;

		if(currentNum > n / 2)
			cout << currentVal << endl;
		else
			cout << "-1" << endl;
	}
}