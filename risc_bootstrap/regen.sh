#!/bin/bash

set -e

cd ../compiler
../build/rcompile Compiler.ob
if ! cmp -s ../build/risc_code.txt ../risc_bootstrap/risc_code.txt; then
  cp ../build/risc_code.txt ../risc_bootstrap
fi
