#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>
struct Parameters {  /////////Infection////////
  std::array<double, 2> beta;
  /////////Healing/////////////
  std::array<double, 2> gamma;
  //////////Dying//////////
  std::array<double, 2> omega;
  double vax;
  // Parametric Constructor
  Parameters(const std::array<double, 2>& b, const std::array<double, 2>& g,
             const std::array<double, 2>& o, const double& v);
  // Default Constructor
  Parameters();
  // Copy Constructor
  Parameters(const Parameters& other);

  // Operator=
  Parameters& operator=(const Parameters& other);
  // Operator ==
  friend bool operator==(const Parameters& left, const Parameters& right);

  ~Parameters();
};

#endif