## ALG
- Q:
    - The algorithm on the function is not working
- Sol: 

## cannot find python
- Q: pybind construction fail
- Sol:
    - modify the CmakeList
    - cmake .. -DPYTHON_EXECUTABLE=$(which python)
    - let the system to find the python


# lack of Python.h
- cmake .. -Wdev 
```
-- pybind11 v2.13.0 dev1
-- Python found: /opt/homebrew/Frameworks/Python.framework/Versions/3.12/bin/python3.12
-- Configuring done (0.2s)
-- Generating done (0.0s)
-- Build files have been written to: /Users/hsiaoyenlaing/Software-course/DE/DE/src/build

```
- make
    - miss the Python.h header
    - https://www.askpython.com/python/examples/macos-fix-python-h-not-found-error


# 執行authority
```
chmod +x /Users/hsiaoyenlaing/Software-course/DE/DE/test/test_pybind.py
```

## Pytest problem
error messages:
    ModuleNotFoundError: No module named 'pybind11_tests
SOL:
    fix CmakeList.txt of run_test_pybind command


    