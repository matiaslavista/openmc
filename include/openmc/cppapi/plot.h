#ifndef OPENMC_CPP_PLOT_H
#define OPENMC_CPP_PLOT_H

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

//This file is exclusively to allow cppapi to see the declaration of adding
//plot functions to the python shared module

namespace openmc {
namespace py = pybind11;
void init_plot(py::module&);
} // namespace openmc

#endif // OPENMC_CPP_PLOT_H