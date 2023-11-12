project(api)

set(ASIO_VERSION 1.28.1)
set(BOOST_VERSION 1.83.0)

include_directories(include /opt/homebrew/Cellar/asio/${ASIO_VERSION}/include /opt/homebrew/Cellar/boost/${BOOST_VERSION}/include)

include(FetchContent)
FetchContent_Declare(
        fruit
        GIT_REPOSITORY https://github.com/google/fruit.git
        GIT_TAG 8149131119475ccaae3c1ae386fe9f2c679317f0 #v.3.7.1
)

FetchContent_MakeAvailable(fruit)
FetchContent_GetProperties(fruit)
if (NOT fruit_POPULATED)
    FetchContent_Populate(fruit)
    add_subdirectory(${fruit_SOURCE_DIR} ${fruit_BINARY_DIR})
endif()


add_executable(api main.cpp)


target_link_libraries(api PRIVATE pthread fruit)
target_include_directories(api PUBLIC ${fruit_SOURCE_DIR}/include ${fruit_BINARY_DIR}/include)