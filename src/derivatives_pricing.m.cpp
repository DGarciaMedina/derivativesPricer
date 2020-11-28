#include <iostream>
#include <string>

// #include <derivatives_pricer.h>
#include <derivatives_types.h>
#include <vanilla_european_option_pricer.h>

void show_usage(std::string name)
{
  std::cerr << "Usage: " << name << " <option(s)> derivative_type\n\n"
            << "Options:\n"
            << "\t-h,--help\t\tShow this help message\n"
            << "derivative_type:\n"
            << "\t0\tVanilla European Option\n"
            << "\t1\tShort Call\n"
            << "\t2\tShort Put\n"
            << "\t3\tLong Call\n"
            << "\t4\tLong Put\n\n";
}

int main(int argc, char *argv[])
{
  if (argc < 2 || argc > 3)
  {
    std::cerr << "Invalid number of arguments: " << argc << "\n";
    show_usage(argv[0]);
    return 1;
  }

  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];
    if ((arg == "-h") || (arg == "--help"))
    {
      show_usage(argv[0]);
      return 0;
    }

    switch (std::stoi(arg))
    {
    case (Derivative_t::VanillaEuropeanOption):
    {
      VanillaEuropeanOptionPricer p(1000, 0.05, 0.5, 1000, 2.0, 1, 100, 2000);
      p.calculate();
      p.print_results();
      break;
    }
    case (Derivative_t::ShortCall):
      std::cout << "-- Short Call --\n";
      break;
    case (Derivative_t::ShortPut):
      std::cout << "-- Short Put --\n";
      break;
    case (Derivative_t::LongCall):
      std::cout << "-- Long Call --\n";
      break;
    case (Derivative_t::LongPut):
      std::cout << "-- Long Put --\n";
      break;
    default:
      std::cerr << "Invalid derivative type " << arg << "\n";
      show_usage(argv[0]);
      return 1;
    }
  }

  return 0;
}