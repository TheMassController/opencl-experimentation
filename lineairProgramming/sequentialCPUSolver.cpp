#include <algorithm> //std::find
#include <cmath> //std::signbit
#include "sequentialCPUSolver.hpp"

LineairProgramming::SequentialCPUSolver::SequentialCPUSolver(const LPSolver& inst) : LineairProgramming::LPSolver::LPSolver(inst){

}

LineairProgramming::SequentialCPUSolver::SequentialCPUSolver() : LineairProgramming::LPSolver::LPSolver(){

}

std::tuple<std::vector<double>, std::vector<std::size_t>> LineairProgramming::SequentialCPUSolver::deriveBasicSolutionInformation(const std::vector<std::vector<double>>& simplexTableau){
    std::size_t colCount = simplexTableau[0].size();
    std::vector<double> basicSolution(colCount);
    std::vector<std::size_t> rowIndex(colCount);
    // Every variable is either basic or non-basic.
    // Each row has exactly one basic variable.
    // The first row is excluded from this, if a variable has a value in the first row,
    // then it cannot be basic.
    for (std::size_t col = 0; col < colCount-1; ++col){
        if (simplexTableau[0][col] != 0) continue;
        // Check if this is the only non-zero element in the row
        std::size_t curRow = 0;
        bool found = false;
        for (std::size_t row = 1; row < simplexTableau.size(); ++row){
            if (simplexTableau[row][col] != 0){
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
        double solution = simplexTableau[curRow][simplexTableau[0].size() - 1] / simplexTableau[curRow][col];
        std::vector<std::size_t>::iterator it = std::find(rowIndex.begin(), rowIndex.end(), curRow);
        if (it == rowIndex.end()){
            // Not found
            rowIndex[col+1] = curRow;
            basicSolution[col+1] = solution;
        } else {
            // Found, check sign equality to determine which one should stay
            std::size_t knownIndex = it - rowIndex.begin();
            double knownSolution = basicSolution[knownIndex];
            double rightHandSide = simplexTableau[curRow][knownIndex];
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

std::tuple<std::vector<double>, std::vector<std::size_t>> LineairProgramming::SequentialCPUSolver::deriveBasicSolutionInformation(const LPInstance& inst){
    return deriveBasicSolutionInformation(inst.getSimplexTableau());
}

std::tuple<LineairProgramming::LPInstance, LineairProgramming::SolType> LineairProgramming::SequentialCPUSolver::solve(const LPInstance& inst){
    return std::make_tuple(inst, LineairProgramming::unknown);
}
