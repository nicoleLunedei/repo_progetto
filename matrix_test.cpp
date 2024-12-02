#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "matrix.hpp"



TEST_CASE("Matrix Struct"){
SUBCASE("Constructor"){
     
 SUBCASE("Parametric"){
///////////////by dimension///////////////////////
   std::size_t l = 5;
  Matrix<int> parametric1(l,5);

  CHECK(parametric1.M.size() == 5);

  CHECK(parametric1.M[0].size() == 5);
  CHECK(parametric1.M[1].size() == 5);
  CHECK(parametric1.M[2].size() == 5);
  CHECK(parametric1.M[3].size() == 5);
  CHECK(parametric1.M[4].size() == 5);

  CHECK(parametric1.M[0][0] == 5);
  CHECK(parametric1.M[0][1] == 5);
  CHECK(parametric1.M[0][2] == 5);
  CHECK(parametric1.M[0][3] == 5);
  CHECK(parametric1.M[0][4] == 5);
  CHECK(parametric1.M[4][0] == 5);
  CHECK(parametric1.M[4][1] == 5);
  CHECK(parametric1.M[4][2] == 5);
  CHECK(parametric1.M[4][3] == 5);
  CHECK(parametric1.M[4][4] == 5);
//////////////by vector of vectors//////////////////////
   std::vector<int> vec{0,1,2,3,4};
   std::vector<std::vector<int>>other(6,vec);
  

  CHECK_THROWS_AS( Matrix<int> parametric2(other), std::runtime_error); 
  CHECK_THROWS_WITH(Matrix<int> parametric2(other), "Error! The matrix, you're trying to copy, isn't squared"); 

  vec.push_back(6);
  std::vector<std::vector<int>> other2(6,vec);
  
  Matrix<int> parametric2(other2);

  CHECK(parametric2.M[0].size() == 6);
  CHECK(parametric2.M[1].size() == 6);
  CHECK(parametric2.M[2].size() == 6);
  CHECK(parametric2.M[3].size() == 6);
  CHECK(parametric2.M[4].size() == 6);

  CHECK(parametric2.M[0][0] == 0);
  CHECK(parametric2.M[2][1] == 1);
  CHECK(parametric2.M[4][2] == 2);
  CHECK(parametric2.M[2][3] == 3);
  CHECK(parametric2.M[4][4] == 4);

  CHECK(parametric2.M[2][0] == 0);
  CHECK(parametric2.M[0][1] == 1);
  CHECK(parametric2.M[4][2] == 2);
  CHECK(parametric2.M[2][3] == 3);
  CHECK(parametric2.M[1][4] == 4);

  CHECK(parametric2.M.size() == 6);

  CHECK_THROWS_AS( Matrix<int> parametric3(other), std::runtime_error); 
  CHECK_THROWS_WITH(Matrix<int> parametric3(other), "Error! The matrix, you're trying to copy, isn't squared"); 

  CHECK_THROWS_AS( Matrix<int> parametric4(0,1), std::runtime_error); 
  CHECK_THROWS_WITH(Matrix<int> parametric4(0,1), "The dimension must be positive "); 



 }
 SUBCASE("Default"){
  Matrix<int> base;

  CHECK(base.M.size() == 50);

  CHECK(base.M[0].size() == 50);
  CHECK(base.M[1].size() == 50);
  CHECK(base.M[2].size() == 50);
  CHECK(base.M[3].size() == 50);
  CHECK(base.M[4].size() == 50);

  CHECK(base.M[0][0] == 0);
  CHECK(base.M[2][1] == 0);
  CHECK(base.M[5][2] == 0);
  CHECK(base.M[7][3] == 0);
  CHECK(base.M[4][4] == 0);

  CHECK(base.M[7][0] == 0);
  CHECK(base.M[10][1] == 0);
  CHECK(base.M[4][2] == 0);
  CHECK(base.M[2][3] == 0);
  CHECK(base.M[6][4] == 0);

 }





 
}  

SUBCASE("Members functions"){
   Matrix<int> member(10,8);
   ////////////modify & read/////////////////////
   for(std::size_t  r = 0 ; r < 10 ; r++ ){
      for(std::size_t c = 0 ; c < 10 ; c++ ){
       const int& v = static_cast<int>(r * c);
       member.modify(v,r,c);
      }
   }
   CHECK(member.read(9,5) == 45);
   /////////////each_cell////////////////
    int max = 0;
   member.each_cell([&max](int& cell){
        
         if(cell > max ){
            max = cell;
         }

   });
   CHECK(max == 81);
   /////////////inside_matrix///////////////
   
   std::vector<int> vec1{0,1,2,3,4,5,6,7,8,9};
   std::vector<std::vector<int>> mat(10,vec1);

   Matrix<int> m(mat);
   max = 0;
   m.inside_matrix([&max](int& cell, std::size_t r, std::size_t c){
      
      if ((r+c) % 2 == 0 && cell > max){
            max = cell;  
      }
    return max;
   });
   CHECK(max == 9);
   /////////////operator==////////////////
   CHECK((m == member) == false);

    Matrix<int> w(mat);
   CHECK((m == w) == true);

    vec1.push_back(10);
    std::vector<std::vector<int>> mat_(11,vec1);
    CHECK(mat_.size() == 11);
    CHECK(mat_[0].size() == 11);
    Matrix<int> v(mat_);
    CHECK(v.M.size() == 11);
    CHECK(v.M[0].size() == 11);
    
    Matrix<int> v_(11,4);
   

  
   CHECK((v == w) == false);
   CHECK((v != w) == true);
  
   CHECK(v.M.size() == v_.M.size()); 
   CHECK(v.M[0].size() == v_.M[0].size()); 
   CHECK((v_ != v) == true);
    
 
    v_ = v;
   CHECK((v_ == v) == true);
   //Copy constructor
   Matrix<int> vv(v);
   CHECK((vv == v) == true);

   std::vector<std::vector<int>> empty1;
   CHECK_THROWS_AS(Matrix<int> assign1(empty1), std::runtime_error); 
   CHECK_THROWS_WITH(Matrix<int> assign1(empty1), "Error! The matrix, you're trying to copy, is empty");
   
   std::vector<std::vector<int>> not_square_(5,{0,1,2,3,4,5,6,7,8});
   CHECK_THROWS_AS( Matrix<int> assign1_ = not_square_, std::runtime_error); 
   CHECK_THROWS_WITH(Matrix<int> assign1_ = not_square_, "Error! The matrix, you're trying to copy, isn't squared");
   
  //////////////////operator=/////////////////
   
   std::vector<std::vector<int>> square(17,{0,1,9,2,8,3,7,4,5,6,7,4,3,2,2,1,34});
   Matrix<int> assign2(mat_);
   Matrix<int> line(square);
   CHECK_THROWS_AS( assign2 = line, std::runtime_error); 
   CHECK_THROWS_WITH( assign2 = line, "They don't have the same number of lines");

   /////////////sum////////////////
   CHECK(m.sum() == 450);
   
   

}
 

}