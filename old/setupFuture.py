#!/usr/bin/env python
from __future__ import unicode_literals

from distutils.core import setup
from distutils.extension import Extension

setup(name=b"PackageName",
    ext_modules=[
        Extension(b"stringTest", [b"testString.cpp"],
        libraries = [b"boost_python"])
    ])

