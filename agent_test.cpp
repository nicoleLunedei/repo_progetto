#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "agent.hpp"


#include <memory>
void check_state (Agent& a){

Matrix<Person> previous(a.get_matrix());
CHECK(previous == a.get_matrix());
People next{{0,0},{0,0},0,0};
a.evolve(next);
bool state ;
a.get_matrix().inside_matrix([previous, &state](Person& cell, std::size_t r, std::size_t c){
  ////////////Checking each cell///////////////
  switch (previous.read(r,c))
  {
  case Person::Susceptible:

    state = (cell == Person::Susceptible || cell == Person::Infected); 
    break;
  case Person::Susceptible_v:
    state = (cell == Person::Susceptible_v || cell == Person::Infected_v);
    break;
     case Person::Infected:
    state =(cell == Person::Healed || cell == Person::Dead || cell == Person::Infected );
     break;
  case Person::Infected_v:
      state = (cell == Person::Healed || cell == Person::Dead || cell == Person::Infected_v );
    break;
  case Person::Healed:
     ////costant state///////
     break;
    case Person::Dead:
     ////costant state///////
     break;

  }
    CHECK(state);
}
  
);
}
  
TEST_CASE("Agent Class"){
  std::unique_ptr<Agent> ag0 = std::make_unique<Agent>();

    
    SUBCASE("Constructors"){
     
        SUBCASE("Default"){
         
            CHECK(ag0->get_side() == 50);
            CHECK(ag0->get_matrix().M[0].size() == 50);

            CHECK(ag0->get_Parameters().beta[0] ==0.6);
            CHECK(ag0->get_Parameters().beta[1] ==0.);
            CHECK(ag0->get_Parameters().gamma[0] ==0.2);
            CHECK(ag0->get_Parameters().gamma[1] ==0.);
            CHECK(ag0->get_Parameters().omega[0] ==0.35);
            CHECK(ag0->get_Parameters().omega[1] ==0.);
            CHECK(ag0->get_Parameters().vax ==0.);


            CHECK(ag0->get_situation_day(1).S_[0] == 2499);
            CHECK(ag0->get_situation_day(1).S_[1] == 0);
            CHECK(ag0->get_situation_day(1).I_[0] == 1);
            CHECK(ag0->get_situation_day(1).I_[1] == 0);

            ag0->get_matrix().inside_matrix([&ag0](Person& cell, std::size_t r, std::size_t c){ 
                 if (r == (ag0->get_matrix().M.size())/2 && c == ag0->get_matrix().M.size()/2){
                 CHECK(cell == Person::Infected);
                 } else{
                   CHECK(cell == Person::Susceptible); 
                 }
        });
        
    }
    SUBCASE("Parametric"){
    std::vector<People> pop;
    Parameters par{{0.6,0.},{0.25, 0.},{0.3, 0.},0.};

     
    CHECK_THROWS_AS(Agent ag1(pop,par,10011), std::runtime_error );
    CHECK_THROWS_WITH(Agent ag1(pop,par,10011),"The number of the population must a perfect square");
    

    std::unique_ptr<Agent> ag1 = std::make_unique<Agent>(pop,par,400);
   
            CHECK(ag1->get_side() == 20);
            CHECK(ag1->get_matrix().M[0].size() == 20);

            CHECK(ag1->get_Parameters().beta[0] ==0.6);
            CHECK(ag1->get_Parameters().beta[1] ==0.);
            CHECK(ag1->get_Parameters().gamma[0] ==0.25);
            CHECK(ag1->get_Parameters().gamma[1] ==0.);
            CHECK(ag1->get_Parameters().omega[0] ==0.3);
            CHECK(ag1->get_Parameters().omega[1] ==0.);
            CHECK(ag1->get_Parameters().vax ==0.);
            
             ag1->get_matrix().each_cell([&ag1](Person& cell){ 
            
                   CHECK(cell == Person::Susceptible); 
                 
            });
            SUBCASE("Member Functions"){
          ////////////////Draw_matrix with the initial condition/////////////////////
            People begin{{390,0},{10,0},0,0};
            //////////First day///////////////
            ag1->draw_matrix(begin);
            
            ////////////////collection_data/////////////////
            /////////Second day//////////////
            People blank{{0,0},{0,0},0,0};
            ag1->data_collection(blank);
            
           
            CHECK(ag1->get_days() == 2);

           
            ////////////////Testing counting/////////////
            CHECK(blank. S_[0] == 390);
            CHECK(blank. S_[1] == 0 );
            CHECK(blank. I_[0] == 10);
            CHECK(blank. I_[1] == 0);
            CHECK(blank.H_ == 0);
            CHECK(blank. D_ == 0);
        ///////////Printing matrix///////////
     std::cout<<"Matrix :"<<'\n';
     std::cout<<ag1->get_matrix();
     
    ////////Checking on toroidale structure/////////
   ///////////////Show_cell////////////////////////
    CHECK(ag1->show_cell(0,0) == ag1->show_cell(0,100));
    CHECK(ag1->show_cell(100,100) == ag1->show_cell(100,0));


  ////////////////sorting/////////////////////////
    ag1->introduce_vacc(0.4);
    ag1->sorting();
    std::cout<< "Somma dei suscettibili:"<<sum(ag1->get_evolution().back().S_)<<'\n';
    std::cout<< "I non vaccinati :"<< ag1->get_evolution().back().S_[0]<<'\n';
    std::cout<< "I vaccinati :"<< ag1->get_evolution().back().S_[1]<<'\n';
    CHECK(static_cast<double>(ag1->get_situation_day(2).S_[0])/(sum(ag1->get_situation_day(2).S_)) == doctest::Approx(0.6).epsilon(0.1));
    CHECK(static_cast<double>(ag1->get_situation_day(2).S_[1])/(sum(ag1->get_situation_day(2).S_)) == doctest::Approx(0.4).epsilon(0.1));
    std::cout<<"Matrix, dopo il vaccino:"<<'\n';
     std::cout<<ag1->get_matrix();
////////////////infected_neighbours/////////////
   People n{{0,0},{0,0},0,0};
   ag1->evolve(n);
   std::cout<<"Infected neighbours:"<<'\n';
   ag1->get_matrix().inside_matrix([&ag1](Person& cell, std::size_t r, std::size_t c){

    if (cell == Person::Susceptible || cell == Person::Susceptible_v ){
     CHECK(ag1->infected_neighbours(r,c) <= 8 );
     std::cout<< ag1->infected_neighbours(r,c) << "|";
    }
   }

   );
    std::cout<<"\n\n";
 ///////////////change_state & evolve/////////////////////
 ////////////////#1////////////////////
  check_state(*ag1);
std:: cout<< "Matrix dopo l'evoluzione"<<'\n';
std::cout << ag1->get_matrix()<<"\n\n";
  CHECK(ag1->get_days() == 4);
/////////////////#2/////////////////////
  check_state(*ag1);
  
  CHECK(ag1->get_days() == 5);

       SUBCASE("Copy Constructor"){
      
      std::unique_ptr<Agent> copy_ag1 = std::make_unique<Agent>(ag1);
      CHECK(copy_ag1->get_number_population() == ag1->get_number_population());
      CHECK(copy_ag1->get_Parameters() == ag1->get_Parameters());
      CHECK(copy_ag1->get_situation_day(1) == ag1->get_situation_day(1) );
      CHECK(copy_ag1->get_days() == 1);

         }

      }
      
    } 
         
  }
     
   
}
