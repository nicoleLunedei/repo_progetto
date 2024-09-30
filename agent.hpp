//costruzione della classe agent per automa cellulare della diffusione pandemica 
//concetto di ereditarietà o polimorfismo, questo è da definire prima capire cosa è più adatto, 
//struttura toroidale: definizione dell'operatore == (ricorda: la funzione mod )
#include <iostream>
#include <vector>
#include <cmath>
#include "pandemic.hpp"
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




enum Person {Susceptible = 0, Infected, Healed, Dead};
using Matrix_P = std::vector<std::vector<Person>>  ;
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
    Matrix_P M_;

public:
   
    Agent(std::vector<People>& population,  Parameters& par,const int& N, const Matrix_P& M);///
    Agent();///
    Matrix_P& get_matrix();//
    void draw_matrix(People& begin);//
    int get_side();///
    Person& show_cell(int r, int c);///
    int infected_neighbours( int r, int c);///
    void change_state(int r, int c, int i,Matrix_P& next);
    void evolve(People& follow) override; 
    void evolve_with_vax(People& follow)override;
    void Print();//deve restituire tutta la matrice
    ~Agent();
};
Agent::Agent(std::vector<People>& population,  Parameters& par,const int& N, const Matrix_P& M): Pandemic(population,par,N), M_{M}{
      if (!M.empty()){
        throw std::runtime_error{"The Matrix must be empty"};
      }

      if (!is_perfect_square(this->get_number_population())) 
      throw std::runtime_error{"The number of the population must a perfect square "};
    }
Agent::Agent(): Pandemic(),M_{}{
  //ricavo il lato che deve avere la griglia 
  int l = sqrt(this->get_number_population());//devi cambiare L'N_ in pandemic
  //creo un oggetto vettore 
  std::vector<Person> row;
  //inizio a costruire le righe 
      for (int r= 0; r < l ; r++ )
  {
    //inizio a costruire le colonne 
    for (int c = 0; c < l ; c++ )
     {
      Person s ;
         if (r == (l/2) && c == (l/2) ){
           s = Person::Infected;
         } else {
           s = Person::Susceptible;
         }
       row.push_back(s);
        
     }
    M_.push_back(row);

  }
}

void Agent::draw_matrix(People& begin){
  //prende gli infetti da pandemic e riempie la matrice fincheè non è stata settata la situzione iniziale 
  this->set_initial_condition(begin);
  for(int r = 0 ; r < this->get_side(); r++){// Infetti
       int i=0;
        for(int c = 0; c < this->get_side(); c++){
           while (i <= this->get_condition_day(1).I_[0])
         {
           
         }
        }
          
        
  }
  for(){//suscettibili
    
  }
}
Matrix_P& Agent::get_matrix() {
  return this->M_;
}
int Agent::get_side(){
  return std::sqrt(this->get_number_population());
}
// toroidal structure viewing
Person& Agent::show_cell(int r, int c) {
  //controllo che la matrice sia vuota oppure no 
  if(this->get_matrix().empty())
   throw std::runtime_error{"The Matrix is empty!"};

  if ((r < 0 || r > this->get_side()) || (c < 0 || c > this->get_side()) )
  throw std::runtime_error{"Out of range!"};


  int rr = (r + this->get_side()) % this->get_side();
  int cc= (c + this->get_side() ) % this->get_side();

   this->get_matrix()[rr][cc];
} 

//Check infected number next to the cell
int Agent::infected_neighbours( int r, int c) {

  int contacts = 0;
  for (int i : {-1, 0, 1})
  {
    for (int j : {-1, 0, 1})
    {
      if (this->Agent::show_cell(r+i, c+j) == Person::Infected) {
        contacts++;
      }
    }
  }

  return contacts;
}
void Agent::change_state(int r, int c, int i, Matrix_P& next){
  switch (this->show_cell(r,c))
  { 
    case Person::Susceptible:
  /* genera il numero casualmente e confrontalo con la probabilià che d'infezione  */
   double prob = this->get_Parameters().beta[i] * ; // devicapire come aumenta la probabilità d'infezione considerando anche il numero degli infetti 
  if (this->dis(this->gen) <= )
  case Person::Infected:
    /* genera il  */
    break;
 
  case Person::Healed :
  case Person::Dead :
  default:
    break;
  }
}
void

#endif
/*






//Setting initial infected
Pandemic Pandemic::start(Pandemic& clear, int infected) {

  int l=clear.get_Side();
  Pandemic set(l, infected);
  
  std::default_random_engine eng{std::random_device{}()};
  std::uniform_int_distribution<int> dist{0, l - 1};

  for (int j=0; j < infected; j++) {

    int k = dist(eng);
    int h = dist(eng);
    
    while (set.Reading_cell(k,h) == Person::Infected) {
      k+=2;
      h+=2;
    }
    set.Writing_cell(k,h) = Person::Infected;
    
  }

  return set;
}






//Creating toroidal structure 
Person const& Pandemic::Reading_cell(int r, int c) {

  int rr = (r + Side_) % Side_;
  int cc= (c + Side_ ) % Side_;
  int index = (rr* Side_) + cc;

  return Grid_[index];
} 


Person& Pandemic::Writing_cell(int r, int c){

  int rr = (r + Side_ ) % Side_;
  int cc= (c + Side_ ) % Side_;
  int index = (rr* Side_) + cc;

  return Grid_[index];   
}



//Check infected number next to the cell
int Pandemic::infected_neighbours(Pandemic& pandemic, int r, int c) {

  int contacts = 0;
  for (int i : {-1, 0, 1})
  {
    for (int j : {-1, 0, 1})
    {
      if (pandemic.Reading_cell(r+i, c+j) == Person::Infected) {
        contacts++;
      }
    }
  }

  return contacts;
}


//Day evolution
Pandemic Pandemic::evolve(Pandemic& now, Parameters ps) {
  
  //next=now
  int l = now.get_Side();
  int f = now.get_I();
  Pandemic next(l, f);
  
  std::default_random_engine eng{std::random_device{}()};
  std::uniform_real_distribution <float> dis(0.0, 1.0); 

  for (int r = 0 ; r < l ; r++ ) {

    for (int c = 0 ; c < l ; c++) {

      if (now.Reading_cell(r,c) == Person::Susceptible ) {

        float p1 = dis(eng);
        double b = ps.get_Beta()*now.infected_neighbours(now, r, c); 
           
        if (ps.get_Alfa() != 0 && p1 <= ps.get_Alfa()) {

          next.Writing_cell(r,c) = Person::Recovered; 
          next.R_ += 1;
          next.S_ -= 1;

        } else  if ( p1 <= (ps.get_Alfa() + b)) {

          next.Writing_cell(r,c) = Person::Infected;
          next.I_+=1; 
          next.S_-=1; 
              
        } else {
          //It doesn't change states
        }

      } else if (now.Reading_cell(r,c) == Person::Infected) {                 

        double p2 = dis(eng);

        if (p2<=(ps.get_Gamma())) {

          next.Writing_cell(r,c) = Person::Recovered;
          next.R_+=1;
          next.I_-=1; 

        } else if ( p2 <= (ps.get_Gamma()+ps.get_Mu())) {

          next.Writing_cell(r,c) = Person::Dead; 
          next.I_-=1;
          next.D_+=1;

        } else { 
          //Here it doesn't change state
        }
      }
    }
  }

  return next;
}
*/