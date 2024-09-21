#include <vector>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <random>
#include <array>
#include "pandemic.hpp"
#include "equation.hpp"



Equation::Equation(std::vector<People>& population,  Parameters& par,const int& N,std::vector<std::array<int,4>>& counting): population_{population},par_{par},N_{N},counting_{counting}
{
}
Equation::Equation(): gen(std::random_device{}()), dis(0.0, 1.0),population_{},par_({0.5, 0.0},{0.6, 0.0} ,{0.4, 0.0} , 0.0 ),N_{2000000},counting_{}{
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
        
        std::array<int,4> initial_count;
        initial_count[0] = N_ - 1; 
        initial_count[1] = 1 ; 
        initial_count[2] = 0 ; 
        initial_count[3] = 0 ; 
        
        counting_.push_back(initial_count);


        


    } 
//recupera i dati registrati nel conteggio fornendogli il giorno  
   std::array<int,4> Equation::get_counting(const int& n){
    return this->counting_[n];
   }
   //aggiunge
   void Equation::add_count(const std::array<int,4>& add){
     this->counting_.push_back(add);
   }
   //riceve il foglio bianco, ci calcola dentro e lo restituisce scritto
   std::array<int,4>& Equation::calculate(const int& n, std::array<int,4>& calc ){

     if (n < 1 || static_cast<std::vector<People>::size_type>(n) > this->counting_.size()) {
              throw std::out_of_range("Invalid day number!"); // controllo che il gionro entri nell'inyervallo di population
         }
         else {
        calc[0] = this->get_condition_day(n).S_[0] + this->get_condition_day(n).S_[1];
        calc[1] =this->get_condition_day(n).I_[0] + this->get_condition_day(n).I_[1];
        calc[2] = this->get_condition_day(n).H_;
        calc[3]= this->get_condition_day(n).D_;
        return calc;
   }
          }
       

   void Equation::update_situation(int index, People& next){
      People& last = (this->population_.back());//qua ritorna l'ultimo elemento del vettore population_
      //People* next = new People() ;stai usando il puntatore e l'allocazione dinamica puoi usaro nella simulazione

      next.S_[index] = last.S_[index] - (this->par_.beta[index])*(last.S_[index]/N_)*last.I_[index]; // Sarà divertente poi vedere come risolvere questo problema
      next.I_[index] = last.I_[index] + (this->par_.beta[index])*(last.S_[index]/N_)*last.I_[index] - (this->par_.gamma[index])*(last.I_[index])- (this->par_.omega[index]);
      next.H_ = last.H_ + (this->par_.gamma[index])*last.I_[index];
      next.D_ = last.D_ + (this->par_.omega[index])*last.I_[index];

      
   }
   void Equation::evolve(People& follow ) {
      if (this->Pandemic::calculate_R0() > 1){
          //prendi l'ultimo elemento del vettore 
      this->update_situation(0,follow);//aggiorna 
      // qui dovrebbero essere stati modificati i valori di S_, I_ e H_
      this->add_data( follow);// viene aggiunto il giorno successivo 
      } 
      else std::runtime_error{"The simulation can't start if the critical threshold is minor than one! "};
      
     
      

      }
   void Equation::evolve_vaccine(People& follow) {
        if (this->Pandemic::calculate_R0() > 1){
            //i No vax
      this->update_situation(0,follow);//evoluzione tra i no vax 
      //i vax
      this->update_situation(1,follow);//evoluzione tra i vax

      // qui dovrebbero essere stati modificati i valori di S_, I_ ,H_ e D_
      this->population_.push_back(follow);// viene aggiunto il giorno successivo 
        } else std::runtime_error{"The simulation with the vaccine can't start if the critical threshold is minor than one! "};
      
    }
    //questo metodo restituisce tutta l'evoluzione della popolazione 
    std::array<int,4>& Equation::Print(int& d){//d è il numero del giorno
        this->counting_[d][0] = this->population_[d].S_[0] + this->population_[0].S_[1];
        this->counting_[d][1] =this->population_[d].I_[0] + this->population_[0].I_[1];
        this->counting_[d][2] = this->population_[d].H_;
        this->counting_[d][3]= this->population_[d].D_;
        return this->counting_[d];
    }
Equation::~Equation() = default;


  
    
  