#pragma once

#include <vector>
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
            void printCurrentBasicSolution();
            std::string solTypeToMessage();
            double getSolution();
            std::vector<double> getCurrentBasicSolution();
            LineairProgramming::SolType getCurSol();
            virtual void solve() = 0;
    };
}
