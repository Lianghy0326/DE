import pytest
import pyde
from pyde import DifferentialEvolution as DE
from pyde import Optimize

# test function
class QuadraticFunction(Optimize):

    def Evaluate(self, input):
        return sum([x**2 for x in input])
    
    def NumberOfParameters(self):
        return 2
    
    def GetConstraints(self):
        return [Optimize.Constraint(-5, 5, True) for _ in range(2)]
    

def test_de():
    cost_function = QuadraticFunction()

    # Define no-op functions for the callbacks
    def no_op_callback(de_instance):
        pass
    def no_op_termination(de_instance):
        return False

    optimizer = DE(cost_function, 10, 123, True, no_op_callback, no_op_termination)
    optimizer.InitializePopulation()
    optimizer.OptimizeStep(100, verbose=False)

    best_individual = optimizer.GetBestAgent()
    best_cost = optimizer.GetBestCost()

    assert best_cost < 1e05, f"Expected best cost to be very small, but got {best_cost}"
    assert all(-5.0 <= x <= 5.0 for x in best_individual), "Best agent violates constraints"

    
if __name__ == "__main__":
    pytest.main()
