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
#include <cassert>


//template<typename T, std::size_t N> T sum(std::array<T,N>& a);
//template<typename T, std::size_t N> T& maximum_dec(std::array<T,N> a);

#ifndef PANDEMIC_HPP
#define PANDEMIC_HPP

template<typename T, std::size_t N> T sum(const std::array<T,N>& a){
  T tot = T();
  for(const T& t: a ){
    tot+=t;
  }

  return tot;
}
/*template<typename T> T sum(std::vector<T>& v){
  T tot = 0;
  for(T& t: v ){
    tot+=t;
  }

  return tot;
}*/
template<typename T, std::size_t N> int maximum_dec(std::array<T,N>& a){
    T max = 0;
    int t = 0;//lui rappresenta l'iteratore uscente 
   for (auto it = 0; it < 6; ++it)
          {
             if ((a[it] - std::floor(a[it])) > max)//per guadagnarsi il titolo di maximum deve essere maggiore non uguale 
             {
                max = a[it] - std::floor(a[it]);
                t = it;
             }
          }
    return  t;
 }

  
 template<typename T,typename C, std::size_t N> const std::array<T,N> convert(const std::array<C,N>& c){

  std::array<T,N> t;
 
  for (std::size_t i = 0; i < N; i++)
  {
    //t[i] = std::floor(c[i]);
    t[i] = static_cast<T>(c[i]);
  }
    return t;
 }




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

template<typename T, std::size_t N>  const std::array<T,N> transform_arr( const People& p){
     
       return {static_cast<T>(p.S_[0]),static_cast<T>(p.S_[1]),static_cast<T> (p.I_[0]), static_cast<T>(p.I_[1]), static_cast<T>(p.H_), static_cast<T>(p.D_)} ;
 }
template<typename T, std::size_t N>   const People transform_people(const std::array<T,N>& t){

     return {{t[0],t[1]},{t[2],t[3]},t[4],t[5]} ;//non hai potuto metterlo T& perchè stai restituendo una variabile lovale che muore nelle scope e il riferimento perde di significato
     //mi raccomando ricorda il legame T&->const& non va bene perchè T& è modificabile  e const T& no perciò viene messa in pericolo la protezione di const T&
     //invce const T& || T-> T& si può fare e non mette in pericolo nulla 
 }






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
    std::mt19937 gen;  // Generatore di numeri casuali, chiedi se è opportuno metterli pubblici
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
   void introduce_vacc(const double& v);
   void change_after_vacc();
   void check_normalization();
   void check_normalization( Parameters& p);
   void set_Parameters( Parameters& p);
   Parameters& get_Parameters();
     // Struct People 
   void set_initial_condition(People& start);
    
   People& get_condition_day( const int& i);
     //in generale ho più mandemie in corso con popolazioni diverse e voglio sapere in particolare 
  
  const People& get_data(int& d);//test
  void add_data(const People& add);//  test
  //dovresti vare un remove per simmetria
  bool is_vaccinated();//test
    //smistamento
  void sorting();//test
  int get_days();
  int get_number_population() const;
  std::vector<People>& get_evolution();//questo mi restituisce tutta l'evoluzione 
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