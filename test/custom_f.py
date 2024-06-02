import numpy as np

# Termination condition
def termination_condition(de):
    # Implement a termination condition (e.g., stop after a certain number of iterations)
    return False

# Define a callback function
def callback(de):
    print("Current best cost:", de.GetBestCost())


## Functions

""" Rastrigin Function """
def rastrigin(x,A=10):
    return A * len(x) + sum([(xi**2 - A * np.cos(2 * np.pi * xi)) for xi in x])