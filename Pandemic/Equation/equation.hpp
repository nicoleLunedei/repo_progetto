#ifndef EQUATION_HPP
#define EQUATION_HPP


#include "pandemic.hpp"

class Equation : public Pandemic {
 private:
  
////////////////Same members of the class Pandemic////////////////
 public:
  ////////////////////////Constructors////////////////////////////

  ////////Parametric//////////////
  Equation(const std::vector<People>& population, Parameters& par, int N);
  ///////Default////////////
  Equation();

 //Does a data collection about who decides to get vaccinated, according the probability to get vaccinated
  void sorting();
  ////////////////////////////////////Evolving
  ///functionalities////////////////////////////
  std::array<double, 6> update_situation(const int index, People const& next);
  const People fix(std::array<double, 6>&& next);
  void evolve();
  void evolve_vaccine();

  ///////////////////////////////////////////Displaying
  ///Functionalities///////////////////////////
  ////////////////////////Summing data////////////////////
  std::array<int, 4> calculate( int t);
  ////////////////////Printing on terminal///////////////
  void print( int d);
  ////////////Distructor////////////
  ~Equation();
};

#endif