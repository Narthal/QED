#include <iostream>


#include "pybind11/pybind11.h"
#include <pybind11/embed.h>
#include "Python.h"

namespace py = pybind11;



int add(int i, int j) {
	return i + j;
}

PYBIND11_EMBEDDED_MODULE(example, m) {
	m.doc() = "pybind11 example plugin"; // optional module docstring

	m.def("add", &add, "A function which adds two numbers");
}

int main()
{
	py::initialize_interpreter();




	try
	{
		py::module calc = py::module::import("calc");
		py::object result = calc.attr("add")(1, 2);
		int n = result.cast<int>();

		py::module fastCalc = py::module::import("fastCalc");
		result = fastCalc.attr("add")(1, 3);
		int m = result.cast<int>();
	}
	catch(std::exception e)
	{
		std::cout << e.what() << std::endl;
	}

	py::finalize_interpreter();

	return 0;
}