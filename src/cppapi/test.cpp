#include <pybind11/pybind11.h>

namespace py = pybind11;


int add(int i, int j) {
  return i + j;
}

int subtract(int i, int j) {
  return i-j;
}

namespace openmc {

void init_test_file(py::module& m) {
  m.def("add", &add);
  m.def("subtract", &subtract);
}

};

