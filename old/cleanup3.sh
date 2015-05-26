#!/bin/bash

# main test script for the whole unicode string testing stuff
# runs setup.py, copies python test scripts to where they are supposed to be
# and runs them from there

LIBPATH=build/lib.linux-x86_64-3.4

rm -r build/
python3 setupEsc.py build
cp test.py $LIBPATH/test.py
cd $LIBPATH
echo ""
echo ""
echo "future test, python 3.4"
python3 test.py
echo ""
echo ""

