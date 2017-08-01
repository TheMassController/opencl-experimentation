#pragma once

#include "lpInstance.hpp"

namespace LineairProgramming{
    class LPSolver : public LPInstance {
        public:
            void printCurrentBasicSolution();
            virtual void solve();
    };
}
