#include <map>
#include <list>
#include "D:\c++\app\dp_problem\dp_invest\header\invest_profit.h"
#include "D:\c++\app\dp_problem\dp_invest\header\direct.h"
using std::map;
using std::list;
using std::pair; using std::make_pair;

pair<double, list<int>> bellman(double period, double plants){
    typedef pair<double, double> state;
    typedef pair<double, list<int>> result;
    map<state, result> profit_tab;
    return invest_bellman(period, plants, profit_tab);
}


pair<double, list<int>> invest_bellman(double period, double plants,
                      map<pair<double, double>, pair<double, list<int>>>& mapping)
{
    list<int> vec;
    if (period == 31)
        return make_pair(0.0, vec);

    typedef pair<double, double> pair_key;
    typedef pair<double, list<int>> pair_value;

    pair_key key_1 = {period + 1, plants};
    pair_value next_no_build, next_build;

    if (mapping.count(key_1))
        next_no_build = mapping.at(key_1);
    else {
        next_no_build = invest_bellman(period + 1, plants, mapping);
        mapping[key_1] = next_no_build;
    }

    pair_key key_2 = {period + 1, plants + 1};
    if (mapping.count(key_2))
        next_build = mapping.at(key_2);
    else {
        next_build = invest_bellman(period + 1, plants + 1, mapping);
        mapping[key_2] = next_build;
    }

    Invest_profit profit_no_build(period, plants);
    Invest_profit profit_build(period, plants + 1);

    if (next_no_build.first + profit_no_build.profit() > next_build.first + profit_build.profit() - 2500) {
        next_no_build.second.push_front(0);
        double total_no_build_profit = next_no_build.first + profit_no_build.profit();
        return make_pair(total_no_build_profit, next_no_build.second);
    } else {
          next_build.second.push_front(1);
          double total_build_profit = next_build.first + profit_build.profit() - 2500;
          return make_pair(total_build_profit, next_build.second);
    }
}
