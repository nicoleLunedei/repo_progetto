#include <cmath>
#include <iostream>
#include <vector>
#include <numeric>
#include "agent.hpp"

////////////////Checking if the number is a perfect square///////////////////
bool is_perfect_square(int num) {
  int root = static_cast<int>(std::sqrt(num));
  return (root * root == num);
}

/////////////////////////Sum in Person contest/////////////////////////////
int sum_one_line(std::vector<Person>& pers) {
  std::vector<int> pers_n;
  for (Person& el : pers) {
    pers_n.push_back(static_cast<int>(el));
  }
 return std::accumulate(pers_n.begin(), pers_n.end(), 0);
}
////////////////////Sum of an object Matrix<Person>////////////
int sum_Matrix(Matrix<Person>& total){

 int tot = 0;
 
std::for_each(total.M.begin(), total.M.end(),[&tot]( std::vector<Person>& current){
     tot+=sum_one_line(current);
  }) ;
  return tot ;
}
/////////////////////CLASS AGENT///////////////////////////////////////////
////////////////////////Constructors////////////////////////////

///////Parametric///////////
Agent::Agent(const std::vector<People>& population, Parameters& par, int N)
    : Pandemic(population, par, N),
      M_(static_cast<std::size_t>(std::sqrt(N)), Susceptible) {
  if (!is_perfect_square(N))
    throw std::runtime_error{
        "The number of the population must a perfect square"};
}
////////////Default/////////
Agent::Agent() : Pandemic(), M_() {
  //////////////////Setting initial situation////////////////
  People initial_data;
  set_initial_condition(initial_data);
  M_.each_cell([this](Person& cell, std::size_t r, std::size_t c) {
    if (r == M_.M.size() / 2 && c == M_.M.size() / 2) {
      cell = Person::Infected;
    } else {
      cell = Person::Susceptible;
    }
  });
}
//////////Copy////////////
Agent::Agent(Agent& copy) : Pandemic(copy), M_(copy.get_matrix()) {}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////Getters///////

Matrix<Person>& Agent::get_matrix() { return M_; }
std::size_t Agent::get_side() const { return M_.M.size(); }
///////////// Toroidal structure viewing/////////////////////
const Person& Agent::show_cell(std::size_t r, std::size_t c) const{
  if (M_.M.empty())
    throw std::runtime_error{"The Matrix is empty!"};
  /////////////////////Manipulating indixes for the toroidal structure///////////////
  const std::size_t rr =
      static_cast<std::size_t>((r + get_side()) % get_side());
  const std::size_t cc =
      static_cast<std::size_t>((c + get_side()) % get_side());

  if ((rr == get_side()) || (cc == get_side())) {
    throw std::runtime_error{"Out of range!!!!!!!!!!!!!!!!!"};
  }

  return M_.M[rr][cc];
}
/////////Setter///////
/////////Setting the first situation and drawing it on the Matrix///////////

void Agent::draw_matrix(People& begin) {
  if (sum_Matrix(M_) != 0) {
    throw std::runtime_error{"You already set the initial condition"};
  }
  
  set_initial_condition(begin);

  int i = 0;
  while (i < get_situation_day(1).I_.no_vax) {
    ////////////////Extraction of the random coordinates////////////////////////
    std::size_t r = static_cast<std::size_t>(
        std::trunc(generate() * static_cast<double>(get_side())));

    std::size_t c = static_cast<std::size_t>(
        std::trunc(generate() * static_cast<double>(get_side())));
    if (show_cell(r, c) == Person::Infected) {
      ////////////Checking wich line has sum == to the side of
      ///matrix////////////////
      while (sum_one_line(M_.M[r]) ==
             static_cast<int>(get_side())) {
        r++;
      }
      ////////////////Scrolling columns//////////////////
      while (show_cell(r, c) == Person::Infected) {
        c++;
      }
      M_.modify(Person::Infected, r, c);
      i++;
    } else {
      M_.modify(Person::Infected, r, c);
      i++;
    }
  }
}

/////////////////////////////General
///functionalities//////////////////////////////////////////

bool Agent::throwing_dices(double dice) const{
  if (generate() <= dice) {
    // Change
    return true;
  } else {
    // Invariation
    return false;
  }
}

//////////Counting the infected people around a specific cell of Matrix/////////
int Agent::infected_neighbours(std::size_t r, std::size_t c) const {
  int contacts = 0;
  for (std::size_t r_ : {(r - 1), r, (r + 1)}) {
    for (std::size_t c_ : {(c - 1), c, (c + 1)}) {
      if (show_cell(r_, c_) == Person::Infected) {
        contacts++;
      }
    }
  }
  assert(contacts <= 8);
  return contacts;
}

////////////Data collection about the vaccine///////////////
void Agent::sorting() {

  ////////////////Important for the assert////////////////
  const int check = population_.back().S_.no_vax;
  ////////////to prevent the unused variable warning/////////////
  (void)check;
  M_.each_object([this](Person& cell) {
    if (cell == Person::Susceptible) {
      if (is_vaccinated()) {
        cell = Person::Susceptible_v;
        (population_.back().S_.vax)++;
        (population_.back().S_.no_vax)--;
      }
    }
  });
  assert(total(population_.back().S_) == check);
}

/////////////////////Evolving functionalities/////////////////

/////////Recognizing the state of a cell and than change it according on the
///rules//////////////

void Agent::change_state() {
  M_.each_cell(
      [this](Person& cell, std::size_t r, std::size_t c) {
        {
          int inf = 0;
          int k = 1;

          switch (cell) {
            case Person::Susceptible:

              inf = infected_neighbours(r, c);

              for (; k <= inf; k++) {
                if (throwing_dices(par_.beta.no_vax)) {
                  cell = Person::Infected;
                  break;
                }
              }
              break;
            case Person::Susceptible_v:

              inf = infected_neighbours(r, c);

              for (; k <= inf; k++) {
                if (throwing_dices(par_.beta.no_vax)) {
                  cell = Person::Infected_v;
                  break;
                }
              }

              break;
            case Person::Infected:

              if (throwing_dices(par_.gamma.no_vax)) {
                cell = Person::Healed;
              } else {
                if (throwing_dices(par_.omega.no_vax)) {
                  cell = Person::Dead;
                } else {
                  // Still Infected
                }
              }

              break;
            case Person::Infected_v:

              if (throwing_dices(par_.gamma.vax)) {
                cell = Person::Healed;
              } else {
                if (throwing_dices(par_.omega.vax)) {
                  cell = Person::Dead;
                } else {
                  // Still Infected
                }
              }
              break;
            case Person::Healed:
              //////////////Inavariation///////////
              break;
            case Person::Dead:
              //////////////Inavariation///////////
              break;
          }
        }
      });
}

void Agent::data_collection(People& collection) {
  M_.each_object([this, &collection](Person& cell) {
    switch (cell) {
      case Person::Susceptible:

        collection.S_.no_vax++;
        break;
      case Person::Susceptible_v:
        collection.S_.vax++;
        break;
      case Person::Infected:
        collection.I_.no_vax++;
        break;
      case Person::Infected_v:
        collection.I_.vax++;
        break;
      case Person::Healed:
        collection.H_++;
        break;
      case Person::Dead:
        collection.D_++;
        break;
    }
  });

  assert(sum(transform_Array<int, 6>(collection)) ==
         get_number_population());

  add_data(collection);
}

void Agent::evolve(People& follow) {
  ///////Changing///////////
  change_state();
  ///////////Collecting///////////////
  data_collection(follow);
}

//////////////Distructor//////////////
Agent::~Agent() = default;
