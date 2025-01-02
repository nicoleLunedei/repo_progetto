
#ifndef PANDEMIC_HPP
#define PANDEMIC_HPP

#include "parameters.hpp"
#include "people.hpp"
//////////////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t N>
T sum(const std::array<T, N>& a) {
  T tot = T();
  for (const T& t : a) {
    tot += t;
  }

  return tot;
}
template <typename T>
T sum(const std::vector<T>& v) {
  T tot = 0;
  for (const T& t : v) {
    tot += t;
  }

  return tot;
}
template <typename T, std::size_t N>
std::size_t maximum_dec(const std::array<T, N>& a) {
  T max = 0;
  std::size_t t = 0;
  for (std::size_t it = 0; it < N; ++it) {
    if ((a[static_cast<std::size_t>(it)] -
         std::floor(a[static_cast<std::size_t>(it)])) > max) {
      max = a[static_cast<std::size_t>(it)] -
            std::floor(a[static_cast<std::size_t>(it)]);
      t = it;
    }
  }
  return t;
}

/*template<typename T,typename C, std::size_t N> const std::array<T,N>
convert(const std::array<C,N>& c){

 std::array<T,N> t;

 for (std::size_t i = 0; i < N; i++)
 {
   t[i] = std::floor(c[i]);
 }
   return t;
}*/
template <typename C, std::size_t N>
const std::array<int, N> integer_part(const std::array<C, N>& c) {
  std::array<int, N> t;

  for (std::size_t i = 0; i < N; i++) {
    t[i] = static_cast<int>(std::floor(c[i]));
  }
  return t;
}

template <typename T, std::size_t N>
const std::array<T, N> transform_Array(const People& p) {
  return {static_cast<T>(p.S_[0]), static_cast<T>(p.S_[1]),
          static_cast<T>(p.I_[0]), static_cast<T>(p.I_[1]),
          static_cast<T>(p.H_),    static_cast<T>(p.D_)};
}
template <typename T, std::size_t N>
const People transform_People(const std::array<T, N>& t) {
  return {{t[0], t[1]}, {t[2], t[3]}, t[4], t[5]};
}
///////////////////////////////////////////////////////////////////////////////////////////////////

class Pandemic {
 private:
  ///////////A tracking vector that registrates data of each day of the
  /// simulation////////////
  std::vector<People> population_;
  /////////////Probabilistic parameters //////////////////////////
  Parameters par_;
  //////////////Number of the population///////////////
  const int N_;
  /////////////Efficacy of the vaccine //////////////////
  static std::array<double, 2> efficacy_;
  /////////////Pseudo Random Number Generator//////////
  static std::mt19937 gen;
  static std::uniform_real_distribution<> dis;

 public:
  ////////////////////////Constructors////////////////////////////

  ////////Parametric//////////////

  Pandemic(const std::vector<People>& population, Parameters& par, const int N);

  /////////////Default///////////
  Pandemic();

  ////////////////Copy/////////////////////////
  Pandemic(Pandemic& copy);

  //////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////Setters///////////////////
  void set_Parameters(Parameters& p);
  void introduce_vacc(double v);
  void set_initial_condition(const People& start);
  ////////////Getters//////////////////
  std::vector<People>& get_evolution();
  Parameters& get_Parameters();
  const int& get_number_population() const;

  std::size_t get_days() const;
  const People& get_situation_day(const int i);

  ////////////Checking///////////////
  bool check_R0(Parameters& p);
  void check_normalization(Parameters& p) const;

  ////////////General functionalities///////////////

  /////////Updates the probabilities for the vaccinated people
  void change_after_vacc();

  /////////////Generates a casual number
  double generate() const;

  /////////////Adds data by adding a new element People to the vector
  /// population_
  void add_data(const People& add);

  /////////////Does a data collection about who decides to get vaccinated,
  /// according the probability to get vaccinated
  bool is_vaccinated();

  /////////////Calculates the critical threshold
  double calculate_R0(Parameters& p);
  //////////////////Informs when the evolution has finished because there aren't
  /// infected people left
  bool terminate();

  ///////////Distructor//////////////////////////////////////
  ~Pandemic();
};

#endif