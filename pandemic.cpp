#include <vector>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <random>
#include <array>


#include "pandemic.hpp"



//////////////////// People Struct///////////////////
    //Parametric Constructor
People::People( const std::array<int,2>& s,const std::array<int,2>& i , const int  h, const int& d  ): S_{s},I_{i},H_{h}, D_{d}{}
    //Default Constructor
People::People(){
  S_[0] = 2499;
  S_[1] = 0;
  I_[0] = 1;
  I_[1] = 0;
  H_ = 0 ;
  D_ = 0 ;
  
}
  //Copy Constructor
People::People(const People& other): S_{other.S_}, I_{other.I_}, H_{other.H_}, D_{other.D_}{}

////////////////////// Over loading /////////////////////
 People& People::operator=( const People& value)
 {
////////////////////Checking if they are the same object//////////////////
    if (this != &value)
    { 
       this->S_[0] = value.S_[0];
       this->S_[1] = value.S_[1];
       this->I_[0] = value.I_[0];
       this->I_[1] = value.I_[1];
       this->H_ = value.H_;
       this->D_ = value.D_;
    }
    return *this;
 }
 bool operator==( const People& left, const People& right)
 {
      return (left.S_[0] == right.S_[0] && left.S_[1] == right.S_[1] && left.I_[0] == right.I_[0] && left.I_[1] == right.I_[1] && left.H_ == right.H_ && left.D_ == right.D_);
 }
 

 std::ostream& operator<<(std::ostream& os, const People& p_out)
     {
   
    os << "Suscepttible not vaccinated : " << p_out.S_[0] << "||  Suscepttible vaccinated : " <<p_out.S_[1] << "\n\n";
    os << "Infected not vaccinated: " << p_out.I_[0] <<"|| Infected not vaccinated: "<< p_out.I_[1] << "\n\n";
    os << " Healed : " << p_out.H_ << "\n\n";
    os << "Dead : " << p_out.D_ << "\n\n";
   
               return os;
     }
        //Operator>>
 std::istream& operator>>(std::istream& is, People& p_in )
   {

    is >> p_in.S_[0] >> p_in.I_[0] >> p_in.H_ >> p_in.D_;
    ///////////////////Checking if the reading went good/////////////////
    if ( !is) {
      is.setstate(std::ios::failbit);
    }
    return is;
    
   }
 People::~People() = default;





//Struct Parameters
//Parametric Constructor
Parameters::Parameters(const std::array<double,2>& b, const std::array<double,2>& g, const std::array<double,2>& o, const double& v) : beta{b},gamma{g},omega{o},vax{v} {}// l'assegnazione degli array non li puoi mettere nella lista d'inizializzazione perchè non è supportata la loro assegnazione in blocco
//Default Constructor   
Parameters::Parameters(): beta{0.6,0.},gamma{0.2,0.},omega{0.35,0.}, vax{0.}{}
//Copy Constructor
Parameters::Parameters(const Parameters& other ) {// costruttore di copia che è diverso dal costruttore parametrico; questo è propio per costruire un oggetto a partire da un altro oggetto dello stesso tispo 
        beta[0] = other.beta[0];
        beta[1] = other.beta[1];
        gamma[0] = other.gamma[0];
        gamma[1] = other.gamma[1];
        omega[0] = other.omega[0];
        omega[1] = other.omega[1];
        vax = other.vax;

 }

  //Operator=
Parameters& Parameters::operator=( const Parameters& other){
      if (this != &other) { 
      this->beta[0] = other.beta[0];
      this->beta[1] = other.beta[1];
      this->gamma[0] = other.gamma[0];
      this->gamma[1] = other.gamma[1];
      this->omega[0] = other.omega[0];
      this->omega[1] = other.omega[1];
      this->vax = other.vax;
      }
      return *this;
     }

           //Operator ==
bool operator==( const Parameters& left, const Parameters& right){
      return (left.beta[0] == right.beta[0] && left.beta[1] == right.beta[1] && left.gamma[0] == right.gamma[0] && left.gamma[1] == right.gamma[1] && left.omega[0] == right.omega[0] &&left.omega[1] == right.omega[1] && left.vax == right.vax );
    } 
        //Operator<<
    std::ostream& operator<<(std::ostream& os, const Parameters& p_out){
      os<< p_out.beta[0] <<"||"<<p_out.beta[1]<<'\n';
      os<< p_out.gamma[0] <<"||"<<p_out.gamma[1]<<'\n';
      os<< p_out.omega[0] <<"||"<<p_out.omega[1]<<'\n';
      os<< p_out.vax<<'\n';
      
      return os;

    }
   Parameters::~Parameters() = default ; 




// [0]=infection efficacy, [1] = death efficacy
std::array<double,2> Pandemic::efficacy_{0.71,0.65};
std::mt19937 Pandemic::gen(std::random_device{}());
std::uniform_real_distribution<> Pandemic::dis(0.0, 1.0);
///////////////////////////////////////Pandemic Class///////////////////////////////////
//Parametric Constructor

    Pandemic::Pandemic( std::vector<People>& population,  Parameters& par,const int& N) : population_{population}, par_(par), N_{N} {
    
      /////////////////////Checking values////////////////////////////////
     if ((par.beta[0] < 0. || par.beta[0] > 1. ) || (par.gamma[0] < 0. || par.gamma[0] > 1. ) ||  (par.omega[0]< 0. || par.omega[0] > 1.) || (  par.vax<0 || par.vax > 1. )  ) 
       throw  std::runtime_error{"The values of the parameters must be inside the interval [0,1] !"};

     if (par.beta[1] != 0 || par.gamma[1] != 0 || par.omega[1] != 0  || par.vax != 0 )
       throw  std::runtime_error{"The value of the parameters in case of vaccination must be 0 !"};

     this->check_normalization(par);
     this->check_R0(par);

     assert(population.empty());
    }

    //Default Constructor
     Pandemic::Pandemic(): population_{},par_(),N_{2500}{} 
    
      
 
  
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////Setters///////////////////
   void  Pandemic::set_Parameters(Parameters& p){
     if ((p.beta[0] < 0. || p.beta[0] > 1. ) || (p.gamma[0] < 0. || p.gamma[0] > 1. ) ||  (p.omega[0]< 0. || p.omega[0] > 1.) || (  p.vax<0 || p.vax > 1. )  ) 
       throw  std::runtime_error{"The values of the parameters must be inside the interval [0,1] !"};
     
     if (p.beta[1] != 0 || p.gamma[1] != 0 || p.omega[1] != 0  || p.vax != 0 ) 
       throw  std::runtime_error{"The value of the parameters in case of vaccination must be 0 !"};
     
      this->check_normalization(p);
      this->check_R0(p);
      
      this->par_= p; 
     }
    void Pandemic::introduce_vacc(const double& v){
    
    if (this->get_Parameters().vax != 0.)
     throw std::runtime_error{ "You can't introduce the vaccine more than once"};//si può introdurre il vaccino solo una volta
  
    if(( v < 0. || v > 1. ) )
       throw  std::runtime_error{"The values of the parameters must be inside the interval [0,1] !"};
    this->get_Parameters().vax = v;
   }

    void  Pandemic::set_initial_condition(const People& start)
    {
       
       if (this->get_evolution().empty()){
       
          ///////////////////////Controll on initial data/////////////////////////////////////
        //////////////Controll on Susceptible and Infected not vaccinated////////////////////
                if ( start.I_[0] <= 0 || start.S_[0] <= 0) {
        
                   throw std::runtime_error{"It can't start the evolution without any susceptible or any infected ! "};
                } 
      //////////////Controll on Susceptible and Infected vaccinated////////////////////
                if (start.S_[1] != 0 || start.I_[1] != 0){
          
                  throw std::runtime_error{"At the begining the number of vaccinated people must be null! "};
                }
      ////////////Controll on Healed and Dead////////////
                if (start.H_ != 0 || start.D_ != 0){
        
                  throw std::runtime_error{"It doesn't make sense start with some healed or dead people"};
                }

      ///////////////////Everything is fine, so it can be set the initial condition: it's left the final check///////////////
      int tot = sum(transform_arr<int,6>(start));
        if ( tot <= this->get_number_population())
        {
        this->add_data(start);
        this->get_evolution().back().S_[0]+= (this->get_number_population()-tot);
       
        } else
         {
          throw std::runtime_error{"The inserted values must be coherent with the number of the population !"};
         }
        
       
       
       } else 
        {
         throw std::runtime_error{"This simulation has already an initial condition, please start another simulation"};
        } 
       }  
   ////////////Getters//////////////////
   Parameters&  Pandemic::get_Parameters() { 
      return this->par_;
     }
   People&  Pandemic::get_situation_day( const int& i){
      
      if ( i <= 0 || static_cast<std::vector<People>::size_type>(i) > this->population_.size()) {
          
           if (i == 0)
        {
               throw std::runtime_error{"The simulation starts from day one!"};
        }  else 
        {
         throw std::out_of_range{"Invalid day number!"}; 
        }     
             
      } 
      
      return this->get_evolution()[i -1];
     }
    
    int  Pandemic::get_days(){
      return this->population_.size();
    }

      int  Pandemic::get_number_population() const
    { 
      return this->N_;
    }
 
  std::vector<People>&  Pandemic::get_evolution()
    {
        return this->population_;
    }
   // Struct Parameters
    ////////////Checking///////////////
    void Pandemic::check_normalization( Parameters& p)
    {
    double com = p.gamma[0] + p.omega[0];

    if (com > 1){
      p.omega[0] = p.beta[0] - p.gamma[0] - 0.1;

      std::cout<< "The probablities of healing and dying must respect the normalization property, don't worry it has been fixed"<< "\n\n";
     }
    }

     bool Pandemic::check_R0(Parameters& p){
      if (this->calculate_R0(p) >1){
         return true;
      } else {
     
        throw std::runtime_error{"The simulation with the vaccine can't start if the critical threshold is minor than or equal to one! "};
      }
    }
  
   
   ////////////General functionalities///////////////
   
      /////////Updates the probabilities for the vaccinated people
     void Pandemic::change_after_vacc(){
      
      this->get_Parameters().beta[1] = this->get_Parameters().beta[0]*(1 - efficacy_[0] );
      this->get_Parameters().omega[1] = this->get_Parameters().omega[0]*(1 - efficacy_[1] );
      /////////////////eventuale scarto/////////////////
      double x_0 = 1 - this->get_Parameters().gamma[0] - this->get_Parameters().omega[0];
        //mantengo in prporzione lo scarto delle due probabilità
      this->get_Parameters().gamma[1] = 1 - x_0 - this->get_Parameters().omega[1];
      
      
    }
     /////////////Generates a casual number
    const double& Pandemic::generate(){
      const double& extr = dis(gen);
      return extr;
    }

  /////////////Adds data by adding a new element People to the vector population_  
void  Pandemic::add_data(const People& add){
    assert((sum(transform_arr<int,6>(add))) == (this->get_number_population()));
    this->get_evolution().push_back(add);
  }

    
  /////////////Does a data collection about who decides to get vaccinated, according the probability to get vaccinated  
  bool  Pandemic::is_vaccinated(){
     
      if ((this->generate()) <= this->get_Parameters().vax)
      {
       return true;
      }
      else 
       {
        return false ; 
       }
  }
 
 /////////////Calculates the critical threshold
 double Pandemic::calculate_R0(Parameters& p) {
     
      return  (p.beta[0])/(p.gamma[0] + p.omega[0]);   
       }
  //////////////////Informs when the evolution has finished because there aren't infected people left
 bool Pandemic::terminate(){
      if (sum(this->get_evolution().back().I_) >= 0)
       {
           return false;

       } else{
           return true;
    }
  
    }
  /////////////////////Distructor///////////////////////
    Pandemic::~Pandemic() = default;