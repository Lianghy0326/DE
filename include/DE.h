#pragma once

#include <iostream>
#include <vector>
#include <cassert>
#include <random>
#include <iomanip>
#include <utility>
#include <memory>
#include <limits>


namespace DE
{
    // class Optimize
    class Optimize{
        public:
            struct Constraint
            {
                // member variables
                double lower;
                double upper;
                bool isConstrained; 

                // Constraint constructor
                Constraint(double lower=0.0,double upper=1.0,bool isConstrained=false) : 
                    lower(lower), // assign the value of lower to the member variable lower
                    upper(upper),
                    isConstrained(isConstrained)
                {
                    assert (lower <= upper), "Lower bound must be less than or equal to upper bound";
                }

                // To check if the candidate is within the constraint
                bool Check(double candidate)
                {
                    if (isConstrained){
                        if (candidate < lower || candidate > upper){
                            return false;
                        }
                        else
                            return true;
                    }
                    else
                        return true;   
                }

            };

            // virtual function can be overriden in the Base class(Optimize class) and implemented in the derived class(Func class)
            virtual double EvaluateCost(std::vector<double> input) const = 0;
            virtual unsigned int numOfParameters() const = 0; // return the number of parameters(dimensions) of the cost function
            // constraint structure vector is returned by the getConstraints() function
            virtual std::vector<Constraint> getConstraints() const = 0;
            // destructor
            virtual ~Optimize() {};

    };

    // class DE
    class DifferentialEvolution{
        // cost function: function to minimize
        
        private:
            // member variables
            // Parameters
            const Optimize& costFunction;
            unsigned int populationSize;
            double F;
            double CR;
            int bestAgentIndex; // index of the best agent
            double minCost; //initialize to negative infinity
            bool shouldCheckConstraint;

            // number of parameters
            unsigned int numOfParameters;

            // std::function
            std::function<void(const DifferentialEvolution&)> callBack;
            std::function<void(const DifferentialEvolution&)> terminateCondition;

            // std random number generator
            std::default_random_engine generator;

            // defien population double vector
            std::vector<std::vector<double>> population;
            // min cost of each agent in population
            std::vector<double> piCost;

            // constraint vector
            std::vector<Optimize::Constraint> constraints;

            // static lower and upper bound
            static constexpr double lowerConstraint = -std::numeric_limits<double>::infinity();
            static constexpr double upperConstraint = std::numeric_limits<double>::infinity();


        public:
            // Constructor
            DifferentialEvolution(
                const Optimize& costFunction,
                unsigned int populationSize,
                int RandomSeed=123,
                bool shouldCheckConstraint=true,
                // c++ std::function accept any "const DiffentialEvolution&" 
                // as an argument and return void.

                // callback is a container for a function that takes a DifferentialEvolution 
                // object as an argument and returns void.
                // callback is initialized to nullptr, which means that it does not point to any function.
                std::function<void(const DifferentialEvolution&)> callback=nullptr,
                std::function<void(const DifferentialEvolution&)> terminateCondition=nullptr
            ):
                costFunction(costFunction),
                populationSize(populationSize),
                F(0.8),
                CR(0.9),
                bestAgentIndex(0),
                minCost(-std::numeric_limits<double>::max()),
                shouldCheckConstraint(shouldCheckConstraint),
                callBack(callback),
                terminateCondition(terminateCondition)


            {
                /* Constructor implementation */
                // Set the random seed of the generator
                generator.seed(RandomSeed);
                
                // Makesure the population size is at least 4
                assert(populationSize >= 4);

                // number of parameters
                numOfParameters = costFunction.numOfParameters();
                
                // Resize the dimension=0 of the population vector to the population size
                population.resize(populationSize);
                // Resize the dimension=1 of the population vector to the "number of parameters(dimensions)"
                for (auto& pi:population){
                    pi.resize(numOfParameters);
                }

                // resize the piCost vector to the population size
                piCost.resize(populationSize);

                // get each constraint from getConstraints() function
                constraints = costFunction.getConstraints();

            }
            

            // Population initialization
            void InitializePopulation(){
                // create a uniform distribution
                // control the distribution by a shared pointer
                // pass the pre-defined generator to the distribution

                // shared_ptr is a smart pointer that retains shared ownership of an object through a pointer.
                // used to constrol the life-cycle of the object
                // the object type is "std::uniform_real_distribution<double>"
                std::shared_ptr<std::uniform_real_distribution<double>> dist;


                // run through the population vector and set the value of each pi
                for (auto& pi : population){
                    // double vector
                    for (int i=0;i<numOfParameters;i++){

                        // constraints[i] is about x,y,z...
                        if (constraints[i].isConstrained){
                            // create a uniform distribution with defined lower and upper bound
                            // assign the distribution to the shared pointer
                            dist = std::make_shared<std::uniform_real_distribution<double>>(std::uniform_real_distribution<double> (constraints[i].lower,constraints[i].upper););
                        }
                        else{
                            dist = std::make_shared<std::uniform_real_distribution<double>>(std::uniform_real_distribution<double>(lowerConstraint,upperConstraint));
                        }

                        // assign the value of pi[i] to the random number generated by the distribution
                        pi[i] = (*dist)(generator);
                    }
                }

                // Initialize minCost
                for(int i=0;i<populationSize;i++){
                    // Evaluate the cost function
                    piCost[i] = costFunction.EvaluateCost(population[i]);
                    // find the best cost and index 
                    if (piCost[i] < minCost){
                        minCost = piCost[i];
                        bestAgentIndex = i;
                        // Cost: in the cost function means the value of the cost function
                    }
                }
            

            }



    };


}