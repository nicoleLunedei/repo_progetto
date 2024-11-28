#include "matrix.hpp"
#include "agent.hpp"

////////////////Checking if the number is a perfect square///////////////////
bool is_perfect_square(int num){  
  int root = static_cast<int> (std::sqrt(num));
  return (root * root == num);
}

/////////////////////////sum in Person contest/////////////////////////////
int sum_person(std::vector<Person>& pers){
  std::vector<int> pers_n;
 for(Person& el: pers){
    pers_n.push_back(static_cast<int>(el));
 }
 return sum(pers_n);
}


/////////////////////CLASS AGENT///////////////////////////////////////////
////////////////////////Constructors////////////////////////////

      ///////Parametric/////////// 
Agent::Agent(std::vector<People>& population,  Parameters& par,const int& N): Pandemic(population,par,N),M_(static_cast<int>(std::sqrt(N)), Susceptible) {
   
      if (!is_perfect_square(this->get_number_population())) 
      throw std::runtime_error{"The number of the population must a perfect square"};
      
    }
 ////////////Default/////////  
Agent::Agent(): Pandemic(),M_(){
 //////////////////Setting initial situation////////////////
     People initial_data;
            this->set_initial_condition(initial_data);
   M_.inside_matrix([this](Person& cell, int r, int c){

         if (r == (static_cast<int>(M_.M.size())/2) && c == static_cast<int>(M_.M.size()/2) ){
           cell= Person::Infected;
         } else {
          cell = Person::Susceptible;
         }
  
     });
   }
       //////////Getters///////
       
Matrix<Person>& Agent::get_matrix() {
  return this->M_;
}
int Agent::get_side() const{
  return std::sqrt(this->get_number_population());
}
///////////// Toroidal structure viewing/////////////////////
Person& Agent::show_cell(int r, int c) {
  
  if(this->get_matrix().M.empty())
   throw std::runtime_error{"The Matrix is empty!"};

  int rr = (r + this->get_side()) % this->get_side();
  int cc= (c + this->get_side() ) % this->get_side();
    
  if ((rr < 0 || rr > this->get_side() ) || (cc < 0 || cc > this->get_side()  ) ){
    throw std::runtime_error{"Out of range!!!!!!!!!!!!!!!!!"};
  }

   return this->get_matrix().M[rr][cc];
} 
    /////////Setter///////
    /////////Setting the first situation and drawing it on the Matrix///////////  
    
void Agent::draw_matrix(People& begin){
  
  if (this->get_matrix().sum() !=0){
    throw std::runtime_error{"You already set the initial condition"};
  }

  this->set_initial_condition(begin);
  
  int i = 0;
  while (i < sum(this->get_situation_day(1).I_)){
    ////////////////Extraction of the random coordinates////////////////////////
    int rr = std::floor(this->generate() * this->get_side());
    int cc = std::floor(this->generate() * this->get_side());
     
      if (this->show_cell(rr,cc) == Person::Infected)
         {
////////////Checking wich line has sum == to the side of matrix////////////////
           while (sum_person(this->get_matrix().M[rr]) == this->get_side()){
               rr++;
           }
////////////////Scrolling columns//////////////////
           while(this->show_cell(rr,cc) == Person::Infected ){
            cc++;
           }
          this->show_cell(rr,cc) = Person::Infected;
          i++;
         } else {
            this->show_cell(rr,cc) = Person::Infected;
            i++;
         }
    
       } 
  }  
       
  /////////////////////////////General functionalities//////////////////////////////////////////

    bool Agent::throwing_dices(double& dice){
  if (this->generate()<= dice){
    //Chenge
    return true;
  } else {
    //Invariation
    return false;
  }
}

 //////////Counting the infected people around a specific cell of Matrix/////////
int Agent::infected_neighbours( int r, int c) {

  int contacts = 0;
  for (int i : {- 1, 0, 1})
  {
    for (int j : {-1, 0, 1})
    {
      if (this->Agent::show_cell(r+i, c+j) == Person::Infected) {
        contacts++;
      }
    }
  }
 assert(contacts <= 8);
  return contacts;
}
     
       ////////////Data collection about the vaccine///////////////
       void Agent::sorting(){
    int check = this->get_evolution().back().S_[0];
    this->get_matrix().each_cell([this](Person& cell ){
        if (cell == Person::Susceptible){
           if (this->is_vaccinated()){
             cell = Person::Susceptible_v;
             (this->get_evolution().back().S_[1])++;
             (this->get_evolution().back().S_[0])--;
           } 
        }
    });
    assert((this->get_evolution().back().S_[0])+(this->get_evolution().back().S_[1]) == check );
}

          /////////////////////Evolving functionalities/////////////////

    /////////Recognizing the state of a cell and than change it according on the rules//////////////

void Agent::change_state(){ 
  this->get_matrix().inside_matrix([this](Person& cell, int r, int c ){{ 

int inf = 0;
int k = 1;

     
     switch (cell)
  { 
    case Person::Susceptible:
 
  inf = this->infected_neighbours(r ,c);

   for(; k <= inf; k++){
    if(this->throwing_dices(this->get_Parameters().beta[0])){
              cell = Person::Infected;
              break;
    }
   }
   break;
     case Person::Susceptible_v:
 
   inf = this->infected_neighbours(r ,c );

  for(; k <= inf; k++){
    if(this->throwing_dices(this->get_Parameters().beta[0])){
              cell = Person::Infected_v;
              break;
    }
   }


   break;
  case Person::Infected:
     
     if(this->throwing_dices(this->get_Parameters().gamma[0])){
        cell = Person::Healed;
     } else {
      if(this->throwing_dices(this->get_Parameters().omega[0])){
        cell = Person::Dead;
      } else { 
        //Still Infected
      }
     }
  
    break;
 case Person::Infected_v:


 if(this->throwing_dices(this->get_Parameters().gamma[1])){
        cell = Person::Healed;
     } else {
      if(this->throwing_dices(this->get_Parameters().omega[1])){
        cell = Person::Dead;
      } else { 
        //Still Infected
      }
      
     }
  break;
  case Person::Healed :
//////////////Inavriation///////////
     break;
  case Person::Dead :
//////////////Inavriation///////////
    break;
  }
}});

  
}

void Agent::data_collection(People& collection){
this->get_matrix().each_cell([this, &collection](Person& cell){
    switch (cell)
    {
    case Person::Susceptible:
       
       collection.S_[0]++;        
        break;
    case Person::Susceptible_v:
     collection.S_[1]++; 
        break;
    case Person::Infected:
       collection.I_[0]++; 
        break;    
    case Person::Infected_v:
       collection.I_[1]++; 
        break;    
    case Person::Healed:
       collection.H_++; 
        break; 
    case Person::Dead:
       collection.D_++; 
        break;            
    }
});

assert(sum(transform_arr<int,6>(collection)) == this->get_number_population());

this->add_data(collection);
}

 
void Agent::evolve(People& follow){
  ///////Changing///////////
  this->change_state();
  ///////////Collecting///////////////
  this->data_collection(follow);
}

//////////////Distructor//////////////
 Agent::~Agent() = default;
