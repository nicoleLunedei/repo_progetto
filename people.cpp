#include "people.hpp"

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





