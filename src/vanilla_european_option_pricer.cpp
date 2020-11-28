
#include <vanilla_european_option_pricer.h>

VanillaEuropeanOptionPricer::VanillaEuropeanOptionPricer(double asset_price,
                                                         double drift,
                                                         double vol,
                                                         int num_time_steps,
                                                         double interest_rate,
                                                         double maturity,
                                                         int num_scenarios,
                                                         double strike_price)
    : DerivativesPricer::DerivativesPricer(asset_price,
                                           drift,
                                           vol,
                                           num_time_steps,
                                           interest_rate,
                                           maturity,
                                           num_scenarios,
                                           strike_price,
                                           "Vanilla European Option")
{
}

double VanillaEuropeanOptionPricer::apply_derivative_func(double price)
{
  return (price > d_strike_price) ? price : 0.0;
}