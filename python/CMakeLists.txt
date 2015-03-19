cmake_minimum_required(VERSION 3.0)

FIND_PACKAGE(Boost 1.45.0 COMPONENTS python filesystem system REQUIRED)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR} "/usr/include/python2.7" ${CMAKE_CURRENT_SOURCE_DIR}/../engine)

ADD_LIBRARY(pycifrex SHARED pycifrex.cpp)
target_include_directories(pycifrex PUBLIC ${ENGINE_SRC})
TARGET_LINK_LIBRARIES(pycifrex engine ${Boost_LIBRARIES} libre2.so)

install(TARGETS pycifrex
        LIBRARY DESTINATION lib)
