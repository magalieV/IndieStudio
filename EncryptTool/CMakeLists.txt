cmake_minimum_required(VERSION 3.11)
project(encrypt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS)

include_directories(inc/)

set(SRCS
        src/Encryption.cpp
        src/Decryption.cpp
        src/XMLReader.cpp
        inc/Decryption.hpp
        inc/Encryption.hpp
        inc/XMLReader.hpp)

add_library(encrypt ${SRCS})