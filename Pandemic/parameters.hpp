#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

#include "vaccine.hpp"

struct Parameters {  /////////Infection////////
  vaccine<double> beta;
  /////////Healing/////////////
   vaccine<double> gamma;
  //////////Dying//////////
   vaccine<double> omega;
  /////////getting vaccinated//////////////
   double v;
  // Parametric Constructor
  Parameters(const vaccine<double>& b, const vaccine<double>& g,
             const vaccine<double>& o, double v);
  // Default Constructor
  Parameters();
  // Copy Constructor
  //Parameters(const Parameters& other);

  // Operator=
 // Parameters& operator=(const Parameters& other);
  // Operator ==
  friend bool operator==(const Parameters& left, const Parameters& right);
  friend std::ostream& operator<<(std::ostream& os, const Parameters& p_out);
  ~Parameters();
};

#endif