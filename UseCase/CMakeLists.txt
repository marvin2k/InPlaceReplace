cmake_minimum_required(VERSION 2.8)

project(testInPlaceReplace)

set(SOURCES
    src/bar.cpp
    src/dummy.cpp
    )
set(HEADERS
    src/bar.h
    src/dummy.h
    )

add_library(${PROJECT_NAME} ${SOURCES})
add_executable(${PROJECT_NAME}_main src/main.cpp)
target_link_libraries(${PROJECT_NAME}_main ${PROJECT_NAME})








# PRIVATE
# create a .clang_complete -- used by a cool vim plugin
file(REMOVE ${PROJECT_SOURCE_DIR}/.clang_complete)
get_property(incdirs DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
file(APPEND ${PROJECT_SOURCE_DIR}/.clang_complete "-x c++\n")
foreach(loopvar ${incdirs})
    set(Iline "-I" ${loopvar} "\n")
    file(APPEND ${PROJECT_SOURCE_DIR}/.clang_complete ${Iline} )
endforeach(loopvar)
get_property(defines DIRECTORY ${subdir} PROPERTY COMPILE_DEFINITIONS)
foreach(loopvar ${defines})
    set(Dline "-D" ${loopvar} "\n")
    file(APPEND ${PROJECT_SOURCE_DIR}/.clang_complete ${Dline} )
endforeach(loopvar)
# and clean up the mess inside the .clang_complete
execute_process(COMMAND sort -u ${PROJECT_SOURCE_DIR}/.clang_complete -o ${PROJECT_SOURCE_DIR}/.clang_complete)
