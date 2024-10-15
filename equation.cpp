#include <vector>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <random>
#include <array>

#include "pandemic.hpp"
#include "equation.hpp"
 
 
Equation::Equation(std::vector<People>& population,  Parameters& par,const int& N,std::vector<std::array<int,4>>& counting):  Pandemic(population,par,N),counting_{counting}
{     
}
Equation::Equation(): Pandemic(),counting_{}{
      // Inizializziamo i parametri con valori predefiniti
      // Inizialmente nessuno vaccinato
      // Inizializziamo una popolazione con un unico individuo infetto
       

        
        std::array<int,4> initial_count;
        initial_count[0] = (this->get_number_population()) - 1; //non potevi mettere direttamente N_ perchè è un attributo provato di Pandemic
        initial_count[1] = 1 ; 
        initial_count[2] = 0 ; 
        initial_count[3] = 0 ; 
        
        counting_.push_back(initial_count);


        


    } 
//recupera i dati registrati nel conteggio fornendogli il giorno  
   std::array<int,4> Equation::get_counting(const int& n){
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
   std::array<int,4>& Equation::calculate(const int& n, std::array<int,4>& calc ){

        calc[0] = sum(this->get_condition_day(n).S_);
        calc[1] = sum (this->get_condition_day(n).I_);
        calc[2] = this->get_condition_day(n).H_;
        calc[3]= this->get_condition_day(n).D_;
        return calc;
   }
        
       

    std::array<float,6> Equation::update_situation(int index, const People& next){
    assert(index == 1 || index == 0 );
        
     const People& last = (this->get_evolution().back());//qua ritorna l'ultimo elemento del vettore population_
     
      std::array<float,6> next_a{transform_arr<float,6>(next)};
      
      next_a[0 + index] = last.S_[index] - ((((this->get_Parameters().beta[index])*((last.S_[index])))/this->get_number_population())* (last.I_[0] +last.I_[1])); //qua devo considerare tutti gli infetti perchè si tratta di una pobabilità d'interazione che l'individuo ha con tutti gli infetti quindi, perciò beta[1] tiene in considerazione la protezione personale ma non smette d'interagire con chi non è vaccinato e la tendenza dell'infetto ad infettare 
      next_a[2 + index]= last.I_[index] + ((((this->get_Parameters().beta[index])*(last.S_[index])) / (this->get_number_population())) * (last.I_[0] +last.I_[1]) ) - ((this->get_Parameters().gamma[index]) * last.I_[index] ) -((this->get_Parameters().omega[index]) * last.I_[index]);
      //il problema della perdita di dati 
      if (index == 1) {
          next_a[4] += last.H_ + (this->get_Parameters().gamma[index])*last.I_[index];
          next_a[5] += last.D_ + (this->get_Parameters().omega[index])*last.I_[index];
      } else {
          next_a[4]= last.H_ + (this->get_Parameters().gamma[index])*last.I_[index];
          next_a[5] = last.D_ + (this->get_Parameters().omega[index])*last.I_[index];
      }
      
       assert( this->get_number_population() == sum(next_a));
       return next_a ;//questi sono i dati People in formato array
      
   }
   const People Equation::fix(std::array<float,6> next){
     
     const float diff = this->get_number_population() - sum(convert<int>(next));//qua mi sto calcolando lo scarto dei decimali, dati dai contributi degli elementi del vettore
     
     if (0 < diff && diff < 2)
      {
      next[maximum_dec(next)] += 1;//nel caso ce ne siano due con uguale parte decimale va bene uno dei due a a caso 
      }
       else 
      {
        if (diff >= 2){
           
      //next[maximum_dec(next)] += std::floor(diff); è con l'iteratore
      next[maximum_dec(next)] += std::floor(diff);//qua maximum mi restituisce direttamente next[t], bisogna vedere se funziona bene +=
      }
      }

      assert(this->get_number_population() == sum(convert<int>(next)));
      return transform_people(convert<int>(next));
     }
   
   void Equation::evolve(People& follow ) {
      if (this->Pandemic::calculate_R0() > 1){
          //prendi l'ultimo elemento del vettore 
      ;//aggiorna 
      // qui dovrebbero essere stati modificati i valori di S_, I_ e H_
      this->add_data(this->fix(this->update_situation(0,follow)));// viene aggiunto il giorno successivo 
      } 
      else {
        throw std::runtime_error{"The simulation can't start if the critical threshold is minor than one! "};}

      }
     
     
   void Equation::evolve_vaccine(People& follow) {
        if (this->Pandemic::calculate_R0() > 1){
            //i No vax, evoluzione al naturale
      const People& natural = this->fix(this->update_situation(0,follow));//evoluzione tra i no vax 
      //i vax
      this->add_data(this->fix(this->update_situation(1,natural)));// viene aggiunto il giorno successivo 
        } else 
        throw std::runtime_error{"The simulation with the vaccine can't start if the critical threshold is minor than one! "};
      
    }
    //questo metodo restituisce tutta l'evoluzione della popolazione 
    std::array<int,4>& Equation::Print(int& d){//d è il numero del giorno
        std::cout<< "S = " << this->get_counting(d)[0] << " || ";
        std::cout<< "I = " << this->get_counting(d)[1] << " || ";
        std::cout<< "H = " << this->get_counting(d)[2] << " || ";
        std::cout<< "D = " << this->get_counting(d)[3] << '\n';
        return this->counting_[d - 1];
    }
Equation::~Equation() = default;


  
    
  