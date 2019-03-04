#include <algorithm>
#include <map>
#include <math.h>
#include "D:\c++\app\dp_problem\dp_invest\header\invest_profit.h"
using std::pair; using std::min;
using std::make_pair; using std::pow;

Invest_profit::Invest_profit(): period(0), num_plants(0) { }

Invest_profit::Invest_profit(int a, int b) { read(a, b); }

void Invest_profit::read(int a, int b)
{
    period = a;
    num_plants = b;
}

double Invest_profit::profit() const
{
    return revenue() - production_cost() - fixed_cost();
}

double Invest_profit::profit_include_build_cost() const
{
    return profit() - build_cost();
}

pair<double, double> Invest_profit::production() const
{
//    static  map<double, double> product;
    double changed_demand = ( 1 + A_t * period) * A;
    double real_demand = num_plants*(changed_demand - alpha*B)/(num_plants + beta*B);
    double max_production = num_plants * capacity;
    double real_production = min(real_demand, max_production);
    double price = (changed_demand - real_production)/B;
    return make_pair(price, real_production);
}

double Invest_profit::revenue() const
{
   pair<double, double> prod_situ = production();
   return prod_situ.first * prod_situ.second;
}

double Invest_profit::production_cost() const
{
    pair<double, double> prod_situ = production();
    double _production_cost = 0;
    if (num_plants != 0)
        _production_cost = alpha*prod_situ.second + beta * pow(prod_situ.second, 2)/(2*num_plants);
    return _production_cost;
}

double Invest_profit::fixed_cost() const
{
    return num_plants * fixed_cost_const;
}

double Invest_profit::build_cost() const
{
    return num_plants * build_cost_const;
}
