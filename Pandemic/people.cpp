#include <array>
#include <cassert>
//#include <functional>
#include <iostream>
//#include <random>
//#include <stdexcept>
//#include <vector>
#include "people.hpp"

//////////////////// People Struct///////////////////
// Parametric Constructor
People::People(const Vaccine<int>& s, const  Vaccine<int>& i,
                int h, int d)
    : S_{s}, I_{i}, H_{h}, D_{d} {}
// Default Constructor
People::People() {
  S_.no_vax = 2499;
  S_.vax = 0;
  I_.no_vax = 1;
  I_.vax = 0;
  H_ = 0;
  D_ = 0;
}
// Copy Constructor
/*People::People(const People& other)
    : S_{other.S_}, I_{other.I_}, H_{other.H_}, D_{other.D_} {}

////////////////////// Over loading /////////////////////
People& People::operator=(const People& value) {
  ////////////////////Checking if they are the same object//////////////////
  if (this != &value) {
    S_.no_vax = value.S_.no_vax;
    S_.vax = value.S_.vax;
    I_.no_vax = value.I_.no_vax;
    I_.vax = value.I_.vax;
    H_ = value.H_;
    D_ = value.D_;
  }
  return *this;
}*/
bool operator==(const People& left, const People& right) {
  return (left.S_.no_vax == right.S_.no_vax && left.S_.vax == right.S_.vax &&
          left.I_.no_vax == right.I_.no_vax && left.I_.vax == right.I_.vax &&
          left.H_ == right.H_ && left.D_ == right.D_);
}

std::ostream& operator<<(std::ostream& os, const People& p_out) {
  os << "Suscepttible not vaccinated : " << p_out.S_.no_vax
     << "||  Suscepttible vaccinated : " << p_out.S_.vax << "\n\n";
  os << "Infected not vaccinated: " << p_out.I_.no_vax
     << "|| Infected not vaccinated: " << p_out.I_.vax << "\n\n";
  os << " Healed : " << p_out.H_ << "\n\n";
  os << "Dead : " << p_out.D_ << "\n\n";

  return os;
}
// Operator>>
std::istream& operator>>(std::istream& is, People& p_in) {
  is >> p_in.S_.no_vax >> p_in.I_.no_vax >> p_in.H_ >> p_in.D_;
  ///////////////////Checking if the reading went good/////////////////
  if (!is) {
    is.setstate(std::ios::failbit);
  }
  return is;
}
People::~People() = default;
