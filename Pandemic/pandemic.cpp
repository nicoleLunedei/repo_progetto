#include "pandemic.hpp"

#include <array>
#include <iostream>
#include <random>
#include <cassert>
#include <stdexcept>
#include <vector>

int total(const vaccine<int>& v){

return (v.no_vax + v.vax);

}
///////////////////////////////////////Pandemic
/// Class///////////////////////////////////
////////////////////////Constructors////////////////////////////

////////Parametric//////////////

Pandemic::Pandemic(const std::vector<People>& population, const Parameters& par,
                   const int N)
    : population_{population}, par_(par), N_{N} {
  /////////////////////Checking values////////////////////////////////
  if ((par.beta.no_vax < 0. || par.beta.no_vax > 1.) ||
      (par.gamma.no_vax < 0. || par.gamma.no_vax> 1.) ||
      (par.omega.no_vax < 0. || par.omega.no_vax > 1.) || (par.v < 0 || par.v > 1.))
    throw std::runtime_error{
        "The values of the parameters must be inside the interval [0,1[ !"};

  if (par.beta.vax != 0 || par.gamma.vax != 0 || par.omega.vax != 0 ||
      par.v != 0)
    throw std::runtime_error{
        "The value of the parameters in case of vaccination must be 0 !"};
  if(N <= 0) throw std::runtime_error{"The number of the population must be a positve integer number"};
  check_normalization();
  check_R0();

  assert(population.empty());
}

////////////////Default //////////////////
Pandemic::Pandemic() : population_{}, par_(), N_{2500} {}

////////////////Copy/////////////////////////
Pandemic::Pandemic(Pandemic& copy)
    : par_(copy.get_Parameters()), N_{copy.get_number_population()} {
  this->set_initial_condition(copy.get_evolution().front());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////Setters///////////////////
/*void Pandemic::set_Parameters(Parameters& p) {
  if ((p.beta[0] < 0. || p.beta[0] > 1.) ||
      (p.gamma[0] < 0. || p.gamma[0] > 1.) ||
      (p.omega[0] < 0. || p.omega[0] > 1.) || (p.vax < 0 || p.vax > 1.))
    throw std::runtime_error{
        "The values of the parameters must be inside the interval [0,1] !"};

  if (p.beta[1] != 0 || p.gamma[1] != 0 || p.omega[1] != 0 || p.vax != 0)
    throw std::runtime_error{
        "The value of the parameters in case of vaccination must be 0 !"};

  check_normalization(p);
  check_R0(p);

  par_ = p;
}*/
void Pandemic::introduce_vacc(double vv) {
  if (par_.v != 0.)
    throw std::runtime_error{"You can't introduce the vaccine more than once"};

  if ((vv < 0. || vv > 1.))
    throw std::runtime_error{
        "The values of the parameters must be inside the interval [0,1] !"};
  par_.v = vv;
}

void Pandemic::set_initial_condition(const People& start) {
  if (population_.empty()) {
    ///////////////////////Controll on initial
    /// data/////////////////////////////////////
    //////////////Controll on Susceptible and Infected not
    /// vaccinated////////////////////
    if (start.I_.no_vax <= 0 || start.S_.no_vax <= 0) {
      throw std::runtime_error{
          "It can't start the evolution without any susceptible or any "
          "infected ! "};
    }
    //////////////Controll on Susceptible and Infected
    /// vaccinated////////////////////
    if (start.S_.vax != 0 || start.I_.vax != 0) {
      throw std::runtime_error{
          "At the begining the number of vaccinated people must be null! "};
    }
    ////////////Controll on Healed and Dead////////////
    if (start.H_ != 0 || start.D_ != 0) {
      throw std::runtime_error{
          "It doesn't make sense starting with some healed or dead people"};
    }

    /////////////////// Coherency between number population and the sum of the
    ///Infected and Susceptible people///////////////
    const int tot = sum(transform_Array<int, 6>(start));
    if (tot <= get_number_population()) {
      add_data(start);
      population_.back().S_.no_vax +=
          (N_ - tot);

    } else {
      throw std::runtime_error{
          "The inserted values must be coherent with the number of the "
          "population !"};
    }

  } else {
    throw std::runtime_error{
        "This simulation has already an initial condition, please start "
        "another simulation"};
  }
}
////////////Getters//////////////////
const Parameters& Pandemic::get_Parameters() const { return par_; }
const People& Pandemic::get_situation_day(int i) {
  std::size_t i_ = static_cast<std::size_t>(i);
  if (i_ <= 0 || i_ > population_.size()) {
    if (i_ == 0) {
      throw std::runtime_error{"The simulation starts from day one!"};
    } else {
      throw std::out_of_range{"Invalid day number!"};
    }
  }

  return population_[i_ - 1];
}

std::size_t Pandemic::get_days() const { return population_.size(); }

const int& Pandemic::get_number_population() const { return N_; }

const std::vector<People>& Pandemic::get_evolution() const { return population_; }

////////////Checking///////////////
void Pandemic::check_normalization() const {
  double com = par_.gamma.no_vax + par_.omega.no_vax;

  if (com > 1) {
   //metti il throw
   throw std::runtime_error{
        "The sum of the healing and the dying probabilities must be minor than or equal to one!"};
  }
}

bool Pandemic::check_R0() {
  if (calculate_R0() > 1) {
    return true;
  } else {
    throw std::runtime_error{
        "The simulation can't start if the critical threshold is minor than or "
        "equal to one! "};
  }
}

////////////General functionalities///////////////

/////////Updates the probabilities for the vaccinated people
void Pandemic::change_after_vacc(double e_infection, double e_death) {
  assert((e_infection > 0 && e_infection < 1 ) && (e_death > 0 && e_death < 1 ));

  par_.beta.vax =
      par_.beta.no_vax * (1 - e_infection);
  par_.omega.vax =
      par_.omega.no_vax * (1 - e_death);
  //////////////////////////////////
  double x_0 =
      1 - par_.gamma.no_vax - par_.omega.no_vax;
  
  par_.gamma.vax = 1 - x_0 - par_.omega.vax;
}

/////////////Adds data by adding a new element People to the vector population_
void Pandemic::add_data(const People& add) {
  assert((sum(transform_Array<int, 6>(add))) ==
         (N_));
  population_.push_back(add);
}
/////////////Generates a casual number
double generate() { 
 std::mt19937 gen(std::random_device{}());
 std::uniform_real_distribution<> dis(0.0, 1.0);
  return dis(gen); }

/////////////Does a data collection about who decides to get vaccinated,
/// according the probability to get vaccinated
bool Pandemic::is_vaccinated() {
  if ((generate()) <= par_.v) {
    return true;
  } else {
    return false;
  }
}

/////////////Calculates the critical threshold
double Pandemic::calculate_R0() const {
  return (par_.beta.no_vax) / (par_.gamma.no_vax + par_.omega.no_vax);
}
//////////////////Informs when the evolution has finished because there aren't
/// infected people left
bool Pandemic::terminate() const {
  if (total(population_.back().I_) >= 0) {
    return false;

  } else {
    return true;
  }
}
/////////////////////Distructor///////////////////////
Pandemic::~Pandemic() = default;