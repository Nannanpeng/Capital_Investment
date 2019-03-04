#ifndef GUARD_invest_profit
#define GUARD_invest_profit


class Invest_profit {
public:
    double profit() const;
    double profit_include_build_cost() const;
    double revenue() const;
    double production_cost() const;
    double fixed_cost() const;
    double build_cost() const;
    std::pair<double, double> production() const;
    Invest_profit();
    Invest_profit(int a, int b);
    void read(int a, int b);

private:
    double period, num_plants;
    double A = 420;
    double B = 1;
    double A_t = 0.02;
    double capacity = 100;
    double alpha = 10;
    double beta = 0.5;
    double fixed_cost_const = 1250;
    double build_cost_const = 2500;
};

#endif
