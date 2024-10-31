cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME PnC)
project(${PROJECT_NAME} LANGUAGES CXX)

file(GLOB source_files
    "src/*.cpp"
    "src/Activities/*.cpp"
    "src/Activities/FightActivity/*.cpp"
    "src/Activities/FightActivity/FightStates/*.cpp"
    "src/Activities/MenuActivity/*.cpp"
    "src/Activities/CharacterActivity/*.cpp"
    "src/Activities/CharacterActivity/Character_Inventory/*.cpp"
    "src/Actors/*.cpp"
    "src/Animations/*.cpp"
    "src/Global/*.cpp"
    "src/ObserverPattern/*.cpp"
    "src/System/*.cpp"
    "src/UIElements/*.cpp"
)
set(SOURCES ${source_files})

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/project_build)
set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/resources")

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
)

target_include_directories(${PROJECT_NAME} PRIVATE "src" "${CMAKE_SOURCE_DIR}")
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
    PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
    VERBATIM)

install(TARGETS ${PROJECT_NAME})
install(DIRECTORY ${PROJECT_SOURCE_DIR}/resources DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
