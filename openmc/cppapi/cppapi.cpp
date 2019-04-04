#include <pybind11/pybind11.h>
#include "openmc/capi.h" 
#include <string>
#include <vector>
#include <pybind11/stl.h>
#include <algorithm>
namespace py = pybind11;


namespace openmc {

using std::string;
using std::vector;

int init(vector<string> argv_c = {}, const void* intracomm = NULL) {
    vector<char*> argv_char(argv_c.size());
    std::transform(argv_c.begin(), argv_c.end(), argv_char.begin(),
            [](string& a){return const_cast<char *>(a.c_str());} );
    return openmc_init(argv_char.size(), argv_char.data(), intracomm);
}
        
}

int add(int i, int j) {
    return i + j;
}
PYBIND11_MODULE(openmc_cpp, m) {
    m.doc() = R"pbdoc(
        CPP API to OPENMCs
        -----------------------
        .. currentmodule:: openmc_cpp
        .. autosummary::
           :toctree: _generate
           init
    )pbdoc";

    m.def("init", &openmc::init, py::arg("argv_c") = py::list(), 
            py::arg("intracomm") = NULL,
          );

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}
