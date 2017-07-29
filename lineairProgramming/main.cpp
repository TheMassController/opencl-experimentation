#include "lpInstance.hpp"
#include "randomLPInstanceGenerator.hpp"

int main(){
    LineairProgramming::LPInstance inst = LineairProgramming::generateRandomInstance(2, 10, -20, 20);
    inst.print();
}
