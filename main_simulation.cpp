#include "pandemic.hpp"
#include "equation.hpp"
#include "agent.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

void corrispondence_sfml(Matrix<Person>& associate, sf::RenderWindow& window){
    associate.inside_matrix([&window](Person& cell, int r, int c){
        
            sf::CircleShape circle;
            circle.setRadius(10.f); 

            circle.setPosition( 100.f + c * 20.f, 150.f + r * 20.f);

               switch(cell){

                case (Person::Susceptible) : {
                    circle.setFillColor(sf::Color::Green);
                       window.draw(circle);
                    break;
                }
                case ( Person::Susceptible_v ):{
                    circle.setFillColor(sf::Color::Green);
                       window.draw(circle);
                    break; 
                }
                case (Person::Infected ) : {
                    circle.setFillColor(sf::Color::Red);
                       window.draw(circle);
                    break;
                }
                case( Person::Infected_v ): {
                    circle.setFillColor(sf::Color::Red);
                       window.draw(circle);
                    break;
                }
                case (Person::Healed ) : {
                    circle.setFillColor(sf::Color::Blue);
                       window.draw(circle);
                    break;
                }
                case (Person::Dead) : {
                    circle.setFillColor(sf::Color::Magenta);
                       window.draw(circle);
                    break;
                }
               }
    });
}
int main() {
    //Vuoi simulare con dei dati standard ?[Y/N]
    char sim;
    int T;
    std::cout<< "Hi! Do you want to run a default[D] or a personalized[P] simulation?[D/P]"<< '\n';
    std::cin>> sim;

    while (sim != 'D' || sim != 'P' )
     {
        std::cout << "Please insert D, for default, or P , for personalized "<< '\n';
        std::cin>> sim;
     }
    std::cout<< "For how many days do you want your simulation to last?"<< '\n';
    std::cin>> T;

    if (sim == 'D'){
       //simulazione by default
       std::shared_ptr<Pandemic> pan = std::make_shared<Equation>();
       std::shared_ptr<Equation> eq = std::dynamic_pointer_cast<Equation>(pan);

       std::cout<< " Great! You've chosen the default simulation, here below some data :" << '\n';
       std::cout<< " The population corrisponds to " << pan->get_number_population() << " people"<< '\n';
       std::cout<< " Susceptible =  " << pan->get_condition_day(1).S_[0] << " || "<< " Infected = " <<  pan->get_condition_day(1).I_[0] ;
       std::cout<< " Healed = 0 || Dead = 0 " << '\n';
       std::cout<< " Probability to infect is " << pan->get_Parameters().beta[0] * 100 << "%";
       std::cout<< ", Probability of healing is  " << pan->get_Parameters().gamma[0] * 100 << "%";
       std::cout<< ",Probability of dying is " << pan->get_Parameters().omega[0] * 100 << "%";
       std::cout<< " and to get vaccination, initially is null, later you'll have the chance to introduce it." << '\n';
       std::cout<< "Ok ! Let's get started ! "<<'\n';

     } else {//sim == 'P'
       //simulazione personalizzata
       int N;
       Parameters prob;
       People people;
       std::vector<People> days; 
       std::vector<std::array<int, 4>> count;

       std::cout<< " Awesome! You've chosen the personalized simulation! Now please insert your data" << '\n';
       std::cout<< " Number population " << '\n';
       std::cin>> N;
       std::cout<< " With how many Susceptible people doyou want to start " << '\n';
       std::cin>> people.S_[0];
       std::cout<< " and with how many Infected people " << '\n';
       std::cin>> people.I_[0];
       std::cout<< "Probability to infect [0,1]" << '\n';
       std::cin>>prob.beta[0];
       std::cout<< "Probability of healing [0,1] " <<'\n';
       std::cin>>prob.gamma[0];
       std::cout<< "Probability of dying [0,1] " << '\n';
       std::cin>>prob.omega[0];
       std::cout<< " and the probability of getting vaccination, initially must be null, later you'll have the chance to introduce it." << '\n';
       std::cout<< "Ok ! Let's get started ! "<<'\n';

       try { 
       
       std::shared_ptr<Pandemic> pan_ = std::make_shared<Equation>(days,prob,N,count);
       std::shared_ptr<Equation> eq_ = std::dynamic_pointer_cast<Equation>(pan_);
    } catch (){}

      
       pan_->set_initial_condition(people);
       
       std::array<int,4> c{0,0,0,0};
       eq_->add_count(eq_->calculate(1,c));
       
     }
    // allocazione delle varibili di cui ho bisogno
       //di quali variabili ho bisogno ?=> Ricorda il numero dei giorni
    
    //salutare e introdurre in quali modalità può simulare la pandemia 
       //Logica e prevenzione 
    //richiesta dei parametri di probabilità e dei numeri iniziali della popolazione: informare dei range ammessi
    
    
    
    //gestione dei parametri input try and catch
      //probabilità try and catch multipli
      //People t & c multipli
      //Controlli sulle giornate
      //Controllo rispetto R0
    //Ti piacerebbe vedere il confronto con gli stessi numeri con vaccino e senza vaccino?
      // stampa dei valori alla fine della simulazione, ed evidenziare le differenze tramite la differenza aritmetica o la percentuale 


    return 0;
}