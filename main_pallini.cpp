/*#include "pandemic.hpp"
#include "agent.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <chrono>      
#include <thread> 
//sf::CircleShape circle;
            //circle.setRadius(10.f); 
            //circle.setPosition( 100.f + c * 20.f, 150.f + r * 20.f);

sf::Color paint(Person& element){
          sf::Color color;
               switch(element){

                case (0) : {
                  color = sf::Color::Green;
                    break;
                }
                case (4):{
                color = sf::Color::Green;
                  
                    break; 
                }
                case (1) : {
                 color = sf::Color::Red;
                    break;
                }
                case(5): {
                    color = sf::Color::Red;
                    break;
                }
                case (2) : {
                    color = sf::Color::Blue;
                    break;
                }
                case (3) : {
                     color = sf::Color::Magenta;
                    break;
                }
               }
    return color; 
}
int main(){
    std::vector<People> track;
    Parameters p{{0.67,0.},{0.34,0.},{0.56,0.},0.} ;
    int N = 400;
    Agent agent(track,p,N);
    People start{{300,0},{100,0},0,0};
    agent.draw_matrix(start);
       sf::RenderWindow window(sf::VideoMode(800, 600), "SIHD: without vaccine");
         window.setPosition(sf::Vector2i(100, 50));  
    
     ////////Creazione della matrice di pallini, coerente all'oggetto agent///////////
         Matrix<sf::CircleShape> circles;
         agent.get_matrix().inside_matrix([&window,&circles](Person& cell,int r, int c){
         sf::CircleShape circle1;
         circle1.setRadius(4.f); 
         circle1.setPosition(120.f + (c * 8.f)+ 0.1f , 100.f + (r * 8.f )+ 0.1f);
         circle1.setFillColor(paint(cell));
         circles.add(r,circle1);
         
         
         });
    //////Stampa su terminale della matrice e de le conteggio
          std::cout <<"Ecco la matrice-> Giorno N° 1 " <<'\n';
        std::cout << agent.get_matrix()<<'\n';
        std::cout << agent.get_condition_day(1)<<'\n';
     bool simulationOn = false;
     int t = 2;

     ///////////////inizio ciclo per l'evoluzione, se avviata//////////////
   // while(t <= 6 ) {
        /////////////inizio del ciclo di vita della finestra/////////////
        while (window.isOpen()) {
        
     
       sf::Event event1;
       
        ///////////////interrogatorio degli eventi/////////////////
        while (window.pollEvent(event1)) {
            // Se viene premuto il bottone di chiusura della finestra
            if (event1.type == sf::Event::Closed) {
                window.close();  // Chiude la finestra
            }
            if(event1.type == sf::Event::KeyPressed && event1.key.code == sf::Keyboard::Space) {
                simulationOn = true;  // Avvia la simulazione
            }
            
        }
        // Pulisce la finestra per prepararla al nuovo disegno
         window.clear(sf::Color::Black);  // Sfondo nero 



  
        //////////////verifica dell'avvio volontario della simulazione/////////////////7
        if (simulationOn){

        //////////Nuovo giorno d'evoluzione //////////////
        People next {{0,0},{0,0},0,0};
        agent.evolve(next);

        ///////////////Modifica dei colori dei pallini//////
        agent.get_matrix().inside_matrix([&window,&circles](Person& cell, int r, int c){ 
         circles[r][c].setRadius(4.f); 
         circles[r][c].setPosition(120.f + (c * 8.f)+ 0.1f , 100.f + (r * 8.f )+ 0.1f);
         circles[r][c].setFillColor(paint(cell));
         window.draw(circles[r][c]);

        });

        ////////////////////Stampa su terminale della matrice e dei numeri////////////
        std::cout <<"Ecco la matrice-> Giorno N° "<< t <<'\n';
        std::cout << agent.get_matrix()<<'\n';
        std::cout << agent.get_condition_day(t)<<'\n';
        ///////incremento delle giornate////////////
        t++;
         ////////////ritardo dell'evoluzione //////////////
       std::this_thread::sleep_for(std::chrono::milliseconds(2000)); 
       } else {
        ////////////////mostra l'ultima matrice a pallini/////////
        circles.each_cell([&window](sf::CircleShape& cell){
            window.draw(cell);
        });
       }


       if(t == 6){
         simulationOn = false;
       }
 
     
              
        
        
     
    //////////aggiornamento della finestra 
     window.display();
    
     ////////qua finisce il ciclo di vita della finestra
    }  
    //////qua ricomincia il ciclo d'evoluzione
    //}

     
       

        // Qui è dove potresti aggiungere i disegni, come forme o testo
         // Disegna il rettangolo
   
     }*/
    #include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <atomic>

// Variabile atomica per controllare lo stato del programma
std::atomic<bool> running(true);

// Funzione per gestire l'input e output del terminale
void terminalIO() {
    while (running) {
        std::string input;
        std::cout << "Inserisci un comando (digita 'exit' per chiudere): ";
        std::cin >> input;

        if (input == "exit") {
            running = false; // Segnale per terminare il programma
        } else {
            std::cout << "Hai inserito: " << input << std::endl;
        }
    }
}

int main() {
    // Crea una finestra SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "Finestra SFML");

    // Avvia il thread per l'I/O del terminale
    std::thread ioThread(terminalIO);

    // Ciclo principale della finestra
    while (window.isOpen() && running) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false; // Chiude il programma
                window.close();
            }
        }

        // Logica di rendering
        window.clear(sf::Color::Black);

        // Disegno di esempio
        sf::CircleShape shape(50);
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(375, 275);
        window.draw(shape);

        window.display();
    }

    // Aspetta che il thread del terminale termini
    ioThread.join();

    return 0;
}


