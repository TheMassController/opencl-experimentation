#include <iostream>
#include "solver.hpp"

LineairProgramming::LPSolver::LPSolver(const LPInstance& inst) : LineairProgramming::LPInstance::LPInstance(inst){
    curSol = unknown;
}

std::vector<double> LineairProgramming::LPSolver::getCurrentBasicSolution(){
    std::vector<double> basicSol(names.size());
    basicSol[0] = getSolution();
    std::vector<std::size_t> basicForRow(names.size());
    // Every variable is either basic or non-basic.
    // Each row has exactly one basic variable.
    // The first row is excluded from this, if a variable has a value in the first row,
    // then it cannot be basic.
    for (std::size_t col = 0; col < names.size()-1; ++col){
        if (lpRepr[0][col] != 0) continue;
        for (std::size_t row = 1; row < lpRepr.size(); ++row){
            if (lpRepr[row][col] == 0) continue;
            if (lpRepr[row][col] != 1 || basicForRow[col+1] != 0){
                basicSol[col+1] = 0;
                basicForRow[col+1] = 0;
                break;
            }
            bool unique = true;
            for (std::size_t& it : basicForRow){
                if (it == row){
                    unique = false;
                    break;
                }
            }
            if (unique){
                basicForRow[col+1] = row;
                basicSol[col+1] = lpRepr[row][lpRepr[0].size() -1];
            }
        }
    }
    return basicSol;
}

// Some instances just do not have a basic solution. This is checked, and reported
// If a basic solution is possible but violates some variable constraints, it is printed and the problem is reported
void LineairProgramming::LPSolver::printCurrentBasicSolution(void){
    std::vector<double> basicSolution = getCurrentBasicSolution();
    for (std::size_t i = 0; i < basicSolution.size(); ++i){
        std::cout << names[i] << " " << basicSolution[i] << std::endl;
    }
}

double LineairProgramming::LPSolver::getSolution(void){
    return lpRepr[0][lpRepr[0].size()-1];
}

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

std::string LineairProgramming::LPSolver::solTypeToMessage(){
    return LineairProgramming::solTypeToMessage(curSol);
}

LineairProgramming::SolType LineairProgramming::LPSolver::getCurSol(){
    return curSol;
}
