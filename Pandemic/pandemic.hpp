
#ifndef PANDEMIC_HPP
#define PANDEMIC_HPP

#include <random>
#include <array>
#include <numeric>
#include <algorithm>
#include "parameters.hpp"
#include "people.hpp"
//////////////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t N>
T sum(const std::array<T, N>& a) {
 
  return std::accumulate(a.begin(), a.end(), T());
}

template <typename T, std::size_t N>
typename  std::array<T,N>::iterator maximum_dec( std::array<T, N>& a) {

//////looking for the iterator at the element with maximum decimal part//////////
typename  std::array<T,N>::iterator right_one = std::max_element(a.begin(), a.end(),[](T higher, T test ){
     double dec_h= higher - std::floor(higher);
     double dec_t= test - std::floor(test);
     return ( dec_h < dec_t ); 
 });

 /////////returning the position of the "right one" element ///////////
  
  return right_one;
}


template <typename C, std::size_t N>
const std::array<int, N> integer_part(const std::array<C, N>& c) {
  std::array<int, N> t{};
  for(std::size_t i = 0; i < N ; ++i){
    t[i] = static_cast<int>(std::floor(c[i]));
  }
  
  return t;
}

template <typename T, std::size_t N>
const std::array<T, N> transform_Array(const People& p) {
  return {static_cast<T>(p.S_.no_vax), static_cast<T>(p.S_.vax),
          static_cast<T>(p.I_.no_vax), static_cast<T>(p.I_.vax),
          static_cast<T>(p.H_),    static_cast<T>(p.D_)};
}
template <typename T, std::size_t N>
const People transform_People(const std::array<T, N>& t) {
  return {{t[0], t[1]}, {t[2], t[3]}, t[4], t[5]};
}
//////////////////////////////////////////////////////////////////////////////////////////////////
int total(const Vaccine<int>& v);
///////////////////////////////////////////////////////////////////////////////////////////////////

class Pandemic {
 protected:
  ///////////A tracking vector that registrates data of each day of the
  /// simulation////////////
  std::vector<People> population_;
  /////////////Probabilistic parameters //////////////////////////
  Parameters par_;
  //////////////Number of the population///////////////
  const int N_;
  //////////////////Protected Members/////////////////
   ////////////Checking///////////////
  bool check_R0();
  void check_normalization() const;

  bool is_vaccinated();

 public:
  ////////////////////////Constructors////////////////////////////

  ////////Parametric//////////////

  Pandemic(const std::vector<People>& population, const Parameters& par, const int N);

  /////////////Default///////////
  Pandemic();

  ////////////////Copy/////////////////////////
  Pandemic(Pandemic& copy);

  //////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////Setters///////////////////
  //void set_Parameters(Parameters& p);
  void introduce_vacc(double v);
  void set_initial_condition(const People& start);
  /////////////Adds data by adding a new element People to the vector
  /// population_
  void add_data(const People& add);
  ////////////Getters//////////////////
  const std::vector<People>& get_evolution() const;
  const Parameters& get_Parameters() const;
  const int& get_number_population() const;

  std::size_t get_days() const;
  const People& get_situation_day( int i);

 

  ////////////General functionalities///////////////

  /////////Updates the probabilities for the vaccinated people
  void change_after_vacc(double e_death, double e_heal);


  /////////////Calculates the critical threshold
  double calculate_R0() const;
  //////////////////Informs when the evolution has finished because there aren't
  /// infected people left
  bool terminate() const;

  ///////////Distructor//////////////////////////////////////
  ~Pandemic();
};

  /////////////Generates a casual number
  double generate() ;
#endif