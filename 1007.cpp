#include <iostream>
#include <vector>
#include <algorithm>
/*
 *  最长递增子序列。
 *  Accepted.
 */

using namespace std;

int main()
{
	int N;
	cin >> N;

	vector<int> nums;
	int temp;
	bool isAllNeg = true;

	for (int i = 0; i < N; ++i)
	{
		cin >> temp;
		nums.emplace_back(temp);
		if (temp >= 0)
			isAllNeg = false;
	}

	int maxSum = -1, tempSum = 0;
	int i = 0, j = 0, i_temp = i;

	for (int loop = 0; loop < N; ++loop)
	{
		tempSum += nums[loop];
		if (tempSum < 0)
		{
			i_temp = loop + 1;
			tempSum = 0;
		}
		else
		{
			if (tempSum > maxSum)
			{
				maxSum = tempSum;
				i = i_temp;
				j = loop;
			}
		}
	}
	if (isAllNeg)
		cout << 0 << " " << nums.front() << " " << nums.back() << endl;
	else
		cout << maxSum << " " << nums[i] << " " << nums[j] << endl;

	return 0;
}