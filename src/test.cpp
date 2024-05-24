// test pybind11
#include "./pybind11/include/pybind11/pybind11.h"


namespace  py = pybind11;

float function(float a, float b) {
    return a + b;
}

PYBIND11_MODULE(pybind11_test,handle){
    handle.doc() = "This is a test module";
    handle.def("function", &function, "A function that adds two numbers");
}