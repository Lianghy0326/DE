// bindings.cpp

#include "./pybind11/include/pybind11/pybind11.h"
#include "./pybind11/include/pybind11/stl.h"
#include "../include/DE.h"

namespace py = pybind11;

class PyOptimize : public DE::Optimize
{
    public:
        using DE::Optimize::Optimize; // Inherit constructors

        double EvaluateCost(std::vector<double> pi) const override {
            PYBIND11_OVERRIDE_PURE(double,DE::Optimize,EvaluateCost,pi);
        }

        unsigned int numOfParameters() const override {
            PYBIND11_OVERRIDE_PURE(unsigned int,DE::Optimize,numOfParameters, );
        }

        std::vector<DE::Optimize::Constraint> getConstraints() const override {
            PYBIND11_OVERRIDE_PURE(std::vector<DE::Optimize::Constraint>,DE::Optimize,getConstraints, );
        }
};

PYBIND11_MODULE(pyde, m) {
    m.doc() = "Differential Evolution Optimization";

    py::class_<DE::Optimize, PyOptimize,std::shared_ptr<DE::Optimize>>(m,"Optimize")
        .def(py::init<>())
        .def("EvaluateCost",&DE::Optimize::EvaluateCost)
        .def("numOfParameters",&DE::Optimize::numOfParameters)
        .def("getConstraints",&DE::Optimize::getConstraints);
    
    py::class_<DE::DifferentialEvolution>(m,"DifferentialEvolution")
        .def(py::init<const DE::Optimize&,unsigned int,int,bool,
            std::function<void(const DE::DifferentialEvolution&)>,
            std::function<bool(const DE::DifferentialEvolution&)>>())
        .def("InitializePopulation",&DE::DifferentialEvolution::InitializePopulation)
        .def("SelectAndCross",&DE::DifferentialEvolution::SelectAndCross)
        .def("GetBestAgent",&DE::DifferentialEvolution::GetBestAgent)
        .def("GetBestCost",&DE::DifferentialEvolution::GetBestCost)
        .def("GetPopulationCost",&DE::DifferentialEvolution::GetPopulationCost)
        .def("PrintPopulation",&DE::DifferentialEvolution::printPopulation)
        .def("OptimizeStep",&DE::DifferentialEvolution::OptimizeStep);

}
