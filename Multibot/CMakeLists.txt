cmake_minimum_required(VERSION 2.8.11)

project(Multibot)



include_directories(
    /home/karol/Dokumenty/Mój stolik/Multibot/
    /home/karol/Dokumenty/Mój stolik/Multibot/

)

# Linker options
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS}  ")

# Library path
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS} -L\".\" ")

# Define the CXX sources
set ( CXX_SRCS
    Ts3API.cpp
    Ts3Socket.cpp
    main.cpp
    Functions/Loger.cpp
)

set_source_files_properties(
    ${CXX_SRCS} PROPERTIES COMPILE_FLAGS 
    " -g -O0 -std=c++14 -Wall")

add_executable(Multibot ${CXX_SRCS} ${C_SRCS})

