#include "equation.hpp"

#include <cassert>
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
  set_initial_condition(initial_data);
}


//////////////////Data collection about the vaccine///////////////////////

void Equation::sorting() {
  ////////Saving the current value of the Susceptible people////////////////
  int t = population_.back().S_.no_vax;

  for (int i = 0; i <= t; i++) {
    if (is_vaccinated()) {
      population_.back().S_.no_vax--;
      population_.back().S_.vax++;
    }
  }
  assert(total(population_.back().S_) == t);
}
////////////////Evolving functionalities////////////////////////////
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||//

std::array<double, 6> Equation::update_situation(const int index,
                                                 People const& next) {
  //////0 = no vaccine, 1 = with vaccine////////////
  assert(index == 1 || index == 0);
  ////////////////Controlling that the vector isn't
  ///empty////////////////////////
  assert(!(population_.empty()));
  //////////////////Trasforming the object People to an array/////////////////
  ////////////////////Local variable////////////////////
  std::array<double, 6> next_a{transform_Array<double, 6>(next)};

  ////////// H_ & D_ ///////////
  if (sum(next_a) == 0) {
    next_a[4] +=
        population_.back().H_ +
        (par_.gamma.no_vax) * population_.back().I_.no_vax;
    next_a[5] +=
        population_.back().D_ +
        (par_.omega.no_vax) * population_.back().I_.no_vax;
  } else {
    next_a[4] +=
        (par_.gamma.vax) * population_.back().I_.vax;
    next_a[5] +=
        (par_.omega.vax) * population_.back().I_.vax;
  }
  ///////////// S_ & I_ /////////////
  switch (index) {
    case 0: {
      next_a[0] =
          population_.back().S_.no_vax -
          ((((par_.beta.no_vax) *
             ((population_.back().S_.no_vax))) /
            N_) *
           (total(population_
                    .back()
                    .I_))); 

      next_a[2] = population_.back().I_.no_vax +
                  ((((par_.beta.no_vax) *
                     (population_.back().S_.no_vax)) /
                    (N_)) *
                   (total(population_.back().I_))) -
                  ((par_.gamma.no_vax) *
                   population_.back().I_.no_vax) -
                  ((par_.omega.no_vax) *
                   population_.back().I_.no_vax);

      break;
    }
    case 1: {
      next_a[1] =
          population_.back().S_.vax -
          ((((par_.beta.vax) *
             ((population_.back().S_.vax))) /
           N_) *
           (total(population_
                    .back()
                    .I_))); 

      next_a[3] = population_.back().I_.vax +
                  ((((par_.beta.vax) *
                     (population_.back().S_.vax)) /
                    (N_)) *
                   (total(population_.back().I_))) -
                  ((par_.gamma.vax) *
                   population_.back().I_.vax) -
                  ((par_.omega.vax) *
                   population_.back().I_.vax);
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
  double& max_el = *maximum_dec(next);
  if (0 < diff && diff < 2) {
    max_el += 1;
  } else {
    max_el+= std::floor(diff);
  }
  return transform_People(integer_part(next));
}

void Equation::evolve() {
  const People follow = {{0, 0}, {0, 0}, 0, 0};

  //////////////////////Updating the situation/////////////////////////
  add_data(fix(update_situation(0, follow)));

  assert(get_number_population() ==
         sum(transform_Array<int, 6>(get_evolution().back())));
}

void Equation::evolve_vaccine() {
  const People& follow = {{0, 0}, {0, 0}, 0, 0};
  ///////////////////////First the natural evolution//////////////////
  const People& natural = fix(update_situation(0, follow));

  //////////////////////Second the evoulution with the
  ///vaccine///////////////////
  add_data(fix(update_situation(1, natural)));

  assert(N_ ==
         sum(transform_Array<int, 6>(get_evolution().back())));
}
///////////////////////////////////////////Displaying
///Functionalities///////////////////////////
////////////////////////Summing data////////////////////
std::array<int, 4> Equation::calculate(const int t) {
  std::array<int, 4> calc{0, 0, 0, 0};
  calc[0] = total(get_situation_day(t).S_);
  calc[1] = total(get_situation_day(t).I_);
  calc[2] = get_situation_day(t).H_;
  calc[3] = get_situation_day(t).D_;
  return calc;
}
////////////////////Printing on terminal////////////////////
void Equation::print( int d) {
  std::cout << "S = " << calculate(d)[0] << " || ";
  std::cout << "I = " << calculate(d)[1] << " || ";
  std::cout << "H = " << calculate(d)[2] << " || ";
  std::cout << "D = " << calculate(d)[3] << "\n\n";
}

////////////Distructor////////////
Equation::~Equation() = default;
