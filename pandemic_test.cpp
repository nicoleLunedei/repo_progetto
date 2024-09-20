#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "pandemic.hpp"


TEST_CASE("People type"){
    std::array<int,2> s{57,6};
    std::array<int,2> i{64,93};
    int h = 39;
    int d = 87;
    People one(s,i,h,d);
    People two;
   SUBCASE("Parametric Constructor: People"){
   
     CHECK(one.S_[0] == 57);
     CHECK(one.S_[1] == 6);
     CHECK(one.I_[0] == 64);
     CHECK(one.I_[1] == 93);
     CHECK(one.H_ == 39);
     CHECK(one.D_ == 87);
   }
   SUBCASE("Default Constructor: People"){
   
     CHECK( two.S_[0] == 1);
     CHECK(two.S_[1] == 0);
     CHECK(two.I_[0] == 1);
     CHECK(two.I_[1] == 0);
     CHECK(two.H_ == 1);
     CHECK(two.D_ == 1);
   }
   SUBCASE("Copy Construttor: People"){}
   People three(two);
   CHECK( three == two);
    
}
TEST_CASE("Parameters type"){
    std::array<double,2> b {0.6,0.};
    std::array<double,2> g {0.4,0.};
    std::array<double,2> o {0.5,0.};
    double  vax = 0.3 ;
    Parameters one(b,g,o,vax);
    Parameters two;
    SUBCASE("Parametric Constructor: Parameters"){
   
     CHECK( one.beta[0] == 0.6);
     CHECK(one.beta[1] == 0.);
     CHECK(one.gamma[0] == 0.4);
     CHECK(one.gamma[1] == 0.);
     CHECK(one.omega[0] == 0.5);
     CHECK(one.omega[1] == 0.);
     CHECK(one.vax == 0.3);
   }
   SUBCASE("Default Constructor: Parameters"){
   
     CHECK(two.beta[0] == 0.3);
     CHECK(two.beta[1] == 0.);
     CHECK(two.gamma[0] == 0.25);
     CHECK(two.gamma[1] == 0.);
     CHECK(two.omega[0] == 0.15);
     CHECK(two.omega[1] == 0.);
     CHECK(two.vax == 0.);
   }
   SUBCASE("Copy Construttor"){}
   Parameters three(two);
   CHECK( three == two);
}

//Classe madre 

TEST_CASE("Mother Class")
{
  SUBCASE("Testing the default Constructor"){
   Pandemic global;

      CHECK( global.get_number_population() == 2000000);
      CHECK( global.get_Parameters().beta[0] == 0.5 ); 
      CHECK( global.get_Parameters().beta[1] == 0. ); 
      CHECK( global.get_Parameters().gamma[0] == 0.6 ); 
      CHECK( global.get_Parameters().gamma[1] == 0.); 
      CHECK( global.get_Parameters().omega[0] == 0.4 ); 
      CHECK( global.get_Parameters().omega[1] == 0. ); 
      CHECK( global.get_Parameters().vax == 0. ); 
      
      CHECK( global.get_condition_day(1).S_[0] == 1999999);
      CHECK( global.get_condition_day(1).S_[1] == 0);
      CHECK( global.get_condition_day(1).I_[0] == 1);
      CHECK( global.get_condition_day(1).I_[1] == 0);
      CHECK( global.get_condition_day(1).H_ == 0);
      CHECK( global.get_condition_day(1).D_ == 0);

      CHECK(global.get_days() == 1);
    
  People subject({1999995,0},{3,0},1,1);
  global.add_data(subject);

    CHECK(global.get_days() == 2);
}
  SUBCASE("Testing th Parametric Constructor ")
  {

   Parameters p_r({0.1,0.},{0.7,0.},{0.3,0.},0.);//giusto
   Parameters p_w1({3.,0.},{0.1,0.},{4.,0.},0.);//sbaglaiato ha valori delle probabilità che eccedono
   Parameters p_w2({0.,0.6},{0.,0.5},{0.,0.},0.4);//ha le probabilità condizionate diverse da 0
   People sub_r({3000000,0},{500000,0},300000,200000);
   People sub_w1({5000000,0},{1,0},0,0);//non c'è coerenza con con l'altro parametro della classe
   People sub_w2({0,3},{1,5},0,0);//i valori dei vaccinati non sono nulli 
   std::vector<People> days;
   int N = 4000000;
   Pandemic global_p (days,p_r,N);
CHECK(global_p.get_days() == 0);


//CHECK(global_p.get_Parameters() == p_r);
  CHECK(global_p.get_Parameters().beta[0] == 0.1);
  CHECK(global_p.get_Parameters().beta[1]== 0.);
  CHECK(global_p.get_Parameters().gamma[0] == 0.7);
  CHECK(global_p.get_Parameters().gamma[1] == 0.);
  CHECK(global_p.get_Parameters().omega[0]== 0.3);
  CHECK(global_p.get_Parameters().omega[1] == 0.);
  CHECK(global_p.get_Parameters().vax== 0.);

global_p.set_initial_condition(sub_r);
  CHECK(global_p.get_days() == 1);

  CHECK(global_p.get_number_population() == 4000000);
 // CHECK(global_p.get_condition_day(1) == sub_r );
  CHECK(global_p.get_condition_day(1).S_[0] == 3000000 );
  CHECK(global_p.get_condition_day(1).S_[1] == 0);
  CHECK(global_p.get_condition_day(1).I_[0] == 500000 );
  CHECK(global_p.get_condition_day(1).I_[1] == 0 );
  CHECK(global_p.get_condition_day(1).H_== 300000 );
  CHECK(global_p.get_condition_day(1).D_== 200000 );
  

  CHECK_THROWS_AS(global_p.get_condition_day(0), std::runtime_error);
  CHECK_THROWS_WITH(global_p.get_condition_day(0), "The simulation starts from day 1 !" );
//Checking the values of the  parameters objects
  CHECK_THROWS_AS(Pandemic(days, p_w1, N), std::runtime_error);//CHECK_THROWS_AS controlla che il tipo di operazitwo sia quello che voglio
  CHECK_THROWS_WITH(Pandemic(days, p_w1, N),"The values of the parameters must be inside the interval [0,1] !"); 

  CHECK_THROWS_AS(Pandemic(days, p_w2, N), std::runtime_error);
  CHECK_THROWS_WITH(Pandemic(days, p_w2, N),"The value of the parameters in case of vaccination must be 0 !"); 

//Checking the values of the people objects 
 CHECK_THROWS_AS(global_p.set_initial_condition(sub_w1), std::runtime_error );
 CHECK_THROWS_WITH(global_p.set_initial_condition(sub_w1), "The inserted values must be coherent with the number of the population !" );

 CHECK_THROWS_AS(global_p.set_initial_condition(sub_w2), std::runtime_error );
 CHECK_THROWS_WITH(global_p.set_initial_condition(sub_w2), "At the begining the number of vaccinated people must be null! " );

People sub_w3({4,0},{0,0},10,89);

 CHECK_THROWS_AS(global_p.set_initial_condition(sub_w3), std::runtime_error );
 CHECK_THROWS_WITH(global_p.set_initial_condition(sub_w3), "It can't start the evolution without any suscettible or any infected ! " );

//Check that the initial condition is absent
People sub;
CHECK_THROWS_AS(global_p.set_initial_condition(sub),std::runtime_error);
CHECK_THROWS_WITH(global_p.set_initial_condition(sub), "This simulation has already the initial condition, please start another simulation" );


SUBCASE ("Check and fix probabilities"){

std::stringstream oss;
std::streambuf* or_cout=std::cout.rdbuf(oss.rdbuf());// dupilce azione il metodo rdbuf(arg*) non solo sostituisce il buffer ma estrapola il buffer originale dell'oggetto che lo chiama, per poi ripristinare il buffer originale 

Parameters c{{0.7,0.},{0.8,0.},{0.2,0.}, 0.};
std::vector<People> days2;
Pandemic pop(days2,c,1000000);
pop.check_complementarity(c);

//Verifico che non ci siano output perchè c è corretto
CHECK( oss.str().empty());

std::cout.rdbuf(or_cout);

//Verifica del output perché d non è corretto

std::stringstream oss2;
std::cout.rdbuf(oss2.rdbuf());

Parameters d{{0.7,0.},{0.7,0.},{0.2,0.}, 0.};
pop.set_Parameters(d);
//pop.check_complementarity(d);


CHECK( oss2.str() == "The probablities of healing and dying must be complementary, don't worry it has been fixed\n" );
CHECK( pop.get_Parameters().omega[0] == doctest::Approx(0.3).epsilon(0.0000000000000001));

Parameters e({0.7,0.},{0.7,0.},{0.2,0.}, 0.);
Pandemic pop2(days,e, 900000);
std::stringstream oss3;
std::cout.rdbuf(oss3.rdbuf());
pop2.check_complementarity();

CHECK( oss3.str() == "The probablities of healing and dying must be complementary, don't worry it has been fixed\n" );
CHECK( pop2.get_Parameters().omega[0] == doctest::Approx(0.3).epsilon(0.0000000000000001));



std::cout.rdbuf(or_cout);

SUBCASE("Checking members of the Pandemic class"){
  //////////checking change_after_vacc//////////
Parameters p_r({0.75,0.},{0.4,0.},{0.6,0.},0.);
std::vector<People> days;

Pandemic members(days,p_r,3000000);
members.introduce_vacc(0.15);

CHECK(members.get_Parameters().vax == 0.15);

members.change_after_vacc();

CHECK(members.get_Parameters().beta[1] == doctest::Approx(0.2666666).epsilon(0.000001) );
CHECK(members.get_Parameters().gamma[1] == doctest::Approx(0.533333).epsilon(0.000001));
CHECK(members.get_Parameters().omega[1] == doctest::Approx(0.4666666).epsilon(0.000001));

///////////calculate_R0///////////////////

CHECK(members.calculate_R0() == doctest::Approx(1.33333333).epsilon(0.000001));

Parameters p({0.85,0.},{0.3,0.},{0.7,0.},0.);
members.set_Parameters(p);
CHECK(members.calculate_R0() == doctest::Approx(1.176470).epsilon(0.000001));

Parameters pp({0.55,0.},{0.65,0.},{0.35,0.},0.);
members.set_Parameters(pp);
CHECK(members.calculate_R0() == doctest::Approx(1.818181).epsilon(0.000001));

/////////is_vaccinated & sorting///////////

People sort{{2999500,0},{500,0},0,0};
members.add_data(sort);
members.sorting();
CHECK(members.get_days() == 1);
CHECK(members.get_number_population() == 3000000 );

CHECK((members.get_condition_day(1).S_[1])/(members.get_number_population()) == doctest::Approx(0.15).epsilon(1));
CHECK((members.get_condition_day(1).S_[0])/(members.get_number_population()) == doctest::Approx(0.85).epsilon(1));

CHECK((members.get_condition_day(1).S_[1])/(members.get_number_population()) == doctest::Approx(0.15).epsilon(0.8));
CHECK((members.get_condition_day(1).S_[0])/(members.get_number_population()) == doctest::Approx(0.85).epsilon(0.8));

CHECK((members.get_condition_day(1).S_[1])/(members.get_number_population()) == doctest::Approx(0.15).epsilon(0.5));
CHECK((members.get_condition_day(1).S_[0])/(members.get_number_population()) == doctest::Approx(0.85).epsilon(0.5));

}






}

  }

}




