#pragma once

#include <vector>
#include <tuple>
#include "lpInstance.hpp"

namespace LineairProgramming{
    enum SolType {unknown, unbounded, infeasible, feasible, optimal};
    std::string solTypeToMessage(LineairProgramming::SolType sol);
    // LPSolver is an abstract class: it cannot exist on its own.
    class LPSolver : public LPInstance {
        private:
        protected:
            SolType curSol;
        public:
            LPSolver(const LPInstance& inst);

            virtual std::tuple<std::vector<double>, std::vector<std::size_t>> deriveBasicSolutionInformation(void) = 0;
            LineairProgramming::SolType getCurSol();

            double getSolution();
            virtual void solve() = 0;

            void printCurrentBasicSolution();
            std::string solTypeToMessage();
    };
}
