
#include "openmc/capi.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <algorithm>
#include <string>
#include <vector>
namespace py = pybind11;

namespace openmc {

using std::string;
using std::vector;

int init(vector<string> argv = {}, const void* intracomm = NULL) 
{
  vector<char*> argv_char(argv.size());
  std::transform(argv.begin(), argv.end(), argv_char.begin(),
                 [](string& a) { return const_cast<char*>(a.c_str()); });
  return openmc_init(argv_char.size(), argv_char.data(), intracomm);
}

int run() { return openmc_run(); }

int finalize() { return openmc_finalize(); }

int simulation_finalize() { return openmc_simulation_finalize(); }

int simulation_init() { return openmc_simulation_init(); }

int next_batch(int* status) { return next_batch(status); }

} // namespace openmc

PYBIND11_MODULE(openmc_cpp, m) 
{
  m.doc() = R"pbdoc(
        C++ API to OpenMC
        -----------------------
        .. currentmodule:: openmc_cpp
        .. autosummary::
           :toctree: _generate
           init
    )pbdoc";

  m.def("init", &openmc::init, py::arg("argv") = py::list(),
        py::arg("intracomm") = NULL);
  m.def("run", &openmc::run);
  m.def("finalize", &openmc::finalize);

#ifdef VERSION_INFO
  m.attr("__version__") = VERSION_INFO;
#else
  m.attr("__version__") = "dev";
#endif
}
