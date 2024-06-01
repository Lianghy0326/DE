// bindings.cpp

#include "./pybind11/include/pybind11/pybind11.h"

#include "./pybind11/include/pybind11/functional.h" // 為 std::function 支持

#include "./pybind11/include/pybind11/stl.h"
#include "../include/DE.h"
#include "../include/functions.h"


namespace py = pybind11;

class PyOptimize : public DE::Optimize
{
    public:
        using DE::Optimize::Optimize; // Inherit constructors

        double EvaluateCost(std::vector<double> pi) const override {
            PYBIND11_OVERRIDE_PURE(
                double,
                DE::Optimize,
                EvaluateCost,
                pi
            );
        }

        unsigned int numOfParameters() const override {
            PYBIND11_OVERRIDE_PURE(
                unsigned int,
                DE::Optimize,
                numOfParameters, 
            );
        }

        std::vector<DE::Optimize::Constraint> getConstraints() const override {
            PYBIND11_OVERRIDE_PURE(
                std::vector<DE::Optimize::Constraint>,
                DE::Optimize,
                getConstraints, 
            );
        }
};

PYBIND11_MODULE(pyde, m) {
    m.doc() = "Differential Evolution Optimization";

    

    py::class_<DE::Optimize, PyOptimize,std::shared_ptr<DE::Optimize>>(m,"Optimize")
        .def(py::init<>())
        .def("EvaluateCost",&DE::Optimize::EvaluateCost)
        .def("numOfParameters",&DE::Optimize::numOfParameters)
        .def("getConstraints",&DE::Optimize::getConstraints);
    
    // Expose the Constraint class within the scope of Optimize
    py::class_<DE::Optimize::Constraint>(m.attr("Optimize"), "Constraint")
        .def(py::init<double, double, bool>())
        .def_readwrite("lower", &DE::Optimize::Constraint::lower)
        .def_readwrite("upper", &DE::Optimize::Constraint::upper)
        .def_readwrite("isConstrained", &DE::Optimize::Constraint::isConstrained)
        .def("Check", &DE::Optimize::Constraint::Check);

    // Expose the Func class
    py::class_<DE::Func, DE::Optimize, std::shared_ptr<DE::Func>>(m, "Func")
        .def(py::init<unsigned int>())
        .def("EvaluateCost", &DE::Func::EvaluateCost)
        .def("numOfParameters", &DE::Func::numOfParameters)
        .def("getConstraints", &DE::Func::getConstraints);
        
    // Custom function
    py::class_<DE::customFunction, DE::Optimize, std::shared_ptr<DE::customFunction>>(m, "customFunction")
        .def(py::init<unsigned int, std::function<double(const std::vector<double>&)>,double,double >())
        .def("EvaluateCost", &DE::customFunction::EvaluateCost)
        .def("numOfParameters", &DE::customFunction::numOfParameters)
        .def("getConstraints", &DE::customFunction::getConstraints);


    py::class_<DE::DifferentialEvolution>(m,"DifferentialEvolution")
        .def(py::init<const DE::Optimize&,unsigned int,int,bool,
            std::function<void(const DE::DifferentialEvolution&)>,
            std::function<bool(const DE::DifferentialEvolution&)>>(),
            py::arg("costFunction"), py::arg("populationSize"), py::arg("RandomSeed"),
            py::arg("shouldCheckConstraint"), py::arg("callback"), py::arg("terminationCondition"))
        // InitializePopulation operation
        .def("InitializePopulation",&DE::DifferentialEvolution::InitializePopulation)
        // get the population
        .def("getPopulation",&DE::DifferentialEvolution::getPopulation)
        // SelectAndCross
        .def("SelectAndCross",&DE::DifferentialEvolution::SelectAndCross)
        .def("GetBestAgent",&DE::DifferentialEvolution::GetBestAgent)
        .def("GetBestCost",&DE::DifferentialEvolution::GetBestCost)
        .def("GetPopulationCost",&DE::DifferentialEvolution::GetPopulationCost)

        .def("PrintPopulation",&DE::DifferentialEvolution::printPopulation)
        .def("OptimizeStep",&DE::DifferentialEvolution::OptimizeStep,
            py::arg("iterations"), py::arg("verbose")=true);

}
