#include <string>
#include <sstream>
#include <pybind11/pybind11.h>
#include "sudoku.hpp"

namespace py = pybind11;

PYBIND11_MODULE(sudokumod, m)
{
	py::class_<Sudoku>(m, "Sudoku")
		.def(py::init<>())
		.def(py::init<const std::string&>())
		.def("loadfile", &Sudoku::loadfile)
		.def("solve", &Sudoku::solve)
		.def("__repr__", [](const Sudoku& s){
			std::ostringstream oss;
			oss << s;
			return oss.str();
		});
}