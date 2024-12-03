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
   ////////////////Cleaning the in stream//////////////////
         std::cin.clear();
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   //////////////////Iteration cycle ///////////////////////
        it++;
        if(it == MAX_IT){
         std::cout<<" The attempts are finished! It'll start the default simulation"<<"\n\n";
         sim = 'D';
         break;
        }
     }
    it = 0;
    
  

    if (sim == 'D'){
  /////////////////////////Default simulation/////////////////
      std::unique_ptr<Equation>  eq = std::make_unique<Equation>();
     
       std::cout<< " Great! You've chosen the default simulation, here below some data :" << '\n';
       std::cout<< " The population corrisponds to " << eq->get_number_population() << " people"<< '\n';
       std::cout<< "Situation of the firt day :"<<'\n';
       eq->Print(1);
       std::cout<< " Note the following probabilities are refering to what happends in one day  "<<"\n\n";
       std::cout<< " Probability to infect : " << eq->get_Parameters().beta[0] * 100 << "%"<<'\n';
       std::cout<< " Probability of healing : " << eq->get_Parameters().gamma[0] * 100 << "%"<<'\n';
       std::cout<< " Probability of dying : " << eq->get_Parameters().omega[0] * 100 << "%"<<'\n';
       std::cout<< " Probability to get vaccinated, initially is null, later you'll have the chance to introduce it." << '\n';
       
      ////////////////////////Intentional start //////////////////// 
       char start;
       std::cout<< "Ok ! Let's start, are you ready?[y/n]"<<'\n';
      
        while(!(std::cin>>start)||(start != 'y' && start!= 'n')){
           
            std::cout<< "Please, insert 'y', for yes, or 'n', for no"<<'\n';
      //////////Cleaning the in stream///////////////
            //std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          
          if(it == MAX_IT){
            std::cout<<" The attempts are finished! The simulation will start"<<"\n\n";
            start = 'y';
             break;
            }
         }

        ///////////////////////////////////////////////////////////////////////////
        MAX_IT = 1;
      if (start =='y'){
         int t = 1 ;
///////////////Automatic evoluation//////////////////// 
       while (!eq->terminate())
         {  
          
             std::cout<<"Day N° :"<< t <<"\n\n";
             eq->Print(t);
             
             if (sum(eq->get_evolution().back().I_) == 0){
               it++;
                if(it == MAX_IT){
                     std::cout<<" Simulation terminated !"<<"\n\n";
                       break;
                  }
             }
              eq->evolve(); 
                  /////Increasing day counter///////
              t++;
  ////////////////Imposing a delay//////////////////// 
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));    
         }
  //////////////Chance of comparison with a simulation with vaccine//////////////// 
         it = 0;
       char comparison;
       MAX_IT = 5;
       std::cout<<"Would you be interested to observe the difference between the last simulation and another with the option to get vaccinated?[y/n]"<<'\n';
      
        while((comparison != 'y' && comparison != 'n')){

            std::cout<< "Please, insert 'y', for yes, or 'n', for no"<<'\n';
            std::cin>> comparison;
  /////////////////Cleaning the in stream///////////////////////////
            //std::cin.clear();  
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            it++;
            if(it == MAX_IT){
               std::cout<<" The attempts are finished! Let's continue with the comparison"<<"\n\n";
               comparison = 'y';
                  break;
            }
         }
      
        if(comparison == 'y'){

        std::cout<<"Great! Let's start another simulation! The initial conditions are the same."<<'\n';
        Equation eq_v;
  ////////////Probability of getting vaccinated///////////////
        double prob_v;

        std::cout<<"Insert the probability of getting vaccinated"<<'\n';
        std::cin>> prob_v;

        bool input_v = false;
        it = 0;
      
        while (!input_v)
        {
           try{

          eq_v.introduce_vacc(prob_v);
          input_v = true;

          } catch(std::runtime_error& e){

         std::cout << "Error: " << e.what() << "\n\n";
         std::cout << "Please correct your data, according to the error, and insert them in the same order"<< '\n';
  ////////////////////Cleaning the in stream////////////////////
         std::cin.clear();  
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

         std::cin>> prob_v;
         it++;
  //////////////////MAX_IT == 5///////////////////////
          if(it == MAX_IT){
                     std::cout<<"The attempts are finished! The probability of getting vaccinated is 65%"<<"\n\n";
                     prob_v = 0.65;
                       break;
                  }
          }
        }
  ///////////////Modifying the probability for the vaccinated people/////////////////
        eq_v.change_after_vacc();
         std::cout<<"For the vaccinated people the values of the probabilities are : "<<'\n';
               std::cout<< "beta :"<< eq_v.get_Parameters().beta[1] <<'\n'<< "omega :" << eq_v.get_Parameters().omega[1] <<'\n' << "gamma :"<< eq_v.get_Parameters().gamma[1]<<"\n\n";   
               std::cout<< "==========================================================================="<<"\n\n";
         std::cout<< "Situation of the firt day :"<<'\n';
        std::cout << eq_v.get_situation_day(1);
        eq_v.sorting();
        MAX_IT = 1;
        int tt = 1;
        it = 0;
/////////////////Automatic evolution/////////////////////
           while (!eq_v.terminate())
         {  
             
             std::cout<< "Day N° :" << tt <<"\n\n";
             std::cout<<eq_v.get_situation_day(tt)<<'\n';

             std::cout<< "Total counting :" <<"\n\n";
             eq_v.Print(tt);
             

              if (sum(eq_v.get_evolution().back().I_) == 0){
               it++;
//////////////////MAX_IT == 1//////////////////////////
                if(it == MAX_IT){
                     std::cout<<" Simulation terminated !"<<"\n\n";
                       break;
                  }
              }
              eq_v.evolve_vaccine();
                  /////Increasing day counter///////
              tt++;
////////////////////Imposing a delay////////////////////////
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));    
         }

       std::cout<<"//////////// COMPARISON //////////////////////"<<"\n\n";

       std::cout<< "| Simulation with vaccine |" <<"\n\n";
       std::cout<<" Numbers of days :" << eq_v.get_days()<<'\n';
       std::cout<< "Total counting :" <<"\n\n";
       eq_v.Print(tt);
        } else {

         std::cout<<"Alright, thank you for your time! Below here there are the results of your simulation"<<'\n';
        }

       std::cout<<"| Simulation without vaccine |" <<"\n\n";
       std::cout<<"The critical threshold is equal to " << eq->calculate_R0(eq->get_Parameters())<<'\n';
       std::cout<<" Numbers of days :" << eq->get_days()<<'\n';
       std::cout<< "Total counting :" <<"\n\n";
       eq->Print(t);
      
} else {
        std::cout<< "Alright! See you next time!"<< '\n';
      }
     
      

     } else {
///////////////////////Personalized simulation////////////////////////////
       int N;
       Parameters prob;
       People people;
       std::vector<People> days; 
    
       
       std::cout<< " Awesome! You've chosen the personalized simulation! Now please insert your data" << "\n\n";
       std::cout<< " Number population (please at least 100 )" << '\n';
       std::cin>> N;
       
       if (N < 100){
         char change;
         std::cout<<"You're number population is quite small, do you want to change ?[y/n]"<<'\n';
         std::cin>>change;
       
         while(change != 'y' && change != 'n'){
          ///////////////////Cleaning the out strem////////////////
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
       std::cout<< "Probability of dying [0,1] " <<'\n';
       std::cin>>prob.omega[0];
       std::cout<< "\n\n";
/////////////////////Creating the equation object by using a smart pointer /////////////////////////
      std::unique_ptr<Equation> eq_ = nullptr;
       bool input0 = false;
       it = 0;
       while(!input0){
///////////////////////////Handling ecceptions ////////////////////
////////////////////////#1//////////////////////////
       try{
       
        eq_ = std::make_unique<Equation>(days,prob,N);
       
       input0 = true;
    
    } catch (std::runtime_error& e){
     
        std::cout<<"Error :"<<e.what()<<"\n\n";
        //////////////Cleaning the in stream//////////
        std::cin.clear();  // Remove the error state on the in stream
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Please correct your data, according to the error"<< '\n';

        if (!(std::string(e.what()) == "The simulation with the vaccine can't start if the critical threshold is minor than one! ")){
         std::cout <<"Number of population"<<'\n';
         std::cin>> N;
        }else{
         std::cout << "R_0 : "<<eq_->calculate_R0(prob) << "\n\n";
        }
 
        std::cout <<"The probabilities, in the previous order"<<'\n';
        std::cin>> prob.beta[0] >> prob.gamma[0] >> prob.omega[0];
       }
      MAX_IT = 5;
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

    std::cout<<"Now insert the condition of the first day you want to begin with."<<"\n\n";
    std::cout<<"In order : Susceptiple, Infected, Healed and Dead (the last two must be null)"<<'\n';
    std::cin >> people;
   
       bool input1 = false;
       it = 0;
      while(!input1){
      try{
         ///////////////////////
        
         eq_->set_initial_condition(people);  
      
         if (eq_->get_evolution().size() > 0) {
           std::cout << "Ok! Situation of the first day :" <<'\n';
           std::cout<< eq_->get_situation_day(1) << "\n\n";
         }
         ///////////////////////////////
    
         input1 = true;
      } catch(std::runtime_error& e){
         if (!(std::string(e.what()) == "This simulation has already an initial condition, please start another simulation")){
          
          std::cout << "Error: " << e.what() << "\n\n";
          ////////////////////Cleaning the in stream//////////////
          std::cin.clear();  // Remove the error state on the in stream
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

                     people = {{1,0},{1,0},0,0};
                       break;
                  }
         
      }
      
             
      }
   
       char duration_;
       std::cout<<" Do you want to evolve the simulation AUTOMATICALLY until the infected people are finished ['A'] or to CHOOSE the number of days ['C']?"<<'\n';
       std::cin>> duration_;
       while (duration_ != 'A' && duration_ != 'C')
       {
        ////////////////Cleaning the in stream//////////////
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout<< "Please, insert 'A' or 'C' "<<'\n';
        std::cin>> duration_;
       }
      if ( duration_ == 'A')
       {
    ///////////////////////Automatic simulation/////////////////////
         int t = 1;
         it = 0;
         MAX_IT = 1 ;
       
         while ( !eq_->terminate())
         {  
             std::cout<<"Day N° :"<< t <<"\n\n";
             std::cout<< "====================="<<"\n\n";
             std::cout<< eq_->get_situation_day(t)<<'\n';
             std::cout<< "====================="<<"\n\n";
             std::cout<< "Total Counting :"<<'\n';
             eq_->Print(t);
            
             if (sum(eq_->get_evolution().back().I_) == 0){
               it++;
                if(it == MAX_IT){
                     std::cout<<" Simulation terminated !"<<"\n\n";
                       break;
                  }
             }
             eq_->evolve();
                 /////Increasing day counter///////
              t++;
  ////////////////Imposing a delay//////////////////
               std::this_thread::sleep_for(std::chrono::milliseconds(1000));    
         }

          it = 0;
       char comparison2;
       MAX_IT = 5;
std::cout<<"Would you be interested to observe the difference between the last simulation and another with the option to get vaccinated?[y/n]"<<'\n';
      
        while(!( std::cin>>comparison2)||(comparison2 != 'y' && comparison2 != 'n')){
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
           
          std::cout<< "Please, insert 'y', for yes, or 'n', for no"<<'\n';
            it++;
//////////////////MAX_IT == 1//////////////////////////////
            if(it == MAX_IT){
               std::cout<<" The attempts are finished! Let's continue with the comparison"<<"\n\n";
               comparison2 = 'y';
                  break;
            }
         }
        
        if(comparison2 == 'y'){
        std::cout<<"Great!Let's start another simulation! The initial conditions are the same."<<'\n';
        std::unique_ptr<Equation> eq_vp = std::make_unique<Equation>(*eq_);
        
        double prob_v;
        std::cout<<"Insert the probability of getting vaccinated"<<'\n';
        std::cin>> prob_v;
        bool input_v = false;
        it = 0;
      
        while (!input_v)
        {
           try{
          eq_vp->introduce_vacc(prob_v);
          input_v = true;
          } catch(std::runtime_error& e){
         std::cout << "Error: " << e.what() <<"\n\n";
         std::cout << "Please correct your data, according to the error, and insert them in the same order"<< '\n';
/////////////////Cleaning the in stream/////////////////////////
         std::cin.clear();  // Remove the error state of the in stream
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

         std::cin>> prob_v;
        MAX_IT = 5;
         it++;
          if(it == MAX_IT){
                     std::cout<<"The attempts are finished! The probability of getting vaccinated is 65%"<<"\n\n";
                     prob_v = 0.65;
                       break;
                  }
          }
        }
        eq_vp->change_after_vacc();
         std::cout<<"For the vaccinated people the values of the probabilities are : "<<'\n';
               std::cout<< "beta :"<< eq_vp->get_Parameters().beta[1] <<'\n'<< "omega :" << eq_vp->get_Parameters().omega[1] <<'\n' << "gamma :"<< eq_vp->get_Parameters().gamma[1]<<"\n\n";   
               std::cout<< "==========================================================================="<<"\n\n";
      
        eq_vp->sorting();
        std::cout << eq_vp->get_situation_day(1);
        MAX_IT = 1;
        int tt = 1;
        it = 0;
           while (!eq_vp->terminate())
         {  
             
             std::cout<< "Day N° :" << tt <<"\n\n";
             std::cout<<eq_vp->get_situation_day(tt)<<'\n';
             std::cout<< "Total Counting : " <<'\n';
             eq_vp->Print(tt);
             

              if (sum(eq_vp->get_evolution().back().I_) == 0){
               it++;
                if(it == MAX_IT){
                     std::cout<<" Simulation terminated !"<<"\n\n";
                       break;
                  }
              }
              eq_vp->evolve_vaccine();
                  /////Increasing day counter///////
              tt++;
//////////////////////Imposing the daley//////////////////////////////
          std::this_thread::sleep_for(std::chrono::milliseconds(1000));    
         }
       std::cout<<"//////////////COMPARISON////////////////////////"<<"\n\n";
       std::cout<< "| Simulation with vaccine |" <<"\n\n";
       std::cout<<" Numbers of days :" << eq_vp->get_days()<<'\n';
       eq_vp->Print(tt); 

       } else {
         std::cout<<"Alright, thank you for your time! Below here there are the results of your simulation"<<'\n';
        }

       std::cout<<"| Simulation without vaccine |" <<"\n\n";
       std::cout<<" Numbers of days :" << eq_->get_days()<<'\n';
       eq_->Print(t);
       }////////////////////Automatic scope closed//////////////////////
       else {
  /////////////////Evolution with a choosen number of days///////////////
            int T;
            std::cout<< " For how many days do you want your simulation to last?"<< '\n';
            std::cin>> T;
         
            std::cout<< "Ok ! Let's get started ! "<<'\n';
            ////////////////Simulation started//////////////////////
            int t;
            MAX_IT = 1;
            for( t = 1 ; t <= T; t++)
            {
              
             std::cout<<"Day N° :"<< t<<"\n\n";
             std::cout<< "====================="<<"\n\n";
             std::cout<< "Total Counting : " <<'\n';
             eq_->Print(t);

              eq_->evolve();
      /////////////////Imposing a delay///////////////
               std::this_thread::sleep_for(std::chrono::milliseconds(1000));
          ////////////Emergency top///////////// 
                 if (sum(eq_->get_evolution().back().I_) == 0){
               it++;
                if(it == MAX_IT){
                     std::cout<<" There aren't infected people left !"<<"\n\n";
                       break;
                  }
             }   
                
            }
  /////////////////////Chance of introducing the vaccine option/////////////////////       
            if(sum(eq_->get_evolution().back().I_)>0){
            char finish;
             std::cout<<" Do you want to finish the simulation?[y/n]"<<'\n';
             std::cin>> finish;
             while (finish!= 'y' && finish != 'n')
             {
               std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
               std::cout<< "Please, insert 'y' or 'n' "<<'\n';
               std::cin>> finish;
            
             }
             if(finish == 'y'){
             
             double vaccine;
             std::cout<<"Insert the probability to get vaccinated [0,1], if you want the option, otherwise just insert 0, please"<< '\n';
             std::cin>> vaccine;
          
             
              if(vaccine != 0) 
             {
               bool input_v2 = false;
               while(!input_v2){
                try{
                  eq_->introduce_vacc(vaccine);
                  input_v2 = true;
                } catch(std::runtime_error& e){
                  std::cout << "Error: " << e.what() <<"\n\n";
                  std::cout << "Please correct your data, according to the error, and insert them in the same order"<< '\n';
      /////////////////Cleaning the in stream///////////
                  std::cin.clear();  // Remove the error state
                  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
              
               std::cout<<"Day N° :"<< t<<"\n\n";
               std::cout<< "====================="<<"\n\n";
               std::cout<<eq_->get_situation_day(t);
               std::cout<< "====================="<<"\n\n";
               std::cout<<" Total Countig :"<< '\n';
               eq_->Print(t);
               //////////////////Stop///////////////
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
       ///////////////////////Imposing a delay////////////////     
              std::this_thread::sleep_for(std::chrono::milliseconds(1000));
               }
               
             } else {
   
     
         it = 0;
         while(!eq_->terminate())
               {       
             
               std::cout<<"Day N° :"<< t<<"\n\n";
               std::cout<< "====================="<<"\n\n";
               std::cout<<eq_->get_situation_day(t);
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
          }
          std::cout<<"| Simulation Data|" <<'\n';
          std::cout<<" ____________________________" <<'\n';
          std::cout<<" Numbers of days :" << eq_->get_days();
          std::cout<< "====================="<<"\n\n";
          std::cout<< "Total Counting :"<<'\n';
          eq_->Print(t);
             }
        } 
       /////////////////////Chosen scope closed//////////////////    
         
       
      std::cout<<"The critical threshold is equal to "<< eq_->calculate_R0(eq_->get_Parameters())<<'\n';
    
     }
     ///////////////////Personalized scope closed/////////////////


    return 0;
}




