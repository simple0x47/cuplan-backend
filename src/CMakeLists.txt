project(api VERSION 5123.0.0)

include(FetchContent)

# Google Fruit
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
endif ()

# Crow
FetchContent_Declare(
        crow
        GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
        GIT_TAG edf12f699ec3bf6f751cf73cb97f32919e48ca6e #v.1.0+5 Security Patch
)

FetchContent_MakeAvailable(crow)
FetchContent_GetProperties(crow)
if (NOT crow_POPULATED)
    FetchContent_Populate(crow)
    add_subdirectory(${crow_SOURCE_DIR} ${crow_BINARY_DIR})
endif ()

set(CROW_FEATURES ssl)

# JSON
FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG bc889afb4c5bf1c0d8ee29ef35eaaf4c8bef8a5d #v.3.11.2
)

FetchContent_MakeAvailable(json)
FetchContent_GetProperties(json)
if (NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR})
endif ()

add_library(api STATIC core/ISecretsManager.h
        core/Result.h
        core/Error.h
        core/BitwardenSecretsManager.cpp
        core/BitwardenSecretsManager.h
        core/ErrorKind.h
        core/ConfigurationReader.cpp
        core/ConfigurationReader.h
        core/Constants.h
        core/SecretsManagerComponent.h
        routes.h
        routes.cpp
)
add_executable(apiRunner main.cpp)


set_target_properties(api PROPERTIES LINKER_LANGUAGE CXX)


target_link_libraries(api PRIVATE pthread fruit Crow::Crow nlohmann_json)
target_include_directories(api PUBLIC ${fruit_SOURCE_DIR}/include ${fruit_BINARY_DIR}/include
        ${json_SOURCE_DIR}/include)

target_link_libraries(apiRunner PRIVATE fruit Crow::Crow api)

file(COPY ${CMAKE_SOURCE_DIR}/config/ DESTINATION ${CMAKE_BINARY_DIR}/src)
file(COPY ${CMAKE_SOURCE_DIR}/ssl/ DESTINATION ${CMAKE_BINARY_DIR}/src)