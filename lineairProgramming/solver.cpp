#include "solver.hpp"

LineairProgramming::LPSolver::LPSolver(const LPInstance& inst) : LineairProgramming::LPInstance::LPInstance(inst){
    curSol = unknown;
}

std::vector<double> getCurrentBasicSolution(){
}

// Some instances just do not have a basic solution. This is checked, and reported
// If a basic solution is possible but violates some variable constraints, it is printed and the problem is reported
void LineairProgramming::LPSolver::printCurrentBasicSolution(void){

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
