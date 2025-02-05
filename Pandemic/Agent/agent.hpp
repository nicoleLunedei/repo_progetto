#ifndef AGENT_HPP
#define AGENT_HPP


#include "matrix.hpp"
#include "pandemic.hpp"

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
int sum_one_line(std::vector<Person>& pers);

int sum_Matrix(Matrix<Person>& total);

class Agent : public Pandemic {
 private:
  ///////////////Matrix object rappresenting the population/////////////////////
  Matrix<Person> M_;
  /////////Recognizing the state of a cell and than change it according on the
  ///rules//////////////
  void change_state();

  bool throwing_dices(double dice) const;
 

 public:
  ////////////////////////Constructors////////////////////////////

  ///////Parametric///////////
  Agent(const std::vector<People>& population, Parameters& par, int N);
  ////////////Default/////////
  Agent();
  //////////Copy////////////
  Agent(Agent& copy);
  //////////Getters///////
  Matrix<Person>& get_matrix();
 
  std::size_t get_side() const;
  /////////Setter///////
  /////////Setting the first situation and drawing it on the Matrix///////////
  void draw_matrix(People& begin);

  ///////////////General functionalities///////////////
   //////////////Member functions/////////////////
 const Person& show_cell(std::size_t r, std::size_t c)const;
 
  void data_collection(People& collection);
  //////////Counting the infected people around a specific cell of
  ///Matrix/////////
  int infected_neighbours(std::size_t r, std::size_t c) const;
  ////////////Data collection about the vaccine///////////////
  void sorting();
  /////////////////////Evolving function/////////////////
  void evolve(People& follow);
  ////////////Distructor////////////
  ~Agent();
};
#endif
