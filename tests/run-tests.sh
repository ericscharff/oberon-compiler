#!/bin/bash

set -e

TESTS=(
  ArrayTest
  CaseTest
  FibFact
  IOTest
  KnightsTour
  LangExtensionsTests
  Maze
  OopTest
  Pentominoes
  RecCopy
  Recurse2
  Recurse
  SetTest
  Shadow
  ShortCircuit
  StrTest
  TestBed
  TypeExt
)

# Generate stdin for IOTest
echo "19" > ../build/stdin.txt

fail() {
  echo "Failed test $1. See above output for diff"
  exit 1
}

for i in ${TESTS[@]}; do
  echo "Running test $i..."
  ../build/compile -cpp ${i}.ob
  ../build/out.prg < ../build/stdin.txt > ../build/$i.output
  diff -c goldens/$i.output ../build/$i.output || fail $i
done
echo "All tests passed!"
