
#include <cmath>
#include <cassert>
#ifndef EQUATION_HPP
#define EQUATION_HPP
#include "pandemic.hpp"


class Equation : public Pandemic
{
private:
    std::mt19937 gen;  // Generatore di numeri casuali
    std::uniform_real_distribution<> dis; 
    std::vector<People> population_;
    Parameters par_;
    int N_;  //N
    static std::array<double,2> intersec_; 
     //std::vector<std::array<int,4>> counting_; //mezzo di visualizzazione dell'andamento

public:
    ////////////////////////Constructors////////////////////////////

    ////////Parametric////////////// 
    Equation( std::vector<People>& population,  Parameters& par, const int& N);
    ///////Default////////////
    Equation();
  
   
   ////////////Data collection about the vaccine///////////////
    void sorting();
    ////////////////////////////////////Evolving functionalities////////////////////////////
     std::array<double,6> update_situation(int index, People const& next);
    const People fix(std::array<double,6> next);
    void evolve();
    void evolve_vaccine();

    ///////////////////////////////////////////Displaying Functionalities///////////////////////////
         ////////////////////////Summing data////////////////////
    std::array<int,4> calculate(const int& t);
         ////////////////////Printing on terminal///////////////
    void Print(const int& d);
////////////Distructor////////////
    ~Equation();
};

#endif