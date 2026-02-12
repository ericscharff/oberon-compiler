file(GLOB TEST_OB_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.ob")

foreach(TEST_OB ${TEST_OB_FILES})
    string(REPLACE ".ob" "" TEST_NAME ${TEST_OB})
    
    set(TEST_OB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_OB})
    set(STDIN_PATH ${CMAKE_CURRENT_SOURCE_DIR}/stdin.txt)
    set(GOLDEN_PATH ${CMAKE_CURRENT_SOURCE_DIR}/goldens/${TEST_NAME}.output)

    # 1. C Test
    set(C_FILE ${CMAKE_CURRENT_BINARY_DIR}/${TEST_NAME}.c)
    add_custom_command(
        OUTPUT ${C_FILE}
        COMMAND oberon ${TEST_OB_PATH} > ${C_FILE}
        DEPENDS oberon ${TEST_OB_PATH}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        VERBATIM
    )
    set(C_EXE c_test_${TEST_NAME})
    add_executable(${C_EXE} ${C_FILE})
    target_include_directories(${C_EXE} PRIVATE ${RUNTIME_DIR})
    target_compile_options(${C_EXE} PRIVATE -Wno-unused-parameter)
    
    add_test(
        NAME ${C_EXE}
        COMMAND ${CMAKE_COMMAND} 
            -DEXE=$<TARGET_FILE:${C_EXE}> 
            -DINPUT=${STDIN_PATH} 
            -DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/${TEST_NAME}.c.output 
            -DGOLDEN=${GOLDEN_PATH} 
            -P ${CMAKE_CURRENT_SOURCE_DIR}/run_test.cmake
    )

    # 2. C Bounds Test
    set(C_BOUNDS_FILE ${CMAKE_CURRENT_BINARY_DIR}/${TEST_NAME}_bounds.c)
    add_custom_command(
        OUTPUT ${C_BOUNDS_FILE}
        COMMAND oberon -bounds ${TEST_OB_PATH} > ${C_BOUNDS_FILE}
        DEPENDS oberon ${TEST_OB_PATH}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        VERBATIM
    )
    set(C_BOUNDS_EXE c_bounds_test_${TEST_NAME})
    add_executable(${C_BOUNDS_EXE} ${C_BOUNDS_FILE})
    target_include_directories(${C_BOUNDS_EXE} PRIVATE ${RUNTIME_DIR})
    target_compile_options(${C_BOUNDS_EXE} PRIVATE -Wno-unused-parameter)

    add_test(
        NAME ${C_BOUNDS_EXE}
        COMMAND ${CMAKE_COMMAND} 
            -DEXE=$<TARGET_FILE:${C_BOUNDS_EXE}> 
            -DINPUT=${STDIN_PATH} 
            -DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/${TEST_NAME}_bounds.c.output 
            -DGOLDEN=${GOLDEN_PATH} 
            -P ${CMAKE_CURRENT_SOURCE_DIR}/run_test.cmake
    )

    # 3. C++ Test
    set(CPP_FILE ${CMAKE_CURRENT_BINARY_DIR}/${TEST_NAME}.cpp)
    add_custom_command(
        OUTPUT ${CPP_FILE}
        COMMAND oberon -cpp ${TEST_OB_PATH} > ${CPP_FILE}
        DEPENDS oberon ${TEST_OB_PATH}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        VERBATIM
    )
    set(CPP_EXE cpp_test_${TEST_NAME})
    add_executable(${CPP_EXE} ${CPP_FILE})
    target_include_directories(${CPP_EXE} PRIVATE ${RUNTIME_DIR})
    target_compile_options(${CPP_EXE} PRIVATE -Wno-unused-parameter)

    add_test(
        NAME ${CPP_EXE}
        COMMAND ${CMAKE_COMMAND} 
            -DEXE=$<TARGET_FILE:${CPP_EXE}> 
            -DINPUT=${STDIN_PATH} 
            -DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/${TEST_NAME}.cpp.output 
            -DGOLDEN=${GOLDEN_PATH} 
            -P ${CMAKE_CURRENT_SOURCE_DIR}/run_test.cmake
    )

    # 4. RISC Test
    set(RISC_CODE_FILE ${CMAKE_CURRENT_BINARY_DIR}/${TEST_NAME}_risc_code.txt)
    add_custom_command(
        OUTPUT ${RISC_CODE_FILE}
        COMMAND oberonr -dumpcode ${TEST_OB_PATH} > ${RISC_CODE_FILE}
        DEPENDS oberonr ${TEST_OB_PATH}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        VERBATIM
    )
    
    set(RISC_EXE risc_test_${TEST_NAME})
    add_executable(${RISC_EXE} ${CMAKE_SOURCE_DIR}/risc_runner/runner.c ${RISC_CODE_FILE})
    target_include_directories(${RISC_EXE} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
    target_compile_definitions(${RISC_EXE} PRIVATE MAX_MEM=65536 "CODE_FILE=\"${TEST_NAME}_risc_code.txt\"")
    set_source_files_properties(${CMAKE_SOURCE_DIR}/risc_runner/runner.c PROPERTIES OBJECT_DEPENDS ${RISC_CODE_FILE})

    add_test(
        NAME ${RISC_EXE}
        COMMAND ${CMAKE_COMMAND} 
            -DEXE=$<TARGET_FILE:${RISC_EXE}> 
            -DINPUT=${STDIN_PATH} 
            -DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/${TEST_NAME}_risc.output 
            -DGOLDEN=${GOLDEN_PATH} 
            -P ${CMAKE_CURRENT_SOURCE_DIR}/run_test.cmake
    )

endforeach()

# Compiler self-tests
add_test(NAME oberon_self_test COMMAND oberon)
set_tests_properties(oberon_self_test PROPERTIES WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
