cmake_minimum_required(VERSION 3.5.0)
project(project VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

file (GLOB_RECURSE project_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB_RECURSE project_HEADERS CONFIGURE_DEPENDS "src/*.hpp")

file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/data)

set (project_INCLUDE_DIRS "")
foreach (_headerFile ${project_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND project_INCLUDE_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES project_INCLUDE_DIRS)
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

if (WIN32)
FILE(GLOB DLLS "build/_deps/sfml-build/lib/*.dll")
file(COPY ${DLLS} DESTINATION "${CMAKE_BINARY_DIR}")
endif ()

add_executable(out ${project_SOURCES})
target_compile_features(out PRIVATE cxx_std_20)
target_link_libraries(out PRIVATE sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
target_include_directories(out PRIVATE ${project_INCLUDE_DIRS})
file(COPY "data" DESTINATION "${CMAKE_BINARY_DIR}")

install(TARGETS out)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)