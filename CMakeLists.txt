cmake_minimum_required(VERSION 3.11) 
project(LivingWorld VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 
)

FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.87.0 
)

# Set Boost to include only the serialization library
set(BOOST_INCLUDE_LIBRARIES serialization)
set(BOOST_ENABLE_CMAKE ON)

FetchContent_MakeAvailable(Catch2 Boost)

include_directories(include)

add_library(worldlib 
src/organisms/Organism.cpp
src/organisms/Animal.cpp
src/organisms/Plant.cpp
src/organisms/Dandelion.cpp
src/organisms/Grass.cpp
src/organisms/Toadstool.cpp
src/organisms/Wolf.cpp
src/organisms/Sheep.cpp
src/organisms/LineageInfo.cpp
src/organisms/OrganismFactory.cpp
src/validators.cpp
src/Position.cpp  
src/World.cpp
src/Simulator.cpp
)
target_link_libraries(worldlib PRIVATE Boost::serialization)

add_executable(main LivingWorld.cpp)
target_link_libraries(main PRIVATE worldlib Boost::serialization)

add_executable(tests 
  tests/World_test.cpp
  tests/Position_test.cpp
  tests/Organism_test.cpp
  tests/Serialization_test.cpp
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain worldlib Boost::serialization) 

list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)

include(CTest)
include(Catch)
enable_testing() 
catch_discover_tests(tests)