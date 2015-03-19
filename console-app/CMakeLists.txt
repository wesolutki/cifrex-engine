cmake_minimum_required(VERSION 3.0)

SET (SRC
    ./Options.cpp
    ./Options.hpp
    ./main.cpp
)

FIND_PACKAGE( Boost 1.45.0 COMPONENTS filesystem program_options system REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

add_executable(console ${SRC})
target_link_libraries(console LINK_PUBLIC engine ${Boost_LIBRARIES} libre2.so)

install(TARGETS console
        RUNTIME DESTINATION bin)
