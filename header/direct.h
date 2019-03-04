#ifndef GUARD_direct
#define GUARD_direct

#include <list>
#include <map>

std::pair<double, std::list<int>> bellman(double, double);
std::pair<double, std::list<int>> invest_bellman(double, double,
                      std::map<std::pair<double, double>, std::pair<double, std::list<int>>>&);

#endif
