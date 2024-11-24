//costruzione della classe agent per automa cellulare della diffusione pandemica 
//concetto di ereditarietà o polimorfismo, questo è da definire prima capire cosa è più adatto, 
//struttura toroidale: definizione dell'operatore == (ricorda: la funzione mod )
#include <iostream>
#include <vector>
#include <cmath>
#include "pandemic.hpp"
#include "matrix.hpp"
#ifndef AGENT_HPP
#define AGENT_HPP

enum Person {Susceptible = 0, Infected, Healed, Dead, Susceptible_v, Infected_v};


bool is_perfect_square(int num);


/////////////////////////sum in Person contest/////////////////////////////
int sum_person(std::vector<Person>& pers);



class Agent : public Pandemic
{
private:
    std::mt19937 gen;  // Generatore di numeri casuali
    std::uniform_real_distribution<> dis; 
    std::vector<People> population_;
    Parameters par_;
    int N_;  //N
    static std::array<double,2> intersec_; 
    //oggetto griglia bidimensionale di oggetti person
    Matrix<Person> M_;

public:
   
    Agent(std::vector<People>& population,  Parameters& par,const int& N);///
    Agent();///
    Matrix<Person>& get_matrix();//
    void draw_matrix(People& begin);//
    int get_side()const ;///
    Person& show_cell(int r, int c);///
    bool throwing_dices(double& dice);
    int infected_neighbours( int r, int c);///
    void sorting();
    void change_state();
    void data_collection(People& collection);
    void evolve(People& follow) ; 

    ~Agent();
};
#endif

