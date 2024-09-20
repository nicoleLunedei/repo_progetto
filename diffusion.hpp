 #ifndef DIFFUSION_HPP
 #define DIFFUSION_HPP
 struct People{ //questo è per Equation 
    int S_;
    int I_;
    int R_;
    //int D_;
 };
 //enum People {Suscettible, Infected, Removed, Dead};
 struct Parameters{
    double alfa;
    double beta;
    double omega;
 };
// Dichiarazione e definizione ella classe Diffusion 
 class Diffusion{
   private:
   //People p_;
   Parameters par_;
   int T_;
   int N_;
   public:
    //costruttore default
    Diffusion(){}
    
    //costruttore per controlli e inizializzazione 
    Diffusion (Parameters par_, int T,int N ){
    //controllo con trhow
    }

 //setters 
 void set_par(double a, double b, double o);//poi vedi se mettere i const e le referenze 
 void set_days(int t);//poi vedi se mettere i const e le referenze
 void set_population(int N);//poi vedi se mettere i const e le referenze
 //getters 
 Parameters get_parameters (){ }// vedi come far restituire i parametri estraendoli dallo struct Parameters 
 int get_days(){ return T_;}
 int get_population(){return N_;}
 };
 #endif 
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //costruzione della classe equation based: sistema di equazioni differenziali 
//evoluzione della diffusione con incremento discreto 
//restituire il parametro R0 che ora non ricordi a cosa fa riferimento 

//questa sarà la classe madre delle due quindi la stai pensando come se fosse una fusione primordiale delle due
//per poi specializzarsi nelle figlie agent e equation 
//LEGGI E GUARDA BENE I COMMENTI CHE TI SERVONO PER POI SPEZZARE IL CODICE
#include <vector>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <random>

struct People
{
 int S_[2]; //sarebbe utile usare S e I come due vettori bidimensionali  
 int I_[2]; // // // // //
 int H_;
 int D_;
People(int s_0 ,int s_1, int i_0, int i_1, int h, int d  ): H_{h}, D_{d}{
  S_[0] = s_0;
  S_[1] = s_1;
  I_[0] = i_0;
  I_[1] = i_1;
}
People(){
  S_[0] = 1;
  S_[1] = 0;
  I_[0] = 1;
  I_[1] = 0;
  H_ = 1 ;
  D_ = 1 ;
  
}
////////////////////// Over loading /////////////////////
 People& operator=( const People& value)
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
 friend bool operator==( const People& left, const People& right)
 {
      return (left.S_ == right.S_ && left.I_ == right.I_ && left.I_ == right.I_ && left.H_ == right.H_ && left.D_ == right.D_);
 }
 
 //considera che potresti fare una valutazione paragonando la situazione no vax e vax
 friend std::ostream& operator<<(std::ostream& os, const People& p_out)
     {
    // write obj to stream
    os << "Suscepttible : " << p_out.S_ << '\n';
    os << "Infected : " << p_out.I_ << '\n';
    os << " Healed : " << p_out.H_ << '\n';
    os << "Dead : " << p_out.D_ << '\n';
   
               return os;
     }
         //Operator>>
 friend std::istream& operator>>(std::istream& is, People& p_in )// qua mettere p_in  con const è un errore perchè >> prende in valora dato in input sall'utente e lo utilizzerà per modificare p_in
   {
    // read obj from stream
    is >> p_in.S_[0] >> p_in.I_[0] >> p_in.H_ >> p_in.D_;
    if ( !is) {// la condizione !is controlla che non ci siano stati errore nella lettura del flusso di dati in entrata
      is.setstate(std::ios::failbit);
    return is;
    }
   }


};
struct Parameters
{ // considera se metterli const 
    double beta[2];//d'infezione ; anche beta e gamma potrei metterle come vettori bidimensionali 
    double gamma[2];//guarigione
    double omega[2];//morire
    double vax;// vaccinazione



Parameters(const double b_0, const double b_1, const double g_0, const double g_1, const double o_0, const double o_1, double v) : vax{v} {// l'assegnazione degli array non li puoi mettere nella lista d'inizializzazione perchè non è supportata la loro assegnazione in blocco7
        beta[0] = b_0;
        beta[1] = b_1;
        gamma[0] = g_0;
        gamma[1] = g_1;
        omega[0] = o_0;
        omega[1] = o_1;
    }


  //Operator=
  Parameters& operator=( const Parameters& other){// di fatto si serve mettere il tipo dell'operatore perchè l'assegnazione restituisce un oggetto modificato che nella dichiarazione ha la referenza ma poi renderà forma con l'oggetto vero 
      if (this != &other) { 
      this->beta[0] = other.beta[0];
      this->beta[1] = other.beta[1];
      this->gamma[0] = other.gamma[0];
      this->gamma[1] = other.gamma[1];
      this->omega[0] = other.omega[0];
      this->omega[1] = other.omega[1];
      this->vax = other.vax;
       return *this;
      }
     }
Parameters() {
   beta[0] = 0.3;
   beta[1] = 0.0;
   gamma[0] = 0.25 ;
   gamma[1] = 0.;
   omega[0] = 0.15;
   omega[1] = 0.;
   vax = 0.;
  }  
           //Operator ==
    friend bool operator==( const Parameters& left, const Parameters& right){
      return (left.beta[0] == right.beta[0] && left.beta[1] == right.beta[1] && left.gamma[0] == right.gamma[0] && left.gamma[1] == right.gamma[1] && left.omega[0] == right.omega[0] &&left.omega[1] == right.omega[1] && left.vax == right.vax );
    } 
        //Operator<<
    /*friend std::ostream& operator<<(std::ostream& os, const Parameters& p_out){}
        //Operator>>
    friend std::istream& operator>>(std::istream& is, Parameters& p_in ){}*/
     
};






class Pandemic {
    private:
    std::vector<People> population_;//questa è la griglia primordiale; che protrebbe essere utile per tenere traccia delle giornate;
    //cioè vuole essere una raccolta dati della diffusione 
     Parameters par_;
     int N_;  //Numero della popolazione 
    
    public:
    //Costruttore Parametrico
    Pandemic( std::vector<People>& population, const Parameters& par,const int& N): population_{population}, par_{par}, N_{N}{
     //if and throw statement=> dei controlli sul primo elemento di population 
     if ((par.beta[0] < 0. || par.beta[0] > 1. ) || (par.gamma[0] < 0. || par.gamma[0] > 1. ) ||  (par.omega[0]< 0. || par.omega[0] > 1.) || (  par.vax<0 || par.vax > 1. )  ) 
       throw  std::runtime_error{"The values of the parameters must be inside the interval [0,1] !"};

     if (par.beta[1] != 0 || par.gamma[1] != 0 || par.omega[1] != 0  || par.vax != 0 ) // all'inizione le probabilità modificate devono esssere 0
       throw  std::runtime_error{"The value of the parameters in case of vaccination must be 0 !"};
    }

    //Costruttore default
    Pandemic(): N_{2000000}{
       // Inizializziamo i parametri con valori predefiniti
        par_.beta[0] = 0.5;  // Es. probabilità di infezione base
        par_.beta[1] = 0.0;  // Vaccinati inizialmente non infetti
        par_.gamma[0] = 0.1; // Es. probabilità di guarigione base
        par_.gamma[1] = 0.0; // Inizialmente i vaccinati non sono infetti
        par_.omega[0] = 0.01; // Es. probabilità di morte base
        par_.omega[1] = 0.0;  // I vaccinati inizialmente non muoiono
        par_.vax = 0.0;       // Inizialmente nessuno vaccinato

        // Inizializziamo una popolazione con un unico individuo infetto
        People initial_person;
        initial_person.S_[0] = N_ - 1; // Tutti suscettibili
        initial_person.I_[0] = 1;      // Un unico infetto
        initial_person.S_[1] = 0;
        initial_person.I_[1] = 0;
        initial_person.H_ = 0;         // Nessun guarito
        initial_person.D_ = 0;         // Nessun morto

        population_.push_back(initial_person);
      
    } 
      
    //Operator=; in realtà non mi serve l'operatore =, perchè posso generare un altro oggetto e far diffondere ma non avrebbe senso modificare assegnando altri valori ad un giorno già avvenuto 
   /* People& operator=(People& other){ 
      this->
    }*/ 
 
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Struct Parameters
   // check dei parametri?
   void set_Parameters(Parameters const& p){//devi mettere i controlli anche qua
      this->par_= p; 
     }
    const Parameters& get_Parameters() const { //perchè è di lettura; mettere il const prima del tipo del metodo indica che il valore restituito non può essere modificato ; se invece il const è messo dopo la di chisrazione del metodi significa che questo non può modificare lo stato dell'oggetto su cui è chiamato
      return this->par_;
     }
     // Struct People 
    void set_initial_condition(People& start)
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
        
      }
     //se mette un un vettore con più di un elemento 
     //controllo 
     //per come è strutturato il progetto non ha molto senso mettere più rimossi che suciettibili, non si osserverebbe nulla d'interessante, dal momento che un guarito non si può reinfettare
    }
    People& get_the_conditio_of_the_day( const int& i){//
      if (i == 0)
      {
        throw std::runtime_error{"The simulation starts from day 1 !"};
      }
      
      return this-> population_[i-1];
     }
     //in generale ho più mandemie in corso con popolazioni diverse e voglio sapere in particolare 
  
    const People& get_data(int& d) const{//int d rappresenta il numero del giorno
         if (d < 1 || static_cast<std::vector<People>::size_type>(d) > this->population_.size()) {
              throw std::out_of_range("Invalid day number!"); // controllo che il gionro entri nell'inyervallo di population
         }
         else {
          return this->population_[d - 1];
          } 

    }
  void add_data(const People& add){
    this->population_.push_back(add);
  }

    
    
  bool is_vaccinated(){
       std::random_device rd;  // Will be used to obtain a seed for the random number engine; questo mi serve per avere sempre una una generazione di numeri diversa
       std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd(); è in generatore di numeri casuali interi che dovranno essere convertiti
       std::uniform_real_distribution<> dis(0.,1.0);
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
  void sorting(){
      int t = population_[0].S_[0];// copio il numero di persone a cui chiedere così posso poi modificare i no vax susciettibili
      // ciclo for=> immagina di parlare con tutti gli suscettibilie e di fargli la domanda "sei vaccinato?"
        for (int i = 0; i <=  t ; i++)
           {
             if (this->is_vaccinated() == true)
                {
                    population_[0].S_[1]++;
                    population_[0].S_[0]--;   
    
                }
    
           }
    
  }
  int get_days(){
      return this->population_.size();
    }
    int get_number_population()
    { //potrebbe dare errore, in tal caso vedi se il problema è perchè sto utilizzando un oggetto della classe dentre la definizione della classe stessa
      return this->N_;
  }
  std::vector<People>& get_evolution()
    {
        return this->population_;
    }

   //da qui inizia a specializzarsi in Equation 
   /* void evolve (){
      //prendi l'ultimo elemento del vettore 
      People& last = (this->population_.back());//qua ritorna l'ultimo elemento del vettore population_
      People next ; //vedi poi se è più opportuna una referenza
      next.S_ = last.S_ - (this->par_.beta)*(last.S_/N_)*last.I_; // Sarà divertente poi vedere come risolvere questo problema
      next.I_ = last.I_ + (this->par_.beta)*(last.S_/N_)*last.I_ - (this->par_.gamma)*(last.I_);
      next.H_ = last.H_ + (this->par_.gamma)*last.I_;
      //next.D_ = last.R_ + (this->par_.gamma)*last.I_;:per gli eventuali
      // qui dovrebbero essere stati modificati i valori di S_, I_ e H_
      this->population_.push_back(next);// viene aggiunto il giorno successivo 
      
      }*/
    /*void evolve_with_vax(){
      People& last = (this->population_.back());//qua ritorna l'ultimo elemento del vettore population_
      People next ; //vedi poi se è più opportuna una referenza
      next.S_ = last.S_ - (this->par_.beta)*(last.S_/N_)*last.I_; // Sarà divertente poi vedere come risolvere questo problema
      next.I_ = last.I_ + (this->par_.beta)*(last.S_/N_)*last.I_ - (this->par_.gamma)*(last.I_);
      next.R_ = last.R_ + (this->par_.gamma)*last.I_;
      next.R_ = last.R_ + (this->par_.gamma)*last.I_;//ovviamente è da modificare l'espressione 
      next.D_ = last.R_ + (this->par_.gamma)*last.I_;//per gli eventuali
      // qui dovrebbero essere stati modificati i valori di S_, I_ e R_
      this->population_.push_back(next);// viene aggiunto il giorno successivo 


    }*/
    //questo metodo restituisce tutta l'evoluzione della popolazione 
    

   /*auto& calculate_R0(){// mi sa che te sarai solo dell'equation
      return;    }
  */ 
    
    // Distruttore
    ~Pandemic(){};





//std::function<Pandemic()> ;// mi serve per la funzione di stampa; Rifletti se metterlo nella madre o nella figlia Equation
// è importante che capisci come sfruttare bene gli oggetti funzione perchè, tu non solo vuoi stampare i numeri tu vuoi stampare l'evoluzione della pandemia e perciò ti serve il numero del gioRno che si vuole vedere; 
//siccome population è un vettore dinamico noi non sappiamo a priori la sua effettiva lunghezza perciò sarà necessaria una verifica della sua dimensione e che il giorno richiesto sia avvenuto 

 /*void print(Pandemic& p){
  //allora per la stampa puoi usare l'algoritmo che ti permette di stampare contemporaneamente
  std::vector<People> v_p = p.get_evolution(); 
  std::cout << v_p <<'\n';//ti da errore perchè gli operandi dell'espressione non matchano con gli argomenti dell'operatore <<, di fatto gli stai chiedendo di stampare un vettore quando lui stampa solo tipi pr
 }*/
};