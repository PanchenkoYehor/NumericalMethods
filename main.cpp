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

using namespace std;

const double eps = 1e-5;
vector < double > a = {25, -139, -809, 916, 850, -449, -210, 31};
vector < vector < double > > f;
double step = 0.1;
double L, R;
vector < vector < int > > Table;

void FindLR() {
    double A, B;
    A = fabs(a[0]);
    B = fabs(a.back());
    for (int i = 1; i + 1 < a.size(); i++) {
        A = max(A, fabs(a[i]));
        B = max(B, fabs(a[i]));
    }
    L = 1.0 / (1 + B / fabs(a[0]));
    R = 1 + A / fabs(a.back());
}

bool equal(double a, double b) {
    return fabs(a - b) <= eps;
}

int sgn(double x) {
    return (equal(x, 0) ? 0 : (x > 0 ? 1 : -1));
}

double calculate(vector < double > P, double x) {
    double res = 0;
    for (int i = 0; i < P.size(); i++)
        res += P[i] * pow(x, i);
    return res;
}

vector < double > Mod(vector < double > P, vector < double > Q) {
    while (Q.size() <= P.size()) {
        int deg = (int)P.size() - Q.size();
        double coefficient = P.back() / Q.back();
        for (int i = 0; i < Q.size(); i++) {
            P[i + deg] -= coefficient * Q[i];
        }
        while (!P.empty() && equal(P.back(), 0))
            P.pop_back();
    }
    if (P.empty()) {
        return {0};
    }
    return P;
}

vector < double > Derivative(vector < double > P) {
    for (int i = 0; i + 1 < (int)P.size(); i++) {
        P[i] = (i + 1) * P[i + 1];
    }
    P.pop_back();
    return P;
}

void Print(vector < double > P) {
    printf("Pol: ");
    for (int i = (int)P.size() - 1; i >= 0; i--) {
        if (P[i] >= 0 && i + 1 != P.size()) {
            printf("+");
        }
        printf("%0.2lf", P[i]);
        if (i != 0) {
            printf("*x^%d ",i);
        }
    }
    printf("\n");
}

void MultyBy(vector < double > &P, double c) {
    for (auto &i : P) {
        i *= c;
    }
}

void FindRootByBinaryDividing(vector < double > P, double l, double r) {
    bool isinc = calculate(P, r) > calculate(P, l);
    while (r - l > eps) {
        printf("Interval is [%0.10lf, %0.10lf] and values are [%0.10lf, %0.10lf]\n",
                l, r, calculate(P, l), calculate(P, r));
        double m = (r + l) / 2;
        double x = calculate(P, m);
        if (equal(x, 0)) {
            l = m;
            break;
        }
        (((x > 0 && isinc) || (x < 0 && !isinc)) ? r : l) = m;
    }
    printf("The root found by bin. method is %0.10lf\n", l);
}

void FindRootByChord(vector < double > P, double l, double r) {
    int sign = sgn(calculate(Derivative(Derivative(P)), l));
    bool moveleft = ((sign < 0 && calculate(P, l) > 0) ||
            (sign > 0 && calculate(P, l) < 0));
    vector < double > x;
    for (/*r - l > eps*/ /*int k = 30; k; k--*/; ;) {
        printf("Interval is [%0.10lf, %0.10lf] and values are [%0.10lf, %0.10lf]\n",
               l, r, calculate(P, l), calculate(P, r));
        double c = l - calculate(P, l) * (r - l) / (calculate(P, r) - calculate(P, l));
        if (!x.empty() && (fabs(x.back() - c) < eps || fabs(calculate(P, x.back())) < eps)) {
            break;
        }
        x.push_back(c);
        (moveleft ? l : r) = c;
    }
    printf("The root found by crd. method is %0.10lf\n",
            /*l - calculate(P, l) * (r - l) / (calculate(P, r) - calculate(P, l))*/ x.back());

}

void FindRootByNewton(vector < double > P, double l, double r) {
    vector < double > x(1, (calculate(P, l) * calculate(Derivative(Derivative(P)), l) > 0 ? l : r));
    for (; ;) {
        printf("Point is [%0.10lf] and value is [%0.10lf]\n",
               x.back(), calculate(P, x.back()));
        double c = x.back() - calculate(P, x.back()) / calculate(Derivative(P), x.back());
        if (fabs(x.back() - c) < eps || fabs(calculate(P, x.back())) < eps) {
            break;
        }
        x.push_back(c);
    }
    printf("The root found by ntw. method is %0.10lf\n",
            /*l - calculate(P, l) * (r - l) / (calculate(P, r) - calculate(P, l))*/ x.back());
}

void MakeTable(double l, double r) {
    Table.resize(f.size());
    vector < int > changes;
    for (double val = l; val <= r; val += step) {
        for (int i = 0; i < Table.size(); i++) {
            Table[i].push_back(sgn(calculate(f[i], val)));
        }
        changes.push_back(0);
        for (int i = 0; i + 1 < Table.size(); i++) {
            changes.back() += Table[i].back() * Table[i + 1].back() == -1;
        }
    }

    for (double val = l, i = 0; (int)i + 1 < changes.size(); val += step, i += 1) {
        if (changes[i] - changes[i + 1] == 1) {
            printf("There is only one root in [%0.10lf, %0.10lf]\n", val, val + step);
            FindRootByBinaryDividing(a, val, val + step);
            FindRootByChord(a, val, val + step);
            FindRootByNewton(a, val, val + step);
        }
    }
}

int main() {
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