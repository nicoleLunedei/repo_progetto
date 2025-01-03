Per configurare Cmake e generare i file di build :

         cmake -S . -B build
Per buildare :

         cmake --build build

Per l'esecuzione dei file:


  >Simulazione con evoluzione con logica basata sulle  equazioni differenziali

    ./build/sihd_eq

  >Simulazione con evoluzione con logica di tipo probabilistico applicata ad un automa cellulare

    ./build/sihd_ag

  >Test di Pandemic Class

    ./build/sihd_pan_test

   >Test di Equation Class

    ./build/sihd_eq_test

   >Test di Agen Class

    ./build/sihd_ag_test

  >Test di Matrix<T> Struct

    ./build/sihd_mat_test

