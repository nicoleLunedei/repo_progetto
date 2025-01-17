#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "agent.hpp"

#include <memory>

#include "doctest.h"
void check_state(Agent& a) {
  //////////Saving the previous situation of the matrix////////////
  Matrix<Person> previous(a.get_matrix());
  CHECK(previous == a.get_matrix());
  /////////Evolving situation////////////
  People next{{0, 0}, {0, 0}, 0, 0};
  a.evolve(next);
  bool state;
  ///////////Checking each element///////////77
  a.get_matrix().each_cell([previous, &state](Person& cell, std::size_t r,
                                                  std::size_t c) {
    ////////////Checking each cell///////////////
    switch (previous.read(r, c)) {
      case Person::Susceptible:

        state = (cell == Person::Susceptible || cell == Person::Infected);
        break;
      case Person::Susceptible_v:
        state = (cell == Person::Susceptible_v || cell == Person::Infected_v);
        break;
      case Person::Infected:
        state = (cell == Person::Healed || cell == Person::Dead ||
                 cell == Person::Infected);
        break;
      case Person::Infected_v:
        state = (cell == Person::Healed || cell == Person::Dead ||
                 cell == Person::Infected_v);
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
TEST_CASE("Function"){
  std::vector<Person> line0(7,Person::Susceptible);
  CHECK(sum_one_line(line0) == 0);
  std::vector<Person> line1(7,Person::Infected);
  CHECK(sum_one_line(line1) == 7);

  std::vector<Person> line2(7,Person::Dead);
  CHECK(sum_one_line(line2) == 21);

  std::vector<Person> line3{Person::Susceptible_v, Person::Infected_v, Person::Healed};
  CHECK(sum_one_line(line3) == 11);
}

TEST_CASE("Agent Class") {
  std::unique_ptr<Agent> ag0 = std::make_unique<Agent>();

  SUBCASE("Constructors") {
    SUBCASE("Default") {
      CHECK(ag0->get_side() == 50);
      CHECK(ag0->get_matrix().M[0].size() == 50);

      CHECK(ag0->get_Parameters().beta.no_vax == 0.6);
      CHECK(ag0->get_Parameters().beta.vax == 0.);
      CHECK(ag0->get_Parameters().gamma.no_vax == 0.2);
      CHECK(ag0->get_Parameters().gamma.vax == 0.);
      CHECK(ag0->get_Parameters().omega.no_vax == 0.35);
      CHECK(ag0->get_Parameters().omega.vax == 0.);
      CHECK(ag0->get_Parameters().v == 0.);

      CHECK(ag0->get_situation_day(1).S_.no_vax == 2499);
      CHECK(ag0->get_situation_day(1).S_.vax == 0);
      CHECK(ag0->get_situation_day(1).I_.no_vax == 1);
      CHECK(ag0->get_situation_day(1).I_.vax == 0);

      ag0->get_matrix().each_cell(
          [&ag0](Person& cell, std::size_t r, std::size_t c) {
            if (r == (ag0->get_matrix().M.size()) / 2 &&
                c == ag0->get_matrix().M.size() / 2) {
              CHECK(cell == Person::Infected);
            } else {
              CHECK(cell == Person::Susceptible);
            }
          });
    }
    SUBCASE("Parametric") {
      std::vector<People> pop;
      Parameters par{{0.6, 0.}, {0.25, 0.}, {0.3, 0.}, 0.};

      CHECK_THROWS_AS(Agent ag1(pop, par, 10011), std::runtime_error);
      CHECK_THROWS_WITH(Agent ag1(pop, par, 10011),
                        "The number of the population must a perfect square");

      std::unique_ptr<Agent> ag1 = std::make_unique<Agent>(pop, par, 400);

      CHECK(ag1->get_side() == 20);
      CHECK(ag1->get_matrix().M[0].size() == 20);

      CHECK(ag1->get_Parameters().beta.no_vax == 0.6);
      CHECK(ag1->get_Parameters().beta.vax == 0.);
      CHECK(ag1->get_Parameters().gamma.no_vax == 0.25);
      CHECK(ag1->get_Parameters().gamma.vax == 0.);
      CHECK(ag1->get_Parameters().omega.no_vax == 0.3);
      CHECK(ag1->get_Parameters().omega.vax == 0.);
      CHECK(ag1->get_Parameters().v == 0.);

      ag1->get_matrix().each_cell([&ag1](Person& cell) {
        CHECK(cell == Person::Susceptible);
      });
      SUBCASE("Member Functions") {
        ////////////////Draw_matrix with the initial
        ///condition/////////////////////
        People begin{{390, 0}, {10, 0}, 0, 0};
        //////////First day///////////////
        ag1->draw_matrix(begin);
        ////////////////collection_data/////////////////
        /////////without evolution//////////////
        /////////Second day//////////////
        People blank{{0, 0}, {0, 0}, 0, 0};
        ag1->data_collection(blank);

        CHECK(ag1->get_days() == 2);

        ////////////////Testing counting/////////////
        CHECK(blank.S_.no_vax == 390);
        CHECK(blank.S_.vax == 0);
        CHECK(blank.I_.no_vax == 10);
        CHECK(blank.I_.vax == 0);
        CHECK(blank.H_ == 0);
        CHECK(blank.D_ == 0);
      

        ////////Checking on toroidale structure/////////
        ///////////////Show_cell////////////////////////
        CHECK(ag1->show_cell(0, 0) == ag1->show_cell(0, 100));
        CHECK(ag1->show_cell(100, 100) == ag1->show_cell(100, 0));

        ////////////////sorting/////////////////////////
        ag1->introduce_vacc(0.4);
        ag1->sorting();
        ///////////Confirming the inclination to get vaccinated//////////////
        CHECK(static_cast<double>(ag1->get_situation_day(2).S_.no_vax) /
                  (total(ag1->get_situation_day(2).S_)) ==
              doctest::Approx(0.6).epsilon(0.1));
        CHECK(static_cast<double>(ag1->get_situation_day(2).S_.vax) /
                  (total(ag1->get_situation_day(2).S_)) ==
              doctest::Approx(0.4).epsilon(0.1));
    
        ////////////////infected_neighbours/////////////
        People n{{0, 0}, {0, 0}, 0, 0};
        ag1->evolve(n);
   
        ag1->get_matrix().each_cell([&ag1](Person& cell, std::size_t r,
                                               std::size_t c) {
          if (cell == Person::Susceptible || cell == Person::Susceptible_v) {
            CHECK(ag1->infected_neighbours(r, c) <= 8);
           
          }
        }

        );
        ///////////////change_state & evolve/////////////////////
        ////////////////#1////////////////////
        check_state(*ag1);
      
        CHECK(ag1->get_days() == 4);
        /////////////////#2/////////////////////
        check_state(*ag1);

        CHECK(ag1->get_days() == 5);

        SUBCASE("Copy Constructor") {
          std::unique_ptr<Agent> copy_ag1 = std::make_unique<Agent>(*ag1);
          CHECK(copy_ag1->get_number_population() ==
                ag1->get_number_population());
          CHECK(copy_ag1->get_Parameters() == ag1->get_Parameters());
          CHECK(copy_ag1->get_situation_day(1) == ag1->get_situation_day(1));
          CHECK(copy_ag1->get_days() == 1);
        }
      }
    }
  }
}
