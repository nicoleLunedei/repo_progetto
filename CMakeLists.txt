
cmake_minimum_required(VERSION 3.10) # Cmake version 

project(SIHDProject VERSION 1.0) # NameProject

set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED True) 

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined")

include_directories(${PROJECT_SOURCE_DIR}/Pandemic)
################################# Pandemic ##########################################
add_executable( sihd_pan_test Pandemic/people.cpp Pandemic/parameters.cpp Pandemic/pandemic.cpp Pandemic/pandemic_test.cpp )
# Adding compile options for the target
target_compile_options(sihd_pan_test PRIVATE -fsanitize=address -fsanitize=undefined)

target_compile_options(sihd_pan_test PRIVATE -D_GLIBCXX_ASSERTIONS )

target_compile_options(sihd_pan_test PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wshadow -Wimplicit-fallthrough -Wextra-semi -Wold-style-cast )



# Adding linking options for the target
target_link_options(sihd_pan_test PRIVATE -fsanitize=address -fsanitize=undefined)

################################## Equation ##########################################
                    ############# main_eq_simulation ################


add_executable( sihd_eq Pandemic/people.cpp Pandemic/parameters.cpp Pandemic/pandemic.cpp Pandemic/Equation/equation.cpp Pandemic/Equation/main_eq_simulation.cpp )
# Adding compile options for the target
target_compile_options(sihd_eq PRIVATE -fsanitize=address -fsanitize=undefined )

target_compile_options(sihd_eq PRIVATE -D_GLIBCXX_ASSERTIONS )

target_compile_options(sihd_eq PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wshadow -Wimplicit-fallthrough -Wextra-semi -Wold-style-cast)



# Adding linking options for the target
target_link_options(sihd_eq PRIVATE -fsanitize=address -fsanitize=undefined)

                ########### equation_test ##############
add_executable( sihd_eq_test Pandemic/people.cpp  Pandemic/parameters.cpp Pandemic/pandemic.cpp  Pandemic/Equation/equation.cpp Pandemic/Equation/equation_test.cpp )
# Adding compile options for the target
target_compile_options(sihd_eq_test PRIVATE -fsanitize=address -fsanitize=undefined)

target_compile_options(sihd_eq_test PRIVATE -D_GLIBCXX_ASSERTIONS )

target_compile_options(sihd_eq_test PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wshadow -Wimplicit-fallthrough -Wextra-semi -Wold-style-cast  -fsanitize=address,undefined)


# Adding linking options for the target
target_link_options(sihd_eq_test PRIVATE -fsanitize=address -fsanitize=undefined)

#################################### Matrix ###########################################
add_executable( sihd_mat_test Pandemic/Agent/matrix_test.cpp )
# Adding compile options for the target
target_compile_options(sihd_mat_test PRIVATE -fsanitize=address -fsanitize=undefined)

target_compile_options(sihd_mat_test PRIVATE -D_GLIBCXX_ASSERTIONS )

target_compile_options(sihd_mat_test PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wshadow -Wimplicit-fallthrough -Wextra-semi -Wold-style-cast  -fsanitize=address,undefined)


# Adding linking options for the target
target_link_options(sihd_mat_test PRIVATE -fsanitize=address -fsanitize=undefined)


################################## Agent ##############################################
# Find library SFML
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

    
                         ############## main_ag_simulation #####################
add_executable( sihd_ag Pandemic/people.cpp Pandemic/parameters.cpp Pandemic/pandemic.cpp Pandemic/Agent/agent.cpp Pandemic/Agent/main_ag_simulation.cpp )

# Adding compile options for the target
target_compile_options(sihd_ag PRIVATE -fsanitize=address -fsanitize=undefined)

target_compile_options(sihd_ag PRIVATE -D_GLIBCXX_ASSERTIONS )

target_compile_options(sihd_ag PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wshadow -Wimplicit-fallthrough -Wextra-semi -Wold-style-cast  -fsanitize=address,undefined)

# Adding linking options for the target
target_link_options(sihd_ag PRIVATE -fsanitize=address -fsanitize=undefined)


# Link the sfml library to executable file
target_link_libraries(sihd_ag PRIVATE sfml-graphics sfml-window sfml-system)

                    ################ agent_test ######################
add_executable( sihd_ag_test Pandemic/people.cpp Pandemic/parameters.cpp Pandemic/pandemic.cpp Pandemic/Agent/agent.cpp Pandemic/Agent/agent_test.cpp )
# Adding compile options for the target
target_compile_options(sihd_ag_test PRIVATE  -fsanitize=address -fsanitize=undefined)
target_compile_options(sihd_ag_test PRIVATE -D_GLIBCXX_ASSERTIONS )

target_compile_options(sihd_ag_test PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wshadow -Wimplicit-fallthrough -Wextra-semi -Wold-style-cast  -fsanitize=address,undefined)

# Adding linking options for the target
target_link_options(sihd_ag_test PRIVATE -fsanitize=address -fsanitize=undefined)



set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

message(STATUS "Configuration completed for ${CMAKE_BUILD_TYPE}")
