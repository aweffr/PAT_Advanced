#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>

using namespace std;

void print_time(int in_min, int out_min);

struct Customer
{
	int id;
	int finish;

	Customer(const int &id, const int &finish):
		id(id), finish(finish) { }
};

int main()
{
	/*  First line:
	 *	N (<=20, number of windows)
	 *	M (<=10, the maximum capacity of each line)
	 *	K (<=1000, number of customers)
	 *	Q (<=1000, number of customer queries).
	 */
	int N, M, K, Q;
	cin >> N >> M >> K >> Q;

	/* The processing time of the K customers */
	vector<int> time;
	for (int i = 0, k; i < K; ++i)
	{
		cin >> k;
		time.push_back(k);
	}

	/* The customers who are asking about the time */
	vector<int> quires;
	for (int i = 0, q; i < Q; ++i)
	{
		cin >> q;
		quires.push_back(q);
	}
	
	/*
	 *	建模： 建立N个队列（queue）。
	 *
	 *	Stage 1: 最开始NM个人直接进队列。
	 *	Stage 2: 此时所有队列都填了M个人。
	 *	考虑每个队列的top人的完成时间，取完成时间最短的pop。
	 *	每当pop一个人，就从外部队列里新读一个人进来。
	 *	Stage 3: 当外部队列所有人都读完了，每个人也就都知道了自己的完成时间。
	 */

	vector<int> finish_time(K);                 /* finish_time */
	vector<queue<Customer> > queue_vec(N);      /* vector of queues*/

	for (int i = 0; i < N && i < K; ++i)
	{
		Customer cust(i, 0 + time[i]);
		finish_time[i] = cust.finish;
		queue_vec[i].push(cust);
	}

	for (int i = N; i < N * M && i < K; ++i)
	{
		Customer cust(i, queue_vec[i % N].back().finish + time[i]);
		finish_time[i] = cust.finish;
		queue_vec[i % N].push(cust);
	}

	for (int i = N*M; i < K; ++i)
	{
		auto it = min_element(queue_vec.begin(), queue_vec.end(),
			[](const queue<Customer> &lhs, const queue<Customer> &rhs)
		{return lhs.front().finish < rhs.front().finish; });
		Customer cust(i, it->back().finish + time[i]);
		finish_time[i] = cust.finish;
		it->pop();
		it->push(cust);
	}


	/* Debug: 看每个人的结束时间 */
    // for (int i : finish_time)
    //     cout << i << endl;

	for (int id : quires)
	{
		/* 题目中的查询id是 1 to N， 本题存储用的是 0 to N-1 */
		int out_min = finish_time.at(id - 1);
		int in_min = out_min - time.at(id - 1);
		print_time(in_min, out_min);
	}

	return 0;
}

void print_time(int in_min, int out_min)
{
	if (in_min >= 540)
		cout << "Sorry" << endl;
	else
	{
		int hr = out_min / 60;
		int min = out_min % 60;
		printf("%02d:%02d\n", hr + 8, min);
	}
}