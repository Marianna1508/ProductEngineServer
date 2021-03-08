cmake_minimum_required(VERSION 3.7.2)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DIR_BUILD_PRODUCT})

# Add list with sources for PhoneCallManager component
set(Server_SOURCES
  CServer.cpp
)

message(STATUS "CMAKE_SOURCE_DIR     : ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR     : ${CMAKE_CURRENT_LIST_DIR}")

# Add directories pathes
include_directories(${PROJECT_NAME} 
  ${CMAKE_SOURCE_DIR}/include

)

add_executable(${PROJECT_NAME} main.cpp
                               ${Server_SOURCES}
)

#target_link_libraries(${PROJECT_NAME} WdSlave::import)

