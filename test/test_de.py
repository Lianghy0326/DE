import pytest
from pyde import DifferentialEvolution as DE
from pyde import Optimize

# test function
class QuadraticFunction(Optimize):

    def Evaluate(self, input):
        return sum([x**2 for x in input])
    
    def NumberOfParameters(self):
        return 2
    
    def GetConsrants(self):
        return [Optimize.Constraint(-5,5,True) for _ in range(2)]
    

# test differential evolution
def test_de():
    cost_function = QuadraticFunction()

    optimizer = DE(cost_function,10,123)
    optimizer.InitializePopulation()
    optimizer.OptimizeStep(100,verbose=False)

    best_individual = optimizer.GetBestAgent()
    best_cost = optimizer.GetBestCost()

    assert best_cost <1e05, f"Expected best cost to be very small, but got {best_cost}"
    assert all(-5.0 <= x <= 5.0 for x in best_individual), "Best agent violates constraints"

if __name__ == "__main__":
    pytest.main()