#!/bin/bash

set -e

TESTS=(
  ArrayTest
  CaseTest
  FibFact
  PtrTest
  RealNumbers
  Mandelbrot
  IOTest
  KnightsTour
  LangExtensionsTests
  Maze
  Pentominoes
  TestLex
  Recurse2
  Recurse
  SetTest
  Shadow
  ShortCircuit
  StrTest
)

RISC_TESTS=(
  ArrayTest
  CaseTest
  FibFact
  PtrTest
  RealNumbers
  Mandelbrot
  IOTest
  KnightsTour
  Maze
  Pentominoes
  TestLex
  SetTest
  Shadow
  ShortCircuit
  StrTest
)

CPP_TESTS=(
  OopTest
  RecCopy
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
  ../build/compile ${i}.ob
  ../build/out.prg < ../build/stdin.txt > ../build/$i.output
  diff -c goldens/$i.output ../build/$i.output || fail $i
done
for i in ${RISC_TESTS[@]}; do
  echo "Running RISC test $i..."
  ../build/rcompile ${i}.ob
  ../build/out.prg < ../build/stdin.txt > ../build/$i.output
  diff -c goldens/$i.output ../build/$i.output || fail $i
done
for i in ${CPP_TESTS[@]}; do
  echo "Running test $i..."
  ../build/compile -cpp ${i}.ob
  ../build/out.prg < ../build/stdin.txt > ../build/$i.output
  diff -c goldens/$i.output ../build/$i.output || fail $i
done
echo "All tests passed!"
