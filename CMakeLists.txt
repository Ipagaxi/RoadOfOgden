cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME PnC)
project(${PROJECT_NAME} LANGUAGES CXX)

file(GLOB source_files
    "src/main/*.cpp"
    "src/main/Activities/*.cpp"
    "src/main/UIElements/*.cpp"
    "src/main/UIComponents/*.cpp"
    "src/main/Actors/*.cpp"
    "src/main/Animations/*.cpp"
    "src/main/UI_Objects/*.cpp"
    "src/main/FightStates/*.cpp"
)
set(SOURCES ${source_files})

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/project_build)
message (STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)


include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable (
    ${PROJECT_NAME}
    ${SOURCES}
        src/include/FightStates/StateFight.hpp
        src/include/FightEnv.hpp
)

target_include_directories(${PROJECT_NAME} PRIVATE "src/include")
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-audio)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()

add_custom_command(
    TARGET ${PROJECT_NAME}
    COMMENT "Copy resources"
    PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/src/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
    VERBATIM)

install(TARGETS ${PROJECT_NAME})
install(DIRECTORY ${PROJECT_SOURCE_DIR}/src/resources DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
