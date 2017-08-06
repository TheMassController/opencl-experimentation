#include <algorithm> //std::find
#include <cmath> //std::signbit
#include "sequentialCPUSolver.hpp"

LineairProgramming::SequentialCPUSolver::SequentialCPUSolver(const LPSolver& inst) : LineairProgramming::LPSolver::LPSolver(inst){

}

LineairProgramming::SequentialCPUSolver::SequentialCPUSolver(const LPInstance& inst) : LineairProgramming::LPSolver::LPSolver(inst){

}

std::tuple<std::vector<double>, std::vector<std::size_t>> LineairProgramming::SequentialCPUSolver::deriveBasicSolutionInformation(void){
    std::vector<double> basicSolution(names.size());
    std::vector<std::size_t> rowIndex(names.size());
    // Every variable is either basic or non-basic.
    // Each row has exactly one basic variable.
    // The first row is excluded from this, if a variable has a value in the first row,
    // then it cannot be basic.
    for (std::size_t col = 0; col < names.size()-1; ++col){
        if (lpRepr[0][col] != 0) continue;
        // Check if this is the only non-zero element in the row
        std::size_t curRow = 0;
        bool found = false;
        for (std::size_t row = 1; row < lpRepr.size(); ++row){
            if (lpRepr[row][col] != 0){
                if (found){
                    found = false;
                    break;
                } else {
                    found = true;
                    curRow = row;
                }
            }
        }
        if (curRow == 0 || (!found && curRow != 0)) continue;
        // We have a candidate. Check if there already was one
        // If yes, check if this one is a better candidate
        double solution = lpRepr[curRow][lpRepr[0].size() - 1] / lpRepr[curRow][col];
        std::vector<std::size_t>::iterator it = std::find(rowIndex.begin(), rowIndex.end(), curRow);
        if (it == rowIndex.end()){
            // Not found
            rowIndex[col+1] = curRow;
            basicSolution[col+1] = solution;
        } else {
            // Found, check sign equality to determine which one should stay
            std::size_t knownIndex = it - rowIndex.begin();
            double knownSolution = basicSolution[knownIndex];
            double rightHandSide = lpRepr[curRow][knownIndex];
            if (std::signbit(knownSolution) != std::signbit(rightHandSide) && std::signbit(solution) == std::signbit(rightHandSide)){
                rowIndex[knownIndex] = 0;
                basicSolution[knownIndex] = 0;
                rowIndex[col+1] = curRow;
                basicSolution[col+1] = solution;
            }
        }
    }
    return std::make_tuple(basicSolution, rowIndex);
}

void LineairProgramming::SequentialCPUSolver::solve(void){

}
