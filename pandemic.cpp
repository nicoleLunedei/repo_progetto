#include <vector>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <random>
#include <array>
#include "pandemic.hpp"
//l'attributi static va definito nel file d'implementazione 
std::array<double,2> Pandemic::intersec_{0.04,0.07};// [0]= con infezione, [1] = con guarigione tendo conto anche di conseguenze mediche che il visru potrebbe aver innescato
//Struct People
    //Parametric Constructor
People::People( const std::array<int,2>& s,const std::array<int,2>& i , const int  h, const int& d  ): S_{s},I_{i},H_{h}, D_{d}{}
    //Default Constructor
People::People(){
  S_[0] = 1;
  S_[1] = 0;
  I_[0] = 1;
  I_[1] = 0;
  H_ = 1 ;
  D_ = 1 ;
  
}
    //Copy Constructor
People::People(const People& other): S_{other.S_}, I_{other.I_}, H_{other.H_}, D_{other.D_}{}

////////////////////// Over loading /////////////////////
 People& People::operator=( const People& value)
 {
    if (this != &value)//qua se non metti & , che prende l'inidrizzo dell'oggetto, non riconosce !=
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
 
 //considera che potresti fare una valutazione paragonando la situazione no vax e vax
 std::ostream& operator<<(std::ostream& os, const People& p_out)
     {
    // write obj to stream
    os << "Suscepttible : " << p_out.S_[0] + p_out.S_[1] << '\n';
    os << "Infected : " << p_out.I_[0] + p_out.I_[1] << '\n';
    os << " Healed : " << p_out.H_ << '\n';
    os << "Dead : " << p_out.D_ << '\n';
   
               return os;
     }
         //Operator>>
 std::istream& operator>>(std::istream& is, People& p_in )// qua mettere p_in  con const è un errore perchè >> prende in valora dato in input sall'utente e lo utilizzerà per modificare p_in
   {
    // read obj from stream
    is >> p_in.S_[0] >> p_in.I_[0] >> p_in.H_ >> p_in.D_;
    if ( !is) {// la condizione !is controlla che non ci siano stati errore nella lettura del flusso di dati in entrata
      is.setstate(std::ios::failbit);
    }
    return is;
    
   }
 People::~People() = default;





//Struct Parameters

Parameters::Parameters(const std::array<double,2>& b, const std::array<double,2>& g, const std::array<double,2>& o, const double& v) : beta{b},gamma{g},omega{o},vax{v} {}// l'assegnazione degli array non li puoi mettere nella lista d'inizializzazione perchè non è supportata la loro assegnazione in blocco
//Default Constructor   
Parameters::Parameters(): beta{0.3,0.},gamma{0.25,0.},omega{0.15,0.}, vax{0.}{}
//Copy Constructor
Parameters::Parameters(const Parameters& other ) {// costruttore di copia che è diverso dal costruttore parametrico; questo è propio per costruire un oggetto a partire da un altro oggetto dello stesso tispo 
        beta[0] = other.beta[0];
        beta[1] = other.beta[1];
        gamma[0] = other.gamma[0];
        gamma[1] = other.gamma[1];
        omega[0] = other.omega[0];
        omega[1] = other.omega[1];
        vax = other.vax;

 }

  //Operator=
Parameters& Parameters::operator=( const Parameters& other){// di fatto si serve mettere il tipo dell'operatore perchè l'assegnazione restituisce un oggetto modificato che nella dichiarazione ha la referenza ma poi renderà forma con l'oggetto vero 
      if (this != &other) { 
      this->beta[0] = other.beta[0];
      this->beta[1] = other.beta[1];
      this->gamma[0] = other.gamma[0];
      this->gamma[1] = other.gamma[1];
      this->omega[0] = other.omega[0];
      this->omega[1] = other.omega[1];
      this->vax = other.vax;
      }
      return *this;
     }

           //Operator ==
bool operator==( const Parameters& left, const Parameters& right){
      return (left.beta[0] == right.beta[0] && left.beta[1] == right.beta[1] && left.gamma[0] == right.gamma[0] && left.gamma[1] == right.gamma[1] && left.omega[0] == right.omega[0] &&left.omega[1] == right.omega[1] && left.vax == right.vax );
    } 
        //Operator<<
    /*std::ostream& operator<<(std::ostream& os, const Parameters& p_out){}
        //Operator>>
     std::istream& operator>>(std::istream& is, Parameters& p_in ){}*/
   Parameters::~Parameters() = default ; 







//Class pandemic
 //Costruttore Parametrico

    Pandemic::Pandemic( std::vector<People>& population,  Parameters& par,const int& N) :  gen(std::random_device{}()), dis(0.0, 1.0), population_{population}, par_{par}, N_{N} {
    
     //if and throw statement=> dei controlli sul primo elemento di population 
     if ((par.beta[0] < 0. || par.beta[0] > 1. ) || (par.gamma[0] < 0. || par.gamma[0] > 1. ) ||  (par.omega[0]< 0. || par.omega[0] > 1.) || (  par.vax<0 || par.vax > 1. )  ) 
       throw  std::runtime_error{"The values of the parameters must be inside the interval [0,1] !"};

     if (par.beta[1] > 0 || par.gamma[1] > 0 || par.omega[1] > 0  || par.vax > 0 ) // all'inizione le probabilità modificate devono esssere 0
       throw  std::runtime_error{"The value of the parameters in case of vaccination must be 0 !"};

    
    }

    //Costruttore default
     Pandemic::Pandemic(): gen(std::random_device{}()), dis(0.0, 1.0),par_({0.5, 0.0},{0.6, 0.0} ,{0.4, 0.0} , 0.0 ),N_{2000000}{
      // Inizializziamo i parametri con valori predefiniti
      // Inizialmente nessuno vaccinato
      // Inizializziamo una popolazione con un unico individuo infetto
        People initial_data;
        initial_data.S_[0] = N_ - 1; // Tutti suscettibili
        initial_data.S_[1] = 0;
        initial_data.I_[0] = 1; // Un unico infetto
        initial_data.I_[1] = 0;
        initial_data.H_ = 0;         // Nessun guarito
        initial_data.D_ = 0;         // Nessun morto

        population_.push_back( initial_data);
      
    } 
      
 
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Struct Parameters
   // check dei parametri?
   void  Pandemic::check_complementarity()
   {
    double com = this->par_.gamma[0] + this->par_.omega[0];
    if (com != 1){
      this->par_.omega[0] = 1 - (this->par_.gamma[0]);
      std::cout<< "The probablities of healing and dying must be complementary, don't worry it has been fixed"<< '\n';
     }
   }
    void Pandemic::check_complementarity( Parameters& p)
    {
    double com = p.gamma[0] + p.omega[0];

    if (com != 1){
      p.omega[0] = 1 - (p.gamma[0]);
      std::cout<< "The probablities of healing and dying must be complementary, don't worry it has been fixed"<< '\n';
     }
    }
   
   void Pandemic::change_after_vacc(){
      this->par_.beta[1]=(intersec_[0])/(this->par_.vax);
      this->par_.omega[1]=(intersec_[1])/(this->par_.vax);
      this->par_.gamma[1] = 1 - this->par_.omega[1];
    }

   void  Pandemic::set_Parameters(Parameters& p){//devi mettere i controlli anche qua
     if ((p.beta[0] < 0. || p.beta[0] > 1. ) || (p.gamma[0] < 0. || p.gamma[0] > 1. ) ||  (p.omega[0]< 0. || p.omega[0] > 1.) || (  p.vax<0 || p.vax > 1. )  ) 
       throw  std::runtime_error{"The values of the parameters must be inside the interval [0,1] !"};

      this->check_complementarity(p);
      this->par_= p; 
     }
   void Pandemic::introduce_vacc(const double& v){
    //metti un controllo
    this->par_.vax = v;
   }
   const Parameters&  Pandemic::get_Parameters() const { //perchè è di lettura; mettere il const prima del tipo del metodo indica che il valore restituito non può essere modificato ; se invece il const è messo dopo la di chisrazione del metodi significa che questo non può modificare lo stato dell'oggetto su cui è chiamato
      return this->par_;
     }
     // Struct People 
   void  Pandemic::set_initial_condition(People& start)
    {
      if (start.S_[1] != 0 || start.I_[1] != 0) //controllo dei vaccinato che devono essere nulli 
       throw std::runtime_error{"At the begining the number of vaccinated people must be null! "};
   ///////////Controllo dei dati iniziali/////////////////////////////////////
      if (start.I_[0] < 1 || start.S_[0] < 1) // almeno devono essere entrambi uguali a 1
      { 
        throw std::runtime_error{"It can't start the evolution without any suscettible or any infected ! "};
        
      }
       else {
         int tot = start.S_[0] + start.I_[0]+ start.H_ + start.D_;
        if ( tot <= N_) //coerenza tra N_ e l'oggetto People
        {
        start.S_[0]+= (N_-tot);
        this->population_.push_back(start);
        } else
         {
          throw std::runtime_error{"The inserted values must be coherent with the number of the population !"};
         }
      if (population_.size() >1){//può capitare che per errore si voglia cambiare la condizione iniziale di una simulazione già iniziata 
        throw std::runtime_error {"This simulation has already the initial condition, please start another simulation"};
      }
        
      }
     //se mette un un vettore con più di un elemento 
     //controllo 
     //per come è strutturato il progetto non ha molto senso mettere più rimossi che suciettibili, non si osserverebbe nulla d'interessante, dal momento che un guarito non si può reinfettare
    }
   People&  Pandemic::get_condition_day( const int& i){
      if (i == 0)
      {
        throw std::runtime_error{"The simulation starts from day 1 !"};
      }
      
      return this-> population_[i-1];
     }
     //in generale ho più mandemie in corso con popolazioni diverse e voglio sapere in particolare 
  
   const People&  Pandemic::get_data(int& d) const{//int d rappresenta il numero del giorno
         if (d < 1 || static_cast<std::vector<People>::size_type>(d) > this->population_.size()) {
              throw std::out_of_range("Invalid day number!"); // controllo che il gionro entri nell'inyervallo di population
         }
         else {
          return this->population_[d - 1];
          } 

    }
void  Pandemic::add_data(const People& add){
    this->population_.push_back(add);
  }

    
    
  bool  Pandemic::is_vaccinated(){
      // Will be used to obtain a seed for the random number engine; questo mi serve per avere sempre una una generazione di numeri diversa
      // Standard mersenne_twister_engine seeded with rd(); è in generatore di numeri casuali interi che dovranno essere convertiti
      //generazione di un numero casuale che poi verrà confrontato nell'if con la probabilità di vaccinazione; il numero casuale sarà tra 0 e 1  
      if (dis(gen) < par_.vax)
      {
       return true;
      }
      else 
       {
        return false ; 
       }
  }
    //smistamento
  void  Pandemic::sorting(){
      int t = this->population_[0].S_[0];// copio il numero di persone a cui chiedere così posso poi modificare i no vax susciettibili
      // ciclo for=> immagina di parlare con tutti gli suscettibilie e di fargli la domanda "sei vaccinato?"
        for (int i = 0; i <=  t ; i++)
           {
             if (this->is_vaccinated() == true)
                {
                    this->population_[0].S_[1]++;
                    this->population_[0].S_[0]--;   
    
                }
    
           }
    
  }
  int  Pandemic::get_days(){
      return this->population_.size();
    }
  int  Pandemic::get_number_population()
    { //potrebbe dare errore, in tal caso vedi se il problema è perchè sto utilizzando un oggetto della classe dentre la definizione della classe stessa
      return this->N_;
  }
  std::vector<People>&  Pandemic::get_evolution()
    {
        return this->population_;
    }
 void Pandemic::evolve(People& ){}
 void Pandemic::evolve_vaccine(People& ){}
 //std::array<int,4>& Pandemic::Print(int& ){};//ricorda che devi printare la seomma degli infetti 
 double Pandemic::calculate_R0() {//test
      double R_0 = (this->par_.gamma[0] +this->par_.omega[0]) /(this->par_.beta[0]);
      return R_0;   
       }
    // Distruttore
    Pandemic::~Pandemic() = default;