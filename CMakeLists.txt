cmake_minimum_required(VERSION 3.26)
project(3_rd_semester_cpp_project)

set(CMAKE_CXX_STANDARD 23)

file (GLOB_RECURSE 3_rd_semester_cpp_project_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB_RECURSE 3_rd_semester_cpp_project_HEADERS CONFIGURE_DEPENDS "src/*.hpp")

set (3_rd_semester_cpp_project_INCLUDE_DIRS "")
foreach (_headerFile ${3_rd_semester_cpp_project_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND 3_rd_semester_cpp_project_INCLUDE_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES 3_rd_semester_cpp_project_INCLUDE_DIRS)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(3_rd_semester_cpp_project ${3_rd_semester_cpp_project_SOURCES}
        src/logic/handling/editor/editorShipPart.hpp
        src/logic/handling/editor/editorShipPart.cpp
        src/classes/partTypes/control.hpp
        src/classes/partTypes/control.cpp
        src/classes/partTypes/engine.hpp
        src/classes/partTypes/reactor.hpp
        src/classes/parts.hpp
        src/classes/partTypes/reactor.cpp
        src/classes/partTypes/engine.cpp
        src/classes/ship.hpp
        src/classes/ship.cpp
        src/logic/handling/gameplay/gameplayHandling.hpp
        src/graphics/elements/gameplayRender.hpp
        src/graphics/elements/gameplayRender.cpp
        src/logic/handling/gameplay/gameplayHandling.cpp
        src/classes/partTypes/weapon.hpp
        src/classes/partTypes/weapon.cpp
        src/logic/handling/gameplay/projectile.hpp
        src/logic/handling/gameplay/projectile.cpp
        src/classes/aux.hpp
        src/classes/aux.cpp
        src/logic/handling/gameplay/collision.hpp
        src/logic/handling/gameplay/collision.cpp
        src/logic/handling/gameOver/gameOverHandling.hpp
        src/logic/handling/gameOver/gameOverHandling.cpp
        src/graphics/elements/gameOverRenderer.hpp
        src/graphics/elements/gameOverRenderer.cpp)

target_compile_features(3_rd_semester_cpp_project PRIVATE cxx_std_23)
target_link_libraries(3_rd_semester_cpp_project PRIVATE sfml-graphics sfml-window sfml-system sfml-audio sfml-network Xrandr)
target_include_directories(3_rd_semester_cpp_project PRIVATE ${3_rd_semester_cpp_project_INCLUDE_DIRS})
file(COPY "data" DESTINATION "${CMAKE_BINARY_DIR}")

install(TARGETS 3_rd_semester_cpp_project)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)