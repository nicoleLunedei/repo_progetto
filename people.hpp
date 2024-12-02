#include <vector>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <random>
#include <array>
#include <cassert>


#ifndef PEOPLE_HPP
#define PEOPLE_HPP
struct People
{

 std::array<int, 2> S_; 
 std::array<int, 2> I_; 
 int H_;
 int D_;
//Parametric Constructor
People( const std::array<int,2>& s,const std::array<int,2>& i , const int  h, const int& d  );
//Default Constructor
People();
//Copy Constructor
People(const People& other);

////////////////////// Over loading /////////////////////
 People& operator=( const People& value);

 friend bool operator==( const People& left, const People& right);
 

 friend std::ostream& operator<<(std::ostream& os, const People& p_out);
  
         //Operator>>
 friend std::istream& operator>>(std::istream& is, People& p_in );// qua mettere p_in  con const è un errore perchè >> prende in valora dato in input sall'utente e lo utilizzerà per modificare p_in
     //Destructor
 ~People();

};
#endif