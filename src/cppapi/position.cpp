
#include "openmc/position.h"
#include "openmc/cppapi/position.h"
#include "openmc/capi.h"
#include "openmc/error.h"

#include <pybind11/operators.h>

#include <stdexcept>
#include <vector>


namespace openmc {

using std::vector;
namespace py = pybind11;

//==============================================================================
// CPP API
//==============================================================================
//Add elements of Position to the module
void init_position(py::module& m)
{
  py::class_<Position> (m,"Position")
    .def(py::init<double, double, double>())
    .def(py::init([](std::tuple<double,double,double> tup) {
      return Position{std::get<0>(tup),std::get<1>(tup), std::get<2>(tup)};
    }))
    .def(py::self += py::self)
    .def(py::self += double())
    .def(py::self -= py::self)
    .def(py::self -= double())
    .def(py::self *= py::self)
    .def(py::self *= double())
    .def(py::self /= py::self)
    .def(py::self /= double())
    .def(-py::self)
    .def(py::self + py::self)
    .def(py::self + double())
    .def(double() + py::self)
    .def(py::self - py::self)
    .def(py::self - double())
    .def(double() - py::self)
    .def(py::self * py::self)
    .def(py::self * double())
    .def(double() * py::self)
    .def(py::self / py::self)
    .def(py::self / double())
    .def(double() / py::self)
    .def(py::self == py::self)
    .def(py::self != py::self)
    .def("dot", &Position::dot)
    .def("norm", &Position::norm)
    .def_readwrite("x", &Position::x)
    .def_readwrite("y", &Position::y)
    .def_readwrite("z", &Position::z);
  py::implicitly_convertible<std::tuple<double,double,double>, Position>();
    //[] Operator is not overloadable in python
}

}

