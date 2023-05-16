cmake_minimum_required(VERSION 3.0.0)
project(RootsHalves VERSION 0.1.0)

# Enable C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

file(GLOB RootsHalves_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")


add_executable(RootsHalves ${RootsHalves_SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Boost REQUIRED)
message(STATUS "Boost Found: ${Boost_FOUND}")
target_link_libraries(RootsHalves Boost::boost)

find_library(MPFR_LIBRARIES mpfr)
message(STATUS "MPFR Found: ${MPFR_LIBRARIES}")
target_link_libraries(RootsHalves ${MPFR_LIBRARIES})

find_library(GMP_LIBRARIES gmp)
message(STATUS "GMP Found: ${GMP_LIBRARIES}")
target_link_libraries(RootsHalves ${GMP_LIBRARIES})

set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets  COMPONENTS core base REQUIRED)
message(STATUS "wxWidgets Found: ${wxWidgets_FOUND}")
include(${wxWidgets_USE_FILE})
target_link_libraries(RootsHalves ${wxWidgets_LIBRARIES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
