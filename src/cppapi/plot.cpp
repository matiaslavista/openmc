#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include "openmc/plot.h"
#include "openmc/cppapi/plot.h"
#include "openmc/capi.h"
#include "xtensor/xarray.hpp"

#include<algorithm>

namespace openmc {
namespace py = pybind11;

int plot_geometry() { return openmc_plot_geometry();}

void init_plot(py::module& m)
{
  m.def("plot_geometry", &openmc::plot_geometry);
  py::class_<PlotBase>(m,"PlotBase")
    .def(py::init<>())
    .def_readwrite("origin", &PlotBase::origin_)
    .def_readwrite("width", &PlotBase::width_)
    .def_readwrite("pixels", &PlotBase::pixels_)
    .def_readwrite("level", &PlotBase::level_)
    .def_readwrite("basis", &PlotBase::basis_)
    .def("get_property_map", [](const PlotBase &pb) {
      auto props = pb.get_map<PropertyData>();
      py::array_t<double> numpy_array({1,3});
      std::copy(props.data_.begin(), props.data_.end(), 
        numpy_array.mutable_data());
      return numpy_array;
    })
    .def("get_id_map", [](const PlotBase &pb) {
      auto ids = pb.get_map<IdData>();
      py::array_t<int32_t> numpy_array({1,3});
      std::copy(ids.data_.begin(), ids.data_.end(), 
        numpy_array.mutable_data());
      return numpy_array;
    });
  
  py::enum_<PlotBasis>(m,"PlotBasis")
    .value("xy", PlotBasis::xy)
    .value("xz", PlotBasis::xz)
    .value("yz", PlotBasis::yz);
}

} // namespace openmc
