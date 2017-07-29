/**
 * @file lpInstance.hpp
 * @author Jacko Dirks
 *
 * This class represents an LPInstance.
 * It provides a representation, a way to print the setup and a superclass to any solvers.
 * Please note that an ILP is a subset of LP for the purpose of this software.
 */

#pragma once

#include <vector>
#include <string>

namespace LineairProgramming{
    enum minMax {min, max};
    enum eqSym {leq, eq, geq, noSym};
    class LPInstance {
        private:
            std::vector<std::string> names;
        protected:
            std::vector<std::vector<double>> lpRepr;
        public:
            /**
             * @brief default constructor. Processes any form of LP instance to an internal representation
             * @param varNames, the names of the variables. The first one should be the name of the variable that is being optimized (usually z).
             *              After this the other ones follow (usually x_1, x_2, .., x_n)
             * @param lpTable The constraint table.
             *              This matrix contains all coefficients.
             *              The first row is special, it contains the solution.
             *              This is assumed to be in the original form: x_1 + x_2 + .. instead of -x_1 - x_2-...
             * @param ansColmn A vector containing the answers to the equation.
             *              There should be no answer to the first row, since that answer is always zero
             * @param probType Maximization problem or minimization problem.
             * @param rowSymList A colmn indicating for every row the symbol (leq (less or equal), eq (equal), geq (greater then or equal)).
             *              This colmn starts at the first constraint, row zero always as an eq sign
             * @param varSymList A vector containing for every variable except the one that is being optimized wether it should be greater then zero or smaller then zero.
             *              eq and neq are not allowed in this vector.
             */
            LPInstance( const std::vector<std::string>& varNames,
                        const std::vector<std::vector<double>>& lpTable,
                        const std::vector<double>& ansColmn,
                        const LineairProgramming::minMax probType,
                        const std::vector<LineairProgramming::eqSym>& rowSymList,
                        const std::vector<LineairProgramming::eqSym>& varSymList );
            ~LPInstance(void);

            void print();
    };

}
