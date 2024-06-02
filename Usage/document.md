# Differential Evolution API
## Overview
Differential Evolution (DE) is a stochastic population-based optimization algorithm capable of finding the global minimum of a multivariate function without relying on gradient information. This method is particularly effective for dealing with non-linear, non-differentiable, and multi-modal objective functions.

## **Algorithm**


## **Usage**
To use the DE algorithm,fisrt import 'pyde' module.
```python
import pyde
```

## **DE initialization**
```python
pyde.DifferentialEvolution(
    cost_function,
    populationSize,
    F=0.8,
    CR=0.9,
    RandomSeed=123,
    shouldCheckConstraint=True,
    callback=callback,
    terminationCondition=termination_condition
)
```
Finds the global minimum of a multivariate function.
The DE method doesn't use gradient method to find the
minimum, and can search large areas of candidate space.

## **Parameters**

### cost_function : callable
    Please review the 'Function Definition' part.


### populationSize : int 
    
    Number of individuals in the population.

### F : double
    (defualt=0.8)
    The differential weight used in mutation. 
    Typically between [0.5, 2].

### CR : double
    (defualt=0.9)
    The crossover probability used in recombination.
    Typically between [0, 1].

### RandomSeed : int , optional
    Seed for the random number generator to maintain reproducibility.

### shouldCheckConstraint : bool
    Indicates whether to enforce constraints on solution candidates.
### callback : function 
    A function to be called at the end of each iteration. 
    It takes the DifferentialEvolution instance as an argument.
### terminationCondition : function
    A function that returns True if the termination condition is met, otherwise False.

## **Optimize process**
After initializing the optimizer, you can perform the optimization using the OptimizeStep method:
```python
optimizer.OptimizeStep(iterations=100, verbose=True)
```
## **Function Definition**
### Defalut Funciton
The default objective function is defined within the pyde.Func class:
```python
default_function = pyde.Func(dimension=dimension)
```
### Custom Function
```python
def my_function(x):
    return xi**2 for xi in x
# Function 
pyde.customFunction(
        dimension,
        my_function,
        lower_bound,
        upper_bound
    )
```
1. dimension (int): Specifies the number of variables in the function.
2. lower_bound (double): The lower boundary for the optimization variables.
3. upper_bound (double): The upper boundary for the optimization variables.

## Reference
