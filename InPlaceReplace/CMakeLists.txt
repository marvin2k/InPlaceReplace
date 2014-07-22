cmake_minimum_required(VERSION 2.8)

project(InPlaceReplace)

find_program(LLVM_CONFIG NAMES llvm-config-3.3)

exec_program(${LLVM_CONFIG} ARGS --cxxflags OUTPUT_VARIABLE LLVM_CONFIG_CXXFLAGS)
add_definitions(${LLVM_CONFIG_CXXFLAGS})

exec_program(${LLVM_CONFIG} ARGS --ldflags OUTPUT_VARIABLE LLVM_CONFIG_LDFLAGS)
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${LLVM_CONFIG_LDFLAGS}" )

set(SOURCES
    src/InPlaceReplace.cpp
    )
set(HEADERS
    )

add_executable(${PROJECT_NAME} ${SOURCES})

exec_program(${LLVM_CONFIG} ARGS --libs OUTPUT_VARIABLE LLVM_CONFIG_LIBS)
target_link_libraries(${PROJECT_NAME}
    clangFrontend clangSerialization clangDriver
    clangRewriteCore clangParse clangSema clangAnalysis
    clangAST clangASTMatchers clangLex clangBasic clangRewriteFrontend
    clangEdit clangTooling clangFrontend
    ${LLVM_CONFIG_LIBS}
    )


# symlink the actual binary
add_custom_target(${PROJECT_NAME}-lazy-symlink ALL ln --force -s ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/${PROJECT_NAME} DEPENDS ${PROJECT_NAME})
# and clean this up if someone asks us to do so
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${CMAKE_SOURCE_DIR}/${PROJECT_NAME})
