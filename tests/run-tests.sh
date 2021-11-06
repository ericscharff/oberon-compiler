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
echo "4" >> ../build/stdin.txt

for i in ${TESTS[@]}; do
  echo "Running test $i..."
  ../build/compile -cpp ${i}.ob
  ../build/out.prg < ../build/stdin.txt > ../build/$i.output
  diff ../build/$i.output goldens/$i.output
done
echo "All tests passed!"
