cmake_minimum_required(VERSION 3.11) 
project(LivingWorld VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(worldlib 
src/organisms/Animal.cpp
src/organisms/Organism.cpp
src/organisms/Plant.cpp
src/Position.cpp  
src/World.cpp
)

add_executable(main LivingWorld.cpp)
target_link_libraries(main PRIVATE worldlib)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests 
  tests/World_test.cpp
  tests/Position_test.cpp
  tests/Organism_test.cpp
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain worldlib) 

list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)

include(CTest)
include(Catch)
enable_testing() 
catch_discover_tests(tests)