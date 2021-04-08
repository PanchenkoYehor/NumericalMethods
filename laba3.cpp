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
        for (int j = 0; j < A.size(); j++) {
            if (i == j) {
                continue;
            }
            if (A[i][j] >= A[i][i]) {
                return false;
            }
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
    printf("Matrix:\n");
    PrintMat(A_it);
    printf("Column:\n");
    PrintRow(B_it);

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
    printf("Solution:\n");
    PrintRow(x.back());
}