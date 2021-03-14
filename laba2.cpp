#include <vector>
using namespace std;

const vector < vector < double > > A = {{30.1, -1.4, 10, -1.5},
                                        {-17.5, 11.1, 1.3, -7.5},
                                        {1.7, -21.1, 7.1, -17.1},
                                        {2.1, 2.1, 3.5, 3.3}};
const vector < double > B = {10, 1.3, 10, 1.7};

vector < double > Multy(vector < vector < double > > a, vector < double > x) {
    vector < double > res(x.size(), 0);

    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < x.size(); j++) {
            res[i] += a[i][j] * x[j];
        }
    }
    return res;
}

vector < double > Substract(vector < double > a, vector < double > b) {
    for (int i = 0; i < a.size(); i++) {
        a[i] -= b[i];
    }
    return a;
}

pair < vector < vector < double > >, vector < double > > IntoDiagonal(vector < vector < double > > a = A, vector < double > b = B) {

    auto old_a = a;
    auto old_b = b;
    int cnt_p = 0;
    for (int i = 0; i + 1 < a.size(); i++) {

        int ind = i;
        for (int j = i; j < a.size(); j++) {
            if (abs(a[j][i]) > abs(a[ind][i])) {
                ind = j;
            }
        }

        //swap i-th and ind-th row
        cnt_p += (i != ind);
        swap(a[i], a[ind]);
        swap(b[i], b[ind]);
        if (abs(a[i][i]) < eps) {
            continue;
        }

        //subtract i-th from [i+1..a.size()) rows

        for (int r = i + 1; r < a.size(); r++) {

            double val = a[r][i] / a[i][i];
            for (int k = i; k < a.size(); k++) {
                a[r][k] -= val * a[i][k];
            }

            b[r] -= val * b[i];

        }

    }

    vector < double > x(a.size());
    x.back() = b.back() / a.back().back();

    for (int i = (int)a.size() - 2; i >= 0; i--) {

        x[i] = b[i];
        for (int j = i + 1; j < a.size(); j++) {
            x[i] -= a[i][j] * x[j];
        }
        x[i] /= a[i][i];
    }

    for (int i = 0; i < a.size(); i++) {
        for (auto j : a[i])
            printf("%10.3lf ", j);
        printf("%10.3lf\n", b[i]);
    }

    for (int i = 0; i < x.size(); i++) {
        printf("x[%d] = %10.3lf\n", i, x[i]);
    }

    auto diff = Substract(old_b, Multy(old_a, x));

    printf("diff is:\n");
    for (auto j : diff) {
        printf("%10.3lf\n", j);
    }

    double det = pow(-1, cnt_p);
    for (int i = 0; i < a.size(); i++)
        det *= a[i][i];
    printf("det = %10.3lf\n", det);

    return make_pair(a, b);

}