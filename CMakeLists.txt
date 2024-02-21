cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME PnC)
project(${PROJECT_NAME} LANGUAGES CXX)

file(GLOB source_files
    "src/main/*.cpp"
    "src/main/Activities/*.cpp"
    "src/main/UIElements/*.cpp"
)
set(SOURCES ${source_files})

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

target_include_directories(${PROJECT_NAME} PRIVATE "src/include")
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-audio)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

#if(WIN32)
 #   add_custom_command(
  #      TARGET ${PROJECT_NAME}
   #     COMMENT "Copy OpenAL DLL"
    #    PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
     #   VERBATIM)
#endif()

install(TARGETS ${PROJECT_NAME})