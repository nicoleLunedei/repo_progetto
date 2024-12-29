#include "pandemic.hpp"

#include <array>
#include <functional>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

// [0]=infection efficacy, [1] = death efficacy
std::array<double, 2> Pandemic::efficacy_{0.71, 0.65};
std::mt19937 Pandemic::gen(std::random_device{}());
std::uniform_real_distribution<> Pandemic::dis(0.0, 1.0);
///////////////////////////////////////Pandemic
///Class///////////////////////////////////
////////////////////////Constructors////////////////////////////

////////Parametric//////////////

Pandemic::Pandemic(const std::vector<People>& population, Parameters& par,
                   const int N)
    : population_{population}, par_(par), N_{N} {
  /////////////////////Checking values////////////////////////////////
  if ((par.beta[0] < 0. || par.beta[0] > 1.) ||
      (par.gamma[0] < 0. || par.gamma[0] > 1.) ||
      (par.omega[0] < 0. || par.omega[0] > 1.) || (par.vax < 0 || par.vax > 1.))
    throw std::runtime_error{
        "The values of the parameters must be inside the interval [0,1] !"};

  if (par.beta[1] != 0 || par.gamma[1] != 0 || par.omega[1] != 0 ||
      par.vax != 0)
    throw std::runtime_error{
        "The value of the parameters in case of vaccination must be 0 !"};

  this->check_normalization(par);
  this->check_R0(par);

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
void Pandemic::set_Parameters(Parameters& p) {
  if ((p.beta[0] < 0. || p.beta[0] > 1.) ||
      (p.gamma[0] < 0. || p.gamma[0] > 1.) ||
      (p.omega[0] < 0. || p.omega[0] > 1.) || (p.vax < 0 || p.vax > 1.))
    throw std::runtime_error{
        "The values of the parameters must be inside the interval [0,1] !"};

  if (p.beta[1] != 0 || p.gamma[1] != 0 || p.omega[1] != 0 || p.vax != 0)
    throw std::runtime_error{
        "The value of the parameters in case of vaccination must be 0 !"};

  this->check_normalization(p);
  this->check_R0(p);

  this->par_ = p;
}
void Pandemic::introduce_vacc(const double& v) {
  if (this->get_Parameters().vax != 0.)
    throw std::runtime_error{
        "You can't introduce the vaccine more than once"};

  if ((v < 0. || v > 1.))
    throw std::runtime_error{
        "The values of the parameters must be inside the interval [0,1] !"};
  this->get_Parameters().vax = v;
}

void Pandemic::set_initial_condition(const People& start) {
  if (this->get_evolution().empty()) {
    ///////////////////////Controll on initial
    ///data/////////////////////////////////////
    //////////////Controll on Susceptible and Infected not
    ///vaccinated////////////////////
    if (start.I_[0] <= 0 || start.S_[0] <= 0) {
      throw std::runtime_error{
          "It can't start the evolution without any susceptible or any "
          "infected ! "};
    }
    //////////////Controll on Susceptible and Infected
    ///vaccinated////////////////////
    if (start.S_[1] != 0 || start.I_[1] != 0) {
      throw std::runtime_error{
          "At the begining the number of vaccinated people must be null! "};
    }
    ////////////Controll on Healed and Dead////////////
    if (start.H_ != 0 || start.D_ != 0) {
      throw std::runtime_error{
          "It doesn't make sense start with some healed or dead people"};
    }

    ///////////////////Everything is fine, so it can be set the initial
    ///condition: it's left the final check///////////////
    const int tot = sum(transform_Array<int, 6>(start));
    if (tot <= this->get_number_population()) {
      this->add_data(start);
      this->get_evolution().back().S_[0] +=
          (this->get_number_population() - tot);

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
Parameters& Pandemic::get_Parameters() { return this->par_; }
People& Pandemic::get_situation_day(const int& i) {
  if (i <= 0 || static_cast<std::vector<People>::size_type>(i) >
                    this->population_.size()) {
    if (i == 0) {
      throw std::runtime_error{"The simulation starts from day one!"};
    } else {
      throw std::out_of_range{"Invalid day number!"};
    }
  }

  return this
      ->get_evolution()[static_cast<std::vector<People>::size_type>(i - 1)];
}

long unsigned int Pandemic::get_days() const {
  return this->population_.size();
}

const int& Pandemic::get_number_population() const { return this->N_; }

std::vector<People>& Pandemic::get_evolution() { return this->population_; }

////////////Checking///////////////
void Pandemic::check_normalization(Parameters& p) const {
  double com = p.gamma[0] + p.omega[0];

  if (com > 1) {
    p.omega[0] = p.beta[0] - p.gamma[0] - 0.1;

    std::cout << "The probablities of healing and dying must respect the "
                 "normalization property, don't worry it has been fixed"
              << "\n\n";
  }
}

bool Pandemic::check_R0(Parameters& p) {
  if (this->calculate_R0(p) > 1) {
    return true;
  } else {
    throw std::runtime_error{
        "The simulation can't start if the critical threshold is minor than or "
        "equal to one! "};
  }
}

////////////General functionalities///////////////

/////////Updates the probabilities for the vaccinated people
void Pandemic::change_after_vacc() {
  this->get_Parameters().beta[1] =
      this->get_Parameters().beta[0] * (1 - efficacy_[0]);
  this->get_Parameters().omega[1] =
      this->get_Parameters().omega[0] * (1 - efficacy_[1]);
  /////////////////eventuale scarto/////////////////
  double x_0 =
      1 - this->get_Parameters().gamma[0] - this->get_Parameters().omega[0];
  // mantengo in prporzione lo scarto delle due probabilità
  this->get_Parameters().gamma[1] = 1 - x_0 - this->get_Parameters().omega[1];
}
/////////////Generates a casual number
double Pandemic::generate() const { return dis(gen); }

/////////////Adds data by adding a new element People to the vector population_
void Pandemic::add_data(const People& add) {
  assert((sum(transform_Array<int, 6>(add))) ==
         (this->get_number_population()));
  this->get_evolution().push_back(add);
}

/////////////Does a data collection about who decides to get vaccinated,
///according the probability to get vaccinated
bool Pandemic::is_vaccinated() {
  if ((this->generate()) <= this->get_Parameters().vax) {
    return true;
  } else {
    return false;
  }
}

/////////////Calculates the critical threshold
double Pandemic::calculate_R0(Parameters& p) {
  return (p.beta[0]) / (p.gamma[0] + p.omega[0]);
}
//////////////////Informs when the evolution has finished because there aren't
///infected people left
bool Pandemic::terminate(){
  if (sum(this->get_evolution().back().I_) >= 0) {
    return false;

  } else {
    return true;
  }
}
/////////////////////Distructor///////////////////////
Pandemic::~Pandemic() = default;