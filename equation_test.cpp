#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "equation.hpp"

#include <memory>

#include "doctest.h"
#include "pandemic.hpp"
TEST_CASE("Equation Class") {
  SUBCASE("Contructors") {
    Parameters p{{0.5, 0.0}, {0.6, 0.0}, {0.4, 0.0}, 0.0};
    People sub{{6399, 0}, {1, 0}, 0, 0};
    SUBCASE("Default") {
      // Pandemic* pan = new Equation();// sto utilizzando un puntatore
      // pandemic, che è la mia interfaccai comune Equation* eq =
      // dynamic_cast<Equation*>(pan);//questo mi restituisce un puntatore del
      // tipo equation a partire da quello di pandemic, per accedere ai metodi
      // specifici di equation
      std::shared_ptr<Pandemic> pan0 =std::make_shared<Equation>();  // smart pointer che condivide ala
                                         // ownership dell'oggetto che punta,
                                         // OCCHIO PERò!!!!!!!
      std::shared_ptr<Equation> eq0 = std::dynamic_pointer_cast<Equation>(pan0);  // è come dynamic_cast(puntatore grezzo (T*)) che restituisce
                  // un puntatore grezzo, mentre dynamic pointer cast (puntatori
                  // intelligenti(T))
      if (eq0) {
        CHECK(eq0->get_countdays().size() == 1);  // lui qua ha già un elemento quindi ha già fatto  il counting
        CHECK(eq0->get_days() == 1);
        CHECK(eq0->get_Parameters() == p);
        CHECK(eq0->get_number_population() == 6400);
        // CHECK(eq0->get_condition_day(1) == sub);
        CHECK(eq0->get_condition_day(1).S_[0] == 6399);
        CHECK(eq0->get_condition_day(1).S_[1] == 0);
        CHECK(eq0->get_condition_day(1).I_[0] == 1);
        CHECK(eq0->get_condition_day(1).I_[1] == 0);
        CHECK(eq0->get_condition_day(1).H_ == 0);
        CHECK(eq0->get_condition_day(1).D_ == 0);

        // std::array<int,4> vec_c;
        // eq0->add_count(eq0->calculate(1,vec_c));//fa il conteggio della
        // comdizione del primo giorno e lo aggiunge direttamente

        CHECK(eq0->get_counting(1)[0] == 6399);
        CHECK(eq0->get_counting(1)[1] == 1);
        CHECK(eq0->get_counting(1)[2] == 0);
        CHECK(eq0->get_counting(1)[3] == 0);//14
        ////////////////potrei doverlo spostare questo

        std::array<int, 4> vec_b;
        People sub_1{{5300, 100}, {400, 600}, 0, 0};
        pan0->add_data(sub_1);

        CHECK(eq0->get_condition_day(2).S_[0] == 5300);
        CHECK(eq0->get_condition_day(2).S_[1] == 100);
        CHECK(eq0->get_condition_day(2).I_[0] == 400);
        CHECK(eq0->get_condition_day(2).I_[1] == 600);
        CHECK(eq0->get_condition_day(2).H_ == 0);
        CHECK(eq0->get_condition_day(2).D_ == 0);

        CHECK(eq0->calculate(2, vec_b)[0] == 5400);
        CHECK(eq0->calculate(2, vec_b)[1] == 1000);
        CHECK(eq0->calculate(2, vec_b)[2] == 0);
        CHECK(eq0->calculate(2, vec_b)[3] == 0);

        eq0->add_count(eq0->calculate(2, vec_b));

        CHECK(eq0->get_countdays().size() == 2);

        CHECK(eq0->get_counting(2)[0] == 5400);
        CHECK(eq0->get_counting(2)[1] == 1000);
        CHECK(eq0->get_counting(2)[2] == 0);
        CHECK(eq0->get_counting(2)[3] == 0);

        CHECK_THROWS_AS(eq0->calculate(-10, vec_b), std::out_of_range);
        CHECK_THROWS_WITH(eq0->calculate(-10, vec_b), "Invalid day number!");

      } else {
        std::cout << "Failed Cast !" << std::endl;
      }
      // serve un solo delete perchèpuntano alla stessa regione di memoria
      // dinamica quindi ne basta uno
    }

    SUBCASE("Parametric") {
      std::vector<People> days;
      std::vector<std::array<int, 4>> count;
      sub = {{500000, 0}, {100000, 0}, 0, 0};
      p = {{0.6, 0.}, {0.2, 0.}, {0.8, 0.}, 0.};
 
      std::shared_ptr<Pandemic> pan1 =std::make_shared<Equation>(days, p, 600000, count);
      std::shared_ptr<Equation> eq1 = std::dynamic_pointer_cast<Equation>(pan1);

      if (eq1) 
      {
        // a questo pun to io l'oggetto creato con parametri che voglio
        // controllare
        CHECK(eq1->get_countdays().size() == 0);
        CHECK(eq1->get_days() == 0);
        /// perchè rifaccio i check dei metodi di pandemic?perchè mi voglio
        /// assicurae che la struttura ad ereditarietà funzioni bene
        CHECK(eq1->get_Parameters().beta[0] == 0.6);
        CHECK(eq1->get_Parameters().beta[1] == 0.);
        CHECK(eq1->get_Parameters().gamma[0] == 0.2);
        CHECK(eq1->get_Parameters().gamma[1] == 0.);
        CHECK(eq1->get_Parameters().omega[0] == 0.8);
        CHECK(eq1->get_Parameters().beta[1] == 0.);
        CHECK(eq1->get_Parameters().vax == 0.);

        CHECK(eq1->get_number_population() == 600000);

        eq1->add_data(sub);

        CHECK(eq1->get_days() == 1);

        CHECK(eq1->get_condition_day(1).S_[0] == 500000);
        CHECK(eq1->get_condition_day(1).S_[1] == 0);
        CHECK(eq1->get_condition_day(1).I_[0] == 100000);
        CHECK(eq1->get_condition_day(1).I_[1] == 0);
        CHECK(eq1->get_condition_day(1).H_ == 0);
        CHECK(eq1->get_condition_day(1).D_ == 0);

        std::array<int, 4> c;
        eq1->add_count(eq1->calculate(1, c));

        CHECK(eq1->get_countdays().size() == 1);

        CHECK(eq1->get_counting(1)[0] == 500000);
        CHECK(eq1->get_counting(1)[1] == 100000);
        CHECK(eq1->get_counting(1)[2] == 0);
        CHECK(eq1->get_counting(1)[3] == 0);//53

      

        
        SUBCASE(" Equation Members") 
        {
          //////////update situation//////////////////

          CHECK(eq1->get_evolution().back().I_[0] == 100000);
          CHECK(eq1->get_evolution().back().I_[1] == 0);
          CHECK(eq1->get_evolution().back().S_[0] == 500000);
          CHECK(eq1->get_evolution().back().S_[1] == 0);
          CHECK(eq1->get_Parameters().beta[0] == 0.6);

            People n;
           std::array<float,6> situation = eq1->update_situation(0, n);

          CHECK( situation[0] == 450000);
          CHECK( situation[1]== 0);
          CHECK(situation[2]== 50000);
          CHECK(situation[3]== 0);
          CHECK(situation[4]== 20000);
          CHECK(situation[5] == 80000);
          CHECK(sum(situation) == eq1->get_number_population());//65
          
        eq1->add_data(eq1->fix(situation));
        
        People f;
        pan1->evolve(f);

          CHECK(eq1->get_evolution().back().S_[0] == 427500);
          CHECK(eq1->get_evolution().back().S_[1] == 0 );
          CHECK(eq1->get_evolution().back().I_[0] ==22500);
          CHECK(eq1->get_evolution().back().I_[1] == 0);
          CHECK(eq1->get_evolution().back().H_ == 30000 );
          CHECK(eq1->get_evolution().back().D_ == 120000);
        }

      } else 
      {
        std::cout << "Failed Cast !" << std::endl;
      }


    ///////////////////update_situation() & fix()/////////////////////
    Parameters pp{{0.6,0.},{0.4,0.},{0.5,0.},0.};
    std::shared_ptr<Pandemic> pan2 =std::make_shared<Equation>(days, pp, 600, count);
    std::shared_ptr<Equation> eq2 = std::dynamic_pointer_cast<Equation>(pan2);
    if (eq2){
      People c;
      People sub2 = {{550,0},{50,0},0,0};
      pan2->set_initial_condition(sub2);
      CHECK(sum(transform_arr<int,6>(sub2)) == eq2->get_number_population());
      /////////////////////////////#1/////////////////////////////////
      std::array<float,6> situation2 = eq2->update_situation(0,c);

          CHECK(situation2[0] == 522.5 );
          CHECK(situation2[1]== 0);
          CHECK(situation2[2] == 32.5);
          CHECK(situation2[3]== 0);
          CHECK(situation2[4] == 20);
          CHECK(situation2[5]== 25);
          CHECK(sum((situation2)) == eq2->get_number_population());//72
    
      eq2->add_data(eq2->fix(situation2));

       CHECK(eq2->get_condition_day(2).S_[0] == 523 );
       CHECK(eq2->get_condition_day(2).S_[1]== 0);
       CHECK(eq2->get_condition_day(2).I_[0] == 32);
       CHECK(eq2->get_condition_day(2).I_[1]== 0);
       CHECK(eq2->get_condition_day(2).H_ == 20);
       CHECK(eq2->get_condition_day(2).D_== 25);
       CHECK(sum(transform_arr<int,6>(eq2->get_condition_day(2))) == eq2->get_number_population());
     
///////////////////////////////////#2///////////////////////////////////////
      std::array<float,6> situation3 = eq2->update_situation(0,c);

          CHECK(situation3[0] == doctest::Approx(506.264).epsilon(0.000001));
          CHECK(situation3[1]== 0);
          CHECK(situation3[2] == doctest::Approx(19.936).epsilon(0.000001));
          CHECK(situation3[3]== 0);
          CHECK(situation3[4] == doctest::Approx(32.8).epsilon(0.000001));
          CHECK(situation3[5]== doctest::Approx(41).epsilon(0.000001));
          CHECK(sum(situation3) == eq2->get_number_population());//72
          CHECK(eq2->get_number_population() - sum(convert<int>(situation3)) == 2 );//95
         
      
     eq2->add_data(eq2->fix(situation3));
      
       CHECK(eq2->get_condition_day(3).S_[0] == 506 );
       CHECK(eq2->get_condition_day(3).S_[1]== 0);
       CHECK(eq2->get_condition_day(3).I_[0] == 21);
       CHECK(eq2->get_condition_day(3).I_[1]== 0);
       CHECK(eq2->get_condition_day(3).H_ == 32);
       CHECK(eq2->get_condition_day(3).D_== 41);
       CHECK(sum(transform_arr<int,6>(eq2->get_condition_day(3))) == eq2->get_number_population());

       
////////////////////////////////#3//////////////////////////////////
  std::array<float,6> situation4 = eq2->update_situation(0,c);

          CHECK(situation4[0] == doctest::Approx(495.374).epsilon(0.000001));
          CHECK(situation4[1]== 0);
          CHECK(situation4[2] == doctest::Approx(12.726).epsilon(0.000001));
          CHECK(situation4[3]== 0);
          CHECK(situation4[4] == doctest::Approx(40.4).epsilon(0.000001));
          CHECK(situation4[5]== doctest::Approx(51.5).epsilon(0.000001));
          CHECK(sum(situation4) == eq2->get_number_population());//72
          CHECK(eq2->get_number_population() - sum(convert<int>(situation4)) == 2 );//110
         
      
      eq2->add_data(eq2->fix(situation4));
      
       CHECK(eq2->get_condition_day(4).S_[0] == 495 );
       CHECK(eq2->get_condition_day(4).S_[1]== 0);
       CHECK(eq2->get_condition_day(4).I_[0] == 14);
       CHECK(eq2->get_condition_day(4).I_[1]== 0);
       CHECK(eq2->get_condition_day(4).H_ == 40);
       CHECK(eq2->get_condition_day(4).D_== 51);
       CHECK(sum(transform_arr<int,6>(eq2->get_condition_day(4))) == eq2->get_number_population());
      /////////////////////////evolve()/////////////////
      eq2->evolve(c);
       CHECK(eq2->get_days() == 5);
       CHECK(eq2->get_condition_day(5).S_[0] == 488);
       CHECK(eq2->get_condition_day(5).S_[1] == 0);
       CHECK(eq2->get_condition_day(5).I_[0] == 8);
       CHECK(eq2->get_condition_day(5).I_[1] == 0);
       CHECK(eq2->get_condition_day(5).H_ == 46);
       CHECK(eq2->get_condition_day(5).D_ == 58);

       pan2->introduce_vacc(0.24);
       pan2->change_after_vacc();
       pan2->sorting();

       CHECK(eq2->get_condition_day(5).S_[0] == 488);
       CHECK(eq2->get_condition_day(5).S_[1] == 488);
       CHECK(eq2->get_condition_day(5).I_[0] == 488);
       CHECK(eq2->get_condition_day(5).I_[1] == 488);
       CHECK(eq2->get_condition_day(5).H_ == 488);
       CHECK(eq2->get_condition_day(5).D_ == 488);

       CHECK(eq2->get_Parameters().beta[1] == doctest::Approx(0.0833).epsilon(0.001));
       CHECK(eq2->get_Parameters().omega[1] == doctest::Approx(0.2916).epsilon(0.001));
       CHECK(eq2->get_Parameters().gamma[1]== doctest::Approx(0.5369).epsilon(0.001));
      //////////////////////////evolve_vaccine()///////////////////////////////
        
       //eq2->evolve_vaccine(c); è lui che da problemi !!!!!!!!!!!!!!!!!!!!!!!!!!!!

       CHECK(eq2->get_days() == 6);
       CHECK((eq2->get_condition_day(5).S_[0])/(eq2->get_number_population()) == doctest::Approx(0.75392).epsilon(0.000001));
       CHECK(eq2->get_condition_day(5).S_[1]/(eq2->get_number_population()) == doctest::Approx(0.23808).epsilon(0.000001) );
       //CHECK(eq2->get_condition_day(5).I_[0]/(eq2->get_number_population()) == doctest::Approx().epsilon(0.000001));
       //CHECK(eq2->get_condition_day(5).I_[1]/(eq2->get_number_population()) == doctest::Approx(0.23808).epsilon(0.000001));
       //CHECK(eq2->get_condition_day(5).H_/(eq2->get_number_population()) == doctest::Approx(0.23808).epsilon(0.000001));
       //CHECK(eq2->get_condition_day(5).D_/(eq2->get_number_population()) == doctest::Approx(0.23808).epsilon(0.000001)); 


    } else {

       std::cout << "Failed Cast !" << std::endl;
    }

      
    }
  }

  SUBCASE("Distructor") {}
}



       /////////evolve//////////////////////////
       
       /////////////////////////////////evolve_vaccine//////////////////////////////////////////
     

     /*
       CHECK((pan1->get_evolution().back().S_[1])/(pan1->get_number_population())
   == doctest::Approx(0.25).epsilon(1));
       CHECK((pan1->get_evolution().back().S_[0])/(pan1->get_number_population())
   == doctest::Approx(0.65).epsilon(1));


       CHECK((pan1->get_evolution().back().I_[1])/(pan1->get_number_population())
   == doctest::Approx(0.).epsilon(0.8));
       CHECK((pan1->get_evolution().back().I_[0])/(pan1->get_number_population())
   == doctest::Approx(0.65).epsilon(0.8));

       CHECK((pan1->get_evolution().back().S_[1])/(pan1->get_number_population())
   == doctest::Approx(0.35).epsilon(0.5));
       CHECK((pan1->get_evolution().back().S_[0])/(pan1->get_number_population())
   == doctest::Approx(0.65).epsilon(0.5));

       eq1->evolve_vaccine(ff);

       CHECK((eq1->get_evolution().back().S_[0])/ (eq1->get_number_population()
   ) == doctest::Approx(0.4).epsilon(0.02));

       CHECK((pan1->get_evolution().back().S_[1])/(pan1->get_number_population())
   == doctest::Approx(0.35).epsilon(0.5));
       CHECK((pan1->get_evolution().back().S_[0])/(pan1->get_number_population())
   == doctest::Approx(0.65).epsilon(0.5));
       CHECK((pan1->get_evolution().back().I_[1])/(pan1->get_number_population())
   == doctest::Approx(0.35).epsilon(1));
       CHECK((pan1->get_evolution().back().I_[0])/(pan1->get_number_population())
   == doctest::Approx(0.65).epsilon(1));

       CHECK((pan1->get_evolution().back().H_)/(pan1->get_number_population())
   == doctest::Approx(0.35).epsilon(1));

       CHECK((pan1->get_evolution().back().D_)/(pan1->get_number_population())
   == doctest::Approx(0.65).epsilon(1));


       CHECK(eq1->get_evolution().back().S_[1] == );
       CHECK(eq1->get_evolution().back().I_[0] == );
       CHECK(eq1->get_condi);
       CHECK(eq1->get_evolution().back().H_ == );
       CHECK(eq1->get_evolution().back().D_ == );
      CHECK(pan1->get_days() == 4);*/
////////Print//////////////////////

/*SUBCASE(){}
    SUBCASE(){}
SUBCASE(){} */
