#include <iostream>

#include "lpInstance.hpp"
#include "randomLPInstanceGenerator.hpp"
#include "sequentialCPUSolver.hpp"

int main(){
    LineairProgramming::SequentialCPUSolver seqSolver;
    // Create an easy, known instance
    std::vector<std::string> varnames = {"z", "x1", "x2"};
    std::vector<std::vector<double>> lpData(3);
    lpData[0] = {1, 1};
    lpData[1] = {2, 1};
    lpData[2] = {1, 2};
    std::vector<double> ans = { 4, 3};
    std::vector<LineairProgramming::eqSym> rowSymList = { LineairProgramming::leq, LineairProgramming::leq};
    std::vector<LineairProgramming::eqSym> varSymList = { LineairProgramming::geq, LineairProgramming::geq};
    LineairProgramming::LPInstance knownInst(LineairProgramming::LPInstance(varnames, lpData, ans, LineairProgramming::max, rowSymList, varSymList));
    knownInst.print();
    seqSolver.printCurrentBasicSolution(knownInst);

    LineairProgramming::LPInstance inst(LineairProgramming::generateRandomInstance(2, 10, -20, 20));
    inst.print();
    seqSolver.printCurrentBasicSolution(inst);
    std::cout << LineairProgramming::solTypeToMessage(seqSolver.solve(inst)) << std::endl;
}
