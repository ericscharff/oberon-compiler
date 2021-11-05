#!/bin/bash

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

for i in ${TESTS[@]}; do
  ../build/compile -cpp ${i}.ob
  ../build/out.prg > goldens/${i}.output
done
