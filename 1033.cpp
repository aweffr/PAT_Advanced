#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

struct Station
{
    double distance, price;
    Station(const double &d, const double &p):
        distance(d), price(p) { }
    
    bool operator<(const Station &rhs) const
    {
        return distance < rhs.distance;
    }
};

int main(int argc, char** argv)
{
    double capacity, destnation, disPerUnit;
    int N;
    scanf(" %lf %lf %lf %d", &capacity, &destnation, &disPerUnit, &N);
    vector<Station> stations;
    
    double price_temp, distance;
    for(int i = 0; i < N; ++i)
    {
        scanf(" %lf %lf", &price_temp, &distance);
        stations.emplace_back(distance, price_temp);
    }
    sort(stations.begin(), stations.end());
    
//    for (auto &s: stations)
//    {
//        printf("%.2f %.2f\n", s.price, s.distance);
//    }
    
    if (stations[0].distance > 0)
    {
        printf("The maximum travel distance = 0.00\n");
        return 0;
    }
    
    int idx_cur = 0;
    double cur_capacity = 0.0, price_cnt = 0.0;
    double max_reach = capacity * disPerUnit;
    while (true)
    {
        printf("Capacity: %.2f / %.2f, distance:%.2f, price_cnt:%.2f\n", cur_capacity, capacity, price_cnt, stations[idx_cur].distance);
        int idx_next = -1;
        for(int i = idx_cur + 1; i < N; ++i)
        {
            bool outOfRange = stations[i].distance >= destnation;
            bool outOfReach = stations[i].distance - stations[idx_cur].distance > max_reach;
            if(outOfRange || outOfReach)
                break;
            if((idx_next < 0) || (stations[i].price < stations[idx_next].price))
            {
                idx_next = i;
                //If find a next station's price is cheaper than current one, just go to it.
                if(stations[idx_next].price < stations[idx_cur].price)
                    break;
            }
        }
        if (idx_next < 0) // current station is the most reachable station.
        {
            bool outOfReach = destnation - stations[idx_cur].distance > max_reach;
            if (outOfReach)
            {
                printf("The maximum travel distance = %.2lf\n", stations[idx_cur].distance + max_reach);
            }
            else
            {
                printf("%.2f\n", price_cnt + ((destnation - stations[idx_cur].distance)/disPerUnit - cur_capacity) * stations[idx_cur].price);
            }
            break;
        }
        else
        {
            if(stations[idx_cur].price > stations[idx_next].price) //Drive to the more cheap station.
            {
                price_cnt += ((stations[idx_next].distance - stations[idx_cur].distance)/disPerUnit - cur_capacity) * stations[idx_cur].price;
                cur_capacity = 0.0;
            }
            else if ((destnation - stations[idx_cur].distance) <= max_reach)
            {
                // Drive to the destnation.
                price_cnt += ((destnation - stations[idx_cur].distance)/disPerUnit - cur_capacity) * stations[idx_cur].price;
                printf("%.2lf\n", price_cnt);
                break;
            }
            else
            {
                price_cnt += (capacity - cur_capacity) * stations[idx_cur].price;
                cur_capacity = capacity - (stations[idx_next].distance - stations[idx_cur].distance)/disPerUnit;
            }
            idx_cur = idx_next;
        }
    }
    
	return 0;
}
