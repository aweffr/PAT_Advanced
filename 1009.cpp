#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
/*
 *  多项式相乘。唯一要注意的是v3要开的长度是2001。
 */

int main()
{
	vector<double> v1(1001);
	vector<double> v2(1001);

	int N, exp; double cof;
	cin >> N;
	for (int i = 0; i < N; ++i)
	{
		cin >> exp >> cof;
		v1[exp] = cof;
	}
	cin >> N;
	for (int i = 0; i < N; ++i)
	{
		cin >> exp >> cof;
		v2[exp] = cof;
	}

	//cout << "Reading Complete!" << endl;

	vector<double> v3(2001, 0);
	for (int i = 0; i < 1001; ++i)
	{
		for (int j = 0; j < 1001; ++j)
		{
			v3[i + j] += v1[i] * v2[j];
		}
	}

	vector<int> out;
	for (int i = 0; i < 2001; ++i)
	{
		if (abs(v3[i]) > 0.001)
			out.push_back(i);
	}

	if (out.empty())
		cout << 0;
	else
	{
		cout << out.size();
		for (auto it = out.rbegin(); it != out.rend(); ++it)
			printf(" %d %.1f", *it, v3[*it]);
	}
	cout << endl;

	return 0;
}