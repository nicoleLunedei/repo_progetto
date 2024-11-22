
cmake_minimum_required(VERSION 3.10) # Cmake version 

project(SIHDProject VERSION 1.0) # NameProject

set(CMAKE_CXX_STANDARD 14) 
set(CMAKE_CXX_STANDARD_REQUIRED True) # Assicura che sia obbligatorio

include_directories(include)


##################################Equation##########################################
                        #main_eq_simulation
add_executable( sihd_eq main_eq_simulation.cpp pandemic.hpp pandemic.cpp equation.hpp equation.cpp )
# Adding compile options for the target
target_compile_options(sihd_eq PRIVATE -fsanitize=address)

target_compile_options(sihd_eq PRIVATE -Wall -Wextra)

# Adding linking options for the target
target_link_options(sihd_eq PRIVATE -fsanitize=address)




                        #equation_test
add_executable( sihd_eq_test equation_test.cpp pandemic.hpp pandemic.cpp equation.hpp equation.cpp )
# Adding compile options for the target
target_compile_options(sihd_eq_test PRIVATE -fsanitize=address)

target_compile_options(sihd_eq_test PRIVATE -Wall -Wextra)

# Adding linking options for the target
target_link_options(sihd_eq_test PRIVATE -fsanitize=address)



##################################Agent##############################################
# Find library SFML
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

    
#main_ag_simulation
add_executable( sihd_ag main_ag_simulation.cpp pandemic.hpp pandemic.cpp agent.hpp agent.cpp matrix.hpp )

# Adding compile options for the target
target_compile_options(sihd_ag PRIVATE -fsanitize=address)

target_compile_options(sihd_ag PRIVATE -Wall -Wextra)

# Adding linking options for the target
target_link_options(sihd_ag PRIVATE -fsanitize=address)


# Link the sfml library to executable file
target_link_libraries(sihd_ag PRIVATE sfml-graphics sfml-window sfml-system)

                        #agent_test
add_executable( sihd_ag_test agent_test.cpp pandemic.hpp pandemic.cpp agent.hpp agent.cpp matrix.hpp )
# Adding compile options for the target
target_compile_options(sihd_ag_test PRIVATE -fsanitize=address)

target_compile_options(sihd_ag_test PRIVATE -Wall -Wextra)

# Adding linking options for the target
target_link_options(sihd_ag_test PRIVATE -fsanitize=address)



set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

message(STATUS "Configurazione completata per ${CMAKE_BUILD_TYPE}")
