#include "diffusion.hpp"

Diffusion::Diffusion(){}
    
    //costruttore per controlli e inizializzazione 
Diffusion::Diffusion (Parameters par_, int T,int N ){
    //controllo con trhow
}
void Diffusion::set_par(double a, double b, double o){};//poi vedi se mettere i const e le referenze 
 void Diffusion::set_days(int t){};//poi vedi se mettere i const e le referenze
 void Diffusion::set_population(int N){};//poi vedi se mettere i const e le referenze
 //getters 
 Parameters Diffusion::get_parameters (){ }// vedi come far restituire i parametri estraendoli dallo struct Parameters 
 int Diffusion::get_days(){ return T_;}
 int Diffusion::get_population(){return N_;}