#include "matrix.hpp"
#include "agent.hpp"

bool is_perfect_square(int num){  
  int root = static_cast<int> (std::sqrt(num));
  return (root * root == num);
}

////////////////////Binomial Distribution////////////////////////
int fatt_( int& n){
   if (n < 0){ 
    throw std::runtime_error{"The integer number can't be negative "};
}
   
    int n_fatt = 1;

    for(; n > 0;n--){
        n_fatt *= n;
    }
    return n_fatt;
}

double prob_binomial( int& n, int& k, double& p){
    if (n < k)
    throw std::runtime_error{"Error!k can't be higher the n"};

      int diff = n-k;
      double p_bin =(fatt_(n))/(fatt_(k)* fatt_(diff))*(std::pow(p,k)*(std::pow((1-p),diff)));
      return p_bin;
}
/////////////////////////sum in Person contest/////////////////////////////
int sum_person(std::vector<Person>& pers){
  std::vector<int> pers_n;
 for(Person& el: pers){
    pers_n.push_back(static_cast<int>(el));
 }
 return sum(pers_n);
}
/////////////////////CLASS AGENT///////////////////////////////////////////
Agent::Agent(std::vector<People>& population,  Parameters& par,const int& N): Pandemic(population,par,N), M_(sqrt(N)){
  
      if (!is_perfect_square(this->get_number_population())) 
      throw std::runtime_error{"The number of the population must a perfect square"};
    }
Agent::Agent(): Pandemic(),M_(){
   //utilizzo i costruttori di default di Pandemic e Matrix che sono entrambi consistenti con il lato=80
  //inizio a costruire le righe 
   M_.inside_matrix([this](Person& cell, int r, int c){//[] roba che serve soltanto alla lambada function, ()argomenti che ho messo nell'action() in inside_matrix

         if (r == (static_cast<int>(M_.M.size())/2) && c == static_cast<int>(M_.M.size()/2) ){
           cell= Person::Infected;
         } else {
          cell = Person::Susceptible;
         }
    // qua dovrebbe avermi creato la pandemia e la matrice per rappresentarne gli stati
     });
   }
     
void Agent::draw_matrix(People& begin){
  //fare un controllo che non ci sia già la situazione iniziale, esattamente come in set_initial condition
  if (this->get_matrix().sum() !=0){
    throw std::runtime_error{"You already set the initial condition"};
  }
  //prende gli infetti da pandemic e riempie la matrice finchè non è stata settata la situzione iniziale 
  this->set_initial_condition(begin);
  
  int i = 0;
  while (i < sum(this->get_condition_day(1).I_)){//ciclo che mi assicura di mettere tutti gli infetti richiesti
    //estrazione delle coordinate nella matrice 
    int rr = std::floor(this->generate() * this->get_side());
    int cc = std::floor(this->generate() * this->get_side());
     
      if (this->show_cell(rr,cc) == Person::Infected)
         {
           while (sum_person(this->get_matrix().M[rr]) == this->get_side()){//fisso la riga, perchè controllo quale riga ha la somma diversa dal lato della griglia
               rr++;
           }
           while(this->show_cell(rr,cc) == Person::Infected ){//fisso la colonna 
            cc++;
           }
          this->show_cell(rr,cc) = Person::Infected;
          i++;
         } else {
            this->show_cell(rr,cc) = Person::Infected;
            i++;
         }
    
       } 
  }  
     
  

    


Matrix<Person>& Agent::get_matrix() {
  return this->M_;
}
int Agent::get_side() const{
  return std::sqrt(this->get_number_population());
}
// toroidal structure viewing
Person& Agent::show_cell(int r, int c) {
  //controllo che la matrice sia vuota oppure no 
  if(this->get_matrix().M.empty())
   throw std::runtime_error{"The Matrix is empty!"};

  if ((r < 0 || r > this->get_side()) || (c < 0 || c > this->get_side()) )
  throw std::runtime_error{"Out of range!"};


  int rr = (r + this->get_side()) % this->get_side();
  int cc= (c + this->get_side() ) % this->get_side();

   return this->get_matrix().M[rr][cc];
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
//Smistamento 
void Agent::sorting(){
    int check = this->get_evolution().back().S_[0];
    this->get_matrix().each_cell([this](Person& cell ){
        if (cell == Person::Susceptible){
           if (this->is_vaccinated()){
             cell = Person::Susceptible_v;
             (this->get_evolution().back().S_[1])++;
             (this->get_evolution().back().S_[0])--;
           } 
        }
    });
    assert((this->get_evolution().back().S_[0])+(this->get_evolution().back().S_[1]) == check );
}

void Agent::change_state(){ //l'indice i mi permetterà di distinguere l'evoluzione da evolve e evolve vaccine
  this->get_matrix().inside_matrix([this](Person& cell, int r, int c ){{//per ogni elemento viene fatto un controllo della cella 

int inf = 0;
int k = 1;
double p_ = 0.0; 
const double& extra1 = this->generate();
const double& extra2 = this->generate();
     
     switch (cell)
  { 
    case Person::Susceptible:
  /* genera il numero casualmente e confrontalo con la probabilià che d'infezione  */
  inf = this->infected_neighbours(r,c);
  //calcolo della probabilità con un numero specifico di contatti infetti, con utilizzo della distribuzione di probabilità binomiale
   p_ = prob_binomial(inf, k , this->get_Parameters().beta[0]);

  
  if (extra1 < p_){
    cell = Person::Infected;
   
  }
   break;
     case Person::Susceptible_v:
  /* genera il numero casualmente e confrontalo con la probabilià che d'infezione  */
   inf = this->infected_neighbours(r,c);
  //calcolo della probabilità con un numero specifico di contatti infetti, con utilizzo della distribuzione di probabilità binomiale
   p_ = prob_binomial(inf, k , this->get_Parameters().beta[1]);

  if (extra1 < p_){
    cell = Person::Infected_v;
 
  }  
   break;
  case Person::Infected:

 

  if (extra2 < (this->get_Parameters().gamma[0])+(this->get_Parameters().omega[0])){
    if (extra2 < this->get_Parameters().gamma[0]){
        cell = Person::Healed;
        //Aggiornamento di population_
    (this->get_evolution().back().I_[0])--;
    (this->get_evolution().back().H_)++;
    } else {
        cell = Person::Dead;
     
    }
  } else {
    //Rimane infected
  }
    break;
 case Person::Infected_v:



  if (extra2 < (this->get_Parameters().gamma[1])+(this->get_Parameters().omega[1])){
    if (extra2 < this->get_Parameters().gamma[1]){
        cell = Person::Healed;
       
    } else {
        cell = Person::Dead;
   
    }
  } else {
    //Rimane infected
  }
    break;
  case Person::Healed :
    //Non c'è un cambio di stato della cella 
    //La cella rimane Healed
  case Person::Dead :
  //Non c'è un cambio di stato della cella 
    //La cella rimane Morta
    break;
  }
}});
//
  
}

void Agent::data_collection(People& collection){
this-> get_matrix().each_cell([this, &collection](Person& cell){
    switch (cell)
    {
    case Person::Susceptible:
       
       collection.S_[0]++;        
        break;
    case Person::Susceptible_v:
     collection.S_[1]++; 
        break;
    case Person::Infected:
       collection.I_[0]++; 
        break;    
    case Person::Infected_v:
       collection.I_[1]++; 
        break;    
    case Person::Healed:
       collection.H_++; 
        break; 
    case Person::Dead:
       collection.D_++; 
        break;            
    }
});

assert(sum(transform_arr<int,6>(collection)) == this->get_number_population());

this->get_evolution().push_back(collection);
}

 
void Agent::evolve(People& follow){//qua ci sarebbe d verificare che la dimensione di populationè aumentata di 1 e soparttutto che la matrice precedemte è diversa a quella di prima 
  //Far evolvere la matrice 
  this->change_state();
  //e registrare i nuovi dati giornalmente in population
  this->data_collection(follow);
}


 Agent::~Agent() = default;
