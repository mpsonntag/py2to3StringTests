#!/usr/bin/env python
from __future__ import unicode_literals

import sys

if sys.version < '3':
	# future unicode_literals import converts all byte strings to unicode.
	# boost python expects byte strings - therefore with python 2, all strings
	# have to be encoded to byte strings.
	def esc(x):
		return x.encode()
else:
	def esc(x):
		return x

from distutils.core import setup
from distutils.extension import Extension

# determine python version and set required boost_python version dynamically
pyVersion = 'boost_python-py'+ str(sys.version_info.major) + str(sys.version_info.minor)

setup(name=esc('PackageName'),
    ext_modules=[
        Extension(
			esc('stringTest'),
			sources = [esc('testString.cpp')],
        	libraries = [esc(pyVersion)])
    ])

