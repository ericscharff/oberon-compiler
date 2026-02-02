#!/bin/bash

# Usage: fmt.sh SourceFile.ob
#
# If lower case keywords are typed, they become upper case in the file.
# This might make typing easier, and then fmt.sh can be run to make the
# keywords compile properly.

sed -i 's/\barray\b/ARRAY/g' $1
sed -i 's/\bbegin\b/BEGIN/g' $1
sed -i 's/\bbitand\b/BITAND/g' $1
sed -i 's/\bbitor\b/BITOR/g' $1
sed -i 's/\bbitxor\b/BITXOR/g' $1
sed -i 's/\bby\b/BY/g' $1
sed -i 's/\bcase\b/CASE/g' $1
sed -i 's/\bconst\b/CONST/g' $1
sed -i 's/\bdiv\b/DIV/g' $1
sed -i 's/\bdo\b/DO/g' $1
sed -i 's/\belse\b/ELSE/g' $1
sed -i 's/\belsif\b/ELSIF/g' $1
sed -i 's/\bend\b/END/g' $1
sed -i 's/\bfalse\b/FALSE/g' $1
sed -i 's/\bfor\b/FOR/g' $1
sed -i 's/\bif\b/IF/g' $1
sed -i 's/\bimport\b/IMPORT/g' $1
sed -i 's/\bin\b/IN/g' $1
sed -i 's/\bis\b/IS/g' $1
sed -i 's/\bmod\b/MOD/g' $1
sed -i 's/\bmodule\b/MODULE/g' $1
sed -i 's/\bnative\b/NATIVE/g' $1
sed -i 's/\bnil\b/NIL/g' $1
sed -i 's/\bof\b/OF/g' $1
sed -i 's/\bor\b/OR/g' $1
sed -i 's/\bpointer\b/POINTER/g' $1
sed -i 's/\bprocedure\b/PROCEDURE/g' $1
sed -i 's/\brecord\b/RECORD/g' $1
sed -i 's/\brepeat\b/REPEAT/g' $1
sed -i 's/\breturn\b/RETURN/g' $1
sed -i 's/\bthen\b/THEN/g' $1
sed -i 's/\bto\b/TO/g' $1
sed -i 's/\btrue\b/TRUE/g' $1
sed -i 's/\btype\b/TYPE/g' $1
sed -i 's/\buntil\b/UNTIL/g' $1
sed -i 's/\bvar\b/VAR/g' $1
sed -i 's/\bwhile\b/WHILE/g' $1
sed -i 's/\binteger\b/INTEGER/g' $1
sed -i 's/\bchar\b/CHAR/g' $1
sed -i 's/\breal\b/REAL/g' $1
sed -i 's/\bset\b/SET/g' $1
