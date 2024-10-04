
#include "agent.hpp"

/////////////////////////STRUCT MATRIX////////////////////////////////
template<typename T> 
Matrix<T>::Matrix(int l): side{l}{//Null Matrix dinamica
   for (int r = 0; r < l ; r++){
    for (int c = 0; c < l ; c++){
       
       M_[r].push_back(0);
    }
   }
  }
  /// Default: Null Matrix
  Matrix(): side{80}{
    for (int r = 0; r < 80 ; r++){
    for (int c = 0; c < 80 ; c++){
       
       M_[r].push_back(0);//ricorda M_[r] è un vettore
    }
   }
  }
  
  /// Copy
  Matrix(const Matrix& M_other){
  if (this->side != M_other.side) {
    throw std::runtime_error{"The two matrices don't have the same dimension (n x n) or they aren't squared"}
  }
  for (int r = 0; r < this->side ; r++){
    for (int c = 0; c < this->side ; c++){
       
       this->M_[r][c] = M_other.M_[r][c];
    }
   }
  }
  template<typename Func>
  void inside_matrix(Func action){//questa è una funzione che mi permette di fare un'azione e sa già di e come dover entrare nella matrice
    for (int r = 0; r < this->side ; r++){
    for (int c = 0; c < this->side ; c++){
       
        action(M_[r][c],r,c);
    }
   }
  }

  //pensa ad una funzione che permatte adi navigare attarverso le righe 

  int& sum(){
    int tot = 0;
    this->inside_matrix([this, tot](int& cell, int r, int c){
    tot+= cell;
    });
     return tot;
  }
  ///////////////////overloading dell'operator==///////////////////////////////////
  friend bool oparator==(Matrix<T>& left, Matrix<T> right)[

    return left.inside_matrix([](T& cell, int r,int c){ cell == right.M[r][c];});
  ]
  


 











/////////////////////CLASS AGENT///////////////////////////////////////////
const int fatt_( int& n){
   if (n < 0)
    throw std::runtime_error{"The integer number can't be negative "};
    int n_fatt = 0;
    for(n; n > 0;n--){
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

Agent::Agent(std::vector<People>& population,  Parameters& par,const int& N, const Matrix<Person>& M): Pandemic(population,par,N), M_{M}{
      if (!M.M.empty()){
        throw std::runtime_error{"The Matrix must be empty"};
      }
     //crea una matrice nulla 
      if (!is_perfect_square(this->get_number_population())) 
      throw std::runtime_error{"The number of the population must a perfect square "};
    }
Agent::Agent(): Pandemic(),M_(){

  //ricavo il lato che deve avere la griglia 
  M_.side = sqrt(this->get_number_population());
  //inizio a costruire le righe 
   M_.inside_matrix([this](Person& cell, int r, int c){//[] roba che serve soltanto alla lambada function, ()argomenti che ho messo nell'action() in inside_matrix

         if (r == ((M_.side)/2) && c == (M_.side/2) ){
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
    int rr = std::floor(dis(gen) * this->get_side());
    int cc = std::floor(dis(gen) * this->get_side());
     
      if (this->show_cell(rr,cc) == Person::Infected)
         {
           while (sum(this->get_matrix().M[rr]) == this->get_side()){//fisso la riga 
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
int Agent::get_side(){
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

   this->get_matrix().M[rr][cc];
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
    this->get_matrix().inside_matrix([this](Person& cell, int r, int c ){
        if (cell == Person::Susceptible){
           if (this->is_vaccinated()){
             cell == Person::Susceptible_v;
             (this->get_evolution().back().S_[1])++;
             (this->get_evolution().back().S_[0])--;
           } 
        }
    });
    assert((this->get_evolution().back().S_[0])+(this->get_evolution().back().S_[1]) == check );
}

void Agent::change_state(){ //l'indice i mi permetterà di distinguere l'evoluzione da evolve e evolve vaccine
  this->get_matrix().inside_matrix([this](Person& cell, int r, int c ){{//per ogni elemento viene fatto un controllo della cella 
     
     switch (cell)
  { 
    case Person::Susceptible:
  /* genera il numero casualmente e confrontalo con la probabilià che d'infezione  */
  int  inf = this->infected_neighbours(r,c);
  int k = 1;
  //calcolo della probabilità con un numero specifico di contatti infetti, con utilizzo della distribuzione di probabilità binomiale
  const double& p_ = prob_binomial(inf, k , this->get_Parameters().beta[0]);

  const double& extra1 = dis(gen);
  if (extra1 < p_){
    cell = Person::Infected;
   
  }
   break;
     case Person::Susceptible_v:
  /* genera il numero casualmente e confrontalo con la probabilià che d'infezione  */
  int  inf = this->infected_neighbours(r,c);
  int k = 1;
  //calcolo della probabilità con un numero specifico di contatti infetti, con utilizzo della distribuzione di probabilità binomiale
  const double& p_ = prob_binomial(inf, k , this->get_Parameters().beta[1]);

  const double& extra1 = dis(gen);
  if (extra1 < p_){
    cell = Person::Infected_v;
 
  }  
   break;
  case Person::Infected:

  const double& extra2 = dis(gen);

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

  const double& extra2 = dis(gen);

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
  default:
    break;
  }
}});
//
  
}

void Agent::data_collection(People& collection){
this-> get_matrix().inside_matrix([this, &collection](Person& cell, int r, int c){
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



