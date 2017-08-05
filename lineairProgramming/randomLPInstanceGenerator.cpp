#include <random>
#include "randomLPInstanceGenerator.hpp"

LineairProgramming::LPInstance LineairProgramming::generateRandomInstance(std::size_t varCount,
                                                                          std::size_t constrCount,
                                                                          double rangeMin,
                                                                          double rangeMax,
                                                                          LineairProgramming::eqSym constrEqSym,
                                                                          LineairProgramming::eqSym varEqSym,
                                                                          LineairProgramming::minMax problemType){
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<double> distribution(rangeMin, rangeMax);
    // First, generate the names. One per var.
    std::vector<std::string> names(varCount+1);
    names[0] = "z";
    for (std::size_t i = 0; i < varCount; ++i){
        names[i+1] = "x_"+std::to_string(i);
    }
    // Whenever you initialize a std::vector its elements are set to zero. This is exploited, here.
    std::vector<std::vector<double>> data(constrCount+1);
    std::vector<double>row(varCount); // One coefficient per variable, one for the optimizationvar
    // Generate all the constaint rows
    for (std::size_t i = 0; i < constrCount+1; ++i){
        for (std::size_t j = 0; j < varCount; ++j){
            row[j] = distribution(generator);
        }
        data[i] = row;
    }
    std::vector<double> ansRow(constrCount);
    for (std::size_t i = 0; i < constrCount; ++i){
        ansRow[i] = distribution(generator);
    }
    // The constraint equality sign vector
    std::vector<LineairProgramming::eqSym> constrSignVec(constrCount);
    if (constrEqSym != noSym){
        constrSignVec.assign(constrCount, constrEqSym);
    } else {
        std::uniform_int_distribution<int> dist(0, 1);
        for (std::size_t i = 0; i < constrCount; ++i){
            int v = dist(generator);
            switch(v){
                case 0:
                    constrSignVec[i] = leq;
                    break;
                default:
                    constrSignVec[i] = geq;
                    break;
            }
        }
    }
    // The variable equality sign vector
    std::vector<LineairProgramming::eqSym> varSignVec(varCount);
    if (varEqSym != noSym){
        varSignVec.assign(varCount, varEqSym);
    } else {
        std::uniform_int_distribution<int> dist(0, 1);
        for (std::size_t i = 0; i < constrCount; ++i){
            int v = dist(generator);
            switch(v){
                case 0:
                    varSignVec[i] = leq;
                    break;
                default:
                    varSignVec[i] = geq;
                    break;
            }
        }
    }
    return LineairProgramming::LPInstance(names, data, ansRow, problemType, constrSignVec, varSignVec);

}
