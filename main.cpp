#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>
#include <queue>
#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <random>
#include "laba1.cpp"
#include "laba2.cpp"
#include "laba3.cpp"
#include "laba4.cpp"

using namespace std;

const bool ExecuteLaba1 = false;
const bool ExecuteLaba2 = false;
const bool ExecuteLaba3 = false;
const bool ExecuteLaba4 = true;

int main() {
    if (ExecuteLaba1 == true) {
        FindLR();
        printf("L and R are [%0.10lf] and [%0.10lf]\n", L, R);
        f.push_back(a);
        f.push_back(Derivative(a));
        while (true) {
            auto x = Mod(f[f.size() - 2], f.back());
            MultyBy(x, -1);
            f.push_back(x);
            if (x.size() == 1) {
                break;
            }
        }
        /*for (auto i : f) {
            Print(i);
        }*/
        MakeTable(-R, R);
    }

    if (ExecuteLaba2 == true) {
        auto m = IntoDiagonal();
    }

    if (ExecuteLaba3 == true) {
        SolveByYacob();
    }

    if (ExecuteLaba4 == true) {
        SolveBySimpleIterationMethod();
        SolveByNewtonMethod();
    }
}
