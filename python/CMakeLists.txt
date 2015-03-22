cmake_minimum_required(VERSION 3.0)

FIND_PACKAGE(Boost 1.45.0 COMPONENTS python filesystem system REQUIRED)
FIND_PACKAGE(PythonLibs)

INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_DIRS} ${Boost_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../engine)

ADD_LIBRARY(pycifrex SHARED pycifrex.cpp)
target_include_directories(pycifrex PUBLIC ${ENGINE_SRC})
TARGET_LINK_LIBRARIES(pycifrex engine ${Boost_LIBRARIES} libre2.so)

install(TARGETS pycifrex
        LIBRARY DESTINATION lib)
