cmake_minimum_required(VERSION 3.24)
project(antlr4_vba_benchmark)

set(CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_definitions(-DANTLR4CPP_STATIC)
set(ANTLR4_WITH_STATIC_CRT OFF)
set(ANTLR4_TAG 4.13.1)
include(ExternalAntlr4Cpp)
find_package(ANTLR)
if(NOT ANTLR_FOUND)
    set(ANTLR_JAR antlr-${ANTLR4_TAG}-complete.jar)
    set(ANTLR_JAR_URL https://www.antlr.org/download/${ANTLR_JAR})
    message(STATUS "Downloading antlr jar")
    file(DOWNLOAD ${ANTLR_JAR_URL} ${CMAKE_BINARY_DIR}/include/${ANTLR_JAR})
    message(STATUS "Downloading complete")
    set(ANTLR_EXECUTABLE ${CMAKE_BINARY_DIR}/include/${ANTLR_JAR})
    find_package(ANTLR REQUIRED)
endif()

antlr_target(VBAGrammarLexer  ${PROJECT_SOURCE_DIR}/grammar/VBALexer.g4 LEXER)
antlr_target(VBAGrammarParser ${PROJECT_SOURCE_DIR}/grammar/VBAParser.g4
        PARSER
        DEPENDS_ANTLR VBAGrammarLexer
        COMPILE_FLAGS -lib ${ANTLR_VBAGrammarLexer_OUTPUT_DIR}
        VISITOR LISTENER
)

add_executable(antlr4_vba_benchmark src/main.cpp
        ${ANTLR_VBAGrammarLexer_CXX_OUTPUTS}
        ${ANTLR_VBAGrammarParser_CXX_OUTPUTS}
)
target_link_libraries(antlr4_vba_benchmark
        PUBLIC antlr4_static
)
target_include_directories(antlr4_vba_benchmark
        PUBLIC ${ANTLR4_INCLUDE_DIRS}
        PUBLIC ${ANTLR_VBAGrammarLexer_OUTPUT_DIR}
        PUBLIC ${ANTLR_VBAGrammarParser_OUTPUT_DIR}
)