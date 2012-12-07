cmake_minimum_required(VERSION 2.8)

project(InPlaceReplace)

# FIXME...
add_definitions(-g  -DNDEBUG -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -O3 -fomit-frame-pointer -fvisibility-inlines-hidden -fno-exceptions -fno-rtti -fPIC -Woverloaded-virtual -Wcast-qual)

# installation of infrastructure explained in README
include_directories($ENV{HOME}/llvm.install/include)
link_directories($ENV{HOME}/llvm.install/lib)

set(SOURCES
    src/InPlaceReplace.cpp
    )
set(HEADERS
    )

add_executable(${PROJECT_NAME} ${SOURCES})
# don't ask on this one... will have to look into this mess...
target_link_libraries(${PROJECT_NAME}
    clangFrontend clangSerialization clangDriver
    clangRewriteCore clangParse clangSema clangAnalysis
    clangAST clangASTMatchers clangLex clangBasic clangRewriteFrontend
    clangEdit clangTooling clangFrontend
    LLVMCore LLVMMC LLVMAsmParser LLVMAsmPrinter LLVMMCParser LLVMSupport
    dl pthread
    )

# symlink the actual binary
add_custom_target(${PROJECT_NAME}-lazy-symlink ALL ln --force -s ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/${PROJECT_NAME} DEPENDS ${PROJECT_NAME})
# and clean this up if someone asks us to do so
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${CMAKE_SOURCE_DIR}/${PROJECT_NAME})











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
