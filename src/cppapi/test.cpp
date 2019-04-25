#include <pybind11/pybind11.h>

namespace py = pybind11;

//Place holder functions
int add(int i, int j) {
  return i + j;
}
//place holder functions
int subtract(int i, int j) {
  return i-j;
}

namespace openmc {
//adding them to the module from a diff file
void init_test_file(py::module& m) {
  m.def("add", &add);
  m.def("subtract", &subtract);
}

};

