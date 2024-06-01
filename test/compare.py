import numpy as np
from scipy.optimize import differential_evolution

def rastrigin(x, A=10):
    return A * len(x) + sum([(xi**2 - A * np.cos(2 * np.pi * xi)) for xi in x])

# 定义变量的界限
bounds = [(-5.12, 5.12) for _ in range(10)]  # 10维问题

# 调用差分进化算法
result = differential_evolution(rastrigin, bounds, maxiter=100, seed=123)

print("Optimized Result from SciPy:")
print("Best solution found:", result.x)
print("Function value at best solution:", result.fun)
