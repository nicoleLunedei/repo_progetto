Per configurare Cmake e generare i file di build :

         cmake -S . -B build
Per buildare :

         cmake --build build
Spostamento nella directory build :

         cd build
Per l'esecuzione dei file:


  >Simulazione con evoluzione con logica basata sulle  equazioni differenziali

    ./sihd_eq
  >Simulazione con evoluzione con logicadi tipo probabilistico applicata ad un automa cellulare

    ./sihd_ag
  >Test di Pandemic Class

    ./sihd_pan_test
   >Test di Equation Class

    ./sihd_eq_test
   >Test di Agen Class

    ./sihd_ag_test
  >Test di Matrix<T> Struct

    ./sihd_mat_test
