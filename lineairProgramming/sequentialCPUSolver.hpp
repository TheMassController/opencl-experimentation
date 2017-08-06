#pragma once

#include "solver.hpp"

namespace LineairProgramming{
    class SequentialCPUSolver : public LPSolver {
        public:
            SequentialCPUSolver(const LPSolver& inst);
            SequentialCPUSolver(const LPInstance& inst);

            std::tuple<std::vector<double>, std::vector<std::size_t>> deriveBasicSolutionInformation(void);
            void solve(void);
    };
}
