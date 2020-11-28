#include <functional>
#include <future>
#include <iostream>
#include <random>
#include <thread>
#include <vector>
#include <utility>

#include <derivatives_pricer.h>
#include <vanilla_european_option_pricer.h>

DerivativesPricer::DerivativesPricer(double spot_price,
                                     double drift,
                                     double vol,
                                     int num_time_steps,
                                     double interest_rate,
                                     double maturity,
                                     int num_scenarios,
                                     double strike_price,
                                     std::string derivative_name)
    : d_spot_price(spot_price), d_drift(drift), d_num_time_steps(num_time_steps), d_vol(vol), d_dt(maturity / (double)num_time_steps), d_interest_rate(interest_rate), d_maturity(maturity), d_num_scenarios(num_scenarios), d_strike_price(strike_price), d_derivative_name(std::move(derivative_name))
{
}

void DerivativesPricer::calculate()
{
  std::vector<std::future<double>> prices(d_num_scenarios);
  auto simulation = std::bind(&DerivativesPricer::calculate_one_simulation, this, std::placeholders::_1);
  for (int i = 0; i < d_num_scenarios; ++i)
  {
    prices[i] = std::async(simulation, 12345);
  }

  double sum = 0;
  double num;
  for (int i = 0; i < d_num_scenarios; ++i)
  {
    sum += prices[i].get();
  }

  d_asset_price = sum / (double)d_num_scenarios;
}

double DerivativesPricer::calculate_one_simulation(int seed)
{
  std::mt19937_64 mtEngine(seed);
  std::normal_distribution<> norm_dist;

  double price = d_spot_price;
  for (int i = 0; i < d_num_time_steps; ++i)
  {
    price = mc_next_price(price, norm_dist(mtEngine));
  }

  return apply_derivative_func(price);
}

double DerivativesPricer::mc_next_price(double prev_price, double norm)
{
  double exp_arg_1 = d_dt * (d_interest_rate - (d_vol * d_vol) / 2);
  double exp_arg_2 = d_vol * norm * sqrt(d_dt);
  return prev_price * exp(exp_arg_1 + exp_arg_2);
}

double DerivativesPricer::get_spot_price()
{
  return d_spot_price;
}

void DerivativesPricer::print_results()
{
  std::cout << "\n"
            << "#############################################################\n"
            << "#                                                           #\n"
            << "#              Monte Carlo Simulation Results               #\n"
            << "#                                                           #\n"
            << "#############################################################\n"
            << "\n\n\tDerivative Type:\t" << d_derivative_name
            << "\n\n\tNum. Simulations:\t" << d_num_scenarios
            << "\n\tSpot Price:\t\t" << d_spot_price
            << "\n\tStrike Price:\t\t" << d_strike_price
            << "\n\tVolatility:\t\t" << d_vol
            << "\n\tDrift:\t\t\t" << d_drift
            << "\n\tNum. Time Steps:\t" << d_num_time_steps
            << "\n\tInterest Rate:\t\t" << d_interest_rate
            << "\n\tMaturity:\t\t" << d_maturity
            << "\n\n\tAsset Price:\t\t" << d_asset_price << "\n\n";
}