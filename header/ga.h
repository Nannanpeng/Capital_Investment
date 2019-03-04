#ifndef GUARD_GA
#define GUARD_GA

#include <vector>
#include <map>

class Ga_invest {
public:
    std::vector<std::vector<int>> possible_solution() const;
    void mutation(std::vector<int>& vector_solu) const;
    void crossover(std::vector<int>& vector_1, std::vector<int>& vector_2) const;
    std::vector<std::vector<int>> children(std::vector<std::vector<int>>& vec) const;
    std::vector<std::vector<int>> survive(std::vector<std::vector<int>>& vec1, std::vector<std::vector<int>>& vec2);
    std::vector<std::vector<int>> ga_method();
    std::pair<std::vector<int>, double> ga_optimal(std::vector<std::vector<int>>& vec) const;
    Ga_invest();
    Ga_invest(int _sims, int _children, int _periods, int _solution, float _prob);
    void read(int _sims, int _children, int _periods, int _solution, float _prob);

private:
    int num_sims;
    int num_children;
    int num_periods;
    int num_solution;
    float prob;
    std::map<std::vector<int>, double> mapping;
};

int nrand(int);

double total_profit(const std::vector<int>&);

bool compare(const std::vector<int>&, const std::vector<int>&);
#endif
