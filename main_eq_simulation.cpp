#include "pandemic.hpp"
#include "equation.hpp"
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>


int main() {
    char sim;
    std::cout<< "Hi! Do you want to run a default[D] or a personalized[P] simulation?[D/P]"<< '\n';
    std::cin>> sim;
    int MAX_IT = 5;
    int it = 0;

    while (sim != 'D' && sim != 'P' )
     {
        std::cout << "Please insert D, for default, or P , for personalized "<< '\n';
        std::cin>> sim;
        it++;
        if(it == MAX_IT){
         std::cout<<" The attempts are finished! It'll start the default simulation"<<"\n\n";
         sim = 'D';
         break;
        }
     }
    it = 0;
    
  

    if (sim == 'D'){
       //simulazione by default
       Equation eq;
       //eq.set_initial_condition({{2000,0},{500,0},0,0});
     
      
       std::cout<< " Great! You've chosen the default simulation, here below some data :" << '\n';
       std::cout<< " The population corrisponds to " << eq.get_number_population() << " people"<< '\n';
       //std::cout<< " Susceptible =  " << eq.get_condition_day(1).S_[0] << " || "<< " Infected = " <<  eq.get_condition_day(1).I_[0] ;
       //std::cout<< " Healed = 0 || Dead = 0 " << '\n';
       std::cout<< eq.get_condition_day(1);
       eq.Print(1);
       std::cout<< " Note the following probabilities are refering to what happends in one day  "<<"\n\n";
       std::cout<< " Probability to infect : " << eq.get_Parameters().beta[0] * 100 << "%"<<'\n';
       std::cout<< " Probability of healing : " << eq.get_Parameters().gamma[0] * 100 << "%"<<'\n';
       std::cout<< " Probability of dying : " << eq.get_Parameters().omega[0] * 100 << "%"<<'\n';
       std::cout<< " Probability to get vaccinated, initially is null, later you'll have the chance to introduce it." << '\n';
       char start;
       std::cout<< "Ok ! Let's get start, are you ready?[y/n]"<<'\n';
      
        
       
        while(!(std::cin>>start)||(start != 'y' && start!= 'n')){//gli eventi sono 2, di cui uno composto, o è in stato di errore o sono lettere che non hanno significato
           
            std::cout<< "Please, insert 'y', for yes, or 'n', for no"<<'\n';
            std::cin.clear();  // Rimuove lo stato di errore
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// svuota il buffer
          
          if(it == MAX_IT){
            std::cout<<" The attempts are finished! The simulation will start"<<"\n\n";
            start = 'y';
             break;
            }
         }
        ///////////////////////////////////////////////////////////////////////////
        MAX_IT = 1;
      if (start =='y'){ int t = 1 ;
       while (!eq.terminate())//continue until they are infected people
         {  
          
           
             std::cout<<"Day N° :"<< t <<"\n\n";
             std::cout<< "Confronto:"<< eq.get_number_population() <<" = "<< sum(transform_arr<int,6>(eq.get_condition_day(t)))<<"\n\n";
             eq.Print(t);
             
             if (sum(eq.get_evolution().back().I_) == 0){
               it++;
                if(it == MAX_IT){
                     std::cout<<" Simulation terminated !"<<"\n\n";
                       break;
                  }
             }
              eq.evolve(); 
              t++; 
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));    
         }
         it = 0;
       char comparison;
       MAX_IT = 5;
       std::cout<<"Would you be interested to observe the difference between the last simulation and another with the option to get vaccinated?[y/n]"<<'\n';
      
        while(!( std::cin>>comparison)||(comparison != 'y' && comparison != 'n')){
            std::cout<< "Please, insert 'y', for yes, or 'n', for no"<<'\n';
            std::cin.clear();  // Rimuove lo stato di errore
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// svuota il buffer
            it++;
            if(it == MAX_IT){
               std::cout<<" The attempts are finished! Let's continue with the comparison"<<"\n\n";
               comparison = 'y';
                  break;
            }
         }
        
        if(comparison == 'y'){
        std::cout<<"Great!Let's start another simulation! The initial conditions are the same."<<'\n';
        Equation eq_v;
        //eq_v.set_initial_condition({{2000,0},{500,0},0,0});
        float prob_v;
        std::cout<<"Insert the probability of getting vaccinated"<<'\n';
        std::cin>> prob_v;
        bool input_v = false;
        it = 0;
        std::cout<<" Il numero dei giorni : "<< eq_v.get_days()<<'\n';
      
        while (!input_v)
        {
           try{
          eq_v.introduce_vacc(prob_v);
          input_v = true;
          } catch(std::runtime_error& e){
         std::cout << "Error: " << e.what() << '\n';
         std::cout<<"  "<<'\n';
         std::cout << "Please correct your data, according to the error, and insert them in the same order"<< '\n';
         std::cin.clear();  // Rimuove lo stato di errore
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// svuota il buffer
         std::cin>> prob_v;
         it++;
          if(it == MAX_IT){
                     std::cout<<"The attempts are finished! The probability of getting vaccinated is 65%"<<"\n\n";
                     prob_v = 0.65;
                       break;
                  }
          }
        }
        eq_v.change_after_vacc();
         std::cout<<"For the vaccinated people the probability have changed : "<<'\n';
               std::cout<< "beta :"<< eq_v.get_Parameters().beta[1] <<'\n'<< "omega :" << eq_v.get_Parameters().omega[1] <<'\n' << "gamma :"<< eq_v.get_Parameters().gamma[1]<<"\n\n";   
               std::cout<< "==========================================================================="<<"\n\n";
        std::cout << eq_v.get_condition_day(1);
        eq_v.sorting();
        MAX_IT = 1;
        int tt = 1;
        it = 0;
           while (!eq_v.terminate())//continue until they are infected people
         {  
             
             std::cout<< "Day N° :" << tt <<"\n\n";
             std::cout<<eq_v.get_condition_day(tt)<<'\n';
             eq_v.Print(tt);
             

              if (sum(eq_v.get_evolution().back().I_) == 0){
               it++;
                if(it == MAX_IT){
                     std::cout<<" Simulation terminated !"<<"\n\n";
                       break;
                  }
              }
              eq_v.evolve_vaccine();
              tt++;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));    
         }
       std::cout<<"////////////////////////////////////////////////"<<"\n\n";
       std::cout<<"| Simulation without vaccine |" <<"\n\n";
       std::cout<<" Numbers of days :" << eq.get_days()<<'\n';
       eq.Print(t);
       std::cout<< "| Simulation with vaccine |" <<"\n\n";
       std::cout<<" Numbers of days :" << eq_v.get_days()<<'\n';
       eq_v.Print(tt);
        } else {
         std::cout<<"Alright, thank you for your time! Below here there are the results of your simulation"<<'\n';
         std::cout<<"| Simulation without vaccine |" <<"\n\n";
         std::cout<<" Numbers of days :" << eq.get_days()<<'\n';
         std::cout<<"The critical threshold is equal to " << eq.calculate_R0(eq.get_Parameters())<<'\n';
         eq.Print(t);
        }
} else {
        std::cout<< "Alright! See you next time!"<< '\n';
      }
     
      

     } else {//sim == 'P'
       //simulazione personalizzata
       int N;
       Parameters prob;
       People people;
       std::vector<People> days; 
       std::vector<std::array<int, 4>> count;
       
       std::cout<< " Awesome! You've chosen the personalized simulation! Now please insert your data" << '\n';
       std::cout<<" "<<'\n';
       std::cout<< " Number population (please at least 100 )" << '\n';
       std::cin>> N;
       
       if (N<50){
         char change;
         std::cout<<"You're number population is quite small, do you want to change ?[y/n]"<<'\n';
         std::cin>>change;
       
         while(change != 'y' && change != 'n'){
            std::cout<< "Please, insert 'y', for yes, or 'n', for no"<<'\n';
            std::cin>> change;
         }
          if (change == 'y'){
            std::cout << "Great! Insert again your number population" <<'\n';
            std::cin >> N;
        
        }
       }

       std::cout<< "Probability to infect [0,1]" << '\n';
       std::cin>>prob.beta[0];
       std::cout<< "Probability of healing [0,1] " <<'\n';
       std::cin>>prob.gamma[0];
       std::cout<< "Probability of dying [0,1] " << '\n';
       std::cin>>prob.omega[0];
       std::cout<<"  "<<'\n';

       // qua in realtà sarebbe utile usare std::unique_ptr, perchè intanto prima "prenoto"  dello spazio in memoria per l'oggetto, fuori dal ciclo while, e poi all'execution time controllo che siano giusti all'interno del ciclo 
     
      std::unique_ptr<Equation> eq_ = nullptr;
       bool input0 = false;
       it = 0;
       while(!input0){

       try{
       
        eq_ = std::make_unique<Equation>(days,prob,N,count);
       //se il valori input vanno bene l'eccezione non viene lanciata e non viene il ricercato il primo handler disponibile 
       input0 = true;//quindi se c'è un'eccezione non viene non viene cambiato il valore di input 
    
    } catch (std::runtime_error& e){
     
        std::cout<<"Error :"<<e.what()<<"\n\n";
        //getting in the good state the input stream 
        std::cin.clear();  // Rimuove lo stato di errore
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//svuota il buffer del input stream
        std::cout << "Please correct your data, according to the error"<< '\n';
        if (!(std::string(e.what()) == "The simulation with the vaccine can't start if the critical threshold is minor than one! ")){
         std::cout <<"Number of population"<<'\n';
         std::cin>> N;
        }else{
         std::cout << "R_0 : "<<eq_->calculate_R0(prob) << '\n';
         std::cout<<"  "<<'\n';
        }
 
        std::cout <<"The probabilities, in the previous order"<<'\n';
        std::cin>> prob.beta[0] >> prob.gamma[0] >> prob.omega[0];
       }
      
               it++;
                if(it == MAX_IT){
                     std::cout<<"The attempts are finished! The values choosen are: "<<"\n\n";
                     prob.beta[0] = 0.67;
                     prob.gamma[0] = 0.32;
                     prob.omega[0] = 0.41;
                     std::cout<<"P. Infection = 67% || P. Healing = 32% || P. Death = 41% "<<'\n';
                       break;
                  }
             

    }
    std::cout<<"Now insert the condition of the first day you want to begin with."<<'\n';
    std::cout<<"  "<<'\n';
    std::cout<<"Susceptiple, Infected, Healed and Dead (the last two must be null)"<<'\n';
    std::cin >> people;
   
       bool input1 = false;
       it = 0;
      while(!input1){
      try{
         ///////////////////////
         std::cout << "Prima di chiamare set_initial_condition:" << std::endl;
         std::cout << "Dimensione di population_: " << eq_->get_evolution().size() << std::endl;

         eq_->set_initial_condition(people);  // Chiama set_initial_condition
         
         std::cout << "Dopo chiamata a set_initial_condition:" << std::endl;
         std::cout << "Dimensione di population_: " << eq_->get_evolution().size() << std::endl;

         if (eq_->get_evolution().size() > 0) {
           std::cout << "Contenuto del primo giorno: " << eq_->get_condition_day(1) << std::endl;
         }
///////////////////////////////
         //std::cout<< " Il primo giorno è :" << eq_->get_condition_day(1)<<'\n';
         //eq_->set_initial_condition(people);

         input1 = true;
      } catch(std::runtime_error& e){
         if (!(std::string(e.what()) == "This simulation has already an initial condition, please start another simulation")){
          
          std::cout << "Error: " << e.what() << '\n';
          std::cout<<"  "<<'\n';
          std::cin.clear();  // Rimuove lo stato di errore
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << "Please correct your data, according to the error, and insert them in the same order"<<'\n';
          std::cin>> people;
         } else {
            std::cout<<"Error: "<< e.what()<<'\n';
            break;
         }
      
               it++;
                if(it == MAX_IT){
                     std::cout<<" The attempts are finished! "<<"\n\n";

                     //people ={{N*(1-0.25),0},{N*0.25},0,0};
                       break;
                  }
         
      }
      
             
      }
   
       eq_->add_count(eq_->calculate());
       char duration_;
       std::cout<<" Do you want to evolve the simulation AUTOMATICALLY until the infected people are finished ['A'] or to CHOOSE the number of days ['C']?"<<'\n';
       std::cin>> duration_;
       while (duration_ != 'A' && duration_ != 'C')
       {
        std::cout<< "Please, insert 'A' or 'C' "<<'\n';
        std::cin>> duration_;
       }
      if ( duration_ == 'A')
       {
         int t = 1;
         it = 0;
         MAX_IT = 1 ;
         /////////////////Simulation started//////////////////////
         while ( !eq_->terminate())//continue until there are infected people
         {  
             std::cout<<"Day N° :"<< t <<"\n\n";
             std::cout<< "====================="<<"\n\n";
             std::cout<< eq_->get_condition_day(t)<<'\n';
             std::cout<< "====================="<<"\n\n";
             eq_->Print(t);
            
             if (sum(eq_->get_evolution().back().I_) == 0){
               it++;
                if(it == MAX_IT){
                     std::cout<<" Simulation terminated !"<<"\n\n";
                       break;
                  }
             }
             eq_->evolve();
              t++;
               std::this_thread::sleep_for(std::chrono::milliseconds(1000));    
         }

          it = 0;
       char comparison2;
       MAX_IT = 5;
       std::cout<<"Would you be interested to observe the difference between the last simulation and another with the option to get vaccinated?[y/n]"<<'\n';
      
        while(!( std::cin>>comparison2)||(comparison2 != 'y' && comparison2 != 'n')){
            std::cout<< "Please, insert 'y', for yes, or 'n', for no"<<'\n';
            std::cin.clear();  // Rimuove lo stato di errore
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// svuota il buffer
            it++;
            if(it == MAX_IT){
               std::cout<<" The attempts are finished! Let's continue with the comparison"<<"\n\n";
               comparison2 = 'y';
                  break;
            }
         }
        
        if(comparison2 == 'y'){
        std::cout<<"Great!Let's start another simulation! The initial conditions are the same."<<'\n';
        Equation eq_vp(*eq_);
        //eq_vp.set_initial_condition({{2000,0},{500,0},0,0});
        float prob_v;
        std::cout<<"Insert the probability of getting vaccinated"<<'\n';
        std::cin>> prob_v;
        bool input_v = false;
        it = 0;
        std::cout<<" Il numero dei giorni : "<< eq_vp.get_days()<<'\n';
      
        while (!input_v)
        {
           try{
          eq_vp.introduce_vacc(prob_v);
          input_v = true;
          } catch(std::runtime_error& e){
         std::cout << "Error: " << e.what() << '\n';
         std::cout<<"  "<<'\n';
         std::cout << "Please correct your data, according to the error, and insert them in the same order"<< '\n';
         std::cin.clear();  // Rimuove lo stato di errore
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// svuota il buffer
         std::cin>> prob_v;
         it++;
          if(it == MAX_IT){
                     std::cout<<"The attempts are finished! The probability of getting vaccinated is 65%"<<"\n\n";
                     prob_v = 0.65;
                       break;
                  }
          }
        }
        eq_vp.change_after_vacc();
         std::cout<<"For the vaccinated people the probability have changed : "<<'\n';
               std::cout<< "beta :"<< eq_vp.get_Parameters().beta[1] <<'\n'<< "omega :" << eq_vp.get_Parameters().omega[1] <<'\n' << "gamma :"<< eq_vp.get_Parameters().gamma[1]<<"\n\n";   
               std::cout<< "==========================================================================="<<"\n\n";
      
        eq_vp.sorting();
        std::cout << eq_vp.get_condition_day(1);
        MAX_IT = 1;
        int tt = 1;
        it = 0;
           while (!eq_vp.terminate())//continue until they are infected people
         {  
             
             std::cout<< "Day N° :" << tt <<"\n\n";
             std::cout<<eq_vp.get_condition_day(tt)<<'\n';
             eq_vp.Print(tt);
             

              if (sum(eq_vp.get_evolution().back().I_) == 0){
               it++;
                if(it == MAX_IT){
                     std::cout<<" Simulation terminated !"<<"\n\n";
                       break;
                  }
              }
              eq_vp.evolve_vaccine();
              tt++;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));    
         }
       std::cout<<"////////////////////////////////////////////////"<<"\n\n";
       std::cout<<"| Simulation without vaccine |" <<"\n\n";
       std::cout<<" Numbers of days :" << eq_->get_days()<<'\n';
       eq_->Print(t);
       std::cout<< "| Simulation with vaccine |" <<"\n\n";
       std::cout<<" Numbers of days :" << eq_vp.get_days()<<'\n';
       eq_vp.Print(tt); 

       } 
       }else 
          {//number of days
            int T;
            std::cout<< " For how many days do you want your simulation to last?"<< '\n';
            std::cin>> T;
         
            std::cout<< "Ok ! Let's get started ! "<<'\n';
            ////////////////Simulation started//////////////////////
            int t;
            MAX_IT = 1;
            for( t = 1 ; t <= T; t++)
            {
              
            //eq_->update_situation(0,next);
             //std::cout<<"Somma delle persone "<< sum()<< '\n';
             //eq_->add_data(next);
             std::cout<<"Day N° :"<< t<<"\n\n";
             std::cout<< "====================="<<"\n\n";
             eq_->Print(t);

              eq_->evolve();
               std::this_thread::sleep_for(std::chrono::milliseconds(1000)); 
                 if (sum(eq_->get_evolution().back().I_) == 0){
               it++;
                if(it == MAX_IT){
                     std::cout<<" There aren't infected people left !"<<"\n\n";
                       break;
                  }
             }   
                
            }
          
            if(sum(eq_->get_evolution().back().I_)>0){
            char finish;
             std::cout<<" Do you want to finish the simulation?[y/n]"<<'\n';
             std::cin>> finish;
             while (finish!= 'y' && finish != 'n')
             {
               std::cout<< "Please, insert 'y' or 'n' "<<'\n';
               std::cin>> finish;
               ///////////pulizia//////////////
             }
             if(finish == 'y'){
             
             float vaccine;
             std::cout<<"Insert the probability to get vaccinated [0,1], if you want the option, otherwise just insert 0, please"<< '\n';
             std::cin>> vaccine;
          
             
              if(vaccine != 0) 
             {
               //int tt = 1;
               bool input_v2 = false;
               while(!input_v2){
                try{
                  eq_->introduce_vacc(vaccine);
                  input_v2 = true;
                } catch(std::runtime_error& e){
                  std::cout << "Error: " << e.what() <<"\n\n";
                  std::cout << "Please correct your data, according to the error, and insert them in the same order"<< '\n';
                  std::cin.clear();  // Rimuove lo stato di errore
                  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// svuota il buffer
                  std::cin>> vaccine;
                 it++;
                  if(it == MAX_IT){
                     std::cout<<"The attempts are finished! The probability of getting vaccinated is 74%"<<"\n\n";
                     vaccine = 0.74;
                       break;
                  }
                }
               
               }
          
              //////////Modifying the probabilities/////////
               eq_->change_after_vacc();
               std::cout<<"For the vaccinated people the probability have changed : "<<'\n';
               std::cout<< "beta :"<< eq_->get_Parameters().beta[1] <<'\n'<< "omega :" << eq_->get_Parameters().omega[1] <<'\n' << "gamma :"<< eq_->get_Parameters().gamma[1]<<"\n\n";   
               std::cout<< "==========================================================================="<<"\n\n";
               ///////Getting vaccinated////////////
               eq_->sorting();
               it = 0;
               while(!eq_->terminate())
               {    
               
               //People per{{0,0},{0,0},0,0};
                //std::array<float,6> arr_per0 = eq_->update_situation(0,per);
                //std::array<float,6> arr_per = eq_->update_situation(1,eq_->fix(arr_per0));

                std::cout<<"Day N° :"<< t<<"\n\n";
                /*std::cout<< arr_per[0]<<"||"<< arr_per0[0]<<'\n';   
                std::cout<< arr_per[1]<<"||"<<arr_per0[1]<<'\n';    
                std::cout<< arr_per[2]<<"||"<<arr_per0[2]<<'\n';    
                std::cout<< arr_per[3]<<"||"<<arr_per0[3]<<'\n';    
                std::cout<< arr_per[4]<<"||"<<arr_per0[4]<<'\n';    
                std::cout<< arr_per[5]<<"||"<<arr_per0[5]<<'\n'; */
                //eq_->add_data(eq_->fix(arr_per)) ;  
                std::cout<< "Confronto:"<< eq_->get_number_population() <<" = "<< sum(transform_arr<int,6>(eq_->get_condition_day(t)))<<"\n\n";
            
               std::cout<< "====================="<<"\n\n";
               std::cout<<eq_->get_condition_day(t);
               std::cout<< "====================="<<"\n\n";
               eq_->Print(t);
               
               if (sum(eq_->get_evolution().back().I_) == 0){
               it++;
               MAX_IT = 1;
                if(it == MAX_IT){
                     std::cout<<" Simulation terminated !"<<"\n\n";
                       break;
                  }
             }
             /////evolving////
             eq_->evolve_vaccine();
             /////Increasing day counter///////
              t++;
            
              std::this_thread::sleep_for(std::chrono::milliseconds(1000));
               }
               
             } else {
   
     
         it = 0;
         while(!eq_->terminate())
               {       
             
               std::cout<<"Day N° :"<< t<<"\n\n";
               std::cout<< "====================="<<"\n\n";
               std::cout<<eq_->get_condition_day(t);
               std::cout<< "====================="<<"\n\n";
               eq_->Print(t);
             
               if (sum(eq_->get_evolution().back().I_) == 0){
               it++;
                if(it == MAX_IT){
                     std::cout<<" Simulation terminated !"<<"\n\n";
                       break;
                  }
               }
             /////evolving////
                 eq_->evolve();
           /////Increasing day counter///////
                t++;
          std::this_thread::sleep_for(std::chrono::milliseconds(1000));
               }
              
          } 
        } else {
          std::cout<< "Alright, thank you for your time! Here below, you'll find the results of your simulation"<<'\n';
          std::cout<<"| Simulation without vaccine |" <<'\n';
          std::cout<<" ____________________________" <<'\n';
          std::cout<<" Numbers of days :" << eq_->get_days();
          std::cout<< "====================="<<"\n\n";
          eq_->Print(t);
          }
             }
            } 
           
         
       
      std::cout<<"The critical threshold is equal to "<< eq_->calculate_R0(eq_->get_Parameters())<<'\n';
      std::cout<<"Number of days : " << eq_->get_days()<<"\n\n";
     }


    return 0;
}




