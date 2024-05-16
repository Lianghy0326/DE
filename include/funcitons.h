#pragma once

#include <vector>
#include <cassert>
#include "DE.h"


namespace DE
{
    class Func : public Optimize
    {
        private:
            unsigned int dim;
        public:
            // constructor - default value of dim is 2
            Func(unsigned int dim=2) : dim(dim) {}

            // Evaluate the cost function: x^2 - 100*cos(x)^2 - 100*cos(x^2/30) + 1400
            double EvaluateCost(std::vector<double> input) const override // override the virtual function in Optimize
            {
                assert (input.size()==dim);

                double val = 0;
                for(int i=0;i<dim;i++){
                    val += input[i]*input[i]
                            - 100 * cos(input[i]) * cos(input[i])
                            - 100 * cos(input[i] * input[i] /30 );
                }

                return val+1400;
            }

            // numOfParameters()
            unsigned int numOfParameters() const override
            {
                return dim;
            } 

            // The constraints is initialized to -100(L) and 100(U)
            std::vector<Constraint> getConstraints() const override{
                // use the number of demension to define the size of the vector
                std::vector<Constraint> V(dim);
                
                // Set the num=dim constraints, run through the vector
                for (auto& c : V){
                    // c use reference to modify the value of the vector
                    c = Constraint(-100,100,true);
                }
                return V;
            }

    }
}
