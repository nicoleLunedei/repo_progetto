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


 




/*template<typename T> void push_back(std::vector<T>& v, std::vector<std::vector<T>>& V );//il primo argomento è l'elemento nuovo, il secondo il contenitore a cui viene aggiunto
template<typename T> void push_back(std::vector<T>& v, std::vector<std::vector<T>>& V ){
            //allora io potrei accede a V finchè non finisce il vettore elemento v
      if (v.empty())
      throw std::runtime_error {"The vector you want to add is empty"};
    
      if (V.empty()){
        V.push_back(v);// qua non dovrebbe darmi problemi perchè il vettore è vuoto, perchè 
      }
      else {
        for(T& w: v){
          V.push_back(w);
        }
        
      }

    }*/
bool is_perfect_square(int num){
  int root = static_cast<int> (std::sqrt(num));
  return (root * root == num);
}




enum Person {Susceptible = 0, Infected, Healed, Dead, Susceptible_v, Infected_v};

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
   
    Agent(std::vector<People>& population,  Parameters& par,const int& N, const Matrix<Person>& M);///
    Agent();///
    Matrix<Person>& get_matrix();//
    void draw_matrix(People& begin);//
    int get_side();///
    Person& show_cell(int r, int c);///
    int infected_neighbours( int r, int c);///
    void sorting();
    void change_state();
    void data_collection(People& collection);
    void evolve(People& follow) override; 
    //void evolve_with_vax(People& follow)override;
    void Print();//deve restituire tutta la matrice
    ~Agent();
};
#endif

