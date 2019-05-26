#ifndef OPENMC_CPP_BANK_H
#define OPENMC_CPP_BANK_H

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

//This file is exclusively to allow cppapi to see the declaration of adding
//the bank to the python shared module

namespace openmc {
namespace py = pybind11;
void init_bank(py::module&);
} // namespace openmc

#endif // OPENMC_CPP_BANK_H
