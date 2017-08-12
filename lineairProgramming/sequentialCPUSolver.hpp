#pragma once

#include "solver.hpp"

namespace LineairProgramming{
    class SequentialCPUSolver : public LPSolver {
        private:
            std::tuple<std::vector<double>, std::vector<std::size_t>> deriveBasicSolutionInformation(const std::vector<std::vector<double>>& simplexTableau);
        protected:
        public:
            SequentialCPUSolver(const LPSolver& inst);
            SequentialCPUSolver();

            std::tuple<LPInstance, SolType> solve(const LPInstance& inst);
    };
}
