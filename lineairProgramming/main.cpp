#include "lpInstance.hpp"
#include "randomLPInstanceGenerator.hpp"
#include "sequentialCPUSolver.hpp"

int main(){
    // Create an easy, known instance
    std::vector<std::string> varnames = {"z", "x1", "x2"};
    std::vector<std::vector<double>> lpData(3);
    lpData[0] = {1, 1};
    lpData[1] = {2, 1};
    lpData[2] = {1, 2};
    std::vector<double> ans = { 4, 3};
    std::vector<LineairProgramming::eqSym> rowSymList = { LineairProgramming::leq, LineairProgramming::leq};
    std::vector<LineairProgramming::eqSym> varSymList = { LineairProgramming::geq, LineairProgramming::geq};
    LineairProgramming::SequentialCPUSolver knownInst(LineairProgramming::LPInstance(varnames, lpData, ans, LineairProgramming::max, rowSymList, varSymList));
    knownInst.print();
    knownInst.printCurrentBasicSolution();

    LineairProgramming::SequentialCPUSolver inst(LineairProgramming::generateRandomInstance(2, 10, -20, 20));
    inst.print();
    inst.printCurrentBasicSolution();
}
