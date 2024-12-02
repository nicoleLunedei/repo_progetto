

#include "parameters.hpp"
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
