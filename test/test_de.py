import pytest
import pyde

class TestDE:
    """ DE Test Part """

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
