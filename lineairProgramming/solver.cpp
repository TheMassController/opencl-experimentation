#include <iostream>
#include "solver.hpp"

std::string LineairProgramming::solTypeToMessage(LineairProgramming::SolType sol){
    switch(sol){
        case unknown:
            return "No information is currently determined about the system passed";
        case unbounded:
            return "The solution is unbounded (infinity)";
        case infeasible:
            return "The current system has no feasible solutions";
        case feasible:
            return "The current solution is a feasible solution (but might not be optimal)";
        case optimal:
            return "The current solution is an optimal solution";
        default:
            return "Unknown SolType";
    }
}

LineairProgramming::LPSolver::LPSolver(){

}

void LineairProgramming::LPSolver::printCurrentBasicSolution(const LPInstance& inst){
    std::vector<double> basicSolution;
    std::vector<std::size_t> rowInformation;
    std::vector<std::string> names = inst.getNames();
    std::tie(basicSolution, rowInformation) = deriveBasicSolutionInformation(inst);
    for (std::size_t i = 0; i < basicSolution.size(); ++i){
        std::cout << names[i] << " " << basicSolution[i] << std::endl;
    }
}
