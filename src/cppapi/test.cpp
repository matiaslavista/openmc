#include <pybind11/pybind11.h>
#include<pybind11/stl.h>

#include<string>
#include<iostream>
#include<vector>
#include<utility>

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::move;

namespace py = pybind11;

class int_wrapper {
  public:
    int_wrapper() {}
    int_wrapper(int i) : i_(i) {}
    void set_int(int i) {
        i_ = i;
    }
    int get_int() {
        return i_;
    }
    string name;
    void addr_print(){
      cout << &i_;
      cout << " " << &name;
      cout << " " << &name[0] << endl;
    }
  private:
    int i_ = 0;
};

int_wrapper global;
vector<int_wrapper> vec;

void set_global(int i) {
  global.set_int(i);
}

int_wrapper& get_global() {
  return global;
}

void print_wrapper() {
  cout << global.get_int() << endl;
  cout << global.name << endl;
  cout << &(global.name) << endl;
  cout << &global << endl;
}
//Place holder functions
int add(int i, int j) {
  return i + j;
}
//place holder functions
int subtract(int i, int j) {
  return i-j;
}

void initiate_vec() {
  int_wrapper wrap1(1);
  wrap1.name = "Grumpy";
  int_wrapper wrap2(2);
  wrap2.name = "Pumpy";
  int_wrapper wrap3(3);
  wrap3.name = "Dumpy";
  int_wrapper wrap4(4);
  wrap4.name = "Thumpy";
  vec.push_back(move(wrap1));
  vec.push_back(move(wrap4));
  vec.push_back(move(wrap3));
  vec.push_back(move(wrap2));
}

void print_vec(){
  for(auto& item : vec){
    cout << item.name << endl;
    cout << item.get_int() << endl;
  }
}

vector<int_wrapper>& get_vector() {
  return vec;
}

namespace openmc {
//adding them to the module from a diff file
void init_test_file(py::module& m) {
  m.def("add", &add);
  m.def("subtract", &subtract);
  m.def("set_global", &set_global);
  m.def("get_global", &get_global, py::return_value_policy::reference);
  m.def("get_vector", &get_vector, py::return_value_policy::reference);
  m.def("print_wrapper", &print_wrapper);
  m.def("print_vec", &print_vec);
  m.def("initiate_vec", &initiate_vec);
  py::class_<int_wrapper>(m,"int_wrap")
    .def(py::init<int>())
    .def("set_int", &int_wrapper::set_int)
    .def("get_int", &int_wrapper::get_int)
    .def("addr_print", &int_wrapper::addr_print)
    .def_readwrite("name", &int_wrapper::name);
}

};


