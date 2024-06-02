import pytest
import pyde
import numpy as np
from custom_f import rastrigin
from custom_f import termination_condition, callback

class TestDE:
    """ Main Test Part """
    # Ensure all classes are included in the namespace
    def test_imports(self):
        """Test if all """
        assert 'Optimize' in dir(pyde),'Optimize class is not found'
        assert 'Func' in dir(pyde),'Func class is not found'
        assert 'customFunction' in dir(pyde),'customFunction class is not found'
        assert 'DifferentialEvolution' in dir(pyde),'DifferentialEvolution class is not found'

    def test_optimize(self):
        """ Test the Optimize class """
        opt = pyde.Optimize()
        assert opt is not None

    def test_func_initialization(self):
        """ Test initialization and functionality(default function) of Func class """
        num_params = 10
        func = pyde.Func(num_params)
        assert func.numOfParameters() == num_params

    def test_custom_function_initialization(self):
        """ Test initialization and functionality of customFunction class """
        custom_function = pyde.customFunction(10, rastrigin, -5.12, 5.12)

        assert isinstance(custom_function, pyde.customFunction)
        assert custom_function.numOfParameters() == 10
        assert custom_function.EvaluateCost([1,2,3,4,5,6,7,8,9,10]) == rastrigin([1,2,3,4,5,6,7,8,9,10])
        assert custom_function.getConstraints() is not None

    def test_DE_initialization(self):
        """Test initialization of DifferentialEvolution class."""
        Test_function = pyde.customFunction(10, rastrigin,-5.12,5.12)
        de = pyde.DifferentialEvolution(
            costFunction=Test_function,
            populationSize=50,
            F=0.9,
            CR=0.9,
            RandomSeed=123,
            shouldCheckConstraint=True,
            callback=callback,
            terminationCondition=termination_condition
        )
        assert isinstance(de, pyde.DifferentialEvolution)
    
    def test_Constraint_check(self):
        """Test constraint checking within Optimize."""
        constraint = pyde.Optimize.Constraint(0, 1, True)
        assert constraint.Check(0.5) == True, "Constraint check failed,this is within the bounds"
        assert not constraint.Check(-1), "Constraint check failed,this is outside the bounds"

    def test_evaluate_cost(self):
        """ Make sure the defalut cost is calculated correctly """
        num_params = 3
        func = pyde.Func(num_params)
        input =  [1.0, 1.0, 1.0]
        result = func.EvaluateCost(input)
        # caculate the cost
        res = 0
        for v in input:
            res += v**2-100*(np.cos(v))**2-100*(np.cos(v**2/30))
        res+=1400
        assert result - res < 1e-6, "Default cost function is not calculated correctly"
    

    """ Function Test Part """
    def test_num_of_parameters(self):
        func = pyde.Func(2)
        num_params = func.numOfParameters()
        assert num_params == 2

    def test_evaluate_cost(self):
        func = pyde.Func(2)
        # define the input vector
        input_vector = [1.0, 2.0]
        # TEST: Func::EvaluateCost() 
        cost = func.EvaluateCost(input_vector)
        assert isinstance(cost, float)  # Ensure the cost is a float

    # Constraint vector test
    def test_get_constraints(self):
        func = pyde.Func(2)
        constraints = func.getConstraints()

        assert len(constraints) == 2
        for constraint in constraints:
            assert constraint.lower == -100
            assert constraint.upper == 100
            assert constraint.isConstrained
   

if __name__ == "__main__":
    pytest.main()
