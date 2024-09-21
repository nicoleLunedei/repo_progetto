#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <memory>
#include "doctest.h"
#include "pandemic.hpp"
#include "equation.hpp"
TEST_CASE("Equation Class"){
 
    SUBCASE("Contructors"){
    
        SUBCASE("Default")
        {
         Parameters p {{0.5, 0.0},{0.6, 0.0} ,{0.4, 0.0} , 0.0 };
         People sub {{1999999,0},{1,0}, 0, 0};
         
         //Pandemic* pan = new Equation();// sto utilizzando un puntatore pandemic, che è la mia interfaccai comune 
         //Equation* eq = dynamic_cast<Equation*>(pan);//questo mi restituisce un puntatore del tipo equation a partire da quello di pandemic, per accedere ai metodi specifici di equation
          std::shared_ptr<Pandemic> pan = std::make_shared<Equation>();//smart pointer che condivide ala ownership dell'oggetto che punta, OCCHIO PERò!!!!!!!
          std::shared_ptr<Equation> eq = std::dynamic_pointer_cast<Equation>(pan);//è come dynamic_cast(puntatore grezzo (T*)) che restituisce un puntatore grezzo, mentre dynamic pointer cast (puntatori intelligenti(T))
          if (eq){
             CHECK(eq->get_Parameters() == p); 
             CHECK(eq->get_number_population() == 2000000);
             CHECK(eq->get_condition_day(1) == sub);
             std::array<int,4> vec_c;
             eq->add_count(eq->calculate(1,vec_c));//fa il conteggio della comdizione del primo giorno e lo aggiunge direttamente
             
             CHECK(eq->get_counting(1)[0] == 1999999 );
             CHECK(eq->get_counting(1)[1] == 1 );
             CHECK(eq->get_counting(1)[2] == 0);
             CHECK(eq->get_counting(1)[3] == 0);
            ////////////////potrei doverlo spostare questo 

             std::array<int,4> vec_b;
             People sub_1{{300000,200000},{200000,300000},0,0};
             pan->add_data(sub_1);

             CHECK(eq->get_condition_day(2).S_[0] == 300000);
             CHECK(eq->get_condition_day(2).S_[1] == 200000);
             CHECK(eq->get_condition_day(2).I_[0] == 200000);
             CHECK(eq->get_condition_day(2).I_[1] == 300000);
             CHECK(eq->get_condition_day(2).H_ == 0);
             CHECK(eq->get_condition_day(2).D_ == 0);

             eq->add_count(eq->calculate(2, vec_b));
             
             CHECK(eq->get_counting(2)[0] == 500000 );
             CHECK(eq->get_counting(2)[1] == 500000 );
             CHECK(eq->get_counting(2)[2] == 0);
             CHECK(eq->get_counting(2)[3] == 0);
          
          CHECK_THROWS_AS(eq->calculate(0,vec_b), std::out_of_range);
          CHECK_THROWS_WITH(eq->calculate(0,vec_b), "Invalid day number!");

             

          } else {
            std::cout << "Failed Cast !" << std::endl;
          }
          //serve un solo delete perchèpuntano alla stessa regione di memoria dinamica quindi ne basta uno
          
        }

        SUBCASE("Parametric"){}
    }
   /*SUBCASE(" Equation Members"){
         SUBCASE(){}
    SUBCASE(){}
        SUBCASE(){}cert
    SUBCASE(){}*/ 

    }
 

    
   

/*TEST_CASE("Agent Class"){

}*/
