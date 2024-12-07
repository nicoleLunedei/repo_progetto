
#include <cassert>
#include <cmath>
#ifndef EQUATION_HPP
#define EQUATION_HPP
#include "pandemic.hpp"

class Equation : public Pandemic {
 private:
////////////////Same members of the class Pandemic////////////////
 public:
  ////////////////////////Constructors////////////////////////////

  ////////Parametric//////////////
  Equation(std::vector<People>& population, Parameters& par, const int& N);
  ///////Default////////////
  Equation();
  ///////////Copy/////////////
  Equation(Equation& copy);
  ////////////Data collection about the vaccine///////////////
  void sorting();
  ////////////////////////////////////Evolving
  ///functionalities////////////////////////////
  std::array<double, 6> update_situation(int index, People const& next);
  const People fix(std::array<double, 6> next);
  void evolve();
  void evolve_vaccine();

  ///////////////////////////////////////////Displaying
  ///Functionalities///////////////////////////
  ////////////////////////Summing data////////////////////
  std::array<int, 4> calculate(const int& t);
  ////////////////////Printing on terminal///////////////
  void Print(const int& d);
  ////////////Distructor////////////
  ~Equation();
};

#endif