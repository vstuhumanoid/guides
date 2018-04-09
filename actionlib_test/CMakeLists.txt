cmake_minimum_required(VERSION 2.8.3)
project(actionlib_test)

add_compile_options(-std=c++11)


find_package(catkin REQUIRED COMPONENTS
  actionlib
  roscpp
  message_generation
)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
add_action_files(
    FILES
    Test.action
)

## Generate added messages and services with any dependencies listed here
generate_messages(
   DEPENDENCIES
   std_msgs
   actionlib_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES actionlib_test
   CATKIN_DEPENDS actionlib roscpp
#  DEPENDS system_lib
)

include_directories(${catkin_INCLUDE_DIRS})

add_executable(server src/server.cpp)
target_link_libraries(server ${catkin_LIBRARIES})

add_executable(client src/client.cpp)
target_link_libraries(client ${catkin_LIBRARIES})
