cmake_minimum_required(VERSION 3.0)

SET (EXS
    ./exs/Ex.cpp
    ./exs/Ex.hpp
    ./exs/Exs.cpp
    ./exs/Exs.hpp
    ./exs/Vex.cpp
    ./exs/Vex.hpp
    ./exs/Tex.cpp
    ./exs/Tex.hpp
    ./exs/Fex.cpp
    ./exs/Fex.hpp
)

SET (SRC
    ./Engine.cpp
    ./Engine.hpp
    ./FileLoader.cpp
    ./FileLoader.hpp
    ./Types.hpp
    ${EXS}
)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

add_library(engine ${SRC})
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
