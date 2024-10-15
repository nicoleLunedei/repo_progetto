#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <stdexcept>
#include <cassert>

template <typename T> struct  Matrix{//è una matrice dinamica con gli elementi già creati
  
  std::vector<std::vector<T>> M;

Matrix(int l);
Matrix(std::vector<std::vector<T>>& m);
Matrix();
Matrix(const Matrix<T>& M_other);

Matrix<T>& operator=( const Matrix<T>& other );
template<typename U>
friend bool operator==(const Matrix<U>& left, const Matrix<U>& right);
template<typename U>
friend bool operator!=(const Matrix<U>& left, const Matrix<U>& right);

template<typename Func>
void inside_matrix(Func action);

template<typename F>
void each_cell(F operation);

int sum();
void modify(const T& value, int r, int c );
const T& read(int r, int c) const;

  

};
  /// Parametric
  template<typename T>
  Matrix<T>::Matrix(int l): M(l,std::vector<T>(l,static_cast<T>(0))){//Null Matrix dinamica
  if(l <= 0) {
    throw std::runtime_error{"The dimension must be positive "};
  }

  }
  template<typename T> 
  Matrix<T>::Matrix(std::vector< std::vector<T>>& m) : M{m}{
    
    if(m.empty()){
        throw std::runtime_error{"Error! The matrix, you're trying to copy, is empty"};
       }

    if(m.size() != m[0].size()){
        throw std::runtime_error{"Error! The matrix, you're trying to copy, isn't squared"};
       }
       
       
  
  }
  /// Default: Null Matrix
  template<typename T>
  Matrix<T>::Matrix(): M(80,std::vector<T>(80,static_cast<T>(0))){}
  
  /// Copy
  template<typename T>
  Matrix<T>::Matrix(const Matrix<T>& M_other) {
   this->M = M_other.M;
  
  }


  template<typename T>
  template<typename Func>
  void Matrix<T>::inside_matrix(Func action){//questa è una funzione che mi permette di fare un'azione e sa già di e come dover entrare nella matrice
    for (int r = 0; r < static_cast<int>(this->M.size()); r++){
    for (int c = 0; c < static_cast<int>(this->M[r].size()); c++){
       
        action(this->M[r][c],r,c);
    }
   }
  }
    template<typename T>
  template<typename F>
  void Matrix<T>::each_cell(F operation){//questa è una funzione che mi permette di fare un'azione e sa già di e come dover entrare nella matrice
    for (int r = 0; r < static_cast<int>(this->M.size()); r++){
    for (int c = 0; c < static_cast<int>(this->M[r].size()); c++){
       
        operation(this->M[r][c]);
    }
   }
  }

  //pensa ad una funzione che permatte adi navigare attarverso le righe 
  template<typename T>
  int Matrix<T>::sum(){
    int tot = 0;
    this->each_cell([this, &tot](T& cell)  {
    tot+= static_cast<int>(cell);
    });
     return tot;
  }

  template<typename T>
  void Matrix<T>::modify(const T& value, int r, int c ){
     this->M[r][c] = value;
  }

  template<typename T>
   const T& Matrix<T>::read(int r, int c) const{
    return this->M[r][c];
  }
  template<typename T>
  Matrix<T>& Matrix<T>::operator=( const  Matrix<T>& other ) {
 
     if (this != &other) {  // Prevenire l'auto-assegnazione
      
        if (other.M.empty() || other.M[0].empty()){
          
          throw std::runtime_error{"Cannot assign a matrix with an undefined dimension !"};
        } else {
            // Verifica che le dimensioni delle due matrici siano uguali
          
          if (other.M.size() != this->M.size())  {
          
          throw std::runtime_error{"They don't have the same number of lines"};
          }

          if (other.M[0].size() != this->M[0].size()) {
         
          throw std::runtime_error{"They don't have the same number of columns"};
          }
        
          this->inside_matrix([&other](T& cell, int r,int c){
                cell = other.M[r][c];
          });
          return *this;
        } 
      
      
    } else {

      throw std::runtime_error{"Invalid assignment! They are the same object."};
    }
      
  }
  ///////////////////overloading dell'operator==///////////////////////////////////
  template<typename T>
  bool operator==(const Matrix<T>& left, const Matrix<T>& right){
    
    if (left.M.size() != right.M.size() || left.M[0].size() != right.M[0].size() ) {
        return false;
        }
    for (int r = 0; r < static_cast<int>(left.M.size()); r++){
    for (int c = 0; c < static_cast<int>(left.M.size()) ; c++){
      
       if(left.read(r,c) != right.read(r,c)){//read ha il qualifier const così mi assicuro che non modifichi left e right che li ho dichiarati const 
          return false;
        
       } 
    }
   }

  return true;
  /////////////////considera la possibilità di implementare qua l'operatore<< di cout///////////////
    
}
template<typename T>
bool operator!=(const Matrix<T>& left, const Matrix<T>& right){
     return !(left == right);
}


#endif