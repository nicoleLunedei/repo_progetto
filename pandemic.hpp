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
#include <array>
#ifndef PANDEMIC_HPP
#define PANDEMIC_HPP
struct People
{
 std::array<int, 2> S_; // Array per le persone suscettibili
 std::array<int, 2> I_; 
 int H_;
 int D_;
//Parametric Constructor
People( const std::array<int,2>& s,const std::array<int,2>& i , const int  h, const int& d  );
//Default Constructor
People();
//Copy Constructor
People(const People& other);

////////////////////// Over loading /////////////////////
 People& operator=( const People& value);

 friend bool operator==( const People& left, const People& right);
 
 //considera che potresti fare una valutazione paragonando la situazione no vax e vax
 friend std::ostream& operator<<(std::ostream& os, const People& p_out);
  
         //Operator>>
 friend std::istream& operator>>(std::istream& is, People& p_in );// qua mettere p_in  con const è un errore perchè >> prende in valora dato in input sall'utente e lo utilizzerà per modificare p_in
     //Destructor
 ~People();

};
struct Parameters
{ // considera se metterli const 
    std::array<double,2> beta;//d'infezione ; anche beta e gamma potrei metterle come vettori bidimensionali 
    std::array<double,2> gamma;//guarigione
    std::array<double,2> omega;//morire
    double vax;// vaccinazione
//Parametric Constructor
Parameters(const std::array<double,2>& b, const std::array<double,2>& g, const std::array<double,2>& o, const double& v) ;// l'assegnazione degli array non li puoi mettere nella lista d'inizializzazione perchè non è supportata la loro assegnazione in blocco
//Default Constructor   
Parameters();
//Copy Constructor
Parameters(const Parameters& other ) ; //costruttore di copia che è diverso dal costruttore parametrico; questo è propio per costruire un oggetto a partire da un altro oggetto dello stesso tispo 
       

        //Operator=
  Parameters& operator=( const Parameters& other);// di fatto si serve mettere il tipo dell'operatore perchè l'assegnazione restituisce un oggetto modificato che nella dichiarazione ha la referenza ma poi renderà forma con l'oggetto vero 
        //Operator ==
    friend bool operator==( const Parameters& left, const Parameters& right);
        //Operator<<
    /*friend std::ostream& operator<<(std::ostream& os, const Parameters& p_out){}
        //Operator>>
    friend std::istream& operator>>(std::istream& is, Parameters& p_in ){}*/
   ~Parameters();   
};






class Pandemic {
    private:
    std::mt19937 gen;  // Generatore di numeri casuali
    std::uniform_real_distribution<> dis; 
    std::vector<People> population_;//questa è la griglia primordiale; che protrebbe essere utile per tenere traccia delle giornate;
    //cioè vuole essere una raccolta dati della diffusione 
    Parameters par_;
    int N_;  //Numero della popolazione 
    static std::array<double,2> intersec_; 
    
    
    public:

    //Costruttore Parametrico

    Pandemic( std::vector<People>& population,  Parameters& par, const int& N) ;
    
    //Costruttore default
    Pandemic(); 
 
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Struct Parameters
   void change_after_vacc();//test-> 16/09
   void check_complementarity();//test->16/09
   void check_complementarity( Parameters& p);//test ->16/09
   void set_Parameters( Parameters& p);
   void introduce_vacc(const double& v);
   const Parameters& get_Parameters() const ;
     // Struct People 
   void set_initial_condition(People& start);
    
   People& get_condition_day( const int& i);
     //in generale ho più mandemie in corso con popolazioni diverse e voglio sapere in particolare 
  
  const People& get_data(int& d) const;//test
  void add_data(const People& add);//  test
  //dovresti vare un remove per simmetria
  bool is_vaccinated();//test
    //smistamento
  void sorting();//test
  int get_days();
  int get_number_population();
  std::vector<People>& get_evolution();//questo mi restituisce tuttatta l'evoluzione 
  double calculate_R0() ;
virtual void evolve(People& );
virtual void evolve_vaccine (People& );
//virtual std::array<int,4>& Print(int& );

    
    // Distruttore
virtual ~Pandemic();
//std::function<Pandemic()> ;// mi serve per la funzione di stampa; Rifletti se metterlo nella madre o nella figlia Equation
// è importante che capisci come sfruttare bene gli oggetti funzione perchè, tu non solo vuoi stampare i numeri tu vuoi stampare l'evoluzione della pandemia e perciò ti serve il numero del gioRno che si vuole vedere; 
//siccome population è un vettore dinamico noi non sappiamo a priori la sua effettiva lunghezza perciò sarà necessaria una verifica della sua dimensione e che il giorno richiesto sia avvenuto 
};

#endif