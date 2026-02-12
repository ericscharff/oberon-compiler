# Helper script to run a test and compare output with golden file
# Usage: cmake -DEXE=path/to/exe -DINPUT=path/to/stdin.txt -DOUTPUT=path/to/output.txt -DGOLDEN=path/to/golden.output -P run_test.cmake

execute_process(
    COMMAND ${EXE}
    INPUT_FILE ${INPUT}
    OUTPUT_FILE ${OUTPUT}
    ERROR_VARIABLE ERROR_OUTPUT
    RESULT_VARIABLE TEST_RESULT
)

# Merge error output into output file if needed, but Makefile uses > file 2>&1
# So we should probably capture both.
file(APPEND ${OUTPUT} "${ERROR_OUTPUT}")

if(TEST_RESULT)
    message(FATAL_ERROR "Test execution failed with result: ${TEST_RESULT}")
endif()

execute_process(
    COMMAND ${CMAKE_COMMAND} -E compare_files ${OUTPUT} ${GOLDEN}
    RESULT_VARIABLE COMPARE_RESULT
)

if(COMPARE_RESULT)
    message(FATAL_ERROR "Output mismatch for ${EXE}")
endif()
