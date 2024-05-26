
#include "../include/DE.h"
#include "../include/functions.h"
#include <iostream>

int main(){

    // Create a function object
    int dimension = 4;

    // cost function
    DE::Func f(dimension);

    // Create a DE object
    DE::DifferentialEvolution de(f,50); // Input: (cost function, population size)

    // Optimize the function
    de.OptimizeStep(1000);

    

    // print population 
    //de.printPopulation(); 

    return 0;


}