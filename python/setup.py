#!/usr/bin/env python3

from setuptools import setup
from Cython.Build import cythonize

setup(
	name="cydoku",
    ext_modules = cythonize("cydoku.pyx"),
    version="1.0.0"
)
