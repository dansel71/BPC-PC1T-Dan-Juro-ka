# CMakeList.txt : CMake project for Hudba, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Hudba")

# Add source to this project's executable.
add_executable (Hudba "Hudba.cpp" "Hudba.h" "HudbaDB.h" "HudbaDB.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Hudba PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
