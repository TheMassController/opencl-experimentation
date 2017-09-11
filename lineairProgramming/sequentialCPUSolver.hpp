#pragma once

#include "solver.hpp"

namespace LineairProgramming{
    class SequentialCPUSolver : public LPSolver {
        private:
            std::tuple<std::vector<double>, std::vector<std::size_t>> deriveBasicSolutionInformation(const std::vector<std::vector<double>>& simplexTableau);
            SolType doSimplex(LPInstance& inst);
        protected:
        public:
            SequentialCPUSolver(const LPSolver& inst);
            SequentialCPUSolver();

            SolType solve(LPInstance& inst);
    };
}
