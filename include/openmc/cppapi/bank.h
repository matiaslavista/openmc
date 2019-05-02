#ifndef OPENMC_CPP_BANK_H
#define OPENMC_CPP_BANK_H

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


// Without an explicit instantiation of vector<Bank>, the Intel compiler
// will complain about the threadprivate directive on filter_matches. Note that
// this has to happen *outside* of the openmc namespace


namespace openmc {
namespace py = pybind11;
//==============================================================================
// Non-member functions
//==============================================================================
void init_bank(py::module&);
} // namespace openmc

#endif // OPENMC_CPP_BANK_H
