#pragma once

#include <vector>
#include <tuple>
#include "lpInstance.hpp"

namespace LineairProgramming{
    enum SolType {unknown, unbounded, infeasible, feasible, optimal};
    std::string solTypeToMessage(LineairProgramming::SolType sol);
    // LPSolver is an abstract class: it cannot exist on its own.
    class LPSolver  {
        private:
        protected:
        public:
            LPSolver();
            virtual std::tuple<std::vector<double>, std::vector<std::size_t>> deriveBasicSolutionInformation(const LPInstance& inst) = 0;
            virtual std::tuple<LPInstance, SolType> solve(const LPInstance& inst) = 0;

            void printCurrentBasicSolution(const LPInstance& inst);
    };
}
