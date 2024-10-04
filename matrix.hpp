#ifndef MATRIX_HPP
#define MATRIX_HPP


template <typename T> struct  Matrix{//è una matrice dinamica con gli elementi già creati
  std::vector<std::vector<T>> M;
  int side;
Matrix(int l);
Matrix();
Matrix(const Matrix<T>& M_other);

template<typename Func>
void inside_matrix(Func action);

int Matrix<T>::sum();
bool operator==(Matrix<T>& left, Matrix<T>& right);
  

};
  /// Parametric
  template<typename T>
  Matrix<T>::Matrix(int l): side{l},M(l,std::vector<T>(l,0)>){//Null Matrix dinamica
  }
  /// Default: Null Matrix
  template<typename T>
  Matrix<T>::Matrix(): side{80}, M(80,std::vector<T>(80,0)){}
  
  /// Copy
  template<typename T>
  Matrix<T>::Matrix(const Matrix<T>& M_other){
  if (this->side != M_other.side) {
    throw std::runtime_error{"The two matrices don't have the same dimension (n x n) or they aren't squared"}
  }
  for (int r = 0; r < this->side ; r++){
    for (int c = 0; c < this->side ; c++){
       
       this->M_[r][c] = M_other.M_[r][c];
    }
   }
   this->side = M_other;
  }
  template<typename T>
  template<typename Func>
  void Matrix<T>::inside_matrix(Func action){//questa è una funzione che mi permette di fare un'azione e sa già di e come dover entrare nella matrice
    for (int r = 0; r < this->side ; r++){
    for (int c = 0; c < this->side ; c++){
       
        action(M_[r][c],r,c);
    }
   }
  }

  //pensa ad una funzione che permatte adi navigare attarverso le righe 
  template<typename T>
  int Matrix<T>::sum(){
    int tot = 0;
    this->inside_matrix([this, tot](int& cell, int r, int c){
    tot+= cell;
    });
     return tot;
  }
  ///////////////////overloading dell'operator==///////////////////////////////////
  template<typename T>
  bool operator==(Matrix<T>& left, Matrix<T>& right){
     for (int r = 0; r < this->side ; r++){
    for (int c = 0; c < this->side ; c++){
      
       if(left.M[r][c] != right.M[r][c]){
          return false;
          break;
       } 
    }
   }

  return true;
    
}
#endif