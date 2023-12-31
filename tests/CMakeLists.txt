project(test)


include(FetchContent)

# GoogleTest
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG f8d7d77c06936315286eb55f8de22cd23c188571 #v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

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

# cpr
FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 3b15fa82ea74739b574d705fea44959b58142eb8 #curl CVE-2023-38545
)

FetchContent_MakeAvailable(cpr)
FetchContent_GetProperties(cpr)
if (NOT cpr_POPULATED)
    FetchContent_Populate(cpr)
    add_subdirectory(${cpr_SOURCE_DIR} ${cpr_BINARY_DIR})
endif ()


add_executable(test
        core/ResultTest.cpp
        core/ErrorTest.cpp
        core/BitwardenSecretsManagerTest.cpp
        core/ConfigurationReaderTest.cpp
        core/SecretsManagerComponentTest.cpp
        TestBase.h
        TestBase.cpp
        DummyControllerTest.cpp
        DummyControllerTest.h
        authentication/controllers/AuthenticationControllerTest.cpp
        authentication/controllers/AuthenticationControllerTest.h)


target_link_libraries(test GTest::gtest_main api fruit Crow::Crow nlohmann_json cpr::cpr)
target_include_directories(test PRIVATE ${CMAKE_SOURCE_DIR}/src)

include(GoogleTest)
gtest_discover_tests(test)

file(COPY ${CMAKE_SOURCE_DIR}/config/ DESTINATION ${CMAKE_BINARY_DIR}/tests)
file(COPY ${CMAKE_SOURCE_DIR}/ssl/ DESTINATION ${CMAKE_BINARY_DIR}/tests)