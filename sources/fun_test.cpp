#include <iostream>
#include "D:\c++\app\dp_problem\dp_invest\header\invest_profit.h"

using std::cout; using std::endl;


int main() {
    Invest_profit invest(1, 1);
    cout << invest.profit() << "\n";
    cout << invest.revenue() << "\n";
    cout << invest.production_cost() << "\n";
    cout << invest.production().first<< "\t\t" << invest.production().second << "\n";
    cout << invest.fixed_cost() << "\n";
    cout << invest.revenue() << "\n";
}
