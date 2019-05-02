
#include "openmc/bank.h"
#include "openmc/cppapi/bank.h"
#include "openmc/capi.h"
#include "openmc/error.h"

#include <stdexcept>
#include <vector>


namespace openmc {

using std::vector;
namespace py = pybind11;

//==============================================================================
// CPP API
//==============================================================================
//Add elements of banks to the module
void init_bank(py::module& m)
{
  m.def("source_bank", &openmc_source_bank_cpp, py::return_value_policy::reference);
  m.def("fission_bank", &openmc_fission_bank_cpp, py::return_value_policy::reference);
  py::class_<Particle::Bank>(m,"bank")
    .def(py::init<>())
    .def_readwrite("E",&Particle::Bank::E)
    .def_readwrite("wgt",&Particle::Bank::wgt)
    .def_readwrite("delayed_group",&Particle::Bank::delayed_group);
    //.def_readwrite("r",&Particle::Bank::r)
    //.def_readwrite("u",&Particle::Bank::u)
    //.def_readwrite("particle",&Particle::Bank::particle)
}

}

