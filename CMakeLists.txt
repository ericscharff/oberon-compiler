cmake_minimum_required(VERSION 3.10)
project(OberonCompiler C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
set(COMMON_FLAGS "-g -Wall -Wextra -Wpedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS}")

set(RUNTIME_DIR ${CMAKE_CURRENT_SOURCE_DIR}/base)

# Bootstrap 0: The RISC runner with a pre-compiled compiler image
add_executable(oberon0 risc_runner/runner.c)
target_include_directories(oberon0 PRIVATE risc_bootstrap)
target_compile_definitions(oberon0 PRIVATE MAX_MEM=624288)

file(GLOB ALL_OB_FILES "compiler/*.ob" "base/*.ob")

# Bootstrap 1: Use oberon0 to compile the compiler
add_custom_command(
    OUTPUT compiler0.c
    COMMAND oberon0 compiler/Compiler.ob > ${CMAKE_CURRENT_BINARY_DIR}/compiler0.c
    DEPENDS oberon0 ${ALL_OB_FILES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM
)

add_executable(oberon1 ${CMAKE_CURRENT_BINARY_DIR}/compiler0.c)
target_include_directories(oberon1 PRIVATE ${RUNTIME_DIR})

# Bootstrap 2: Use oberon1 to compile the compiler (self-hosting stage 1)
add_custom_command(
    OUTPUT compiler.c
    COMMAND oberon1 compiler/Compiler.ob > ${CMAKE_CURRENT_BINARY_DIR}/compiler.c
    DEPENDS oberon1 ${ALL_OB_FILES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM
)

add_executable(oberon ${CMAKE_CURRENT_BINARY_DIR}/compiler.c)
target_include_directories(oberon PRIVATE ${RUNTIME_DIR})

# Verification: Final compiler should be able to compile itself to the same C code
add_custom_command(
    TARGET oberon POST_BUILD
    COMMAND oberon compiler/Compiler.ob > ${CMAKE_CURRENT_BINARY_DIR}/compiler_self.c
    COMMAND ${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_BINARY_DIR}/compiler.c ${CMAKE_CURRENT_BINARY_DIR}/compiler_self.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Verifying compiler self-consistency"
    VERBATIM
)

# RCompiler: RISC version of the compiler
add_custom_command(
    OUTPUT rcompiler.c
    COMMAND oberon compiler/RCompiler.ob > ${CMAKE_CURRENT_BINARY_DIR}/rcompiler.c
    DEPENDS oberon ${ALL_OB_FILES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM
)

add_executable(oberonr ${CMAKE_CURRENT_BINARY_DIR}/rcompiler.c)
target_include_directories(oberonr PRIVATE ${RUNTIME_DIR})

# Regen target to update the bootstrap RISC code
add_custom_target(regen
    COMMAND oberonr -dumpcode compiler/Compiler.ob > ${CMAKE_CURRENT_SOURCE_DIR}/risc_bootstrap/risc_code.txt
    DEPENDS oberonr
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Updating risc_bootstrap/risc_code.txt"
    VERBATIM
)

# Helper scripts
configure_file(contrib/compile compile COPYONLY)
configure_file(contrib/rcompile rcompile COPYONLY)

enable_testing()

# Add tests
add_subdirectory(tests)
