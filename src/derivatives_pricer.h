#ifndef INCLUDE_DERIVATIVES_PRICER
#define INCLUDE_DERIVATIVES_PRICER

#include <string>

class DerivativesPricer
{
public:
  DerivativesPricer(double spot_price,
                    double drift,
                    double vol,
                    int num_time_steps,
                    double interest_rate,
                    double maturity,
                    int num_scenarios,
                    double strike_price,
                    std::string derivative_name);
  void print_results();
  void calculate();
  double get_spot_price();

protected:
  virtual double apply_derivative_func(double price) = 0;
  double calculate_one_simulation(int seed);
  double mc_next_price(double prev_price, double norm);

  double d_spot_price;
  double d_asset_price;
  double d_drift;
  double d_vol;
  double d_dt;
  int d_num_time_steps;
  double d_interest_rate;
  double d_maturity;
  int d_num_scenarios;
  double d_strike_price;
  std::string d_derivative_name;
};

#endif