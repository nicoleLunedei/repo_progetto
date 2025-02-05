
//#include <cassert>
//#include <functional>
#include <iostream>
//#include <random>
//#include <stdexcept>
//#include <vector>
#include "parameters.hpp"
// Struct Parameters
// Parametric Constructor
Parameters::Parameters(const Vaccine<double>& b,
                       const Vaccine<double>& g,
                       const Vaccine<double>& o, double vv)
    : beta{b},
      gamma{g},
      omega{o},
      v{vv} {
} 
// Default Constructor
Parameters::Parameters()
    : beta{0.6, 0.}, gamma{0.2, 0.}, omega{0.35, 0.}, v{0.} {}
// Copy Constructor
/*Parameters::Parameters(
    const Parameters&
        other) { 
  beta.no_vax = other.beta.no_vax;
  beta.vax = other.beta.vax;
  gamma.no_vax = other.gamma.no_vax;
  gamma.vax = other.gamma.vax;
  omega.no_vax = other.omega.no_vax;
  omega.vax = other.omega.vax;
  v = other.v;
}

// Operator=
Parameters& Parameters::operator=(const Parameters& other) {
  if (this != &other) {
    beta.no_vax = other.beta.no_vax;
    beta.vax = other.beta.vax;
    gamma.no_vax = other.gamma.no_vax;
    gamma.vax = other.gamma.vax;
    omega.no_vax = other.omega.no_vax;
    omega.vax = other.omega.vax;
    v = other.v;
  }
  return *this;
}*/

// Operator ==
bool operator==(const Parameters& left, const Parameters& right) {
  return (left.beta.no_vax == right.beta.no_vax && left.beta.vax == right.beta.vax &&
          left.gamma.no_vax == right.gamma.no_vax && left.gamma.vax == right.gamma.vax &&
          left.omega.no_vax == right.omega.no_vax && left.omega.vax == right.omega.vax &&
          left.v == right.v);
}
// Operator<<
std::ostream& operator<<(std::ostream& os, const Parameters& p_out) {
  os << p_out.beta.no_vax << "||" << p_out.beta.vax << '\n';
  os << p_out.gamma.no_vax << "||" << p_out.gamma.vax << '\n';
  os << p_out.omega.no_vax << "||" << p_out.omega.vax << '\n';
  os << p_out.v << '\n';

  return os;
}
Parameters::~Parameters() = default;
