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
  TestCompiler
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
  TestBed
  KnightsTour
  Maze
  Pentominoes
  TestCompiler
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
  pushd ../build > /dev/null
  ../build/out.prg < ../build/stdin.txt > ../build/$i.output
  popd > /dev/null
  diff -c goldens/$i.output ../build/$i.output || fail $i
done
for i in ${RISC_TESTS[@]}; do
  echo "Running RISC test $i..."
  MEM_SIZE=262144 ../build/rcompile ${i}.ob
  pushd ../build > /dev/null
  ../build/out.prg < ../build/stdin.txt > ../build/$i.output
  popd > /dev/null
  diff -c goldens/$i.output ../build/$i.output || fail $i
done
for i in ${CPP_TESTS[@]}; do
  echo "Running test $i..."
  ../build/compile -cpp ${i}.ob
  pushd ../build > /dev/null
  ../build/out.prg < ../build/stdin.txt > ../build/$i.output
  popd > /dev/null
  diff -c goldens/$i.output ../build/$i.output || fail $i
done
echo "All tests passed!"
