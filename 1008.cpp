#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
	int N;
	cin >> N;


	int fi = 0, se, time = 0;
	for (int i = 0; i < N; ++i)
	{
		cin >> se;
		if (se > fi)
			time += 6*(se - fi);
		else
			time += 4*(fi - se);
		time += 5;
		fi = se;
	}

	cout << time << endl;
}