#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

bool isPrime(int num)
{
	/* 0, 1 is not prime. 2, 3 is prime.*/
	int bound =int(sqrt(num));
	if (num < 2)
		return false;
	if (num < 4)
		return true;
	if (num % 2 == 0)
		return false;
	for (int i = 3; i <= bound; i += 2)
		if (num % i == 0)
			return false;
	return true;
}

int my_transform(int in_num, int radix)
{
	int res = 0;
	/* in every loop, the number which == in_num % radix
	 * occupies the more vital digit in the reversed number.
	 */
	while (in_num > 0)
	{
		res = res * radix + in_num % radix;
		in_num /= radix;
	}
	return res;
}

int main()
{
	int num, radix;
	while (cin >> num)
	{
		if (num < 0)
			break;
		cin >> radix;
		int out = my_transform(num, radix);
		if (isPrime(out) && isPrime(num))
			cout << "Yes" << "\n";
		else
			cout << "No" << "\n";
	}
	flush(cout);
}