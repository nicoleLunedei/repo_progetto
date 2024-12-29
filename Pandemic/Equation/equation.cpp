#include "equation.hpp"

#include <assert.h>

#include <array>
#include <iostream>
#include <vector>



////////////////////////Constructors////////////////////////////

//////////////////////Parametric//////////////////////////////
Equation::Equation(const std::vector<People>& population, Parameters& par,
                   const int N)
    : Pandemic(population, par, N) {}

/////////////////////////Default////////////////////////////
Equation::Equation() : Pandemic() {
  /////////////////Creates an object equal to Pandemic, but setting an initial
  ///situation/////////////////
  People initial_data({2000, 0}, {500, 0}, 0, 0);
  this->set_initial_condition(initial_data);
}
///////////Copy/////////////
Equation::Equation(Equation& copy) : Pandemic(copy) {}

//////////////////Data collection about the vaccine///////////////////////

void Equation::sorting() {
  ////////Savinge the current value of the Susceptible people////////////////
  int t = this->get_evolution().back().S_[0];

  for (int i = 0; i <= t; i++) {
    if (this->is_vaccinated()) {
      this->get_evolution().back().S_[0]--;
      this->get_evolution().back().S_[1]++;
    }
  }
  assert(sum(this->get_evolution().back().S_) == t);
}
////////////////Evolving functionalities////////////////////////////
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||//

std::array<double, 6> Equation::update_situation(const int index,
                                                 People const& next) {
  assert(index == 1 || index == 0);
  ////////////////Controlling that the vector isn't
  ///empty////////////////////////
  assert(!(this->get_evolution().empty()));
  //////////////////Trasforming the object People to an array/////////////////
  ////////////////////Local variable////////////////////
  std::array<double, 6> next_a{transform_Array<double, 6>(next)};

  ////////// H_ & D_ ///////////
  if (sum(next_a) == 0) {
    next_a[4] +=
        this->get_evolution().back().H_ +
        (this->get_Parameters().gamma[0]) * this->get_evolution().back().I_[0];
    next_a[5] +=
        this->get_evolution().back().D_ +
        (this->get_Parameters().omega[0]) * this->get_evolution().back().I_[0];
  } else {
    next_a[4] +=
        (this->get_Parameters().gamma[1]) * this->get_evolution().back().I_[1];
    next_a[5] +=
        (this->get_Parameters().omega[1]) * this->get_evolution().back().I_[1];
  }
  ///////////// S_ & I_ /////////////
  switch (index) {
    case 0: {
      next_a[0] =
          this->get_evolution().back().S_[0] -
          ((((this->get_Parameters().beta[0]) *
             ((this->get_evolution().back().S_[0]))) /
            this->get_number_population()) *
           (sum(this->get_evolution()
                    .back()
                    .I_))); 

      next_a[2] = this->get_evolution().back().I_[0] +
                  ((((this->get_Parameters().beta[0]) *
                     (this->get_evolution().back().S_[0])) /
                    (this->get_number_population())) *
                   (sum(this->get_evolution().back().I_))) -
                  ((this->get_Parameters().gamma[0]) *
                   this->get_evolution().back().I_[0]) -
                  ((this->get_Parameters().omega[0]) *
                   this->get_evolution().back().I_[0]);

      break;
    }
    case 1: {
      next_a[1] =
          this->get_evolution().back().S_[1] -
          ((((this->get_Parameters().beta[1]) *
             ((this->get_evolution().back().S_[1]))) /
            this->get_number_population()) *
           (sum(this->get_evolution()
                    .back()
                    .I_))); 

      next_a[3] = this->get_evolution().back().I_[1] +
                  ((((this->get_Parameters().beta[1]) *
                     (this->get_evolution().back().S_[1])) /
                    (this->get_number_population())) *
                   (sum(this->get_evolution().back().I_))) -
                  ((this->get_Parameters().gamma[1]) *
                   this->get_evolution().back().I_[1]) -
                  ((this->get_Parameters().omega[1]) *
                   this->get_evolution().back().I_[1]);
      break;
    }
  }
/////////////////Returning a local variable///////////////
  return next_a;
}
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||//

const People Equation::fix( std::array<double, 6>&& next) {
  ////////////////////Getting the deviation//////////////////
  const double diff = sum(next) - sum(integer_part(next));
  assert(diff >= 0);
  /////////////////////Searching for the double number with the greatest decimal
  ///part/////////////////////////////
  if (0 < diff && diff < 2) {
    next[maximum_dec(next)] += 1;
  } else {
    next[maximum_dec(next)] += diff;
  }
  return transform_People(integer_part(next));
}

void Equation::evolve() {
  const People follow = {{0, 0}, {0, 0}, 0, 0};

  //////////////////////Updating the situation/////////////////////////
  this->add_data(this->fix(this->update_situation(0, follow)));

  assert(this->get_number_population() ==
         sum(transform_Array<int, 6>(this->get_evolution().back())));
}

void Equation::evolve_vaccine() {
  const People& follow = {{0, 0}, {0, 0}, 0, 0};
  ///////////////////////First the natural evolution//////////////////
  const People& natural = this->fix(this->update_situation(0, follow));

  //////////////////////Second the evoulution with the
  ///vaccine///////////////////
  this->add_data(this->fix(this->update_situation(1, natural)));

  assert(this->get_number_population() ==
         sum(transform_Array<int, 6>(this->get_evolution().back())));
}
///////////////////////////////////////////Displaying
///Functionalities///////////////////////////
////////////////////////Summing data////////////////////
std::array<int, 4> Equation::calculate(const int t) {
  std::array<int, 4> calc{0, 0, 0, 0};
  calc[0] = sum(this->get_situation_day(t).S_);
  calc[1] = sum(this->get_situation_day(t).I_);
  calc[2] = this->get_situation_day(t).H_;
  calc[3] = this->get_situation_day(t).D_;
  return calc;
}
////////////////////Printing on terminal////////////////////
void Equation::Print(const int d) {
  std::cout << "S = " << this->calculate(d)[0] << " || ";
  std::cout << "I = " << this->calculate(d)[1] << " || ";
  std::cout << "H = " << this->calculate(d)[2] << " || ";
  std::cout << "D = " << this->calculate(d)[3] << "\n\n";
}

////////////Distructor////////////
Equation::~Equation() = default;
