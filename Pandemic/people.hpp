#ifndef PEOPLE_HPP
#define PEOPLE_HPP

#include "vaccine.hpp"

struct People {
  Vaccine<int> S_;
  Vaccine<int> I_;
  int H_;
  int D_;
  // Parametric Constructor
  People(const Vaccine<int>& s, const Vaccine<int>& i, int h,
         int d);
  // Default Constructor
  People();
  // Copy Constructor
  //People(const People& other);

  ////////////////////// Over loading /////////////////////
  //People& operator=(const People& value);

  friend bool operator==(const People& left, const People& right);

  friend std::ostream& operator<<(std::ostream& os, const People& p_out);

  // Operator>>
  friend std::istream& operator>>(
      std::istream& is,
      People& p_in); 
                      // Destructor
  ~People();
};
#endif