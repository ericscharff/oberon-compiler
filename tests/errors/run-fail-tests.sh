#!/bin/bash

TESTS=(
  ArrayFail
  CastFail
  NilFail
)

fail() {
  echo "Test $1 should fail, but exited successfully"
  exit 1
}

for i in ${TESTS[@]}; do
  echo "Running test $i..."
  ../../build/compile -bounds ${i}.ob
  pushd ../../build > /dev/null
  if ( ./out.prg || false ) >/dev/null 2>&1; then
    fail $i
  fi
  popd > /dev/null
done
for i in ${TESTS[@]}; do
  echo "Running RISC test $i..."
  ../../build/rcompile ${i}.ob
  pushd ../../build > /dev/null
  if ( ./out.prg || false ) >/dev/null 2>&1; then
    fail $i
  fi
  popd > /dev/null
done
echo "All tests passed!"
