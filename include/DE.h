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
    /* Class-1: Optimize */
    class Optimize{
    public:
        // Forward declaration of Constraint structure
        struct Constraint;

        virtual double EvaluateCost(std::vector<double> input) const = 0;
        virtual unsigned int numOfParameters() const = 0;
        virtual std::vector<Constraint> getConstraints() const = 0;
        virtual ~Optimize() {};
    };
    
    // Define the Constraint structure within the Optimize class
    struct Optimize::Constraint
    {
        double lower;
        double upper;
        bool isConstrained;

        Constraint(double lower = 0.0, 
                    double upper = 1.0, 
                    bool isConstrained = false) : 
            lower(lower),
            upper(upper),
            isConstrained(isConstrained)
        {
            assert(lower <= upper && "Lower bound must be less than or equal to upper bound");
        }

        bool Check(double candidate) const
        {
            if (isConstrained)
            {
                return candidate >= lower && candidate <= upper;
            }
            return true;   
        }
    };

    /* Class-2: DifferentialEvolution */
    class DifferentialEvolution{
        
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

            
            
            // 檢查某個individuals是否符合constraint
            bool CheckConstraints(std::vector<double> agent)
            {
                // 對individuals的每個維度value進行檢查
                // 檢查會先看isConstrained是否為true true代表還沒限制範圍
                // 一旦有限制範圍就會檢查是否在範圍內
                // 這個function會回傳true代表individuals符合constraint false代表不符合
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
                std::function<void(const DifferentialEvolution&)> callback=nullptr,
                std::function<bool(const DifferentialEvolution&)> terminateCondition=nullptr
            ):
                // Initialize the member variables
                costFunction(costFunction),
                populationSize(populationSize),
                F(0.8),
                CR(0.9),
                bestAgentIndex(0),  
                minCost(-std::numeric_limits<double>::infinity()),
                shouldCheckConstraint(shouldCheckConstraint),
                callBack(callback),
                TerminateCondition(terminateCondition)
            {
                /* Constructor Initialization */
                generator.seed(RandomSeed);
                assert(populationSize >= 4);

                // number of parameters
                numOfParameters = costFunction.numOfParameters();
                
                // 初始化population vector
                population.resize(populationSize);

                // 擴展每個xi維度到numOfParameters
                for (auto& pi:population){
                    pi.resize(numOfParameters);
                }
                // piCost代表每個individuals的cost
                piCost.resize(populationSize);
                
                // 包含lower,upper,是否有constraint的vector
                constraints = costFunction.getConstraints();

            }
            

            // INIT POPULATION
            void InitializePopulation(){
                // 產生一個uniform distribution 範圍是0~1
                std::shared_ptr<std::uniform_real_distribution<double>> dist;
                // 對每個個體population[i]進行初始化
                for (auto& pi : population){
                    // 對每個維度進行初始化
                    for (int i=0;i<numOfParameters;i++){

                        if (constraints[i].isConstrained){
                            // 如果有constraint就使用constraint的lower和upper
                            dist = std::make_shared<std::uniform_real_distribution<double>>(std::uniform_real_distribution<double> (constraints[i].lower,constraints[i].upper));
                        }
                        else{
                            // 如果沒有constraint就使用lowerConstraint和upperConstraint
                            dist = std::make_shared<std::uniform_real_distribution<double>>(std::uniform_real_distribution<double>(lowerConstraint,upperConstraint));
                        }
                        // pi[i]產生一個隨機值-範圍如果有constraint就是constraints[i].lower,constraints[i].upper
                        // 如果沒有constraint就是lowerConstraint,upperConstraint
                        pi[i] = (*dist)(generator);
                    }
                }


                // 目的: 更新每個xi的cost 以及 找出最小的cost和index
                for(int i=0;i<populationSize;i++)
                {
                    // piCost[i]代表的是population[i]的cost
                    // cost透過EvaluateCost function計算
                    piCost[i] = costFunction.EvaluateCost(population[i]);
                    // find the best cost and index 
                    if (piCost[i] < minCost){
                        minCost= piCost[i];
                        bestAgentIndex = i;
                        // Cost: in the cost function means the value of the cost function
                    }
                }
            

            }
            // GET POPULATION
            const std::vector<std::vector<double>>& getPopulation() const{
                return population;
            }

            // Selecttion and the crossover process
            void SelectAndCross(){
                std::cout << "Starting SelectAndCross" << std::endl;

                // 產生一個uniform distribution 範圍是0~populationSize
                std::uniform_real_distribution<double> dist(0,populationSize);

                // local MinCost
                double MinCost = piCost[0];
                // local bestAgentIndex
                int oneBestAgentIndex = 0;

                // 選擇和交叉,跑過所有的individuals
                for(int k = 0; k < populationSize; k++){

                    std::cout << "SAC: " << k << std::endl;

                    // 挑選三個不同的individuals a,b,c 初始化=k
                    int a = k;
                    int b = k;
                    int c = k;

                    // 確保a,b,c不相等(透過generator產生隨機數),break while 如果a,b,c不相等且a,b,c不等於k
                    while(a == k || b == k || c == k || a == b || a == c || b == c){
                        // a,b,c are random numbers 範圍在0~populationSize
                        a = dist(generator);
                        b = dist(generator);
                        c = dist(generator);
                    }

                    std::cout << "Selected individuals: a=" << a << " b=" << b << " c=" << c << std::endl;

                    // Form intermediate solutions : Z=a+F*(b-c) // Z[i]代表的是新的individuals(即一個新的x)
                    std::vector<double> Z(numOfParameters);
                    for (int i=0;i<numOfParameters;i++){
                        // 隨機選三個individuals a,b,c 並進行交叉 
                        Z[i] = population[a][i] + F*(population[b][i] - population[c][i]);
                    }


                    // 對所有維度sample一個範圍0-1的值並給到vector X
                    // X大小和一個individuals的維度相同
                    std::uniform_real_distribution<double> distR(0,numOfParameters);
                    int R = distR(generator);
                    std::vector<double> X(numOfParameters);
                    std::uniform_real_distribution<double> distX(0,1);
                    for (auto& x : X){
                        x = distX(generator);
                    }

                    // 交叉
                    // Y大小和一個individuals的維度相同
                    std::vector<double> Y(numOfParameters); //Y代表new individuals(X)
                    for(int i=0; i<numOfParameters; i++)
                    {
                        // X[i]剛剛被初始化為0~1的隨機值
                        if (X[i] < CR || i == R){
                            Y[i] = Z[i];
                        }
                        // 如果X[i] >= CR且i != R就不進行交叉
                        else{
                            Y[i] = population[k][i];
                        }
                    }

                    // 檢查是否符合constraint
                    // 剛開始CheckConstraints是true表示還沒開始限縮範圍
                    // 一旦開始限縮範圍就會檢查是否符合constraint 若不符合CheckConstraints會回傳false 
                    // k--代表重新選擇individuals
                    if (shouldCheckConstraint && !CheckConstraints(Y)){
                        k--;
                        std::cout << "Constraints not met, retrying individual " << k << std::endl;
                        continue;
                    }

                    // 決定現在更新的individuals是否比原本的individuals好 先評估cost fo Y
                    double newCost = costFunction.EvaluateCost(Y);
                    std::cout << "Evaluated new cost: " << newCost << " for individual " << k << std::endl;

                    // 檢查cost是否小於每個individuals的cost
                    if (newCost < piCost[k]){
                        // 更新現在的individuals為Y
                        population[k] = Y;
                        // 更新現在的individuals的cost
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
                std::cout << "Min Cost" << minCost << std::endl;
                std::cout << "Best Agent Index" << bestAgentIndex << std::endl;
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
                std::vector< std::pair< std::vector<double> , double>> populationCost;
                for (int i=0;i<populationSize;i++){
                    populationCost.push_back(std::make_pair(population[i],piCost[i]));

                }
                return populationCost;
            }

            // 印出population
            void printPopulation() const
            {
                for(auto pi:population)
                {
                    // 印出每個individuals的維度的值
                    for(auto& var:pi){
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
                    // Select and cross
                    SelectAndCross();

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