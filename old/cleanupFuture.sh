#!/bin/bash

# main test script for the whole unicode string testing stuff
# runs setup.py, copies python test scripts to where they are supposed to be
# and runs them from there

rm -r build/
python setupFuture.py build
cp test.py build/lib.linux-x86_64-2.7/test.py
cp testFuture.py build/lib.linux-x86_64-2.7/testFuture.py
cd build/lib.linux-x86_64-2.7
echo ""
echo ""
echo "normal test, python 2.7"
python test.py
echo ""
echo ""
echo "future test, python 2.7"
python testFuture.py
echo ""
echo ""
echo "normal test, python 3 switch"
python -3 test.py
echo ""
echo ""
echo "future test, python 3 switch"
python -3 testFuture.py
echo ""
echo ""
echo "normal test, python 3"
python3 test.py
echo ""
echo ""
echo "future test, python 3"
python3 testFuture.py


