#include <vector>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <random>
#include <array>
#include <assert.h>

#include "pandemic.hpp"
#include "equation.hpp"
 
 
Equation::Equation(std::vector<People>& population,  Parameters& par,const int& N,std::vector<std::array<int,4>>& counting):  Pandemic(population,par,N),counting_{counting}
{   
  assert(counting.empty());
  
}
Equation::Equation(): Pandemic(),counting_{}{
      // Inizializziamo i parametri con valori predefiniti
      // Inizialmente nessuno vaccinato
      // Inizializziamo una popolazione con un unico individuo infetto
      ///////Pulisce il vettore creato dal cotruttore di default//////////////
        People initial_data({2000,0},{500,0},0,0);
          this->set_initial_condition(initial_data);

        std::array<int,4> initial_count;
        initial_count[0] = 2000; //non potevi mettere direttamente N_ perchè è un attributo provato di Pandemic
        initial_count[1] = 500 ; 
        initial_count[2] = 0 ; 
        initial_count[3] = 0 ; 
        
        counting_.push_back(initial_count);


        


    } 
//recupera i dati registrati nel conteggio fornendogli il giorno  
   std::array<int,4> Equation::get_counting(const int& n){
     if ( n <= 0 || static_cast<std::vector<std::array<int,4>>::size_type>(n) > this->get_countdays().size()) {
          
           if (n == 0)
        {
               throw std::runtime_error{"The simulation starts from day one!"};
        }  else 
        {
         throw std::out_of_range{"Invalid day number!"}; // controllo che il gionro entri nell'intervallo di population
        }     
             
      }
    return this->counting_[n-1];
   }
   std::vector<std::array<int,4>> Equation::get_countdays(){
    return this->counting_;
   }
   //aggiunge
   void Equation::add_count(const std::array<int,4>& add){
     this->counting_.push_back(add);
   }
   //riceve il foglio bianco, ci calcola dentro e lo restituisce scritto
   std::array<int,4> Equation::calculate(){
        std::array<int,4> calc{0,0,0,0};
        calc[0] = sum(this->get_evolution().back().S_);
        calc[1] = sum (this->get_evolution().back().I_);
        calc[2] = this->get_evolution().back().H_;
        calc[3]= this->get_evolution().back().D_;
        return calc;
   }
        
       

    std::array<double,6> Equation::update_situation(int index, People const& next){
    assert(index == 1 || index == 0 );
        
     //const People& last = (this->get_evolution().back());//qua ritorna l'ultimo elemento del vettore population_
     assert(!(this->get_evolution().empty()));//controlla che il vettore non sia vuoto
      std::array<double,6> next_a{transform_arr<double,6>(next)};
       
       if (sum(next_a) == 0){
        next_a[4]+= this->get_evolution().back().H_ + (this->get_Parameters().gamma[0])*this->get_evolution().back().I_[0];
        next_a[5]+= this->get_evolution().back().D_ + (this->get_Parameters().omega[0])*this->get_evolution().back().I_[0];
      } else {
        next_a[4]+= (this->get_Parameters().gamma[1])*this->get_evolution().back().I_[1];
        next_a[5]+= (this->get_Parameters().omega[1])*this->get_evolution().back().I_[1];
      }

     
      switch(index){
        case 0 : {
        next_a[0] = this->get_evolution().back().S_[0] - ((((this->get_Parameters().beta[0])*((this->get_evolution().back().S_[0])))/this->get_number_population()) * (sum(this->get_evolution().back().I_))); //qua devo considerare tutti gli infetti perchè si tratta di una pobabilità d'interazione che l'individuo ha con tutti gli infetti quindi, perciò beta[1] tiene in considerazione la protezione personale ma non smette d'interagire con chi non è vaccinato e la tendenza dell'infetto ad infettare 
        next_a[2] = this->get_evolution().back().I_[0] + ((((this->get_Parameters().beta[0])*(this->get_evolution().back().S_[0])) / (this->get_number_population())) * (sum(this->get_evolution().back().I_) )) - ((this->get_Parameters().gamma[0]) * this->get_evolution().back().I_[0] ) -((this->get_Parameters().omega[0]) * this->get_evolution().back().I_[0]);
    
          break;
        }
         case 1 : {
        next_a[1] = this->get_evolution().back().S_[1] - ((((this->get_Parameters().beta[1])*((this->get_evolution().back().S_[1])))/this->get_number_population()) * (sum(this->get_evolution().back().I_))); //qua devo considerare tutti gli infetti perchè si tratta di una pobabilità d'interazione che l'individuo ha con tutti gli infetti quindi, perciò beta[1] tiene in considerazione la protezione personale ma non smette d'interagire con chi non è vaccinato e la tendenza dell'infetto ad infettare 
        next_a[3] = this->get_evolution().back().I_[1] + ((((this->get_Parameters().beta[1])*(this->get_evolution().back().S_[1])) / (this->get_number_population())) * (sum(this->get_evolution().back().I_) )) - ((this->get_Parameters().gamma[1]) * this->get_evolution().back().I_[1] ) -((this->get_Parameters().omega[1]) * this->get_evolution().back().I_[1]);
          break;
        }
      }
 
       return next_a ;//questi sono i dati People in formato array
      
   }
   const People Equation::fix(std::array<double,6> next){
     
     const double diff = sum(next) - sum(integer_part(next));//qua mi sto calcolando lo scarto dei decimali, dati dai contributi degli elementi del vettore
     assert(diff>=0);
     if (0 < diff && diff < 2)
      {
      next[maximum_dec(next)] += 1;//nel caso ce ne siano due con uguale parte decimale va bene uno dei due a a caso 
      }
       else 
      {
          
      //next[maximum_dec(next)] += std::floor(diff); è con l'iteratore
      next[maximum_dec(next)] += diff;//qua maximum mi restituisce direttamente next[t], bisogna vedere se funziona bene +=
      
      }
 //std::cout<< diff <<" & "<< next[maximum_dec(next)]<<'\n';
     
      return transform_people(integer_part(next));
     }
       void  Equation::sorting(){
      int t = this->get_evolution().back().S_[0];// copio il numero di persone a cui chiedere così posso poi modificare i no vax susciettibili
      // ciclo for=> immagina di parlare con tutti gli suscettibilie e di fargli la domanda "sei vaccinato?"
        for (int i = 0; i <=  t ; i++)
           {
             if (this->is_vaccinated())
                {
                   this->get_evolution().back().S_[0]--;  
                   this->get_evolution().back().S_[1]++;
                     
    
                }
    
           }
    assert(sum(this->get_evolution().back().S_) == t);
  }
   
   void Equation::evolve() {
      const People& follow = {{0,0},{0,0},0,0};  
      this->add_data(this->fix(this->update_situation(0,follow)));// viene aggiunto il giorno successivo 
         /*std::cout<<"risultati reali :"<<this->update_situation(0,follow)[0]<<'\n';
        std::cout<<"risultati reali :"<<this->update_situation(0,follow)[1]<<'\n';
           std::cout<<"risultati reali :"<<this->update_situation(0,follow)[2]<<'\n';
              std::cout<<"risultati reali :"<<this->update_situation(0,follow)[3]<<'\n';
                 std::cout<<"risultati reali :"<<this->update_situation(0,follow)[4]<<'\n';
                    std::cout<<"risultati reali :"<<this->update_situation(0,follow)[5]<<'\n';*/
        //////////////updating the counting vector///////////////
      this->add_count(this->calculate());
      assert( this->get_number_population()== sum(transform_arr<int,6>(this->get_evolution().back())));
      }
     
     
   void Equation::evolve_vaccine() {
     const People& follow = {{0,0},{0,0},0,0};
            //i No vax, evoluzione al naturale
      const People& natural = this->fix(this->update_situation(0,follow));//evoluzione tra i no vax 
      //i vax
   
      this->add_data(this->fix(this->update_situation(1,natural)));// viene aggiunto il giorno successivo 
   //////////////updating the counting vector///////////////
      this->add_count(this->calculate());
      assert( this->get_number_population()== sum(transform_arr<int,6>(this->get_evolution().back())));
   } 

    //questo metodo restituisce tutta l'evoluzione della popolazione 
    void Equation::Print(const int& d){//d è il numero del giorno
        std::cout<< "S = " << this->get_counting(d)[0] << " || ";
        std::cout<< "I = " << this->get_counting(d)[1] << " || ";
        std::cout<< "H = " << this->get_counting(d)[2] << " || ";
        std::cout<< "D = " << this->get_counting(d)[3] << "\n\n";
    }
Equation::~Equation() = default;


  
    
  