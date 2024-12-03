#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "equation.hpp"

#include <memory>

#include "doctest.h"

TEST_CASE("Equation Class") {
  SUBCASE("Contructors") {
    Parameters p{{0.5, 0.0}, {0.6, 0.0}, {0.4, 0.0}, 0.0};
    People sub{{6399, 0}, {1, 0}, 0, 0};
    SUBCASE("Default") {
      std::unique_ptr<Equation> eq0 = std::make_unique<Equation>();

      CHECK(eq0->get_days() == 1);
      CHECK(eq0->get_Parameters().beta[0] == 0.6);
      CHECK(eq0->get_Parameters().beta[1] == 0.0);
      CHECK(eq0->get_Parameters().gamma[0] == 0.2);
      CHECK(eq0->get_Parameters().gamma[1] == 0.0);
      CHECK(eq0->get_Parameters().omega[0] == 0.35);
      CHECK(eq0->get_Parameters().omega[1] == 0.0);
      CHECK(eq0->get_Parameters().vax == 0.0);
      CHECK(eq0->get_number_population() == 2500);

      CHECK(eq0->get_situation_day(1).S_[0] == 2000);
      CHECK(eq0->get_situation_day(1).S_[1] == 0);
      CHECK(eq0->get_situation_day(1).I_[0] == 500);
      CHECK(eq0->get_situation_day(1).I_[1] == 0);
      CHECK(eq0->get_situation_day(1).H_ == 0);
      CHECK(eq0->get_situation_day(1).D_ == 0);

      CHECK(eq0->calculate(1)[0] == 2000);
      CHECK(eq0->calculate(1)[1] == 500);
      CHECK(eq0->calculate(1)[2] == 0);
      CHECK(eq0->calculate(1)[3] == 0);

      People sub_1{{2100, 100}, {180, 120}, 0, 0};
      eq0->add_data(sub_1);

      CHECK(eq0->get_situation_day(2).S_[0] == 2100);
      CHECK(eq0->get_situation_day(2).S_[1] == 100);
      CHECK(eq0->get_situation_day(2).I_[0] == 180);
      CHECK(eq0->get_situation_day(2).I_[1] == 120);
      CHECK(eq0->get_situation_day(2).H_ == 0);
      CHECK(eq0->get_situation_day(2).D_ == 0);

      CHECK(eq0->calculate(2)[0] == 2200);
      CHECK(eq0->calculate(2)[1] == 300);
      CHECK(eq0->calculate(2)[2] == 0);
      CHECK(eq0->calculate(2)[3] == 0);
    }

    SUBCASE("Parametric") {
      std::vector<People> days;
      sub = {{500000, 0}, {100000, 0}, 0, 0};
      p = {{0.75, 0.}, {0.3, 0.}, {0.35, 0.}, 0.};

      ////////////Creating an Equation object with the parametric
      ///Constructor////////////////
      std::unique_ptr<Equation> eq1 =
          std::make_unique<Equation>(days, p, 600000);

      ///////////Checking the Ereditary dynamic with Pandemic/////////////////

      CHECK(eq1->get_days() == 0);

      CHECK(eq1->get_Parameters().beta[0] == 0.75);
      CHECK(eq1->get_Parameters().beta[1] == 0.);
      CHECK(eq1->get_Parameters().gamma[0] == 0.3);
      CHECK(eq1->get_Parameters().gamma[1] == 0.);
      CHECK(eq1->get_Parameters().omega[0] == 0.35);
      CHECK(eq1->get_Parameters().beta[1] == 0.);
      CHECK(eq1->get_Parameters().vax == 0.);

      CHECK(eq1->get_number_population() == 600000);
      //////////////Adding data/////////////////
      eq1->add_data(sub);

      CHECK(eq1->get_days() == 1);

      CHECK(eq1->get_situation_day(1).S_[0] == 500000);
      CHECK(eq1->get_situation_day(1).S_[1] == 0);
      CHECK(eq1->get_situation_day(1).I_[0] == 100000);
      CHECK(eq1->get_situation_day(1).I_[1] == 0);
      CHECK(eq1->get_situation_day(1).H_ == 0);
      CHECK(eq1->get_situation_day(1).D_ == 0);

      CHECK(eq1->calculate(1)[0] == 500000);
      CHECK(eq1->calculate(1)[1] == 100000);
      CHECK(eq1->calculate(1)[2] == 0);
      CHECK(eq1->calculate(1)[3] == 0);

      SUBCASE(" Specilized Members of Equation") {
        //////////update situation//////////////////

        CHECK(eq1->get_evolution().back().I_[0] == 100000);
        CHECK(eq1->get_evolution().back().I_[1] == 0);
        CHECK(eq1->get_evolution().back().S_[0] == 500000);
        CHECK(eq1->get_evolution().back().S_[1] == 0);
        CHECK(eq1->get_Parameters().beta[0] == 0.75);

        People n{{0, 0}, {0, 0}, 0, 0};
        std::array<double, 6> situation = eq1->update_situation(0, n);

        CHECK(situation[0] == doctest::Approx(437500).epsilon(0.01));
        CHECK(situation[1] == 0);
        CHECK(situation[2] == doctest::Approx(97500).epsilon(0.01));
        CHECK(situation[3] == 0);
        CHECK(situation[4] == 30000);
        CHECK(situation[5] == 35000);
        CHECK(sum(situation) == eq1->get_number_population());

        eq1->add_data(eq1->fix(situation));

        eq1->evolve();

        CHECK(eq1->get_evolution().back().S_[0] == 384180);
        CHECK(eq1->get_evolution().back().S_[1] == 0);
        CHECK(eq1->get_evolution().back().I_[0] == 87445);
        CHECK(eq1->get_evolution().back().I_[1] == 0);
        CHECK(eq1->get_evolution().back().H_ == 59250);
        CHECK(eq1->get_evolution().back().D_ == 69125);
      }

      ///////////////////update_situation() & fix()/////////////////////
      Parameters pp{{0.6, 0.}, {0.2, 0.}, {0.35, 0.}, 0.};
      std::unique_ptr<Equation> eq2 = std::make_unique<Equation>(days, pp, 600);

      People c{{0, 0}, {0, 0}, 0, 0};
      People sub2 = {{550, 0}, {50, 0}, 0, 0};
      eq2->set_initial_condition(sub2);
      CHECK(sum(transform_Array<int, 6>(sub2)) == eq2->get_number_population());
      /////////////////////////////#1/////////////////////////////////
      std::array<double, 6> situation2 = eq2->update_situation(0, c);

      CHECK(situation2[0] == 522.5);
      CHECK(situation2[1] == 0);
      CHECK(situation2[2] == 50);
      CHECK(situation2[3] == 0);
      CHECK(situation2[4] == 10);
      CHECK(situation2[5] == 17.5);
      CHECK(sum((situation2)) == eq2->get_number_population());  // 72

      eq2->add_data(eq2->fix(situation2));

      CHECK(eq2->get_situation_day(2).S_[0] == 523);
      CHECK(eq2->get_situation_day(2).S_[1] == 0);
      CHECK(eq2->get_situation_day(2).I_[0] == 50);
      CHECK(eq2->get_situation_day(2).I_[1] == 0);
      CHECK(eq2->get_situation_day(2).H_ == 10);
      CHECK(eq2->get_situation_day(2).D_ == 17);
      CHECK(sum(transform_Array<int, 6>(eq2->get_situation_day(2))) ==
            eq2->get_number_population());

      ///////////////////////////////////#2///////////////////////////////////////
      std::array<double, 6> situation3 = eq2->update_situation(0, c);

      CHECK(situation3[0] == doctest::Approx(496.85).epsilon(0.000001));
      CHECK(situation3[1] == 0);
      CHECK(situation3[2] == doctest::Approx(48.65).epsilon(0.000001));
      CHECK(situation3[3] == 0);
      CHECK(situation3[4] == doctest::Approx(20).epsilon(0.000001));
      CHECK(situation3[5] == doctest::Approx(34.5).epsilon(0.000001));
      CHECK(sum(situation3) == eq2->get_number_population());  // 72
      CHECK(eq2->get_number_population() - sum(integer_part(situation3)) ==
            2);  // 95

      eq2->add_data(eq2->fix(situation3));

      CHECK(eq2->get_situation_day(3).S_[0] == 498);
      CHECK(eq2->get_situation_day(3).S_[1] == 0);
      CHECK(eq2->get_situation_day(3).I_[0] == 48);
      CHECK(eq2->get_situation_day(3).I_[1] == 0);
      CHECK(eq2->get_situation_day(3).H_ == 20);
      CHECK(eq2->get_situation_day(3).D_ == 34);
      CHECK(sum(transform_Array<int, 6>(eq2->get_situation_day(3))) ==
            eq2->get_number_population());

      ////////////////////////////////#3//////////////////////////////////
      std::array<double, 6> situation4 = eq2->update_situation(0, c);

      CHECK(situation4[0] == doctest::Approx(474.096).epsilon(0.000001));
      CHECK(situation4[1] == 0);
      CHECK(situation4[2] == doctest::Approx(45.504).epsilon(0.000001));
      CHECK(situation4[3] == 0);
      CHECK(situation4[4] == doctest::Approx(29.6).epsilon(0.000001));
      CHECK(situation4[5] == doctest::Approx(50.8).epsilon(0.000001));
      CHECK(sum(situation4) == eq2->get_number_population());  // 72
      CHECK(eq2->get_number_population() - sum(integer_part(situation4)) == 2);

      eq2->add_data(eq2->fix(situation4));

      CHECK(eq2->get_situation_day(4).S_[0] == 474);
      CHECK(eq2->get_situation_day(4).S_[1] == 0);
      CHECK(eq2->get_situation_day(4).I_[0] == 45);
      CHECK(eq2->get_situation_day(4).I_[1] == 0);
      CHECK(eq2->get_situation_day(4).H_ == 29);
      CHECK(eq2->get_situation_day(4).D_ == 52);
      CHECK(sum(transform_Array<int, 6>(eq2->get_situation_day(4))) ==
            eq2->get_number_population());
      /////////////////////////evolve()/////////////////
      eq2->evolve();
      CHECK(eq2->get_days() == 5);
      CHECK(eq2->get_situation_day(5).S_[0] == 452);
      CHECK(eq2->get_situation_day(5).S_[1] == 0);
      CHECK(eq2->get_situation_day(5).I_[0] == 41);
      CHECK(eq2->get_situation_day(5).I_[1] == 0);
      CHECK(eq2->get_situation_day(5).H_ == 38);
      CHECK(eq2->get_situation_day(5).D_ == 69);
      ////////////////////Introducing the option of the
      ///vaccine//////////////////
      eq2->introduce_vacc(0.24);
      eq2->change_after_vacc();

      CHECK(eq2->get_Parameters().beta[1] ==
            doctest::Approx(0.174).epsilon(0.001));
      CHECK(eq2->get_Parameters().omega[1] ==
            doctest::Approx(0.1225).epsilon(0.001));
      CHECK(eq2->get_Parameters().gamma[1] ==
            doctest::Approx(0.4275).epsilon(0.001));
      /////////sorting => is _vaccinated///////////
      eq2->sorting();

      CHECK(eq2->get_days() == 5);
      CHECK(static_cast<double>(eq2->get_situation_day(5).S_[0]) /
                (sum(eq2->get_situation_day(5).S_)) ==
            doctest::Approx(0.76).epsilon(0.1));
      CHECK(static_cast<double>(eq2->get_situation_day(5).S_[1]) /
                (sum(eq2->get_situation_day(5).S_)) ==
            doctest::Approx(0.24).epsilon(0.1));
      CHECK(eq2->get_situation_day(5).I_[0] == 41);
      CHECK(eq2->get_situation_day(5).I_[1] == 0);
      CHECK(eq2->get_situation_day(5).H_ == 38);
      CHECK(eq2->get_situation_day(5).D_ == 69);

      CHECK(sum(transform_Array<int, 6>((eq2->get_evolution()).back())) ==
            eq2->get_number_population());

      /////////////////////////update_situation with vaccine
      /////////////////////////////
      People sorted{{344, 108}, {41, 0}, 38, 69};
      eq2->add_data(sorted);
      People last0 = eq2->get_evolution().back();

      CHECK(last0.S_[0] == 344);
      CHECK(last0.S_[1] == 108);
      CHECK(last0.I_[0] == 41);
      CHECK(last0.I_[1] == 0);
      CHECK(last0.H_ == 38);
      CHECK(last0.D_ == 69);

      ////////////////#1////////////////
      People e{{0, 0}, {0, 0}, 0, 0};
      People natural1 = eq2->fix(eq2->update_situation(0, e));
      People total1 = eq2->fix(eq2->update_situation(1, natural1));

      CHECK(natural1.S_[0] == 331);
      CHECK(natural1.S_[1] == 0);
      CHECK(natural1.I_[0] == 32);
      CHECK(natural1.I_[1] == 0);
      CHECK(natural1.H_ == 46);
      CHECK(natural1.D_ == 83);
      ////////////////////////////////////
      CHECK(total1.S_[0] == 331);
      CHECK(total1.S_[1] == 107);
      CHECK(total1.I_[0] == 32);
      CHECK(total1.I_[1] == 1);
      CHECK(total1.H_ == 46);
      CHECK(total1.D_ == 83);

      eq2->add_data(total1);
      People last1 = eq2->get_evolution().back();

      CHECK(last1.S_[0] == 331);
      CHECK(last1.S_[1] == 107);
      CHECK(last1.I_[0] == 32);
      CHECK(last1.I_[1] == 1);
      CHECK(last1.H_ == 46);
      CHECK(last1.D_ == 83);

      ///////////////////////////////////////////////////////////////////////////
      CHECK(sum(transform_Array<int, 6>((eq2->get_evolution()).back())) ==
            eq2->get_number_population());
      ////////////////#2////////////////
      People e2{{0, 0}, {0, 0}, 0, 0};
      People natural2 = eq2->fix(eq2->update_situation(0, e2));
      People total2 = eq2->fix(eq2->update_situation(1, natural2));

      CHECK(natural2.S_[0] == 320);
      CHECK(natural2.S_[1] == 0);
      CHECK(natural2.I_[0] == 25);
      CHECK(natural2.I_[1] == 0);
      CHECK(natural2.H_ == 53);
      CHECK(natural2.D_ == 94);
      ////////////////////////////////////
      CHECK(total2.S_[0] == 320);
      CHECK(total2.S_[1] == 107);
      CHECK(total2.I_[0] == 25);
      CHECK(total2.I_[1] == 1);
      CHECK(total2.H_ == 53);
      CHECK(total2.D_ == 94);

      eq2->add_data(total2);
      People last2 = eq2->get_evolution().back();

      CHECK(last2.S_[0] == 320);
      CHECK(last2.S_[1] == 107);
      CHECK(last2.I_[0] == 25);
      CHECK(last2.I_[1] == 1);
      CHECK(last2.H_ == 53);
      CHECK(last2.D_ == 94);
      ///////////////////////////////////////////////////////////////////////////////////
      CHECK(sum(transform_Array<int, 6>((eq2->get_evolution()).back())) ==
            eq2->get_number_population());

      CHECK(eq2->get_days() == 8);
      //////////////////////////evolve_vaccine()///////////////////////////////
      eq2->evolve_vaccine();

      CHECK(eq2->get_days() == 9);

      People evolved = eq2->get_evolution().back();

      CHECK(evolved.S_[0] == 311);
      CHECK(evolved.S_[1] == 106);
      CHECK(evolved.I_[0] == 19);
      CHECK(evolved.I_[1] == 1);
      CHECK(evolved.H_ == 59);
      CHECK(evolved.D_ == 104);

      CHECK(sum(transform_Array<int, 6>((eq2->get_evolution()).back())) ==
            eq2->get_number_population());

      SUBCASE("Copy Constructor") {
        std::unique_ptr<Equation> copy_eq1 = std::make_unique<Equation>(*eq1);
        CHECK(copy_eq1->get_number_population() ==
              eq1->get_number_population());
        CHECK(copy_eq1->get_Parameters() == eq1->get_Parameters());
        CHECK(copy_eq1->get_situation_day(1) == eq1->get_situation_day(1));
        CHECK(copy_eq1->get_days() == 1);
      }
    }
  }
}
