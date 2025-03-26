cmake_minimum_required(VERSION 3.16)
project(tema)

include(CTest)
include(ExternalProject)

file(GLOB SOURCES "src/*.cpp")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("include")

set(LOUVRE louvre_project)
ExternalProject_Add(
    louvre_project
    GIT_REPOSITORY https://github.com/Alessandro-Salerno/louvre
    GIT_TAG cf280f6bacaca424286ae25e2df918d514748881
    PREFIX ${PROJECT_SOURCE_DIR}/external/${LOUVRE}
    CONFIGURE_COMMAND cmake ../${LOUVRE}
    BUILD_COMMAND cmake --build .
    INSTALL_COMMAND cmake --install . --prefix ${PROJECT_SOURCE_DIR}
    UPDATE_COMMAND ""
)

add_library(louvre STATIC IMPORTED)
set_property(TARGET louvre PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/liblouvre.a)
add_dependencies(louvre louvre_project)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} louvre)
add_subdirectory(tests)
