
#include "openmc/eigenvalue.h"
#include "openmc/cppapi/eigenvalue.h"

#include <tuple>
#include <stdexcept>

namespace openmc {

namespace py = pybind11;

std::tuple<double, double> get_keff(){
  double arr[2];
  int ret = openmc_get_keff(arr);
  return std::make_tuple(arr[0],arr[1]);
}

//==============================================================================
// CPP API
//==============================================================================
//Add elements of eigenvalue to the module
void init_eigenvalue(py::module& m)
{
  m.def("get_keff", &openmc::get_keff);
}

}
