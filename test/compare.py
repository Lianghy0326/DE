# My library
import pyde

# Python library
import time
import numpy as np
from scipy.optimize import differential_evolution
from memory_profiler import memory_usage

# Global variables
Iteration = 2000
Population_size = 15


"""
Python Scipy DE
"""
def rastrigin(x, A=10):
    return A * len(x) + sum([(xi**2 - A * np.cos(2 * np.pi * xi)) for xi in x])

def Test_rasrigin_scipy(rastrigin):

    # Define the bounds for the 10-dimensional problem
    bounds = [(-5.12, 5.12) for _ in range(10)]  # 10 dimensions

    # Call the differential evolution algorithm
    result = differential_evolution(rastrigin, 
                                bounds, 
                                maxiter=Iteration, 
                                popsize=Population_size,
                                mutation=(0.8,0.9),
                                seed=123)
    return result


"""
My DE
"""
# Define a termination condition function
def termination_condition(de):
    # Implement a termination condition (e.g., stop after a certain number of iterations)
    return False
# Define a callback function
def callback(de):
    print("Current best cost:", de.GetBestCost())

# My DE custom function
def make_custom_function(function,dimension,lower,upper):
    return pyde.customFunction(dimension,function,lower,upper)

# My DE optimization
def DE_optimize(custom_function,callback,termination_condition):
    opt = pyde.DifferentialEvolution(
        costFunction=custom_function, # cost function
        populationSize=Population_size, # population size
        F=0.9,
        CR=0.9,
        RandomSeed=123, # random seed
        shouldCheckConstraint=True,
        callback=callback,
        terminationCondition=termination_condition
    )
    print("\nMyDE Optimizing......")
    opt.OptimizeStep(iterations=Iteration, verbose=False)
    return opt

# Demo comparison from Python Scipy DE and My DE
def demo_comparison(res_scipy,res_myde):
    print("Optimized Result from SciPy:")
    print("Best solution found:", res_scipy.x)
    print("Function value at best solution:", res_scipy.fun)
    # Manually evaluate the function value at the best solution
    manual_evaluation = rastrigin(res_scipy.x)
    print("Manually evaluated function value:", manual_evaluation)
    print(f"MyDE best cost:{res_myde.GetBestCost()}")
    print(f"MyDE best agent:{res_myde.GetBestAgent()}")

"""
Time and memory profiling
"""
def measure_performance(func,*args):
    start_time = time.time()
    mem_usage = memory_usage((func,args))
    end_time = time.time()
    return end_time - start_time, max(mem_usage)-min(mem_usage)


if __name__ == "__main__":
    # Python scipy DE
    scipy_result = Test_rasrigin_scipy(rastrigin)
    python_time, python_memory = measure_performance(Test_rasrigin_scipy,rastrigin)
    
    # My DE
    custom_function = make_custom_function(rastrigin,10,-5.12,5.12)
    opt = DE_optimize(custom_function,callback,termination_condition)
    # DEMO Comparison
    demo_comparison(scipy_result,opt)
    myde_time, myde_memory = measure_performance(DE_optimize,custom_function,callback,termination_condition)

    print(f"\nPython Scipy DE Time: {python_time} seconds")
    print(f"Python Scipy DE Memory: {python_memory} MB")

    print(f"My DE Time: {myde_time} seconds")
    print(f"My DE Memory: {myde_memory} MB")

