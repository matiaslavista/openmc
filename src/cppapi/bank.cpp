
#include "openmc/bank.h"
#include "openmc/cppapi/bank.h"
#include "openmc/error.h"

#include <stdexcept>
#include <vector>


namespace openmc {

using std::vector;
namespace py = pybind11;
//==============================================================================
// CPP API
//==============================================================================

//Retrieves the global source Particle bank for python
std::vector<Particle::Bank>& source_bank()
{
  if (!simulation::source_bank.size()) {
    throw std::runtime_error("Source bank has not been allocated.");
  }
  return simulation::source_bank;
}

//Retrieves the global fission Particle bank for python
std::vector<Particle::Bank>& fission_bank()
{
  if (!simulation::fission_bank.size()) {
    throw std::runtime_error("Fission bank has not been allocated.");
  }
  return simulation::fission_bank;
}

//Add elements of banks to the module
void init_bank(py::module& m)
{
  m.def("source_bank", &source_bank, py::return_value_policy::reference);
  m.def("fission_bank", &fission_bank, py::return_value_policy::reference);
  py::enum_<Particle::Type>(m,"Type")
    .value("neutron", Particle::Type::neutron)
    .value("photon", Particle::Type::photon)
    .value("electron", Particle::Type::electron)
    .value("positron", Particle::Type::positron);
  py::class_<Particle::Bank>(m,"Bank")
    .def(py::init<>())
    .def_readwrite("E",&Particle::Bank::E)
    .def_readwrite("wgt",&Particle::Bank::wgt)
    .def_readwrite("delayed_group",&Particle::Bank::delayed_group)
    .def_readwrite("r",&Particle::Bank::r)
    .def_readwrite("u",&Particle::Bank::u)
    .def_readwrite("particle",&Particle::Bank::particle);
}

}
