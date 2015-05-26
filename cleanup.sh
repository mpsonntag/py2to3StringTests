#!/bin/bash

# main test script for the whole unicode string testing
# executes setup[xxx].py, copies python test scripts to the 
# created custom cpp module and runs them from there

#setupFile=setup.py
# using __future__ requires escape bytestrings/unicode:
setupFile=setupEsc.py
#setupFile=setup.py
# python code for interacting with the custom cpp module
testFile=test.py

# paths to created builds dependent on used python version
LIBPATH27=build/lib.linux-x86_64-2.7
LIBPATH34=build/lib.linux-x86_64-3.4

# remove old build directories if they exist
[ -d build ] && rm -r build/
[ -d build27 ] && rm -r build27/

# tests with python 2.7
python -3 $setupFile build
cp $testFile $LIBPATH27/$testFile
cd $LIBPATH27
echo ""
echo ""
echo "(sh)...__future__ test, python 2.7"
python $testFile
echo ""
echo ""
echo "(sh)...__future__ test, python 3 switch"
python -3 $testFile

# move python 2.7 build folder
cd ../../
mv build/ build27/

# test with python 3
echo ""
python3 $setupFile build
cp $testFile $LIBPATH34/$testFile
cd $LIBPATH34
echo ""
echo ""
echo "(sh)...__future__ test, python 3.4"
python3 $testFile
echo ""
echo ""



