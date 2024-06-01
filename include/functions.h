#pragma once

#include <vector>
#include <cassert>
#include "DE.h"

#include <cmath> // Include cmath for cos function


namespace DE
{
    // custom function
    class customFunction : public Optimize
    {
        private:
            unsigned int dim;
            std::function<double(const std::vector<double>&)> userFunction; 
            const double lower;
            const double upper;

        public:
            // Constructor accepts a std::function
            customFunction(
                unsigned int dimension, 
                std::function<double(const std::vector<double>&)> func,
                const double lower_bound, 
                const double upper_bound
            ) : 
            dim(dimension), 
            userFunction(func) ,
            lower(lower_bound),
            upper(upper_bound)
            {
                assert (dimension > 0), "Dimension must be greater than 0";
                assert (lower_bound < upper_bound), "Lower bound must be less than upper bound";
                assert (func != nullptr), "Function must be defined";
            }

            // Evaluate the cost function
            double EvaluateCost(std::vector<double> input) const override
            {
                assert(input.size() == dim);
                return userFunction(input);
            }

            // Return the number of parameters
            unsigned int numOfParameters() const override
            {
                return dim;
            }

            // Return the constraints
            std::vector<Constraint> getConstraints() const override
            {
                // 
                std::vector<Constraint> C(dim);
                for (auto& c : C){
                    // c use reference to modify the value of the vector
                    c = Constraint(lower,upper,true);
                }
                return C;
            }            
    };
    

    // The function to be evaluated and optimized
    class Func : public Optimize
    {
        private:
            unsigned int dim;// dimension
            const double LOWER_BOUND = -100;
            const double UPPER_BOUND = 100;

        public:
            // Constructor
            Func(unsigned int dim=2) : dim(dim) {}

            // Evaluate the cost function: x^2 - 100*cos(x)^2 - 100*cos(x^2/30) + 1400
            double EvaluateCost(std::vector<double> input) const override // override the virtual function in Optimize
            {

                // input [x1, x2, x3, ... , x_dim]
                assert (input.size()==dim);

                double val = 0;
                // Function value
                for (int i = 0; i < dim; i++){
                    val += input[i] * input[i]
                       - 100 * cos(input[i]) * cos(input[i])
                       - 100 * cos(input[i] * input[i] / 30);
                }
                return val+1400;
            }

            // numOfParameters()
            unsigned int numOfParameters() const override
            {
                return dim;
            } 

            // 返回一个vector，包含了dim個Constraint對象
            std::vector<Constraint> getConstraints() const override
            {
                
                // use the number of demension to define the size of the vector
                std::vector<Constraint> C(dim);
                
                // Set the num=dim constraints, run through the vector
                for (auto& c : C){
                    // c use reference to modify the value of the vector
                    c = Constraint(LOWER_BOUND,UPPER_BOUND,true);
                }
                return C;
            }

    };
}
