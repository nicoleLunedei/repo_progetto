#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN


#include <memory>

#include "doctest.h"
#include "pandemic.hpp"
#include "equation.hpp"
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
      Equation eq0;// smart pointer che condivide ala
                                         // ownership dell'oggetto che punta,
                                         // OCCHIO PERò!!!!!!!
       // è come dynamic_cast(puntatore grezzo (T*)) che restituisce
                  // un puntatore grezzo, mentre dynamic pointer cast (puntatori
                  // intelligenti(T))
      
        CHECK(eq0.get_countdays().size() == 1);  // lui qua ha già un elemento quindi ha già fatto  il counting
        CHECK(eq0.get_days() == 1);
        CHECK(eq0.get_Parameters().beta[0] == 0.6);
        CHECK(eq0.get_Parameters().beta[1] == 0.0);
        CHECK(eq0.get_Parameters().gamma[0] == 0.2);
        CHECK(eq0.get_Parameters().gamma[1] == 0.0);
        CHECK(eq0.get_Parameters().omega[0] == 0.35);
        CHECK(eq0.get_Parameters().omega[1] == 0.0);
        CHECK(eq0.get_Parameters().vax == 0.0);
        CHECK(eq0.get_number_population() == 2500);
        // CHECK(eq0.get_condition_day(1) == sub);
        CHECK(eq0.get_condition_day(1).S_[0] == 2000);
        CHECK(eq0.get_condition_day(1).S_[1] == 0);
        CHECK(eq0.get_condition_day(1).I_[0] == 500);
        CHECK(eq0.get_condition_day(1).I_[1] == 0);
        CHECK(eq0.get_condition_day(1).H_ == 0);
        CHECK(eq0.get_condition_day(1).D_ == 0);

         //std::array<int,4> vec_c;
        //eq0.add_count(eq0.calculate(1,vec_c));//fa il conteggio della
        // comdizione del primo giorno e lo aggiunge direttamente

        CHECK(eq0.get_counting(1)[0] == 2000);
        CHECK(eq0.get_counting(1)[1] == 500);
        CHECK(eq0.get_counting(1)[2] == 0);
        CHECK(eq0.get_counting(1)[3] == 0);//14
        ////////////////potrei doverlo spostare questo

        
        People sub_1{{2100, 100}, {180, 120}, 0, 0};
        eq0.add_data(sub_1);

        CHECK(eq0.get_condition_day(2).S_[0] == 2100);
        CHECK(eq0.get_condition_day(2).S_[1] == 100);
        CHECK(eq0.get_condition_day(2).I_[0] == 180);
        CHECK(eq0.get_condition_day(2).I_[1] == 120);
        CHECK(eq0.get_condition_day(2).H_ == 0);
        CHECK(eq0.get_condition_day(2).D_ == 0);

        CHECK(eq0.calculate()[0] == 2200);
        CHECK(eq0.calculate()[1] == 300);
        CHECK(eq0.calculate()[2] == 0);
        CHECK(eq0.calculate()[3] == 0);

        eq0.add_count(eq0.calculate());

        CHECK(eq0.get_countdays().size() == 2);

        CHECK(eq0.get_counting(2)[0] == 2200);
        CHECK(eq0.get_counting(2)[1] == 300);
        CHECK(eq0.get_counting(2)[2] == 0);
        CHECK(eq0.get_counting(2)[3] == 0);
    }

    SUBCASE("Parametric") {
      std::vector<People> days;
      std::vector<std::array<int, 4>> count;
      sub = {{500000, 0}, {100000, 0}, 0, 0};
      p = {{0.75, 0.}, {0.3, 0.}, {0.35, 0.}, 0.};
 
      
      Equation eq1(days, p, 600000, count);

      
        // a questo pun to io l'oggetto creato con parametri che voglio
        // controllare
        CHECK(eq1.get_countdays().size() == 0);
        CHECK(eq1.get_days() == 0);
        /// perchè rifaccio i check dei metodi di pandemic?perchè mi voglio
        /// assicurae che la struttura ad ereditarietà funzioni bene
        CHECK(eq1.get_Parameters().beta[0] == 0.75);
        CHECK(eq1.get_Parameters().beta[1] == 0.);
        CHECK(eq1.get_Parameters().gamma[0] == 0.3);
        CHECK(eq1.get_Parameters().gamma[1] == 0.);
        CHECK(eq1.get_Parameters().omega[0] == 0.35);
        CHECK(eq1.get_Parameters().beta[1] == 0.);
        CHECK(eq1.get_Parameters().vax == 0.);

        CHECK(eq1.get_number_population() == 600000);

        eq1.add_data(sub);

        CHECK(eq1.get_days() == 1);

        CHECK(eq1.get_condition_day(1).S_[0] == 500000);
        CHECK(eq1.get_condition_day(1).S_[1] == 0);
        CHECK(eq1.get_condition_day(1).I_[0] == 100000);
        CHECK(eq1.get_condition_day(1).I_[1] == 0);
        CHECK(eq1.get_condition_day(1).H_ == 0);
        CHECK(eq1.get_condition_day(1).D_ == 0);

      
        eq1.add_count(eq1.calculate());

        CHECK(eq1.get_countdays().size() == 1);

        CHECK(eq1.get_counting(1)[0] == 500000);
        CHECK(eq1.get_counting(1)[1] == 100000);
        CHECK(eq1.get_counting(1)[2] == 0);
        CHECK(eq1.get_counting(1)[3] == 0);//53

      

        
        SUBCASE(" Equation Members") 
        {
          //////////update situation//////////////////

          CHECK(eq1.get_evolution().back().I_[0] == 100000);
          CHECK(eq1.get_evolution().back().I_[1] == 0);
          CHECK(eq1.get_evolution().back().S_[0] == 500000);
          CHECK(eq1.get_evolution().back().S_[1] == 0);
          CHECK(eq1.get_Parameters().beta[0] == 0.75);

            People n{{0,0},{0,0},0,0};
           std::array<double,6> situation = eq1.update_situation(0, n);

          CHECK( situation[0] ==doctest::Approx(437500).epsilon(0.01) );
          CHECK( situation[1]== 0);
          CHECK(situation[2]==doctest::Approx(97500).epsilon(0.01));
          CHECK(situation[3]== 0);
          CHECK(situation[4]== 30000);
          CHECK(situation[5] == 35000);
          CHECK(sum(situation) == eq1.get_number_population());//65
          
        eq1.add_data(eq1.fix(situation));
        
       
        eq1.evolve();

          CHECK(eq1.get_evolution().back().S_[0] == 384180);
          CHECK(eq1.get_evolution().back().S_[1] == 0 );
          CHECK(eq1.get_evolution().back().I_[0] ==87445);
          CHECK(eq1.get_evolution().back().I_[1] == 0);
          CHECK(eq1.get_evolution().back().H_ == 59250 );
          CHECK(eq1.get_evolution().back().D_ == 69125);
        }

    

    ///////////////////update_situation() & fix()/////////////////////
    Parameters pp{{0.6,0.},{0.20,0.},{0.35,0.},0.};
    Equation eq2(days, pp, 600, count);
  
    
      People c{{0,0},{0,0},0,0};
      People sub2 = {{550,0},{50,0},0,0};
      eq2.set_initial_condition(sub2);
      CHECK(sum(transform_arr<int,6>(sub2)) == eq2.get_number_population());
      /////////////////////////////#1/////////////////////////////////
      std::array<double,6> situation2 = eq2.update_situation(0,c);

          CHECK(situation2[0] == 522.5 );
          CHECK(situation2[1] == 0);
          CHECK(situation2[2] == 50);
          CHECK(situation2[3] == 0);
          CHECK(situation2[4] == 10);
          CHECK(situation2[5] == 17.5);
          CHECK(sum((situation2)) == eq2.get_number_population());//72
    
      eq2.add_data(eq2.fix(situation2));

       CHECK(eq2.get_condition_day(2).S_[0] == 523 );
       CHECK(eq2.get_condition_day(2).S_[1]== 0);
       CHECK(eq2.get_condition_day(2).I_[0] == 50);
       CHECK(eq2.get_condition_day(2).I_[1]== 0);
       CHECK(eq2.get_condition_day(2).H_ == 10);
       CHECK(eq2.get_condition_day(2).D_== 17);
       CHECK(sum(transform_arr<int,6>(eq2.get_condition_day(2))) == eq2.get_number_population());
     
///////////////////////////////////#2///////////////////////////////////////
      std::array<double,6> situation3 = eq2.update_situation(0,c);

          CHECK(situation3[0] == doctest::Approx(496.85).epsilon(0.000001));
          CHECK(situation3[1]== 0);
          CHECK(situation3[2] == doctest::Approx(48.65).epsilon(0.000001));
          CHECK(situation3[3]== 0);
          CHECK(situation3[4] == doctest::Approx(20).epsilon(0.000001));
          CHECK(situation3[5]== doctest::Approx(34.5).epsilon(0.000001));
          CHECK(sum(situation3) == eq2.get_number_population());//72
          CHECK(eq2.get_number_population() - sum(integer_part(situation3)) == 2 );//95
         
      
     eq2.add_data(eq2.fix(situation3));
      
       CHECK(eq2.get_condition_day(3).S_[0] == 498 );
       CHECK(eq2.get_condition_day(3).S_[1]== 0);
       CHECK(eq2.get_condition_day(3).I_[0] == 48);
       CHECK(eq2.get_condition_day(3).I_[1]== 0);
       CHECK(eq2.get_condition_day(3).H_ == 20);
       CHECK(eq2.get_condition_day(3).D_== 34);
       CHECK(sum(transform_arr<int,6>(eq2.get_condition_day(3))) == eq2.get_number_population());

       
////////////////////////////////#3//////////////////////////////////
  std::array<double,6> situation4 = eq2.update_situation(0,c);

          CHECK(situation4[0] == doctest::Approx(474.096).epsilon(0.000001));
          CHECK(situation4[1]== 0);
          CHECK(situation4[2] == doctest::Approx(45.504).epsilon(0.000001));
          CHECK(situation4[3]== 0);
          CHECK(situation4[4] == doctest::Approx(29.6).epsilon(0.000001));
          CHECK(situation4[5]== doctest::Approx(50.8).epsilon(0.000001));
          CHECK(sum(situation4) == eq2.get_number_population());//72
          CHECK(eq2.get_number_population() - sum(integer_part(situation4)) == 2 );//110
         
      
      eq2.add_data(eq2.fix(situation4));
      
       CHECK(eq2.get_condition_day(4).S_[0] == 474 );
       CHECK(eq2.get_condition_day(4).S_[1]== 0);
       CHECK(eq2.get_condition_day(4).I_[0] == 45);
       CHECK(eq2.get_condition_day(4).I_[1]== 0);
       CHECK(eq2.get_condition_day(4).H_ == 29);
       CHECK(eq2.get_condition_day(4).D_== 52);
       CHECK(sum(transform_arr<int,6>(eq2.get_condition_day(4))) == eq2.get_number_population());
      /////////////////////////evolve()/////////////////
      eq2.evolve();
       CHECK(eq2.get_days() == 5);
       CHECK(eq2.get_condition_day(5).S_[0] == 452);
       CHECK(eq2.get_condition_day(5).S_[1] == 0);
       CHECK(eq2.get_condition_day(5).I_[0] == 41);
       CHECK(eq2.get_condition_day(5).I_[1] == 0);
       CHECK(eq2.get_condition_day(5).H_ == 38);
       CHECK(eq2.get_condition_day(5).D_ == 69);

       eq2.introduce_vacc(0.24);
       eq2.change_after_vacc();
       eq2.sorting();
       
      std::cout<<"Somma delle persone aggiornate "<< eq2.get_evolution().back().S_[0]<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< eq2.get_evolution().back().S_[1]<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< eq2.get_evolution().back().I_[0]<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< eq2.get_evolution().back().I_[1]<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< eq2.get_evolution().back().H_<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< eq2.get_evolution().back().D_<<'\n';
      std::cout<<"Somma :"<< sum(transform_arr<int,6>((eq2.get_evolution()).back())) <<'\n';

       CHECK(static_cast<double>(eq2.get_condition_day(5).S_[0])/(sum(eq2.get_condition_day(5).S_)) == doctest::Approx(0.76).epsilon(0.1));//0.76
       CHECK(static_cast<double>(eq2.get_condition_day(5).S_[1])/(sum(eq2.get_condition_day(5).S_))  == doctest::Approx(0.24).epsilon(0.1));
       CHECK(eq2.get_condition_day(5).I_[0] == 41);
       CHECK(eq2.get_condition_day(5).I_[1] == 0);
       CHECK(eq2.get_condition_day(5).H_ == 38);
       CHECK(eq2.get_condition_day(5).D_ == 69);

       CHECK(eq2.get_Parameters().beta[1] == doctest::Approx(0.174).epsilon(0.001));
       CHECK(eq2.get_Parameters().omega[1] == doctest::Approx(0.1225).epsilon(0.001));
       CHECK(eq2.get_Parameters().gamma[1]== doctest::Approx(0.4275).epsilon(0.001));
      /////////is_vaccinated & sorting///////////
      Parameters p_r({0.75, 0.}, {0.3, 0.}, {0.4, 0.}, 0.);
      Equation members(days, p_r, 3000000,count);
        People sort{{2999500, 0}, {500, 0}, 0, 0};
        members.add_data(sort);
        members.sorting();
        CHECK(members.get_days() == 1);
        CHECK(members.get_number_population() == 3000000);

        CHECK((members.get_evolution().back().S_[1]) /
                  (members.get_number_population()) ==
              doctest::Approx(0.15).epsilon(1));
        CHECK((members.get_evolution().back().S_[0]) /
                  (members.get_number_population()) ==
              doctest::Approx(0.85).epsilon(1));

        CHECK((members.get_evolution().back().S_[1]) /
                  (members.get_number_population()) ==
              doctest::Approx(0.15).epsilon(0.8));
        CHECK((members.get_evolution().back().S_[0]) /
                  (members.get_number_population()) ==
              doctest::Approx(0.85).epsilon(0.8));

        CHECK((members.get_evolution().back().S_[1]) /
                  (members.get_number_population()) ==
              doctest::Approx(0.15).epsilon(0.5));
        CHECK((members.get_evolution().back().S_[0]) /
                  (members.get_number_population()) ==
              doctest::Approx(0.85).epsilon(0.5));
      //////////////////////////evolve_vaccine()///////////////////////////////
      People e{{0,0},{0,0},0,0};
      std::cout<<"Somma delle persone aggiornate "<< (eq2.update_situation(0,e))[0]+ eq2.update_situation(1,e)[0]<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< (eq2.update_situation(0,e))[1]+ eq2.update_situation(1,e)[1]<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< (eq2.update_situation(0,e))[2]+ eq2.update_situation(1,e)[2]<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< (eq2.update_situation(0,e))[3]+ eq2.update_situation(1,e)[3]<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< (eq2.update_situation(0,e))[4]+ eq2.update_situation(1,e)[4]<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< (eq2.update_situation(0,e))[5]+ eq2.update_situation(1,e)[5]<<'\n';
      std::cout<<"Somma :"<< sum(transform_arr<int,6>((eq2.get_evolution()).back())) <<'\n';
           std::cout<<"aggiornamento con vaccino"<<'\n';
      People e_caccia{{0,0},{0,0},0,0};
      std::cout<<"Somma delle persone aggiornate "<< eq2.update_situation(1,e_caccia)[0]<< "->"<< eq2.fix(eq2.update_situation(1,e_caccia)).S_[0]<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< eq2.update_situation(1,e_caccia)[1]<< "->"<< eq2.fix(eq2.update_situation(1,e_caccia)).S_[1]<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< eq2.update_situation(1,e_caccia)[2]<< "->"<< eq2.fix(eq2.update_situation(1,e_caccia)).I_[0]<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< eq2.update_situation(1,e_caccia)[3]<< "->"<< eq2.fix(eq2.update_situation(1,e_caccia)).I_[1]<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< eq2.update_situation(1,e_caccia)[4]<< "->"<< eq2.fix(eq2.update_situation(1,e_caccia)).H_<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< eq2.update_situation(1,e_caccia)[5]<< "->"<< eq2.fix(eq2.update_situation(1,e_caccia)).D_<<'\n';
      std::cout<<"Somma :"<< sum(transform_arr<int,6>((eq2.get_evolution()).back())) <<'\n';
       std::cout<<"differenza:"<<eq2.get_number_population()-sum(integer_part(eq2.update_situation(1,e_caccia)))<<'\n'; 
      std::cout<<"Somma delle parti intere"<<sum(integer_part(eq2.update_situation(1,e_caccia)))<<'\n'; 
      std::cout<<"aggiornamento senza vaccino"<<'\n';
        People e_caccia2{{0,0},{0,0},0,0};
      std::cout<<"Somma delle persone aggiornate "<< eq2.update_situation(0,e_caccia2)[0]<< "->"<< eq2.fix(eq2.update_situation(0,e_caccia2)).S_[0]<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< eq2.update_situation(0,e_caccia2)[1]<< "->"<< eq2.fix(eq2.update_situation(0,e_caccia2)).S_[1]<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< eq2.update_situation(0,e_caccia2)[2]<< "->"<< eq2.fix(eq2.update_situation(0,e_caccia2)).I_[0]<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< eq2.update_situation(0,e_caccia2)[3]<< "->"<< eq2.fix(eq2.update_situation(0,e_caccia2)).I_[1]<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< eq2.update_situation(0,e_caccia2)[4]<< "->"<< eq2.fix(eq2.update_situation(0,e_caccia2)).H_<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< eq2.update_situation(0,e_caccia2)[5]<< "->"<< eq2.fix(eq2.update_situation(0,e_caccia2)).D_<<'\n';
      std::cout<<"Somma :"<< sum(transform_arr<int,6>((eq2.get_evolution()).back())) <<'\n';
      std::cout<<"differenza:"<<eq2.get_number_population()-sum(integer_part(eq2.update_situation(0,e_caccia2)))<<'\n'; 
          std::cout<<"Somma delle parti intere"<<sum(integer_part(eq2.update_situation(0,e_caccia2)))<<'\n'; 
     std::cout<<"SUSCETTIBILI PRIMA DI EVOLVERE CON IL VACCINO "<<'\n';
     std::cout<<"Somma delle persone aggiornate "<< eq2.get_evolution().back().S_[0]<<"\n\n";
     std::cout<<"Somma delle persone aggiornate "<< eq2.get_evolution().back().S_[1]<<"\n\n";
      eq2.evolve_vaccine(); 
      std::cout<<"Somma delle persone aggiornate "<< eq2.get_evolution().back().S_[0]<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< eq2.get_evolution().back().S_[1]<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< eq2.get_evolution().back().I_[0]<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< eq2.get_evolution().back().I_[1]<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< eq2.get_evolution().back().H_<<'\n';
      std::cout<<"Somma delle persone aggiornate "<< eq2.get_evolution().back().D_<<'\n';
      std::cout<<'\n';
      
       CHECK(eq2.get_days() == 6);
       //CHECK((eq2.get_condition_day(5).S_[0])!= 0);
      // std::cout<< "Suscettibili non vaccinati :"<< eq2.get_condition_day(6).S_[0] <<'\n';
       //CHECK(eq2.get_condition_day(5).S_[1]!= 0);
       //std::cout<< "Suscettibili vaccinati : "<< eq2.get_condition_day(6).S_[1]<<'\n' ;
       CHECK(static_cast<double>(eq2.get_condition_day(6).S_[0])/(sum(eq2.get_condition_day(6).S_)) == doctest::Approx(0.75392).epsilon(0.04));
       CHECK(static_cast<double>(eq2.get_condition_day(6).S_[1])/(sum(eq2.get_condition_day(6).S_)) == doctest::Approx(0.23808).epsilon(0.04) );
       //CHECK(eq2.get_condition_day(5).I_[0]/(eq2.get_number_population()) == doctest::Approx().epsilon(0.000001));*/
       //CHECK(eq2.get_condition_day(5).I_[1]/(eq2.get_number_population()) == doctest::Approx(0.23808).epsilon(0.000001));
       //CHECK(eq2.get_condition_day(5).H_/(eq2.get_number_population()) == doctest::Approx(0.23808).epsilon(0.000001));
       //CHECK(eq2.get_condition_day(5).D_/(eq2.get_number_population()) == doctest::Approx(0.23808).epsilon(0.000001)); 


      
    }
  }

  SUBCASE("Distructor") {}
}



       /////////evolve//////////////////////////
       
       /////////////////////////////////evolve_vaccine//////////////////////////////////////////
     

     /*
       CHECK((eq1.get_evolution().back().S_[1])/(eq1.get_number_population())
   == doctest::Approx(0.25).epsilon(1));
       CHECK((eq1.get_evolution().back().S_[0])/(eq1.get_number_population())
   == doctest::Approx(0.65).epsilon(1));


       CHECK((eq1.get_evolution().back().I_[1])/(eq1.get_number_population())
   == doctest::Approx(0.).epsilon(0.8));
       CHECK((eq1.get_evolution().back().I_[0])/(eq1.get_number_population())
   == doctest::Approx(0.65).epsilon(0.8));

       CHECK((eq1.get_evolution().back().S_[1])/(eq1.get_number_population())
   == doctest::Approx(0.35).epsilon(0.5));
       CHECK((eq1.get_evolution().back().S_[0])/(eq1.get_number_population())
   == doctest::Approx(0.65).epsilon(0.5));

       eq1.evolve_vaccine(ff);

       CHECK((eq1.get_evolution().back().S_[0])/ (eq1.get_number_population()
   ) == doctest::Approx(0.4).epsilon(0.02));

       CHECK((eq1.get_evolution().back().S_[1])/(eq1.get_number_population())
   == doctest::Approx(0.35).epsilon(0.5));
       CHECK((eq1.get_evolution().back().S_[0])/(eq1.get_number_population())
   == doctest::Approx(0.65).epsilon(0.5));
       CHECK((eq1.get_evolution().back().I_[1])/(eq1.get_number_population())
   == doctest::Approx(0.35).epsilon(1));
       CHECK((eq1.get_evolution().back().I_[0])/(eq1.get_number_population())
   == doctest::Approx(0.65).epsilon(1));

       CHECK((eq1.get_evolution().back().H_)/(eq1.get_number_population())
   == doctest::Approx(0.35).epsilon(1));

       CHECK((eq1.get_evolution().back().D_)/(eq1.get_number_population())
   == doctest::Approx(0.65).epsilon(1));


       CHECK(eq1.get_evolution().back().S_[1] == );
       CHECK(eq1.get_evolution().back().I_[0] == );
       CHECK(eq1.get_condi);
       CHECK(eq1.get_evolution().back().H_ == );
       CHECK(eq1.get_evolution().back().D_ == );
      CHECK(eq1.get_days() == 4);*/
////////Print//////////////////////

/*SUBCASE(){}
    SUBCASE(){}
SUBCASE(){} */
