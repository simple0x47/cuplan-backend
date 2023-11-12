project(api)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)
set(ASIO_VERSION 1.28.1)
set(BOOST_VERSION 1.83.0)

include_directories(include /opt/homebrew/Cellar/asio/${ASIO_VERSION}/include /opt/homebrew/Cellar/boost/${BOOST_VERSION}/include)

add_executable(api main.cpp)

target_link_libraries(api PRIVATE pthread)