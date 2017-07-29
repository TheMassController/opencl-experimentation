/**
 * @file randomLPInstanceGenerator.hpp
 * @author Jacko Dirks
 */

#pragma once

#include "lpInstance.hpp"
#include <cmath>

namespace LineairProgramming {
    LPInstance generateRandomInstance(std::size_t varCount,
                        std::size_t constrCount,
                        double rangeMin,
                        double rangeMax,
                        LineairProgramming::eqSym constrEqSym=leq,
                        LineairProgramming::eqSym varEqSym=geq,
                        LineairProgramming::minMax problemType=max);
}
