#include "lpInstance.hpp"
#include <stdexcept>
#include <iostream>

LineairProgramming::LPInstance::LPInstance( const std::vector<std::string>& varNames,
        const std::vector<std::vector<double>>& lpTable,
        const std::vector<double>& ansColmn,
        const LineairProgramming::minMax probType,
        const std::vector<LineairProgramming::eqSym>& rowSymList,
        const std::vector<LineairProgramming::eqSym>& varSymList ){
    /**
     * A series of size checks:
     * - The lpTable needs one equality symbol per row, except for the first row
     * - Every row of the lpTable needs to be equally long
     * - For every coefficient, there should be one equality sign
     * - There should be one right-hand value per constraint
     */
    if (lpTable.size() != rowSymList.size() + 1){
        throw std::invalid_argument("lpTable.size() != rowSymList.size() + 1");
    }
    std::size_t rowLen = lpTable[0].size();
    for (std::size_t i = 1; i < lpTable.size(); ++i){
        if (lpTable[i].size() != rowLen){
            throw std::invalid_argument("Not all rows of the lpTable are of equal length!");
        }
    }
    if (rowLen != varSymList.size()){
        throw std::invalid_argument("rowLen != varSymList.size()");
    }
    if (ansColmn.size() != lpTable.size() -1){
            throw std::invalid_argument("ansColmn.size() != lpTable.size() -1");
    }
    if (varNames.size() != lpTable[0].size() + 1){
        throw std::invalid_argument("varNames != lpTable[0].size() + 1");
    }
    // Now, rework the input to the object
    names = varNames;
    lpRepr = lpTable;
    // The entire first row *-1 to get it into the right form. Unless the problem type is min
    if (probType == max){
        for (std::size_t i = 0; i < lpRepr[0].size(); ++i){
            lpRepr[0][i] *= -1;
        }
    }
    // We need every varSym to be >=, so if it is <=, invert the sign of any coefficient of that specific var.
    // Also, throw an error on equality and noSym
    for (std::size_t i = 0; i < varSymList.size(); ++i){
        if (varSymList[i] == noSym){
            throw std::invalid_argument("The equality symbol of any variable cannot be noSym");
        }
        if (varSymList[i] == leq){
            for (std::size_t j = 0; j < lpRepr.size(); ++j){
               lpRepr[j][i] *= -1;
            }
        }
    }
    // And now, every row needs an equality sign.
    // noSym is not an option
    std::string slackSymPrefix = "a_";
    std::size_t slackSymSuffix = 0;
    for (std::size_t i = 0; i < rowSymList.size(); ++i){
        if (rowSymList[i] == noSym){
            throw std::invalid_argument("The equality symbol of any row cannot be noSym");
        }
        if (rowSymList[i] == leq){
            lpRepr[i+1].push_back(1);
        } else {
            lpRepr[i+1].push_back(-1);
        }
        for (std::size_t j = 0; j < lpRepr.size(); ++j){
            if (j != i+1) lpRepr[j].push_back(0);
        }
        names.push_back(slackSymPrefix+std::to_string(slackSymSuffix));
        slackSymSuffix++;
    }
    // Push the answers into the lpRepr
    lpRepr[0].push_back(0);
    for (std::size_t i = 0; i < ansColmn.size(); ++i){
        lpRepr[i+1].push_back(ansColmn[i]);
    }
}

LineairProgramming::LPInstance::~LPInstance(void){
}

void LineairProgramming::LPInstance::print(void){
    for (std::size_t i = 0; i < lpRepr.size(); ++i){
        std::size_t j = 0;
        if (i == 0){
            std::cout<< names[0];
        } else {
            std::cout << std::to_string(lpRepr[i][0]) << names[1];
            j = 1;
        }
        for (; j < lpRepr[i].size() - 1; ++j){
            if (lpRepr[i][j] == 0){
                continue;
            } else if (lpRepr[i][j] > 0) {
                std::cout << " + " << std::to_string(lpRepr[i][j]) << names[j+1];
            } else {
                std::cout << " - " << std::to_string(-lpRepr[i][j]) << names[j+1];
            }
        }
        std::cout << " = " << std::to_string(lpRepr[i][lpRepr[i].size()-1]) << std::endl;
    }
}
