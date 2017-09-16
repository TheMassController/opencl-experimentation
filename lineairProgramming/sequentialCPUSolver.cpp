#include <algorithm> //std::find
#include <cmath> //std::signbit
#include <limits> //std::numeric_limits
#include "sequentialCPUSolver.hpp"

LineairProgramming::SequentialCPUSolver::SequentialCPUSolver(const LPSolver& inst) : LineairProgramming::LPSolver::LPSolver(inst){

}

LineairProgramming::SequentialCPUSolver::SequentialCPUSolver() : LineairProgramming::LPSolver::LPSolver(){

}

std::tuple<std::vector<double>, std::vector<std::size_t>> LineairProgramming::SequentialCPUSolver::deriveBasicSolutionInformation(const std::vector<std::vector<double>>& simplexTableau){
    std::size_t colCount = simplexTableau[0].size();
    std::vector<double> basicSolution(colCount);
    std::vector<std::size_t> rowIndex(colCount);
    basicSolution[0] = simplexTableau[0][colCount-1];
    // Every variable is either basic or non-basic.
    // Each row has exactly one basic variable.
    // The first row is excluded from this, if a variable has a value in the first row,
    // then it cannot be basic.
    for (std::size_t col = 0; col < colCount-1; ++col){
        if (simplexTableau[0][col] != 0) continue;
        // Check if this is the only non-zero element in the colmn
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

LineairProgramming::SolType LineairProgramming::SequentialCPUSolver::doSimplex(LPInstance& inst){
    std::vector<std::vector<double>> tableau = inst.getSimplexTableau();
    LineairProgramming::SolType retVal = LineairProgramming::unknown;
    while(1) {
        // Check the first row, find the most negative value
        double mostNeg = 0;
        std::size_t pivotColIndex = 0;
        for (std::size_t i = 0; i < tableau[0].size(); ++i){
            if (tableau[0][i] < mostNeg){
                mostNeg = tableau[0][i];
                pivotColIndex = i;
            }
        }
        if (mostNeg >= 0){
            std::vector<double> ans;
            std::vector<std::size_t> pos;
            std::tie(ans, pos) = deriveBasicSolutionInformation(tableau);
            retVal = LineairProgramming::optimal;
            for (std::size_t i = 0; i < ans.size(); ++i){
                if (ans[i] < 0){
                    retVal = LineairProgramming::infeasible;
                    break;
                }
            }
            break;
        }
        // Go over all the rows, find the ratios.
        double smallestRatio = std::numeric_limits<double>::max();
        std::size_t pivotRowIndex = tableau.size();
        for (std::size_t i = 1; i < tableau.size(); ++i){
            double ratio = tableau[i][tableau[i].size() - 1]/ tableau[i][pivotColIndex];
            if (ratio >= 0 && ratio < smallestRatio){
                smallestRatio = ratio;
                pivotRowIndex = i;
            }
        }
        if (pivotRowIndex == tableau.size()){
            retVal = LineairProgramming::unbounded;
            break;
        }
        // We have the location of the pivot element, start scrubbing.
        // Skip the pivotrow, for now
        for (std::size_t i = 0; i < tableau.size(); ++i){
            if (i == pivotRowIndex) continue;
            double ratio = tableau[i][pivotColIndex] / tableau[pivotRowIndex][pivotColIndex];
            for (std::size_t j = 0; j < tableau[i].size(); ++j){
                tableau[i][j] -= ratio*tableau[pivotRowIndex][j];
            }
        }
        // Do the pivotrow
        double ratio = 1/tableau[pivotRowIndex][pivotColIndex];
        for (std::size_t j = 0; j < tableau[pivotRowIndex].size(); ++j){
            tableau[pivotRowIndex][j] *= ratio;
        }
    }
    inst.updateSimplexTableau(tableau);
    return retVal;
}

LineairProgramming::SolType LineairProgramming::SequentialCPUSolver::solve(LPInstance& inst){
    return doSimplex(inst);
}
