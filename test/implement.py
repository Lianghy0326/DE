import pyde
import numpy as np

#demo vector (double vector each represent as an individual)
demo_vector = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16],[17,18,19,20]]
# get the demo vector dimentions
dimension = len(demo_vector)
# Run through the demo vector
for X in demo_vector:
    dim_inv = len(X)
    f = pyde.Func(dim_inv)
    print(f.EvaluateCost(X))
    print(f.numOfParameters())
    #print(f.getConstraints())


# Define a termination condition function
def termination_condition(de):
    # Implement a termination condition (e.g., stop after a certain number of iterations)
    return False

# Define a callback function
def callback(de):
    print("Current best cost:", de.GetBestCost())

# Create an instance of Func with the appropriate dimension
f = pyde.Func(5)

# Create an instance of DifferentialEvolution
de = pyde.DifferentialEvolution(
    costFunction=f,
    populationSize=50,
    RandomSeed=123,
    shouldCheckConstraint=True,
    callback=callback,
    terminationCondition=termination_condition
)

# Initialize the population
de.InitializePopulation()
population = de.getPopulation()
assert len(population) == 50  # Ensure the population size is correct
# check individual in population
for individual in population:
    assert len(individual) == 5  # Ensure the number of parameters is correct
    for gene in individual:
        assert gene >= -100 and gene <= 100

print(f"Population: {population}")


de.OptimizeStep(iterations=10, verbose=True)
best_cost_0 = de.GetBestCost()
best_agent_0 = de.GetBestAgent()


de.OptimizeStep(iterations=100, verbose=True)
best_cost_1 = de.GetBestCost()
best_agent_1 = de.GetBestAgent()


de.OptimizeStep(iterations=1000, verbose=True)
best_cost_2 = de.GetBestCost()
best_agent_2 = de.GetBestAgent()

# Best cost
print("Best cost:", best_cost_0)
print("Best cost:", best_cost_1)
print("Best cost:", best_cost_2)

# Best individual
print("Best individual:", best_agent_0)
print("Best individual:", best_agent_1)
print("Best individual:", best_agent_2)




def my_function(x):
    return sum(xi**2 for xi in x)

dimension = 4
custom_func = pyde.customFunction(dimension, my_function,-100,100)
print("Custom Function")
f = pyde.Func(4)
print(f.EvaluateCost([1,2,3,4]))
print(custom_func.EvaluateCost([1,2,3,4]))
opt = pyde.DifferentialEvolution(
    costFunction=custom_func,
    populationSize=50,
    RandomSeed=123,
    shouldCheckConstraint=True,
    callback=callback,
    terminationCondition=termination_condition
)
print("Optimize Step")
opt.OptimizeStep(iterations=100, verbose=True)


""" Rastrigin Function """
def rastrigin(x,A=10):
    return A * len(x) + sum([(xi**2 - A * np.cos(2 * np.pi * xi)) for xi in x])

dimension = 10
R = pyde.customFunction(dimension,rastrigin,-5.12,5.12)
opt = pyde.DifferentialEvolution(
    costFunction=custom_func,
    populationSize=50,
    RandomSeed=123,
    shouldCheckConstraint=True,
    callback=callback,
    terminationCondition=termination_condition
)
print("Optimize Step")
opt.OptimizeStep(iterations=100, verbose=True)