#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <stdexcept>
#include <cassert>

template <typename T> struct  Matrix{
  
  std::vector<std::vector<T>> M;

Matrix(int l, const T& value);
Matrix(std::vector<std::vector<T>>& m);
Matrix();
Matrix(const Matrix<T>& M_other);
///////////////////////Operators Overloading////////////////////////
Matrix<T>& operator=( const Matrix<T>& other );
std::vector<T>& operator[](const std::size_t index_r);

template<typename U>
friend bool operator==(const Matrix<U>& left, const Matrix<U>& right);

template<typename U>
friend bool operator!=(const Matrix<U>& left, const Matrix<U>& right);

template<typename U>
friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& matrix);
////////////////////////////Interaction with each element///////////////
template<typename Func>
void inside_matrix(Func action);

template<typename F>
void each_cell(F operation);
/////////General functionalities//////////////
////////////Adding an element at the end of current the last line ////////////
void add(T& plus);
//////////Sum of all the elements/////////
int sum();
/////////////////Modify a specific element of the matrix////
void modify(const T& value, int r, int c );
/////////////////Reading a specific element of the matrix/////////
const T& read(int r, int c) const;

  

};
  /// Parametric
  template<typename T>
  Matrix<T>::Matrix(int l, const T& value): M(l,std::vector<T>(l,value)){
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
  Matrix<T>::Matrix(): M(50,std::vector<T>(50,static_cast<T>(0))){}
  

  template<typename T>
  template<typename Func>
  void Matrix<T>::inside_matrix(Func action){
    for (int r = 0; r < static_cast<int>(this->M.size()); r++){
    for (int c = 0; c < static_cast<int>(this->M[r].size()); c++){/
       
        action(this->M[r][c],r,c);
    }
   }
  }
    /// Copy
  template<typename T>
  Matrix<T>::Matrix(const Matrix<T>& M_other) {
   this->M = M_other.M;
  
   
  }
    template<typename T>
  template<typename F>
  void Matrix<T>::each_cell(F operation){
    for (int r = 0; r < static_cast<int>(this->M.size()); r++){
    for (int c = 0; c < static_cast<int>(this->M[r].size()); c++){
       
        operation(this->M[r][c]);
    }
   }
  }
 
template<typename T>
void Matrix<T>::add( T& plus){
   this->M.back().push_back(plus);
}
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
 ////////////////Not auto-assigning//////////////
     if (this != &other) {
    ////////////////Checking dimension of the two Matrices///////////////////////
          
          if (other.M.size() != this->M.size())  {
          
          throw std::runtime_error{"They don't have the same number of lines"};
          }

        
          this->inside_matrix([&other](T& cell, int r,int c){
                cell = other.M[r][c];
          });
          return *this;
        
      
      
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
      
       if(left.read(r,c) != right.read(r,c)){
          return false;
        
       } 
    }
   }

  return true;
  }
  /////////////////considera la possibilità di implementare qua l'operatore<< di cout///////////////
  template<typename T>
  std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix)
     {
    // write obj to stream
    for (int r = 0; r < static_cast<int>(matrix.M.size()); r++){
      for (int c = 0; c < static_cast<int>(matrix.M[r].size()); c++){
       os << matrix.M[r][c] << " ";
      }
       os << std::string("\n");
    }

       return os; 
    
   
     }
  template<typename T>
  std::vector<T>& Matrix<T>::operator[](const std::size_t index_r){
     return this->M[index_r];
  }
    
template<typename T>
bool operator!=(const Matrix<T>& left, const Matrix<T>& right){
     return !(left == right);
}


#endif