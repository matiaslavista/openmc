#include "openmc/capi.h"
#include "openmc/cppapi/bank.h"
#include "openmc/cppapi/position.h"
#include "openmc/cppapi/eigenvalue.h"
#include "openmc/cppapi/plot.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <algorithm>
#include <string>
#include <vector>
namespace py = pybind11;

namespace openmc {

using std::string;
using std::vector;

// General exception handler 
// This function is called by openmc_cppapi functions
// that wrap error codes, and throw exceptions
void exception_handler(string func, int err) 
{
  string msg = "function " + func + " exited with error code: "
      + std::to_string(err);
  throw std::runtime_error(msg);
}

int init(vector<string> argv = {}, const void* intracomm = nullptr)
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
int reset() { return openmc_reset(); }
int hard_reset() { return openmc_hard_reset(); }

int next_batch()
{
  int status = 0;
  int ret = openmc_next_batch(&status);
  if (ret) { 
      exception_handler(__func__,ret); 
  }
  return status;
}

} // namespace openmc

PYBIND11_MODULE(openmc_cpp, m) 
{
  openmc::init_position(m);
  openmc::init_bank(m);
  openmc::init_eigenvalue(m);
  openmc::init_plot(m);

  m.doc() = R"pbdoc(
        C++ API to OpenMC
        -----------------------
        .. currentmodule:: openmc_cpp
        .. autosummary::
           :toctree: _generate
           init
    )pbdoc";

  m.def("init", &openmc::init, py::arg("argv") = py::list(),
        py::arg("intracomm") = (void*) nullptr);
  m.def("run", &openmc::run);
  m.def("finalize", &openmc::finalize);
  m.def("simulation_finalize", &openmc::simulation_finalize);
  m.def("simulation_init", &openmc::simulation_init);
  m.def("next_batch", &openmc::next_batch);
  m.def("reset", &openmc::reset);
  m.def("hard_reset", &openmc::hard_reset);
#ifdef VERSION_INFO
  m.attr("__version__") = VERSION_INFO;
#else
  m.attr("__version__") = "dev";
#endif
}
