
cmake_minimum_required(VERSION 3.10) # Cmake version 

project(SIHDProject VERSION 1.0) # NameProject

set(CMAKE_CXX_STANDARD 14) 
set(CMAKE_CXX_STANDARD_REQUIRED True) # Assicura che sia obbligatorio

include_directories(include)
################################# Pandemic ##########################################
add_executable( sihd_pan_test  pandemic.hpp pandemic.cpp doctest.h pandemic_test.cpp )
# Adding compile options for the target
target_compile_options(sihd_pan_test PRIVATE -fsanitize=address)

target_compile_options(sihd_pan_test PRIVATE -Wall -Wextra)


# Adding linking options for the target
target_link_options(sihd_pan_test PRIVATE -fsanitize=address)

################################## Equation ##########################################
                    ############# main_eq_simulation ################
add_executable( sihd_eq  pandemic.hpp pandemic.cpp equation.hpp equation.cpp main_eq_simulation.cpp )
# Adding compile options for the target
target_compile_options(sihd_eq PRIVATE -fsanitize=address)

target_compile_options(sihd_eq PRIVATE -Wall -Wextra)

# Adding linking options for the target
target_link_options(sihd_eq PRIVATE -fsanitize=address)

                ########### equation_test ##############
add_executable( sihd_eq_test  pandemic.hpp pandemic.cpp equation.hpp equation.cpp doctest.h equation_test.cpp )
# Adding compile options for the target
target_compile_options(sihd_eq_test PRIVATE -fsanitize=address)

target_compile_options(sihd_eq_test PRIVATE -Wall -Wextra)

# Adding linking options for the target
target_link_options(sihd_eq_test PRIVATE -fsanitize=address)

#################################### Matrix ###########################################
add_executable( sihd_mat_test  matrix.hpp matrix_test.cpp )
# Adding compile options for the target
target_compile_options(sihd_mat_test PRIVATE -fsanitize=address)

target_compile_options(sihd_mat_test PRIVATE -Wall -Wextra)

# Adding linking options for the target
target_link_options(sihd_mat_test PRIVATE -fsanitize=address)


################################## Agent ##############################################
# Find library SFML
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

    
                         ############## main_ag_simulation #####################
add_executable( sihd_ag  pandemic.hpp pandemic.cpp agent.hpp agent.cpp matrix.hpp main_ag_simulation.cpp )

# Adding compile options for the target
target_compile_options(sihd_ag PRIVATE -fsanitize=address)

target_compile_options(sihd_ag PRIVATE -Wall -Wextra)

# Adding linking options for the target
target_link_options(sihd_ag PRIVATE -fsanitize=address)


# Link the sfml library to executable file
target_link_libraries(sihd_ag PRIVATE sfml-graphics sfml-window sfml-system)

                    ################ agent_test ######################
add_executable( sihd_ag_test  pandemic.hpp pandemic.cpp agent.hpp agent.cpp matrix.hpp doctest.h agent_test.cpp )
# Adding compile options for the target
target_compile_options(sihd_ag_test PRIVATE -fsanitize=address)

target_compile_options(sihd_ag_test PRIVATE -Wall -Wextra)

# Adding linking options for the target
target_link_options(sihd_ag_test PRIVATE -fsanitize=address)



set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

message(STATUS "Configurazione completata per ${CMAKE_BUILD_TYPE}")
