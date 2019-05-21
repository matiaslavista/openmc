
#include "openmc/plot.h"
#include "openmc/cppapi/plot.h"
#include "openmc/capi.h"
#include "xtensor/xarray.hpp"
namespace openmc {
namespace py = pybind11;

int plot_geometry() { return openmc_plot_geometry();}

xt::xtensor<double, 3> property_map(const PlotBase& plt) {

  auto props = plt.get_map<PropertyData>();
  double* data_out = new double[props.data_.size()];
  std::copy(props.data_.begin(), props.data_.end(), data_out);
}

void init_plot(py::module& m)
{
  m.def("plot_geometry", &openmc::plot_geometry);
  m.def("property_map", &openmc::property_map);
  py::class_<PlotBase>(m,"PlotBase")
  .def(py::init<>())
  .def_readwrite("origin", &PlotBase::origin_)
  .def_readwrite("origin", &PlotBase::width_)
  .def_readwrite("pixels", &PlotBase::pixels_) //double check array
  .def_readwrite("level", &PlotBase::level_)
  .def_readwrite("basis", &PlotBase::basis_);
  .def("get_property_map",[](){this.get_map<Pr>})
  //get_map
  //.def("get_map_propdata", &PlotBase::get_map<PropertData>)
  //.def("get_map_iddata", &PlotBase::get_map<IdData>)
  
  py::enum_<PlotBasis>(m,"PlotBasis")
  .value("xy", &PlotBasis::xy)
  .value("xz", &PlotBasis::xz)
  .value("yz", &PlotBasis::yz);

  //create PropertyData class 
}
} // namespace openmc
