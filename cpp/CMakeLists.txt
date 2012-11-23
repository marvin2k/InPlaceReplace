cmake_minimum_required(VERSION 2.8)

project(InPlaceReplace)

add_definitions(-g  -DNDEBUG -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -O3 -fomit-frame-pointer -fvisibility-inlines-hidden -fno-exceptions -fno-rtti -fPIC -Woverloaded-virtual -Wcast-qual)

include_directories(/home/mzenzes/llvm.install/include)
link_directories(/home/mzenzes/llvm.install/lib)

set(SOURCES
    src/main.cpp
    )
set(HEADERS
    )

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME}
    clangFrontend clangSerialization clangDriver
    clangRewriteCore clangParse clangSema clangAnalysis
    clangAST clangASTMatchers clangLex clangBasic clangRewriteFrontend
    clangEdit clangTooling clangFrontend
    LLVMCore LLVMMC LLVMAsmParser LLVMAsmPrinter LLVMMCParser LLVMSupport
    dl pthread
    )











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
