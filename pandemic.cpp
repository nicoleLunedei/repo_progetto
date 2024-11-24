#include <vector>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <random>
#include <array>


#include "pandemic.hpp"


//l'attributi static vanno definiti nel file d'implementazione 
std::array<double,2> Pandemic::efficacy_{0.71,0.65};// [0]= con infezione, [1] = con morte tendo conto anche di conseguenze mediche che il visru potrebbe aver innescato
//Struct People
    //Parametric Constructor
People::People( const std::array<int,2>& s,const std::array<int,2>& i , const int  h, const int& d  ): S_{s},I_{i},H_{h}, D_{d}{}
    //Default Constructor
People::People(){
  S_[0] = 2499;
  S_[1] = 0;
  I_[0] = 1;
  I_[1] = 0;
  H_ = 0 ;
  D_ = 0 ;
  
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
    os << "Suscepttible not vaccinated : " << p_out.S_[0] << "||  Suscepttible vaccinated : " <<p_out.S_[1] << "\n\n";
    os << "Infected not vaccinated: " << p_out.I_[0] <<"|| Infected not vaccinated: "<< p_out.I_[1] << "\n\n";
    os << " Healed : " << p_out.H_ << "\n\n";
    os << "Dead : " << p_out.D_ << "\n\n";
   
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
Parameters::Parameters(): beta{0.6,0.},gamma{0.2,0.},omega{0.35,0.}, vax{0.}{}
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
    std::ostream& operator<<(std::ostream& os, const Parameters& p_out){
      os<< p_out.beta[0] <<"||"<<p_out.beta[1]<<'\n';
      os<< p_out.gamma[0] <<"||"<<p_out.gamma[1]<<'\n';
      os<< p_out.omega[0] <<"||"<<p_out.omega[1]<<'\n';
      os<< p_out.vax<<'\n';
      
      return os;

    }
        //Operator>>
     /*std::istream& operator>>(std::istream& is, Parameters& p_in ){}*/
   Parameters::~Parameters() = default ; 







//Class pandemic
 //Costruttore Parametrico

    Pandemic::Pandemic( std::vector<People>& population,  Parameters& par,const int& N) :  gen(std::random_device{}()), dis(0.0, 1.0), population_{population}, par_(par), N_{N} {
    
      /////////////////////Controllo delle probabilità////////////////////////////////
     if ((par.beta[0] < 0. || par.beta[0] > 1. ) || (par.gamma[0] < 0. || par.gamma[0] > 1. ) ||  (par.omega[0]< 0. || par.omega[0] > 1.) || (  par.vax<0 || par.vax > 1. )  ) 
       throw  std::runtime_error{"The values of the parameters must be inside the interval [0,1] !"};

     if (par.beta[1] != 0 || par.gamma[1] != 0 || par.omega[1] != 0  || par.vax != 0 ) // all'inizione le probabilità modificate devono esssere 0
       throw  std::runtime_error{"The value of the parameters in case of vaccination must be 0 !"};

     this->check_normalization(par);

     this->check_R0(par);

      ////////////////////////////Controlli sugli elementi di population////////////////////////////////////// 
     assert(population.empty());
    }

    //Costruttore default
     Pandemic::Pandemic(): gen(std::random_device{}()), dis(0.0, 1.0),population_{},par_(),N_{2500}{
      // Inizializziamo i parametri con valori predefiniti
      // Inizialmente nessuno vaccinato
      // Inizializziamo una popolazione con un unico individuo infetto
      
    } 
      
 
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Struct Parameters
   // check dei parametri
    void Pandemic::check_normalization( Parameters& p)
    {
    double com = p.gamma[0] + p.omega[0];

    if (com > 1){
      p.omega[0] = p.beta[0] - p.gamma[0] - 0.1;

      std::cout<< "The probablities of healing and dying must respect the normalization property, don't worry it has been fixed"<< "\n\n";
     }
    }
   

   void  Pandemic::set_Parameters(Parameters& p){//devi mettere i controlli anche qua
     if ((p.beta[0] < 0. || p.beta[0] > 1. ) || (p.gamma[0] < 0. || p.gamma[0] > 1. ) ||  (p.omega[0]< 0. || p.omega[0] > 1.) || (  p.vax<0 || p.vax > 1. )  ) 
       throw  std::runtime_error{"The values of the parameters must be inside the interval [0,1] !"};
     
     if (p.beta[1] != 0 || p.gamma[1] != 0 || p.omega[1] != 0  || p.vax != 0 ) // all'inizione le probabilità modificate devono esssere 0
       throw  std::runtime_error{"The value of the parameters in case of vaccination must be 0 !"};
     
      this->check_normalization(p);
      this->check_R0(p);
      
      this->par_= p; 
     }
     void Pandemic::change_after_vacc(){
     
      this->get_Parameters().beta[1] = this->get_Parameters().beta[0]*(1 - efficacy_[0] );
      this->get_Parameters().omega[1] = this->get_Parameters().omega[0]*(1 - efficacy_[1] );
      /////////////////eventuale scarto/////////////////
      double x_0 = 1 - this->get_Parameters().gamma[0] - this->get_Parameters().omega[0];
        //mantengo in prporzione lo scarto delle due probabilità
      this->get_Parameters().gamma[1] = 1 - x_0 - this->get_Parameters().omega[1];
      
      
    }
    const double& Pandemic::generate(){
      const double& extr = dis(gen);
      return extr;
    }
   void Pandemic::introduce_vacc(const double& v){
    
    if (this->get_Parameters().vax != 0.)
     throw std::runtime_error{ "You can't introduce the vaccine more than once"};//si può introdurre il vaccino solo una volta
  
    if(( v < 0. || v > 1. ) )
       throw  std::runtime_error{"The values of the parameters must be inside the interval [0,1] !"};
    this->get_Parameters().vax = v;
   }
   Parameters&  Pandemic::get_Parameters() { //perchè è di lettura; mettere il const prima del tipo del metodo indica che il valore restituito non può essere modificato ; se invece il const è messo dopo la di chisrazione del metodi significa che questo non può modificare lo stato dell'oggetto su cui è chiamato
      return this->par_;
     }
     // Struct People 
     //Hai deciso e non cambiare più: set_initial_condition ti fa impostare la situazione iniziale, te la conrolla e te la sistema, population col costruttore parametrico parte vuoto, con quello di default con un elemento
    bool Pandemic::check_R0(Parameters& p){
      if (this->calculate_R0(p) >1){
         return true;
      } else {
        //return false;
        throw std::runtime_error{"The simulation with the vaccine can't start if the critical threshold is minor than or equal to one! "};
      }
    }
   void  Pandemic::set_initial_condition(const People& start)
    {
        //io devo controllare che population sia vuoto, per aggiungere start
       if (this->get_evolution().empty()){
         //se i vettori dei suscettibili e degli infetti non sono vuoti ha senso controllare i valori
          ///////////////////////Controll on initial data/////////////////////////////////////
        //////////////Controll on Susceptible and Infected not vaccinated////////////////////
                if ( start.I_[0] <= 0 || start.S_[0] <= 0) {
        
                   throw std::runtime_error{"It can't start the evolution without any susceptible or any infected ! "};
                } 
      //////////////Controll on Susceptible and Infected vaccinated////////////////////
                if (start.S_[1] != 0 || start.I_[1] != 0){
          
                  throw std::runtime_error{"At the begining the number of vaccinated people must be null! "};
                }
      ////////////Controll on Healed and Dead////////////
                if (start.H_ != 0 || start.D_ != 0){
        
                  throw std::runtime_error{"It doesn't make sense start with some healed or dead people"};
                }

      ///////////////////Everything is fine, so it can be set the initial condition: it's left the final check///////////////
      int tot = sum(transform_arr<int,6>(start));
        if ( tot <= this->get_number_population()) //coerenza tra N_ e l'oggetto People
        {
        this->add_data(start);
        this->get_evolution().back().S_[0]+= (this->get_number_population()-tot);
       
        } else
         {
          throw std::runtime_error{"The inserted values must be coherent with the number of the population !"};
         }
        
       
       
       } else 
        {
         throw std::runtime_error{"This simulation has already an initial condition, please start another simulation"};
        } 
       }  
   
    
   People&  Pandemic::get_condition_day( const int& i){
      
      if ( i <= 0 || static_cast<std::vector<People>::size_type>(i) > this->population_.size()) {
          
           if (i == 0)
        {
               throw std::runtime_error{"The simulation starts from day one!"};
        }  else 
        {
         throw std::out_of_range{"Invalid day number!"}; // controllo che il gionro entri nell'intervallo di population
        }     
             
      } 
      
      return this->get_evolution()[i -1];
     }
     //in generale ho più mandemie in corso con popolazioni diverse e voglio sapere in particolare 
  
void  Pandemic::add_data(const People& add){
    assert((sum(transform_arr<int,6>(add))) == (this->get_number_population()));
    this->get_evolution().push_back(add);
  }

    
    
  bool  Pandemic::is_vaccinated(){
      // Will be used to obtain a seed for the random number engine; questo mi serve per avere sempre una una generazione di numeri diversa
      // Standard mersenne_twister_engine seeded with rd(); è in generatore di numeri casuali interi che dovranno essere convertiti
      //generazione di un numero casuale che poi verrà confrontato nell'if con la probabilità di vaccinazione; il numero casuale sarà tra 0 e 1  
      if ((this->generate()) <= this->get_Parameters().vax)
      {
       return true;
      }
      else 
       {
        return false ; 
       }
  }
 

  int  Pandemic::get_days(){
      return this->population_.size();
    }
  int  Pandemic::get_number_population() const
    { //potrebbe dare errore, in tal caso vedi se il problema è perchè sto utilizzando un oggetto della classe dentre la definizione della classe stessa
      return this->N_;
  }
  std::vector<People>&  Pandemic::get_evolution()
    {
        return this->population_;
    }

 double Pandemic::calculate_R0(Parameters& p) {
     
      return  (p.beta[0])/(p.gamma[0] + p.omega[0]);   
       }
 bool Pandemic::terminate(){
      if (sum(this->get_evolution().back().I_) >= 0)
       {
         //if the infected are finished 
           return false;

       } else{
           return true;
    }
  
    }
    // Distruttore
    Pandemic::~Pandemic() = default;