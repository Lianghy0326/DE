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

    // Class DifferentialEvolution is used to optimize the cost function.
    class DifferentialEvolution{
        // cost ｀function: function to minimize
        
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
            std::function<bool(const DifferentialEvolution&)> TerminateCondition;

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

            

            bool CheckConstraints(std::vector<double> agent)
            {
                for (int i = 0; i < agent.size(); i++)
                {
                    if (!constraints[i].Check(agent[i]))
                    {
                        return false;
                    }
                }

                return true;
            }


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
                std::function<bool(const DifferentialEvolution&)> terminateCondition=nullptr
            ):
                costFunction(costFunction),
                populationSize(populationSize),
                F(0.8),
                CR(0.9),
                bestAgentIndex(0),
                minCost(-std::numeric_limits<double>::max()),
                shouldCheckConstraint(shouldCheckConstraint),
                callBack(callback),
                TerminateCondition(terminateCondition)
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
                            dist = std::make_shared<std::uniform_real_distribution<double>>(std::uniform_real_distribution<double> (constraints[i].lower,constraints[i].upper));
                        }
                        else{
                            dist = std::make_shared<std::uniform_real_distribution<double>>(std::uniform_real_distribution<double>(lowerConstraint,upperConstraint));
                        }

                        // assign the value of pi[i] to the random number generated by the distribution
                        pi[i] = (*dist)(generator);
                    }
                }

                // 對所有的population[i]進行cost function的評估
                // 更新minCost和bestAgentIndex
                for(int i=0;i<populationSize;i++){
                    // Evaluate the cost function
                    piCost[i] = costFunction.EvaluateCost(population[i]);
                    // find the best cost and index 
                    if (piCost[i] < minCost){
                        minCost= piCost[i];
                        bestAgentIndex = i;
                        // Cost: in the cost function means the value of the cost function
                    }
                }
            

            }

            // Selecttion and the crossover process
            void SelectAndCross(){

                // 產生一個uniform distribution 範圍是0~populationSize
                std::uniform_real_distribution<double> dist(0,populationSize);

                // **double minCost
                double MinCost = piCost[0];
                // bestAgentIndex
                int oneBestAgentIndex = 0;

                // 找出最小的cost
                for(int k = 0; k < populationSize; k++){

                    // for k,select 3 random individuals from k
                    int a = k;
                    int b = k;
                    int c = k;

                    // 隨機產生a,b,c 並確保a,b,c不等於k
                    while(a == k || b == k || c == k || a == b || a == c || b == c){
                        // a,b,c are random numbers 範圍在0~populationSize
                        a = dist(generator);
                        b = dist(generator);
                        c = dist(generator);
                    }

                    // Form intermediate solutions : Z=a+F*(b-c)
                    std::vector<double> Z(numOfParameters);
                    for (int i=0;i<numOfParameters;i++){
                        // 隨機選三個individuals a,b,c 並進行交叉 
                        Z[i] = population[a][i] + F*(population[b][i] - population[c][i]);
                    }// Z[i]代表的是新的individuals

                    // 產生一個隨機分佈 範圍落在維度內 0-dimension
                    std::uniform_real_distribution<double> distR(0,numOfParameters);
                    // R是隨機產生的維度value
                    int R = distR(generator);

                    // 創建vector X 是一個vector長度為numOfParameters(=2)
                    std::vector<double> X(numOfParameters);
                    std::uniform_real_distribution<double> distX(0,1);
                    // 給定X一個隨機值(0~1)
                    for (auto& x : X){
                        x = distX(generator);
                    }

                    // 進行交叉
                    std::vector<double> Y(numOfParameters);
                    for(int i=0; i<numOfParameters; i++){
                        // 根據CR的值進行交叉
                        // 如果X[i] < CR 或 i == R就進行交叉
                        if (X[i] < CR || i == R){
                            Y[i] = Z[i];
                        }
                        // 如果X[i] >= CR且i != R就不進行交叉
                        else{
                            Y[i] = population[k][i];
                        }
                    }

                    // 檢查是否符合constraint
                    if (shouldCheckConstraint && !CheckConstraints(Y)){
                        k--;
                        continue;
                    }

                    // 計算新的cost: Y的cost
                    double newCost = costFunction.EvaluateCost(Y);

                    // 檢查cost是否小於每個individuals的cost
                    if (newCost < piCost[k]){
                        // 更新individuals
                        population[k] = Y;
                        // 更新cost
                        piCost[k] = newCost;
                    }
                    // 追蹤最小的cost
                    if (piCost[k] < MinCost){
                        MinCost = piCost[k];
                        oneBestAgentIndex = k;
                    }                    
                }

                minCost = MinCost;
                bestAgentIndex = oneBestAgentIndex;
            }

            // Get the best agent
            std::vector<double> GetBestAgent() const
            {
                return population[bestAgentIndex];
            }

            // Get the best cost
            double GetBestCost() const
            {
                return piCost[bestAgentIndex];
            }

            // Return the population and the cost
            std::vector< std::pair< std::vector<double> , double > > GetPopulationCost() const
            {
                // 定義一個pair對儲存population和cost
                std::vector< std::pair< std::vector<double> , double > > populationCost;
                for (int i=0;i<populationSize;i++){
                    populationCost.push_back(std::make_pair(population[i],piCost[i]));

                }
                return populationCost;
            }

            // 印出population
            void printPopulation() const
            {
                for(auto pi:population){
                    for(auto& var:pi){
                        // run through the dimension of the population
                        std::cout << var << " ";
                    }
                    std::cout << "\n" << std::endl;
                }
            }

            // 優化步驟
            void OptimizeStep(int iterations,bool verbose = true)
            {
                // Initialize the population
                InitializePopulation();

                // Opt loop
                for (int i=0; i<iterations; i++){

                    if (verbose){
                        // 設定小數點位數
                        std::cout << std::fixed << std::setprecision(5);
                        // 印出最小的cost
                        std::cout << "Iteration: " << i << " Best Cost: " << minCost << "\t\t";
                        // 印出最好的individuals(由選出的最小cost的individuals的index決定)
                        std::cout << "Best individual: ";
                        for (int i=0;i<numOfParameters;i++){
                            std::cout<<population[bestAgentIndex][i] << " ";
                        }
                        std::cout << std::endl;
                    }
                }

                // 檢查是否有callback function
                if (callBack){
                    // 將當前對象傳遞給callback function
                    callBack(*this);
                }

                // 檢查是否有terminateCondition function
                if (TerminateCondition){
                    if(TerminateCondition(*this)){
                        if(verbose){
                            std::cout<< "Termination condition is met" << std::endl;
                        }
                        return;
                    }
                }

                if(verbose){
                    std::cout << "Terminated due to exceeding total number of generations." << std::endl;
                }

            }




    };


}