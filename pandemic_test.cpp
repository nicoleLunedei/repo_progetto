#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "pandemic.hpp"

#include "doctest.h"

TEST_CASE("People type") {
  std::array<int, 2> s{57, 6};
  std::array<int, 2> i{64, 93};
  int h = 39;
  int d = 87;
  People one(s, i, h, d);
  People two;
  SUBCASE("Parametric Constructor: People") {
    CHECK(one.S_[0] == 57);
    CHECK(one.S_[1] == 6);
    CHECK(one.I_[0] == 64);
    CHECK(one.I_[1] == 93);
    CHECK(one.H_ == 39);
    CHECK(one.D_ == 87);
  }
  SUBCASE("Default Constructor: People") {
    CHECK(two.S_[0] == 6399);
    CHECK(two.S_[1] == 0);
    CHECK(two.I_[0] == 1);
    CHECK(two.I_[1] == 0);
    CHECK(two.H_ == 0);
    CHECK(two.D_ == 0);
  }
  SUBCASE("Copy Construttor: People") {}
  People three(two);
  CHECK(three == two);
}//13
TEST_CASE("Parameters type") {//15
  std::array<double, 2> b{0.6, 0.};
  std::array<double, 2> g{0.4, 0.};
  std::array<double, 2> o{0.5, 0.};
  double vax = 0.3;
  Parameters one(b, g, o, vax);
  Parameters two;
  SUBCASE("Parametric Constructor: Parameters") {
    CHECK(one.beta[0] == 0.6);
    CHECK(one.beta[1] == 0.);
    CHECK(one.gamma[0] == 0.4);
    CHECK(one.gamma[1] == 0.);
    CHECK(one.omega[0] == 0.5);
    CHECK(one.omega[1] == 0.);
    CHECK(one.vax == 0.3);
  }//20
  SUBCASE("Default Constructor: Parameters") {
    CHECK(two.beta[0] == 0.5);
    CHECK(two.beta[1] == 0.);
    CHECK(two.gamma[0] == 0.6);
    CHECK(two.gamma[1] == 0.);
    CHECK(two.omega[0] == 0.4);
    CHECK(two.omega[1] == 0.);
    CHECK(two.vax == 0.);
  }
  SUBCASE("Copy Construttor") {}
  Parameters three(two);
  CHECK(three == two);
}

// Classe madre

TEST_CASE("Mother Class") {
  Pandemic global;
  SUBCASE("Testing the default Constructor") {//15
    

    CHECK(global.get_number_population() == 6400);
   
    CHECK(global.get_Parameters().beta[0] == 0.5);
    CHECK(global.get_Parameters().beta[1] == 0.);
    CHECK(global.get_Parameters().gamma[0] == 0.6);
    CHECK(global.get_Parameters().gamma[1] == 0.);
    CHECK(global.get_Parameters().omega[0] == 0.4);
    CHECK(global.get_Parameters().omega[1] == 0.);
    CHECK(global.get_Parameters().vax == 0.);

    CHECK(global.get_condition_day(1).S_[0] == 6399);
    CHECK(global.get_condition_day(1).S_[1] == 0);
    CHECK(global.get_condition_day(1).I_[0] == 1);
    CHECK(global.get_condition_day(1).I_[1] == 0);
    CHECK(global.get_condition_day(1).H_ == 0);
    CHECK(global.get_condition_day(1).D_ == 0);

    People subject({6395, 0}, {3, 0}, 1, 1);
    global.add_data(subject);

    CHECK(global.get_condition_day(2).S_[0] == 6395);
    CHECK(global.get_condition_day(2).S_[1] == 0);
    CHECK(global.get_condition_day(2).I_[0] == 3);
    CHECK(global.get_condition_day(2).I_[1] == 0);
    CHECK(global.get_condition_day(2).H_ == 1);
    CHECK(global.get_condition_day(2).D_ == 1);

    CHECK(global.get_days() == 2);
  }//49
  SUBCASE("Parametric Constructor ") {//28
    Parameters p_r({0.1, 0.}, {0.7, 0.}, {0.3, 0.}, 0.);  // giusto
    Parameters p_w1({3., 0.}, {0.1, 0.}, {4., 0.},0.);  // sbaglaiato ha valori delle probabilità che eccedono
    Parameters p_w2({0., 0.6}, {0., 0.5}, {0., 0.},0.4);  // ha le probabilità condizionate diverse da 0
    People sub_r({3000000, 0}, {500000, 0}, 0, 0);
    People sub_w1({5000000, 0}, {1, 0}, 0,0);  // non c'è coerenza con con l'altro parametro della classe
    People sub_w2({23, 3}, {87, 5}, 0, 0);  // i valori dei vaccinati non sono nulli
    People sub_w3({3, 0 }, {0, 0}, 0, 0);
    People sub_w4({3, 0 }, {6, 0}, 10, 89);//i morti e i guariti devono essere nulli 
    std::vector<People> days;
    int N = 4000000;
    Pandemic global_p(days, p_r, N);
    CHECK(global_p.get_days() == 0);

    // CHECK(global_p.get_Parameters() == p_r);
    CHECK(global_p.get_Parameters().beta[0] == 0.1);
    CHECK(global_p.get_Parameters().beta[1] == 0.);
    CHECK(global_p.get_Parameters().gamma[0] == 0.7);
    CHECK(global_p.get_Parameters().gamma[1] == 0.);
    CHECK(global_p.get_Parameters().omega[0] == 0.3);
    CHECK(global_p.get_Parameters().omega[1] == 0.);
    CHECK(global_p.get_Parameters().vax == 0.);

    global_p.set_initial_condition(sub_r);
    CHECK(global_p.get_days() == 1);
    //N_ = 4000000
    CHECK(global_p.get_number_population() == 4000000);
    // CHECK(global_p.get_condition_day(1) == sub_r );
    CHECK(global_p.get_condition_day(1).S_[0] == 3500000);
    CHECK(global_p.get_condition_day(1).S_[1] == 0);
    CHECK(global_p.get_condition_day(1).I_[0] == 500000);
    CHECK(global_p.get_condition_day(1).I_[1] == 0);
    CHECK(global_p.get_condition_day(1).H_ == 0);
    CHECK(global_p.get_condition_day(1).D_ == 0);

           SUBCASE("Checking errors by throw"){
      // Checking the values of the  parameters objects
               CHECK_THROWS_AS(Pandemic(days, p_w1, N),std::runtime_error);  // CHECK_THROWS_AS controlla che il tipo di
                              // operazitwo sia quello che voglio
               CHECK_THROWS_WITH(Pandemic(days, p_w1, N),"The values of the parameters must be inside the interval [0,1] !");

               CHECK_THROWS_AS(Pandemic(days, p_w2, N), std::runtime_error);
               CHECK_THROWS_WITH(Pandemic(days, p_w2, N),"The value of the parameters in case of vaccination must be 0 !");

    // Checking the values of the people objects
              Pandemic global_w1(days,p_r,N);
               CHECK_THROWS_AS(global_w1.set_initial_condition(sub_w1), std::runtime_error);
               CHECK_THROWS_WITH(global_w1.set_initial_condition(sub_w1),"The inserted values must be coherent with the number of the population !");
    
               Pandemic global_w2(days,p_r,N);
               CHECK_THROWS_AS(global_w2.set_initial_condition(sub_w2), std::runtime_error);
               CHECK_THROWS_WITH(global_w2.set_initial_condition(sub_w2),"At the begining the number of vaccinated people must be null! ");

    
               Pandemic global_w3(days,p_r,N);
               CHECK_THROWS_AS(global_w3.set_initial_condition(sub_w3), std::runtime_error);
               CHECK_THROWS_WITH(global_w3.set_initial_condition(sub_w3),"It can't start the evolution without any susceptible or any infected ! ");
               
               Pandemic global_w4(days,p_r,N);
               CHECK_THROWS_AS(global_w4.set_initial_condition(sub_w4), std::runtime_error);
               CHECK_THROWS_WITH(global_w4.set_initial_condition(sub_w4),"It doesn't make sense start with some healed or dead people");

    // Check that the initial condition is absent
              People sub{{300,0},{20,0},0,0};

              CHECK_THROWS_AS(global_p.set_initial_condition(sub), std::runtime_error);
              CHECK_THROWS_WITH(global_p.set_initial_condition(sub),"This simulation has already an initial condition, please start another simulation");
              
    // Check the start from day one 
              CHECK_THROWS_AS(global_p.get_condition_day(0), std::runtime_error);
              CHECK_THROWS_WITH(global_p.get_condition_day(0),"The simulation starts from day one!");
    }

    

    SUBCASE("Checking the output messages") {//5
      std::stringstream oss;
      std::streambuf* or_cout = std::cout.rdbuf(oss.rdbuf());  // dupilce azione il metodo rdbuf(arg*) non solo
                         // sostituisce il buffer ma estrapola il buffer
                         // originale dell'oggetto che lo chiama, per poi
                         // ripristinare il buffer originale

      Parameters c{{0.7, 0.}, {0.8, 0.}, {0.2, 0.}, 0.};
      std::vector<People> days2;
      Pandemic pop(days2, c, 1000000);
      pop.check_normalization(c);

      // Verifico che non ci siano output perchè c è corretto
      CHECK(oss.str().empty());

      std::cout.rdbuf(or_cout);

      // Verifica del output perché d non è corretto
      /////////////////////////////////////metodo puro//////////////////////////////////
      std::stringstream oss2;
      std::cout.rdbuf(oss2.rdbuf());

      Parameters d{{0.7, 0.}, {0.7, 0.}, {0.4, 0.}, 0.};
      pop.set_Parameters(d);
      pop.check_normalization(d);

      CHECK(oss2.str() == "The probablities of healing and dying must be minor than or equal to one, don't worry it has been fixed\n");
      CHECK(pop.get_Parameters().omega[0] == doctest::Approx(0.3).epsilon(0.0000000000000001));
      
      std::cout.rdbuf(or_cout);

      ////////////////////controllo nel costruttore/////////////////////////////////
      
      std::stringstream oss3;
      std::cout.rdbuf(oss3.rdbuf());

      Parameters e({0.7, 0.}, {0.7, 0.}, {0.5, 0.}, 0.);
      Pandemic pop2(days, e, 900000);

      CHECK(oss3.str() == "The probablities of healing and dying must be minor than or equal to one, don't worry it has been fixed\n");
      CHECK(pop2.get_Parameters().omega[0] == doctest::Approx(0.3).epsilon(0.0000000000000001));
     /////////////////////////////  

      std::cout.rdbuf(or_cout);
    }



      SUBCASE("Checking members of the Pandemic class") {//22
        //////////checking change_after_vacc//////////
        Parameters p_r({0.75, 0.}, {0.4, 0.}, {0.6, 0.}, 0.);
        std::vector<People> days;

        Pandemic members(days, p_r, 3000000);
        members.introduce_vacc(0.15);

        CHECK(members.get_Parameters().vax == 0.15);

        members.change_after_vacc();

        CHECK(members.get_Parameters().beta[1] ==
              doctest::Approx(0.13333333).epsilon(0.000001));
        CHECK(members.get_Parameters().gamma[1] ==
              doctest::Approx(0.533333).epsilon(0.000001));
        CHECK(members.get_Parameters().omega[1] ==
              doctest::Approx(0.4666666).epsilon(0.000001));

        CHECK_THROWS_AS(members.introduce_vacc(0.65), std::runtime_error);
        CHECK_THROWS_WITH(members.introduce_vacc(0.65), "You can't introduce the vaccine more than once");

        ///////////calculate_R0///////////////////

        CHECK(members.calculate_R0() == doctest::Approx(1.33333333).epsilon(0.000001));

        Parameters p({0.85, 0.}, {0.3, 0.}, {0.7, 0.}, 0.);
        members.set_Parameters(p);
        CHECK(members.calculate_R0() ==
              doctest::Approx(1.176470).epsilon(0.000001));

        Parameters pp({0.55, 0.}, {0.65, 0.}, {0.35, 0.}, 0.);
        members.set_Parameters(pp);
        CHECK(members.calculate_R0() ==
              doctest::Approx(1.818181).epsilon(0.000001));

        /////////is_vaccinated & sorting///////////

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
      }
    }
  }

