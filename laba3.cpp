#include <vector>

using namespace std;

namespace Laba3 {

    const vector<vector<double> > A = {{2.923, 0.220, 0.159, 0.328},
                                       {0.363, 4.123, 0.268, 0.327},
                                       {0.169, 0.271, 3.906, 0.295},
                                       {0.241, 0.319, 0.257, 3.862}};
    const vector<double> B = {0.605, 0.496, 0.590, 0.896};
    double eps = 1e-5;
}

using namespace Laba3;

bool DiagonalDominant(vector< vector < double > > A) {
    for (int i = 0; i < A.size(); i++) {
        double sum = 0;
        for (int j = 0; j < A.size(); j++) {
            if (i == j) {
                continue;
            }
            sum += A[i][j];
        }
        if (sum >= A[i][i]) {
            return false;
        }
    }

    return true;
}

void PrintMat(vector < vector < double > > A) {
    for (int i = 0; i < A.size(); i++) {
        for (auto j : A[i]) {
            printf("%4.5lf ", j);
        }
        printf("\n");
    }
}

void PrintRow(vector < double > B) {
    for (auto i : B) {
        printf("%4.5lf ", i);
    }
    printf("\n");
}

void SolveByYacob() {
    bool dom = DiagonalDominant(Laba3::A);
    printf("Diagonal dominant: %s\n", dom ? "true" : "false");
    //Ax = B
    auto A_it = Laba3::A;
    auto B_it = Laba3::B;
    for (int i = 0; i < A_it.size(); i++) {
        for (int j = 0; j < A_it.size(); j++) {
            if (i == j) {
                A_it[i][j] = 0;
                continue;
            }
            A_it[i][j] = -Laba3::A[i][j] / Laba3::A[i][i];
        }
        B_it[i] /= Laba3::A[i][i];
    }
    printf("\nMatrix B:\n");
    PrintMat(A_it);
    printf("\nColumn c:\n");
    for (int i = 0; i < B_it.size(); i++) {
        printf("c[%d] = %10.5lf\n", i, B_it[i]);
        //PrintRow(B_it);
    }
    //x = Bx + c

    vector < vector < double > > x(0);
    bool need_random = true;
    if (need_random) {
        srand(time(0));
        vector < double > r(B_it.size());
        for (auto &i : r) {
            i = (double)rand() / rand();
        }
        x.push_back(r);
    } else {
        x.push_back(B_it);
    }

    for (;;) {
        //x_(k+1) = B * x_k + c
        auto x_it = Multy(A_it, x.back());
        for (int i = 0; i < x_it.size(); i++) {
            x_it[i] += B_it[i];
        }


        double maxdiff = 0;
        for (int i = 0; i < x_it.size(); i++) {
            maxdiff = max(maxdiff, abs(x_it[i] - x.back()[i]));
        }

        x.push_back(x_it);

        if (maxdiff <= Laba3::eps) {
            break;
        }
    }

    for (int t = 0; t + 1 < x.size(); t++) {
        printf("%d-th approximation:\n", t);
        for (int i = 0; i < x[t].size(); i++) {
            printf("\tx[%d] = %10.5lf\n", i, x[t][i]);
        }
    }

    printf("\nSolution:\n");
    for (int i = 0; i < x.back().size(); i++) {
        printf("x[%d] = %10.5lf\n", i, x.back()[i]);
        //PrintRow(x.back());
    }

    auto diff = Substract(Laba3::B, Multy(Laba3::A, x.back()));

    printf("\ndiff is:\n");
    for (auto j : diff) {
        printf("%10.5lf\n", j);
    }
}