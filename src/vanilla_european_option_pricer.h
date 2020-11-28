#ifndef INCLUDE_VANILLA_EUROPEAN_OPTION_PRICER
#define INCLUDE_VANILLA_EUROPEAN_OPTION_PRICER

#include <derivatives_pricer.h>

class VanillaEuropeanOptionPricer : public DerivativesPricer
{
public:
  VanillaEuropeanOptionPricer(double asset_price,
                              double drift,
                              double vol,
                              int num_time_steps,
                              double interest_rate,
                              double maturity,
                              int num_scenarios,
                              double strike_price);
  VanillaEuropeanOptionPricer() = delete;

private:
  std::string d_derivative_name;
  
  double apply_derivative_func(double price);
};

#endif