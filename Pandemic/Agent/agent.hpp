
#include <cmath>
#include <iostream>
#include <vector>

#include "matrix.hpp"
#include "pandemic.hpp"
#ifndef AGENT_HPP
#define AGENT_HPP
//////////////enumeration/////////////////////
enum Person {
  Susceptible = 0,
  Infected,
  Healed,
  Dead,
  Susceptible_v,
  Infected_v
};

/////////////////checking if the number is a perfect square////////////////
bool is_perfect_square(int num);

/////////////////////////sum in Person contest/////////////////////////////
int sum_person(std::vector<Person>& pers);

class Agent : public Pandemic {
 private:
  std::mt19937 gen;
  std::uniform_real_distribution<> dis;
  std::vector<People> population_;
  Parameters par_;
  int N_;
  static std::array<double, 2> intersec_;
  ///////////////Matrix object rappresenting the population/////////////////////
  Matrix<Person> M_;

 public:
  ////////////////////////Constructors////////////////////////////

  ///////Parametric///////////
  Agent(std::vector<People>& population, Parameters& par, const int& N);
  ////////////Default/////////
  Agent();
  //////////Copy////////////
  Agent(Agent& copy);
  //////////Getters///////
  Matrix<Person>& get_matrix();
  Person& show_cell(std::size_t r, std::size_t c);
  std::size_t get_side() const;
  /////////Setter///////
  /////////Setting the first situation and drawing it on the Matrix///////////
  void draw_matrix(People& begin);

  ///////////////General functionalities///////////////

  bool throwing_dices(double& dice);
  //////////Counting the infected people around a specific cell of
  ///Matrix/////////
  int infected_neighbours(std::size_t r, std::size_t c);
  ////////////Data collection about the vaccine///////////////
  void sorting();
  /////////////////////Evolving functionalities/////////////////
  /////////Recognizing the state of a cell and than change it according on the
  ///rules//////////////
  void change_state();
  void data_collection(People& collection);
  void evolve(People& follow);
  ////////////Distructor////////////
  ~Agent();
};
#endif
