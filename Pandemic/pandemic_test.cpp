#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "pandemic.hpp"

#include <sstream>
#include <string>

#include "doctest.h"

TEST_CASE("Functions") {
  std::array<double, 6> d{0.9, 10.467, 20.698, 30.123, 40.0, 70.64};
  std::array<int, 6> b{0, 10, 20, 30, 40, 70};
  SUBCASE("sum()") {
    CHECK(sum(d) == 172.828);
    std::vector<int> a{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    CHECK(sum(a) == 45);
    std::vector<double> c{0.5, 0.78, 4.56, 9.67, 2.43, 0.47};
    CHECK(sum(c) == 18.41);

    CHECK(sum(b) == 170);
  }

  std::array<double, 6> e{56.67, 8.34, 3.56, 0.45, 1.925, 7.234};
  std::array<int, 6> f{56, 8, 3, 0, 1, 7};
  SUBCASE("maximum_dec() & integer_part") {
    CHECK(e[maximum_dec(e)] == 1.925);
    CHECK(integer_part(e) == f);

    e = {0.5, 0.78, 4.56, 9.67, 2.43, 0.47};
    f = {0, 0, 4, 9, 2, 0};
    CHECK(e[maximum_dec(e)] == 0.78);
    CHECK(integer_part(e) == f);
    e = {0.9, 10.467, 20.698, 30.123, 40.0, 70.64};
    CHECK(e[maximum_dec(e)] == 0.9);
    CHECK(integer_part(e) == b);
    CHECK(sum(integer_part(e)) == 170);
    CHECK(sum(e) - sum(integer_part(e)) ==
          doctest::Approx(2.828).epsilon(0.000000001));
  }

  SUBCASE("Trasform") {
    ///////////////////array->people///////////////
    People g{{0, 10}, {20, 30}, 40, 70};
    CHECK(transform_People(b) == g);
    ///////////////////people->array////////
    People h{{200, 10}, {20, 30}, 50, 8};
    std::array<int, 6> i{200, 10, 20, 30, 50, 8};

    CHECK(transform_Array<int, 6>(h) == i);
  }
}
////////////////////////////People struct/////////////////7
TEST_CASE("People type") {
  std::array<int, 2> s{57, 6};
  std::array<int, 2> i{64, 93};
  int h = 39;
  int d = 87;
  People one(s, i, h, d);
  People two;

  SUBCASE("Parametric Constructor") {
    CHECK(one.S_[0] == 57);
    CHECK(one.S_[1] == 6);
    CHECK(one.I_[0] == 64);
    CHECK(one.I_[1] == 93);
    CHECK(one.H_ == 39);
    CHECK(one.D_ == 87);
  }
  SUBCASE("Default Constructor") {
    CHECK(two.S_[0] == 2499);
    CHECK(two.S_[1] == 0);
    CHECK(two.I_[0] == 1);
    CHECK(two.I_[1] == 0);
    CHECK(two.H_ == 0);
    CHECK(two.D_ == 0);
  }
  SUBCASE("Copy Construttor") {
    People three(two);
    CHECK(three == two);
  }
}
///////////////////////////Parameters struct//////////////////
TEST_CASE("Parameters type") {
  std::array<double, 2> b{0.6, 0.};
  std::array<double, 2> g{0.4, 0.};
  std::array<double, 2> o{0.5, 0.};
  double vax = 0.3;
  Parameters one(b, g, o, vax);
  Parameters two;
  SUBCASE("Parametric Constructor") {
    CHECK(one.beta[0] == 0.6);
    CHECK(one.beta[1] == 0.);
    CHECK(one.gamma[0] == 0.4);
    CHECK(one.gamma[1] == 0.);
    CHECK(one.omega[0] == 0.5);
    CHECK(one.omega[1] == 0.);
    CHECK(one.vax == 0.3);
  }
  SUBCASE("Default Constructor") {
    CHECK(two.beta[0] == 0.6);
    CHECK(two.beta[1] == 0.);
    CHECK(two.gamma[0] == 0.2);
    CHECK(two.gamma[1] == 0.);
    CHECK(two.omega[0] == 0.35);
    CHECK(two.omega[1] == 0.);
    CHECK(two.vax == 0.);
  }
  SUBCASE("Copy Construttor") {}
  Parameters three(two);
  CHECK(three == two);
}
///////////////////////////////Pandemic class////////////////////

TEST_CASE("Pandemic Class") {
  Pandemic global;
  SUBCASE("Testing the default Constructor") {
    CHECK(global.get_number_population() == 2500);

    CHECK(global.get_Parameters().beta[0] == 0.6);
    CHECK(global.get_Parameters().beta[1] == 0.);
    CHECK(global.get_Parameters().gamma[0] == 0.2);
    CHECK(global.get_Parameters().gamma[1] == 0.);
    CHECK(global.get_Parameters().omega[0] == 0.35);
    CHECK(global.get_Parameters().omega[1] == 0.);
    CHECK(global.get_Parameters().vax == 0.);

    global.set_initial_condition({{2499, 0}, {1, 0}, 0, 0});

    CHECK(global.get_situation_day(1).S_[0] == 2499);
    CHECK(global.get_situation_day(1).S_[1] == 0);
    CHECK(global.get_situation_day(1).I_[0] == 1);
    CHECK(global.get_situation_day(1).I_[1] == 0);
    CHECK(global.get_situation_day(1).H_ == 0);
    CHECK(global.get_situation_day(1).D_ == 0);

    People subject({6395, 0}, {3, 0}, 1, 1);
    global.add_data(subject);

    CHECK(global.get_situation_day(2).S_[0] == 6395);
    CHECK(global.get_situation_day(2).S_[1] == 0);
    CHECK(global.get_situation_day(2).I_[0] == 3);
    CHECK(global.get_situation_day(2).I_[1] == 0);
    CHECK(global.get_situation_day(2).H_ == 1);
    CHECK(global.get_situation_day(2).D_ == 1);

    CHECK(global.get_days() == 2);
  }

  SUBCASE("Parametric Constructor ") {
    ////////////Right///////
    People sub_r({3000000, 0}, {500000, 0}, 0, 0);
    Parameters p_r({0.7, 0.}, {0.156, 0.}, {0.3, 0.}, 0.);
    /////////////Wrong///////////////

    ///////////Outside ]0,1[ ////////////////////
    Parameters p_w1({3., 0.}, {0.1, 0.}, {4., 0.}, 0.);
    ///////////////Probabillities  with vaccine not null////////////////
    Parameters p_w2({0., 0.6}, {0., 0.5}, {0., 0.}, 0.4);
    ///////////////////the R0 > 1/////////////////
    Parameters p_w3({0.56, 0.}, {0.3, 0.}, {0.4, 0.}, 0.);

    ///////////////////////Incoherent with N/////////////////////
    People sub_w1({5000000, 0}, {1, 0}, 0, 0);
    ///////////////////////There are vaccinated people/////////////
    People sub_w2({23, 3}, {87, 5}, 0, 0);
    //////////////////The infected people are null///////////////
    People sub_w3({3, 0}, {0, 0}, 0, 0);
    ///////////////Healed and Dead are not null///////////
    People sub_w4({3, 0}, {6, 0}, 10, 89);

    std::vector<People> days;
    int N = 4000000;
    Pandemic global_p(days, p_r, N);
    CHECK(global_p.get_days() == 0);

    CHECK(global_p.get_Parameters().beta[0] == 0.7);
    CHECK(global_p.get_Parameters().beta[1] == 0.);
    CHECK(global_p.get_Parameters().gamma[0] == 0.156);
    CHECK(global_p.get_Parameters().gamma[1] == 0.);
    CHECK(global_p.get_Parameters().omega[0] == 0.3);
    CHECK(global_p.get_Parameters().omega[1] == 0.);
    CHECK(global_p.get_Parameters().vax == 0.);

    global_p.set_initial_condition(sub_r);
    CHECK(global_p.get_days() == 1);
    // N_ = 4000000
    CHECK(global_p.get_number_population() == 4000000);

    CHECK(global_p.get_situation_day(1).S_[0] == 3500000);
    CHECK(global_p.get_situation_day(1).S_[1] == 0);
    CHECK(global_p.get_situation_day(1).I_[0] == 500000);
    CHECK(global_p.get_situation_day(1).I_[1] == 0);
    CHECK(global_p.get_situation_day(1).H_ == 0);
    CHECK(global_p.get_situation_day(1).D_ == 0);

    SUBCASE("Checking errors by throw") {
      /////////////////////Ecception in parameters///////////////////
      std::vector<People> days_e;
      CHECK_THROWS_AS(Pandemic(days_e, p_w1, N), std::runtime_error);
      CHECK_THROWS_WITH(
          Pandemic(days_e, p_w1, N),
          "The values of the parameters must be inside the interval [0,1] !");

      CHECK_THROWS_AS(Pandemic(days_e, p_w2, N), std::runtime_error);
      CHECK_THROWS_WITH(
          Pandemic(days_e, p_w2, N),
          "The value of the parameters in case of vaccination must be 0 !");
      //////////////////////////Ecception in people//////////////////////
      std::vector<People> days1;
      Pandemic global_w1(days1, p_r, N);
      CHECK_THROWS_AS(global_w1.set_initial_condition(sub_w1),
                      std::runtime_error);
      CHECK_THROWS_WITH(global_w1.set_initial_condition(sub_w1),
                        "The inserted values must be coherent with the number "
                        "of the population !");

      Pandemic global_w2(days_e, p_r, N);
      CHECK_THROWS_AS(global_w2.set_initial_condition(sub_w2),
                      std::runtime_error);
      CHECK_THROWS_WITH(
          global_w2.set_initial_condition(sub_w2),
          "At the begining the number of vaccinated people must be null! ");

      std::vector<People> days3;
      Pandemic global_w3(days3, p_r, N);
      CHECK_THROWS_AS(global_w3.set_initial_condition(sub_w3),
                      std::runtime_error);
      CHECK_THROWS_WITH(global_w3.set_initial_condition(sub_w3),
                        "It can't start the evolution without any susceptible "
                        "or any infected ! ");
      std::vector<People> days4;
      Pandemic global_w4(days4, p_r, N);
      CHECK_THROWS_AS(global_w4.set_initial_condition(sub_w4),
                      std::runtime_error);
      CHECK_THROWS_WITH(
          global_w4.set_initial_condition(sub_w4),
          "It doesn't make sense starting with some healed or dead people");

      ////////////////////The initial condition must be absent//////////////////
      People sub{{300, 0}, {20, 0}, 0, 0};

      CHECK_THROWS_AS(global_p.set_initial_condition(sub), std::runtime_error);
      CHECK_THROWS_WITH(global_p.set_initial_condition(sub),
                        "This simulation has already an initial condition, "
                        "please start another simulation");

      ///////////////////////The first day is 1 not 0/////////////////////
      CHECK_THROWS_AS(global_p.get_situation_day(0), std::runtime_error);
      CHECK_THROWS_WITH(global_p.get_situation_day(0),
                        "The simulation starts from day one!");
      ///////////////////Check_R0////////////////
      CHECK_THROWS_AS(global_p.set_Parameters(p_w3), std::runtime_error);
      CHECK_THROWS_WITH(global_p.set_Parameters(p_w3),
                        "The simulation can't start if the critical threshold "
                        "is minor than or equal to one! ");
    }

    SUBCASE("Checking the output messages") {
      std::cout << "Checking the output messages"
                << "\n\n";
      ////////////////////Constructor/////////////////////////////////
      Parameters c{{0.7, 0.}, {0.4, 0.}, {0.2, 0.}, 0.};

      global_p.check_normalization(c);
      std::cout << "First check : ok!"
                << "\n\n";

      std::cout << "Second check :" << '\n';
      Parameters e({0.7, 0.}, {0.5, 0.}, {0.9, 0.}, 0.);

      global_p.check_normalization(e);

      CHECK(e.omega[0] == doctest::Approx(0.1).epsilon(0.01));
      CHECK(e.beta[0] == doctest::Approx(0.7).epsilon(0.01));
      CHECK(e.gamma[0] == doctest::Approx(0.5).epsilon(0.01));

      std::cout << "Third check : " << '\n';
      Parameters d({0.7, 0.}, {0.4, 0.}, {0.7, 0.}, 0.);
      global_p.set_Parameters(d);

      CHECK(global_p.get_Parameters().omega[0] ==
            doctest::Approx(0.2).epsilon(0.01));

      std::vector<People> days5;
      Pandemic norm(days5, d, 100);

      CHECK(norm.get_Parameters().omega[0] ==
            doctest::Approx(0.2).epsilon(0.01));
    }

    SUBCASE("Checking members of the Pandemic class") {
      //////////checking change_after_vacc//////////
      Parameters p_({0.75, 0.}, {0.3, 0.}, {0.4, 0.}, 0.);
      std::vector<People> days3;

      Pandemic members(days3, p_, 3000000);
      members.introduce_vacc(0.15);

      CHECK(members.get_Parameters().vax == 0.15);

      members.change_after_vacc();

      CHECK(members.get_Parameters().beta[1] ==
            doctest::Approx(0.2175).epsilon(0.000001));
      CHECK(members.get_Parameters().gamma[1] ==
            doctest::Approx(0.56).epsilon(0.000001));
      CHECK(members.get_Parameters().omega[1] ==
            doctest::Approx(0.14).epsilon(0.000001));
      //////////////////////the vaccine must be introduced just one
      ///time///////////////////////
      CHECK_THROWS_AS(members.introduce_vacc(0.65), std::runtime_error);
      CHECK_THROWS_WITH(members.introduce_vacc(0.65),
                        "You can't introduce the vaccine more than once");

      ///////////calculate_R0///////////////////

      CHECK(members.calculate_R0(members.get_Parameters()) ==
            doctest::Approx(1.071428).epsilon(0.000001));

      Parameters p({0.85, 0.}, {0.25, 0.}, {0.5, 0.}, 0.);
      CHECK(members.calculate_R0(p) ==
            doctest::Approx(1.13333333333333).epsilon(0.000001));

      Parameters pp({0.65, 0.}, {0.2, 0.}, {0.35, 0.}, 0.);
      CHECK(members.calculate_R0(pp) ==
            doctest::Approx(1.181818).epsilon(0.000001));
    }

    SUBCASE("Copy Constructor") {
      Pandemic copy_global(global_p);
      CHECK(copy_global.get_number_population() ==
            global_p.get_number_population());
      CHECK(copy_global.get_Parameters() == global_p.get_Parameters());
      CHECK(copy_global.get_situation_day(1) == global_p.get_situation_day(1));
      CHECK(copy_global.get_days() == 1);
    }
  }
}
