#/usr/bin/env python3

from setuptools import Extension, setup
import glob
import pybind11

exts = [
	Extension(
		name="sudokumod",
		sources=glob.glob("./src/*.cpp"),
		include_dirs=[pybind11.get_include(), "./include"],
		define_macros=[("BUILDLIB", None)]
	)
]

setup(
	name="sudokumod",
	ext_modules=exts,
	version="1.0.0"
)