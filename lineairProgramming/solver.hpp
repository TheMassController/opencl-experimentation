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
            virtual std::tuple<std::vector<double>, std::vector<std::size_t>> deriveBasicSolutionInformation(const std::vector<std::vector<double>>& simplexTableau) = 0;
        protected:
        public:
            LPSolver();
            std::tuple<std::vector<double>, std::vector<std::size_t>> deriveBasicSolutionInformation(const LPInstance& inst);
            void printCurrentBasicSolution(const LPInstance& inst);

            virtual SolType solve(LPInstance& inst) = 0;
    };
}
