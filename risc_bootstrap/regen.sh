#!/bin/bash

set -e

cd ../compiler
../build/rcompile Compiler.ob
cp ../build/risc_code.txt ../risc_bootstrap
