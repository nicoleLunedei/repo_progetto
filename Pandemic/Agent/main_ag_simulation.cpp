#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "agent.hpp"

////////////Creating new colors////////////
sf::Color Orange(255, 165, 0);
sf::Color Aquamarine(127, 255, 212);

sf::Color paint(Person& element) {
  sf::Color color;
  switch (element) {
    case (0): {
      color = sf::Color::Green;
      break;
    }
    case (4): {
      color = Aquamarine;

      break;
    }
    case (1): {
      color = sf::Color::Red;
      break;
    }
    case (5): {
      color = Orange;
      break;
    }
    case (2): {
      color = sf::Color::Blue;
      break;
    }
    case (3): {
      color = sf::Color::Magenta;
      break;
    }
  }
  return color;
}
void writing_Circles(Matrix<sf::CircleShape> circ, std::size_t r,
                     std::size_t c) {
  const float r_ = static_cast<float>(r);
  const float c_ = static_cast<float>(c);

  circ[r][c].setPosition(120.f + (c_ * 8.f) + 0.1f, 100.f + (r_ * 8.f) + 0.1f);
  circ[r][c].setRadius(4);
}

int main() {
  int T;
  char sim;
  std::cout << "Hi! Do you want to run a default[D] or a personalized[P] "
               "simulation?[D/P]"
            << '\n';
  std::cin >> sim;

  while (sim != 'D' && sim != 'P') {
    ///////////////////////Cleaning the in stream///////////////////
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Please insert D, for default, or P , for personalized "
              << '\n';
    std::cin >> sim;
  }

  if (sim == 'D') {
    /////////////////////Default simulation/////////////////////
    //////////////////Default Agent object///////////////
    std::unique_ptr<Agent> ag = std::make_unique<Agent>();

    std::cout << " Great! You've chosen the default simulation, here below "
                 "some data :"
              << '\n';
    std::cout << " The population corrisponds to "
              << ag->get_number_population() << " people" << '\n';
    std::cout << " Probability to infect : "
              << ag->get_Parameters().beta[0] * 100 << "%" << '\n';
    std::cout << " Probability of healing :  "
              << ag->get_Parameters().gamma[0] * 100 << "%" << '\n';
    std::cout << " Probability of dying :"
              << ag->get_Parameters().omega[0] * 100 << "%" << '\n';
    std::cout << " Probability of getting vaccinated , initially is null, "
                 "later you'll have the chance to introduce it."
              << "\n\n";
    std::cout << "Ok ! Let's get started ! "
              << "\n\n";
    ///////////////////////////////////////////////////////////////////////////

    std::cout << " For how many days do you want your simulation to last?"
              << '\n';
    std::cin >> T;
    std::cout << "After the apperence of the graphic window, when you're ready "
                 "you can press the 'Enter key' to start the simulation "
              << '\n';

    ///////////////SFML WINDOW/////////////////

    sf::RenderWindow window1;
    window1.setPosition(sf::Vector2i(100, 50));
    ////////Creation of the Matrix of circles corrisponding to the Matrix of
    ///Person of the Agent object ///////////
    sf::CircleShape circle1;
    Matrix<sf::CircleShape> circles(ag->get_side(), circle1);

    //////Showing tha Matrix on the terminal//////////
    std::cout << "Day N° 1 " << '\n';
    std::cout << ag->get_matrix() << '\n';
    std::cout << ag->get_situation_day(1) << '\n';

    bool running = true;
    bool simulationOn = false;
    int t = 2;
    /////////////////////////////////Running state On//////////////////
    while (running) {
      window1.create(sf::VideoMode(800, 600), "SIHD: without vaccine");

      /////////////Opening of the window/////////////
      while (window1.isOpen()) {
        sf::Event event1;

        ///////////////Polling events/////////////////
        while (window1.pollEvent(event1)) {
          // Closing
          if (event1.type == sf::Event::Closed) {
            window1.close();
          }
          // Launching
          if (event1.type == sf::Event::KeyPressed &&
              event1.key.code == sf::Keyboard::Space) {
            simulationOn = true;
          }
        }
        ////////Cleaning window and preparing it for new
        ///drawings/////////////////77
        window1.clear(sf::Color::Black);

        //////////////Intentional launch by Space bar/////////////////
        /////////////Simulation state On/////////////////
        if (simulationOn) {
          //////////New Day //////////////
          People next{{0, 0}, {0, 0}, 0, 0};
          ag->evolve(next);

          ///////////////Drawing circles//////
          ag->get_matrix().inside_matrix(
              [&window1, &circles](Person& cell, std::size_t r, std::size_t c) {
                const float r_ = static_cast<float>(r);
                const float c_ = static_cast<float>(c);

                circles[r][c].setPosition(120.f + (c_ * 8.f) + 0.1f,
                                          100.f + (r_ * 8.f) + 0.1f);
                circles[r][c].setRadius(4);
                // circles[r][c].setRadius(4);
                // circles[r][c].setPosition(120.f + (c * 8.f)+ 0.1f , 100.f +
                // (r * 8.f )+ 0.1f);
                // writing_Circles(circles,r,c);
                circles[r][c].setFillColor(paint(cell));
                window1.draw(circles[r][c]);
              });

          ////////////////////Printing Matrix and data on the
          ///terminal////////////
          std::cout << "Day N°" << t << '\n';
          std::cout << ag->get_matrix();
          std::cout << "Situation data: " << '\n';
          std::cout << ag->get_situation_day(t) << "\n\n";

          ///////Increasing day counter////////////
          t++;
          ////////////Imposing a delay//////////////
          std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        } else {
          ////////////////Shows the last Matrix registered/////////
          ag->get_matrix().inside_matrix(
              [&window1, &circles](Person& cell, std::size_t r, std::size_t c) {
                const float r_ = static_cast<float>(r);
                const float c_ = static_cast<float>(c);

                circles[r][c].setPosition(120.f + (c_ * 8.f) + 0.1f,
                                          100.f + (r_ * 8.f) + 0.1f);
                circles[r][c].setRadius(4);
                // writing_Circles(circles,r,c);
                circles[r][c].setFillColor(paint(cell));
                window1.draw(circles[r][c]);
              });
        }

        ////////////First Stop///////////
        if (t == (T + 1)) {
          simulationOn = false;
        }
        ///////////////Second Stop//////////////////
        if (sum(ag->get_evolution().back().I_) == 0) {
          simulationOn = false;
        }

        //////////Updating window/////////////////
        window1.display();
        ////////////////////Closing window///////////////////////
      }
      //////////////////"Still Infected" people scope////////////////////
      if (sum(ag->get_evolution().back().I_) > 0) {
        char finish;
        std::cout << " There are still infected people, do you want to finish "
                     "the simulation?[y/n]"
                  << '\n';
        std::cin >> finish;
        while (finish != 'y' && finish != 'n') {
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << "Please, insert 'y' or 'n' " << '\n';
          std::cin >> finish;
        }
        /////////////////"Yes" scope /////////////////////
        if (finish == 'y') {
          std::cout << "Great! Press again the Space bar when the window is "
                       "opened, please"
                    << "\n\n";
          ///////////////////Opening again the window //////////////////
        }  ////////////////"Yes" scope closed/////////////
        else {
          running = false;
          std::cout << "Alright! Thanks for your time!"
                    << "\n\n";
        }  ////////////////"No" scope closed/////////////
      }    //////////////////"Still Infected" people scope////////////////////
      else {
        ///////////////////Running state Off//////////////
        running = false;
        std::cout << "That's all! Thanks for your time!"
                  << "\n\n";
      }

    }  ///////////////////Running state//////////////

    std::cout << "Data of your simulation :"
              << "\n\n";
    std::cout << "Number of days : " << ag->get_days() << "\n\n";
    std::cout << "Situation of the last day : " << ag->get_evolution().back()
              << "\n\n";
    std::cout << "Critical threshold : "
              << ag->calculate_R0(ag->get_Parameters()) << "\n\n";
  } else {
    /////////////////////////Personalized simulation
    //////////////////////Limits////////////
    int MAX_IT = 5;
    int it = 0;
    int N;
    Parameters prob;
    People people;
    std::vector<People> days;

    //////////////////////////////Introducing the type
    ///simulation//////////////////////////
    std::cout << " Awesome! You've chosen the personalized simulation! Now "
                 "please insert your data"
              << '\n';
    std::cout << " In this simulation you will have tha chance to insert the "
                 "probability to get vaccinated "
              << "\n\n";

    std::cout << " Number population (max = 5329 )" << '\n';
    std::cin >> N;

    if (N > 5329) {
      char change;
      std::cout << "You're number population is too large for the sfml window (max = 5329), do you want to "
                   "change ?[y/n]"
                << '\n';
      std::cin >> change;

      while (change != 'y' && change != 'n') {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please, insert 'y', for yes, or 'n', for no" << '\n';
        std::cin >> change;
      }
      if (change == 'y') {
        std::cout << "Great! Insert again your number population" << '\n';
        std::cin >> N;
      }
    }

    std::cout << "Probability to infect [0,1]" << '\n';
    std::cin >> prob.beta[0];
    std::cout << "Probability of healing [0,1] " << '\n';
    std::cin >> prob.gamma[0];
    std::cout << "Probability of dying [0,1] " << '\n';
    std::cin >> prob.omega[0];
    std::cout << " and the probability of getting vaccination, initially must "
                 "be null, later you'll have the chance to introduce it."
              << "\n\n";
    std::cout << "Ok ! Let's get started ! "
              << "\n\n";

    ////////////////////Creating the agent object by smart
    ///pointer//////////////////////////
    std::unique_ptr<Agent> ag_;
    bool input0 = false;
    while (!input0) {
      try {
        //////////////Assigning the input data//////////
        ag_ = std::make_unique<Agent>(days, prob, N);

        input0 = true;

      } catch (std::runtime_error& e) {
        //////////////////////////Handling ecceptions/////////////////////////
        std::cout << "Error :" << e.what() << "\n\n";
        ///////////////////Cleaning the in stream////////////
        std::cin.clear();  // Remove the error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please correct your data, according to the error" << '\n';

        if (!(std::string(e.what()) ==
              "The simulation with the vaccine can't start if the critical "
              "threshold is minor than one! ")) {
          std::cout << "Number of population" << '\n';
          std::cin >> N;

        } else {
          std::cout << "R_0 : " << ag_->calculate_R0(prob) << "\n\n";
        }

        std::cout << "The probabilities, in the previous order" << '\n';
        std::cin >> prob.beta[0] >> prob.gamma[0] >> prob.omega[0];
      }
      ///////////////////////////////////////////////////////////////////
    }
    ///////////////////////Asking for the initial
    ///condition//////////////////////
    std::cout
        << "Now insert the condition of the first day you want to begin with."
        << "\n\n";
    std::cout
        << "Susceptiple, Infected, Healed and Dead (the last two must be null)"
        << "\n\n";
    std::cin >> people;

    bool input1 = false;
    //////////////////try and catch while loop////////////////////////
    while (!input1) {
      try {
        ag_->draw_matrix(people);

        input1 = true;
      } catch (std::runtime_error& e) {
        //////////////////////////Handling ecceptions/////////////////////////
        if (std::string(e.what()) !=
                "This simulation has already an initial condition, please "
                "start another simulation" &&
            std::string(e.what()) != "You already set the initial condition") {
          std::cout << "Error: " << e.what() << "\n\n";
          //////////////////Cleaning the in stream///////////
          std::cin.clear();  // Remove the error state
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << "Please correct your data, according to the error, and "
                       "insert them in the same order"
                    << '\n';
          std::cin >> people;
        } else {
          std::cout << "Error: " << e.what() << '\n';
          break;
        }

        it++;
        if (it == MAX_IT) {
          std::cout << " The attempts are finished! "
                    << "\n\n";

          people = {{1, 0}, {1, 0}, 0, 0};
          break;
        }
      }
    }

    //////////////////////Asking for the type duration of
    ///simulation//////////////////////////
    char duration_;
    std::cout << " Do you want to evolve the simulation AUTOMATICALLY until "
                 "the infected people are finished ['A'] or to CHOOSE the "
                 "number of days ['C']?"
              << '\n';
    std::cin >> duration_;
    while (duration_ != 'A' && duration_ != 'C') {
      //////////////////Cleaning the in stream///////////
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Please, insert 'A' or 'C' " << '\n';
      std::cin >> duration_;
    }
    if (duration_ == 'A') {  ////////////AUTOMATICALLY////////////////
                             ///////////////SFML Window/////////////////

      sf::RenderWindow window_(sf::VideoMode(800, 600), "SIHD");

      window_.setPosition(sf::Vector2i(100, 50));
      ////////Creation of the Matrix of circles corrisponding to the Matrix of
      ///Person of the Agent object ///////////
      sf::CircleShape circle1_;
      Matrix<sf::CircleShape> circles_(ag_->get_side(), circle1_);

      //////Showing tha Matrix on the terminal//////////
      std::cout << "Day N° 1 " << '\n';
      std::cout << ag_->get_matrix() << '\n';
      std::cout << ag_->get_situation_day(1) << "\n\n";

      //////////Some Information///////////////
      std::cout
          << " Fanatastic, the simulation will go on undisturbed, but you'll "
             "be able to interact with the window with the following keys :"
          << "\n\n";
      std::cout << " Space bar -> to launch the simulation"
                << "\n\n";
      std::cout << " 'P' -> to pause the simulation"
                << "\n\n";
      std::cout << " 'V' -> to pause  the simulation and introduce the vaccine"
                << "\n\n";
      std::cout
          << " When the window appears you click you can launch the simulation"
          << "\n\n";

      bool simulationOn = false;
      int t = 2;

      /////////////Opening window/////////////
      while (window_.isOpen()) {
        sf::Event event_;

        ///////////////Polling events/////////////////
        while (window_.pollEvent(event_)) {
          ///////////Closing//////////////////
          if (event_.type == sf::Event::Closed) {
            window_.close();
          }
          ///////////////////Launching/////////////////////////
          if (event_.type == sf::Event::KeyPressed &&
              event_.key.code == sf::Keyboard::Space) {
            simulationOn = true;
          }

          ////////////////////Pausing///////////////////
          if (event_.type == sf::Event::KeyPressed &&
              event_.key.code == sf::Keyboard::P) {
            simulationOn = false;
          }
          ///////////////////Introducing vaccine//////////////////////
          if (event_.type == sf::Event::KeyPressed &&
              event_.key.code == sf::Keyboard::V) {
            if (ag_->get_Parameters().vax != 0) {
              throw std::runtime_error{
                  "It has been already set the probability of getting "
                  "vaccinated"};
              std::cout << " Press the Space bar to continue"
                        << "\n\n";
            }
            //////////////////Impossible introducing vaccine///////
            if (sum(ag_->get_evolution().back().S_) == 0) {
              throw std::runtime_error{"There are no susceptible people left"};
              std::cout << " Press the Space bar to continue"
                        << "\n\n";
            }

            simulationOn = false;
            double v;
            std::cout << "Insert the probability of getting vaccinated"
                      << "\n\n";
            std::cin >> v;
            bool input2 = false;
            while (!input2) {
              try {
                ag_->introduce_vacc(v);
                ag_->change_after_vacc();
                ag_->sorting();

                input2 = 2;
              } catch (std::runtime_error& e) {
                std::cout << "Error: " << e.what() << "\n\n";
                ///////////////////Cleaning the in stream/////////////////
                std::cin.clear();  // Remove the errore state
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                '\n');
                std::cin >> v;
                it++;
                if (it == MAX_IT) {
                  std::cout << "The attempts are finished! The probability of "
                               "getting vaccinated is 74%"
                            << "\n\n";
                  v = 0.74;
                  break;
                }
              }
            }
            std::cout
                << "For the vaccinated people the probability have changed : "
                << '\n';
            std::cout << "Beta(Infection) :" << ag_->get_Parameters().beta[1]
                      << '\n'
                      << "omega(Death):" << ag_->get_Parameters().omega[1]
                      << '\n'
                      << "gamma (Healing) :" << ag_->get_Parameters().gamma[1]
                      << "\n\n";
            std::cout << "====================================================="
                         "======================"
                      << "\n\n";
          }
        }

        ////////Cleaning window and preparing it for new
        ///drawings//////////////////////////
        window_.clear(sf::Color::Black);

        //////////////Intentional launching  /////////////////
        if (simulationOn) {
          //////////New Day//////////////
          People next{{0, 0}, {0, 0}, 0, 0};
          ag_->evolve(next);

          ///////////////Changing colors//////
          ag_->get_matrix().inside_matrix([&window_, &circles_](Person& cell,
                                                                std::size_t r,
                                                                std::size_t c) {
            const float r_ = static_cast<float>(r);
            const float c_ = static_cast<float>(c);

            circles_[r][c].setPosition(10.f + (c_ * 8.f) + 0.1f,
                                       10.f + (r_ * 8.f) + 0.1f);
            circles_[r][c].setRadius(4);
            // writing_Circles(circles_,r,c);
            circles_[r][c].setFillColor(paint(cell));
            window_.draw(circles_[r][c]);
          });

          std::cout << "Day N° " << t << '\n';
          std::cout << ag_->get_matrix();
          std::cout << "Ecco i numeri : " << '\n';
          std::cout << ag_->get_situation_day(t) << "\n\n";

          ///////Increasing day counter////////////
          t++;
          ////////////Delay//////////////
          std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        } else {
          ////////////////Showing the last Matrix registered/////////
          ag_->get_matrix().inside_matrix([&window_, &circles_](Person& cell,
                                                                std::size_t r,
                                                                std::size_t c) {
            const float r_ = static_cast<float>(r);
            const float c_ = static_cast<float>(c);

            circles_[r][c].setPosition(10.f + (c_ * 8.f) + 0.1f,
                                       10.f + (r_ * 8.f) + 0.1f);
            circles_[r][c].setRadius(4);
            // writing_Circles(circles_,r,c);
            circles_[r][c].setFillColor(paint(cell));
            window_.draw(circles_[r][c]);
          });
        }

        ///////////////Stop//////////////////
        if (sum(ag_->get_evolution().back().I_) == 0) {
          simulationOn = false;
        }

        //////////Updating window////////////
        window_.display();

      }  ////////////////////Closing window///////////////////////

    } else {  //////////////////CHOOSE NUMBER OF DAYS////////////////////

      std::cout << "For how many days do you want your simulation to last?"
                << '\n';
      std::cin >> T;

      //////////////////////////////////////////////////////////////////////////

      ///////////////SFML Window /////////////////

      sf::RenderWindow window_;

      window_.setPosition(sf::Vector2i(100, 50));
      ////////Creation of the Matrix of circles corrisponding to the Matrix of
      ///Person of the Agent object ///////////
      sf::CircleShape circle1_;
      Matrix<sf::CircleShape> circles_(ag_->get_side(), circle1_);

      //////Showing tha Matrix on the terminal//////////
      std::cout << "Day N° 1 " << '\n';
      std::cout << ag_->get_matrix() << '\n';
      std::cout << ag_->get_situation_day(1) << '\n';
      bool running = true;
      bool simulationOn = false;
      int t = 2;
      while (running) {
        window_.create(sf::VideoMode(800, 600), "SIHD");
        while (window_.isOpen()) {
          sf::Event event_;

          ///////////////Polling events/////////////////
          while (window_.pollEvent(event_)) {
            ////////////////Closing//////////
            if (event_.type == sf::Event::Closed) {
              window_.close();
            }
            /////////////Launching///////////
            if (event_.type == sf::Event::KeyPressed &&
                event_.key.code == sf::Keyboard::Space) {
              simulationOn = true;
            }
          }
          ////////Cleaning window and preparing it for new
          ///drawings//////////////////////////
          window_.clear(sf::Color::Black);

          //////////////Intentional launching/////////////////
          if (simulationOn) {
            //////////New day//////////////
            People next{{0, 0}, {0, 0}, 0, 0};
            ag_->evolve(next);

            ///////////////Changing colors//////
            ag_->get_matrix().inside_matrix(
                [&window_, &circles_](Person& cell, std::size_t r,
                                      std::size_t c) {
                  const float r_ = static_cast<float>(r);
                  const float c_ = static_cast<float>(c);

                  circles_[r][c].setPosition(10.f + (c_ * 8.f) + 0.1f,
                                             10.f + (r_ * 8.f) + 0.1f);
                  circles_[r][c].setRadius(4);
                  // writing_Circles(circles_,r,c);
                  circles_[r][c].setFillColor(paint(cell));
                  window_.draw(circles_[r][c]);
                });

            ////////////////////Stampa su terminale della matrice e dei
            ///numeri////////////
            std::cout << "Day Giorno N° " << t << '\n';
            std::cout << ag_->get_matrix();
            std::cout << "Ecco i numeri : " << '\n';
            std::cout << ag_->get_situation_day(t) << "\n\n";

            ///////Increasing day counter ////////////
            t++;
            ////////////ritardo dell'evoluzione //////////////
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
          } else {
            ////////////////Shows the last Matrix registered/////////
            ag_->get_matrix().inside_matrix(
                [&window_, &circles_](Person& cell, std::size_t r,
                                      std::size_t c) {
                  const float r_ = static_cast<float>(r);
                  const float c_ = static_cast<float>(c);

                  circles_[r][c].setPosition(10.f + (c_ * 8.f) + 0.1f,
                                             10.f + (r_ * 8.f) + 0.1f);
                  circles_[r][c].setRadius(4);
                  // writing_Circles(circles_,r,c);
                  circles_[r][c].setFillColor(paint(cell));
                  window_.draw(circles_[r][c]);
                });
          }

          ////////////First Stop///////////
          if (t == (T + 1)) {
            simulationOn = false;
          }
          ///////////////Second Stop//////////////////
          if (sum(ag_->get_evolution().back().I_) == 0) {
            simulationOn = false;
          }

          //////////Updating the window//////////
          window_.display();

        }  ////////////////////Closing window///////////////////////

        //////////////////quando concludono i giorni si chiede se si vuole
        ///continuare ////////////////////
        if (sum(ag_->get_evolution().back().I_) > 0) {
          char finish;
          std::cout << " There are still infected people, do you want to "
                       "finish the simulation?[y/n]"
                    << '\n';
          std::cin >> finish;
          while (finish != 'y' && finish != 'n') {
            std::cout << "Please, insert 'y' or 'n' " << '\n';
            std::cin >> finish;
          }

          if (finish == 'y') {
            if (sum(ag_->get_evolution().back().S_) != 0) {
              double vacc;
              std::cout << "Insert the probability of getting vaccinated(If "
                           "don't want it, just write 0)[0,1["
                        << "\n\n";
              std::cin >> vacc;

              if (vacc == 0) {
                ag_->introduce_vacc(vacc);
                ag_->change_after_vacc();
                ag_->sorting();

                std::cout << "For the vaccinated people the probability have "
                             "changed : "
                          << '\n';
                std::cout << "Beta(Infection) :"
                          << ag_->get_Parameters().beta[1] << '\n'
                          << "omega (Death):" << ag_->get_Parameters().omega[1]
                          << '\n'
                          << "gamma (Healing):"
                          << ag_->get_Parameters().gamma[1] << "\n\n";
                std::cout << "================================================="
                             "=========================="
                          << "\n\n";
              }

            }  /////////////////"Still Susceptiple people" scope closed
               ////////////

            std::cout << "Somma" << sum(ag_->get_evolution().back().S_)
                      << "\n\n";
            std::cout << "Great! Press again the Space bar when the window is "
                         "opened, please"
                      << "\n\n";
            ///////////////////Opening again the same window //////////////////
          } else {
            running = false;
            std::cout << "Alright! Thanks for your time!"
                      << "\n\n";
          }
        } else {
          running = false;
          std::cout << "There are no infected people left"
                    << "\n\n";
          std::cout << "That's all! Thanks for your time!"
                    << "\n\n";
        }
      }
    }  ///////////////closing of the "CHOOSE" scope/////////////////////////
    std::cout << "Data of your simulation :"
              << "\n\n";
    std::cout << "Number of days : " << ag_->get_days() << "\n\n";
    std::cout << "Situation of the last day : " << ag_->get_evolution().back()
              << "\n\n";
    std::cout << "Critical threshold : "
              << ag_->calculate_R0(ag_->get_Parameters()) << "\n\n";

  }  ///////////////closing of the "PERSONALIZED" scope/////////////////////////
}
