cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
  cmake_policy(SET CMP0071 NEW)
endif()

set(exeName "Juggle")

project(${exeName} LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED QUIET)
find_package(VTK REQUIRED QUIET)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB UI_FILES *.ui)
file(GLOB QT_WRAP *.h)
file(GLOB CXX_FILES *.cpp)
file(GLOB QRC_FILES *.qrc)

qt5_wrap_ui(UISrcs ${UI_FILES})

add_executable(${exeName} MACOSX_BUNDLE ${CXX_FILES} ${UISrcs} ${QT_WRAP} ${QRC_FILES})

qt5_use_modules(${exeName} Core Gui)
target_link_libraries(${exeName} ${VTK_LIBRARIES})

vtk_module_autoinit(
  TARGETS ${exeName}
  MODULES ${VTK_LIBRARIES}
)
