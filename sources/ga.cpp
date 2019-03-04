#include <vector>
#include <map>
#include <stdexcept>
#include <algorithm>
#include "D:\c++\app\dp_problem\dp_invest\header\ga.h"
#include "D:\c++\app\dp_problem\dp_invest\header\invest_profit.h"
using std::vector; using std::map;
using std::domain_error; using std::pair;
using std::swap_ranges; using std::sort; using std::make_pair;


int nrand(int n){
    if (n == 0 || n == RAND_MAX )
        throw domain_error("Argument to rand is out of range");

    const int bucket_size = RAND_MAX / n;
    int r;

    do r = rand() / bucket_size;
    while (r >= n);
    return r;
}

bool compare(const std::vector<int>& vec1, const std::vector<int>& vec2)
{
    return total_profit(vec1) > total_profit(vec2);
}

double total_profit(const vector<int>& vec)
{
    double sum_profit = 0;
    int _plants = 0;
    Invest_profit invest;
    for (vector<int>::size_type i = 0; i != vec.size(); ++i){
         _plants += vec[i];
         invest.read(i+1, _plants);
         sum_profit += invest.profit_include_build_cost() + _plants * 2500 - vec[i] * 2500;
    }
    return sum_profit;
}

Ga_invest::Ga_invest(): num_sims(0), num_children(0), num_periods(0), num_solution(0), prob(0) { }

Ga_invest::Ga_invest(int _sims, int _children, int _periods, int _solution, float _prob)
{
    read(_sims, _children, _periods, _solution, _prob);
}

void Ga_invest::read(int _sims, int _children, int _periods, int _solution, float _prob)
{
    num_sims = _sims; num_children = _children;
    num_periods = _periods; num_solution = _solution;
    prob = _prob;
}

vector<vector<int>> Ga_invest::possible_solution() const{

    vector<vector<int>> solution_vector;
    for (int i = 0; i != num_solution; ++i) {
         vector<int> one_solution;
         for (int i = 0; i != num_periods; ++i){
             one_solution.push_back(nrand(2));
         }
         solution_vector.push_back(one_solution);
    }
    return solution_vector;
}

void Ga_invest::mutation(vector<int>& vector_solu) const {
    for (vector<int>::iterator i = vector_solu.begin();
         i != vector_solu.end(); ++i) {
         int inter = *i;
         float a = (float) rand()/RAND_MAX;
         if ( a < prob)
             *i = 1 - inter;
         }
}

void Ga_invest::crossover(vector<int>& vector_1, vector<int>& vector_2) const
{
    int _index = nrand(num_periods);
    swap_ranges(vector_1.begin(), vector_1.begin() + _index, vector_2.begin());
}

vector<vector<int>> Ga_invest::children(vector<vector<int>>& vec) const
{
    vector<vector<int>>::size_type _lenth = vec.size();
    vector<vector<int>> new_vec;
    for (int i = 0; i != num_children/2; ++i) {
        vector<int> p1 = vec[nrand(_lenth)];
        vector<int> p2 = vec[nrand(_lenth)];
        crossover(p1, p2);
        mutation(p1); mutation(p2);
        new_vec.push_back(p1);
        new_vec.push_back(p2);
    }
    return new_vec;
}

vector<vector<int>> Ga_invest::survive(vector<vector<int>>& vec1,
                                       vector<vector<int>>& vec2)
{
    vec1.insert(vec1.end(), vec2.begin(), vec2.end());

    vector<vector<int>> new_vec, vec = vec1;
    vector<vector<int>>::size_type _lenth = vec.size();
    for (int i = 0; i != num_solution; ++i) {
      vector<int> p1 = vec[nrand(_lenth)];
      vector<int> p2 = vec[nrand(_lenth)];
      double pro_1, pro_2;

      if (mapping.count(p1))
          pro_1 = mapping.at(p1);
      else {
          pro_1 = total_profit(p1);
          mapping[p1] = pro_1;
      }

      if (mapping.count(p2))
          pro_2 = mapping.at(p2);
      else {
          pro_2 = total_profit(p2);
          mapping[p2] = pro_2;
      }

      if (pro_1 > pro_2)
         new_vec.push_back(p1);
      else
         new_vec.push_back(p2);
    }
    return new_vec;
}

vector<vector<int>> Ga_invest::ga_method()
{
    vector<vector<int>> new_population = possible_solution();
    vector<vector<int>> _parents, _children;
    for (int i = 0; i != num_sims; ++i){
        _parents = new_population;
        _children = children(_parents);
        new_population = survive(_parents, _children);
    }
    return new_population;
}

pair<vector<int>, double> Ga_invest::ga_optimal(vector<vector<int>>& vec) const
{
    sort(vec.begin(), vec.end(), compare);
    vector<int> _solution = vec[0];
    double _best = total_profit(_solution);
    return make_pair(_solution, _best);
}
