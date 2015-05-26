#!/usr/bin/env python
#from __future__ import unicode_literals

#when using "__future__ import unicode_literals" all strings will basically be unicode.
#when using boost_python still with python 2.7, this will lead to an error,
#since the setup(...) will contain unicode strings, but the boost_python module
#will expect byte strings.
#so if the setup is run with python2 and the __future__ import, these strings
#manually have to be converted to byte strings e.g. with b'', so the boost_python can handle the strings.

#but if we want to use the same file with python3, b'' is gone, and the boost_python with python3 will anyway expect
#unicode strings... so we can either escape all strings manually depending on the python version we are using, when
#we want to use the unicode_literal import.
#or we dismiss the unicode_literals import - if we use python2 here, the strings will be bytestrings and handed over to
#a boost_python using python2 that expects bytestrings, if we use python3 here the strings will be unicode and handed over to
#a boost_python (and here it comes) hopefully using python3 that expects unicode.

from distutils.core import setup
from distutils.extension import Extension

import sys
# determine python version and set required boost_python version dynamically
pyVersion = 'boost_python-py'+ str(sys.version_info.major) + str(sys.version_info.minor)

setup(name='PackageName',
    ext_modules=[
        Extension('stringTest', sources = ['testString.cpp'],
        libraries = [pyVersion])
    ])

