#include <iostream>
#include <list>
#include <vector>
#include <ios>
#include <iomanip>
#include "D:\c++\app\dp_problem\dp_invest\header\invest_profit.h"
#include "D:\c++\app\dp_problem\dp_invest\header\direct.h"
#include "D:\c++\app\dp_problem\dp_invest\header\ga.h"

using std::cout; using std::endl;
using std::pair; using std::list;
using std::vector; using std::streamsize;
using std::setprecision;

int main() {
    pair<double, list<int>> best_solution = bellman(1.0, 0);
    streamsize pre = cout.precision();
    cout << "Below is the answer using DP." << "\n";
    cout << "The total profit is: " << setprecision(11) <<
         best_solution.first << setprecision(pre) << "\n";
    cout << "The number of total periods are: " << best_solution.second.size() << "\n";
    int s = 0;
    vector<int> vec;
    for (list<int>::const_iterator i = best_solution.second.begin();
         i != best_solution.second.end(); ++i){
          cout << *i ;
          ++s;
          if (*i){
            vec.push_back(s);
          }
         }
    cout << endl;
    cout << "You should build in period: ";
    for (vector<int>::size_type i = 0; i != vec.size(); ++i)
        cout << "\t"<< vec[i] ;

    cout << endl;
    cout << endl;
    cout << "Below is the answer using GA." << "\n";
    Ga_invest GA(300, 50, 30, 100, 0.1);
    vector<vector<int>> vec1 = GA.ga_method();
    pair<vector<int>, double> output  = GA.ga_optimal(vec1);
    cout << "The total profit is :" << setprecision(11) << output.second << endl;
    for (vector<int>::const_iterator i = output.first.begin();
         i != output.first.end(); ++i)
         cout << *i ;
    return 0;
}
