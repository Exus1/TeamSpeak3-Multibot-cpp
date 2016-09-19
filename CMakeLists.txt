cmake_minimum_required(VERSION 3.2.2)

project(TeamSpeak3_Mulibot_Cpp)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "./libs/")

#Opcje budowy m.in. biblioteki

option(BUILD_WELCOMEMESSAGE "Build Welcome Message plugin" ON)
option(BUILD_CORE "build multibot core" ON)

include_directories(
  ./src/includes/
  ./src/Ts3API/includes
)

if(${BUILD_CORE})
  set (SRCS
    ./src/main.cpp
    ./src/Loger.cpp
    ./src/sqlite3.c
    ./src/commandLine.cpp
    ./src/ModulesLoader.cpp
    ./src/Ts3API/Ts3API.cpp
    ./src/Ts3API/Ts3Socket.cpp
    ./src/Ts3API/Ts3Structs.cpp
  )


  add_executable(TeamSpeak3_Mulibot_Cpp ${SRCS})
  target_link_libraries(TeamSpeak3_Mulibot_Cpp dl)
  target_link_libraries(TeamSpeak3_Mulibot_Cpp pthread)
endif(${BUILD_CORE})

if(${BUILD_WELCOMEMESSAGE})
  set(WM_SRCS
    ./plugins/welcomemessage.cpp
  )

  add_library(WelcomeMessage MODULE ${WM_SRCS})

  SET_TARGET_PROPERTIES(WelcomeMessage PROPERTIES PREFIX "")
  SET_TARGET_PROPERTIES(WelcomeMessage PROPERTIES SUFFIX ".ts3M")
endif(${BUILD_WELCOMEMESSAGE})
