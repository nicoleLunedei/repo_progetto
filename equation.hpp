
#include <cmath>
#include <cassert>
#ifndef EQUATION_HPP
#define EQUATION_HPP
#include "pandemic.hpp"

//template<typename T,typename C, std::size_t N> const std::array<T,N> convert(const std::array<C,N>& c);
//template<typename T, std::size_t N>  const std::array<T,N>& transform_arr(const People& p);
//template<typename T, std::size_t N>  const People& trasform_people(const std::array<T,N>& t);





class Equation : public Pandemic
{
private:
    std::mt19937 gen;  // Generatore di numeri casuali
    std::uniform_real_distribution<> dis; 
    std::vector<People> population_;
    Parameters par_;
    int N_;  //N
    static std::array<double,2> intersec_; 
     std::vector<std::array<int,4>> counting_; //mezzo di visualizzazione dell'andamento
    //sarebbe utile usare l'alias per std::vector<std::array<int,4>> 

public:
   
    Equation( std::vector<People>& population,  Parameters& par, const int& N, std::vector<std::array<int,4>>& counting);
    Equation();
    std::array<int,4> get_counting(const int& n);
    std::vector<std::array<int,4>> get_countdays();
    void add_count(const std::array<int,4>& add);
    std::array<int,4> calculate();
    std::array<double,6> update_situation(int index, People const& next);
    const People fix(std::array<double,6> next);
    void sorting();//test
    void evolve();
    void evolve_vaccine();
    void Print(const int& d);
    //double& calculate_R0(); te devi andare in pandemic
    ~Equation();
};

#endif