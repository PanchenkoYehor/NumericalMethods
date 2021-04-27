#include <vector>

using namespace std;

//x = 0.8 - cos(y + 0.5) = f(y)
//y = -0.8 + 0.5 * sin(x) = g(x)

namespace Laba4 {

    double eps = 1e-5;

    double f(double y) {
        return (0.8 - cos(y + 0.5));
    }

    double g(double x) {
        return (-0.8 + 0.5 * sin(x));
    }

    //sin(x+y)-1.4x = 0
    //x^2+y^2 - 1 = 0
    pair<double, double> Subtract(pair<double, double> a, pair<double, double> b) {
        return make_pair(a.first - b.first, a.second - b.second);
    }

};


void SolveBySimpleIterationMethod() {
    vector < pair<double,double> > x;
    if (bool Correct = true; Correct == true) {
        x.push_back(make_pair(-0.13, -0.86));
    } else {
        x.push_back(make_pair(10, 100));
    }

    for (;;) {
        auto nextappr = make_pair(Laba4::f(x.back().second), Laba4::g(x.back().first));
        if (max(abs(nextappr.first - x.back().first), abs(nextappr.second - x.back().second)) < Laba4::eps) {
            x.push_back(nextappr);
            break;
        }
        x.push_back(nextappr);
    }

    for (int i = 0; i < x.size(); i++) {
        printf("%d-th approximation:\n", i);
        printf("\tx, y = %10.5lf, %10.5lf\n", x[i].first, x[i].second);
        if (i > 0) {
            printf("\tdiff  =  %10.5lf\n", max(abs(x[i].first - x[i - 1].first), abs(x[i].second - x[i - 1].second)));
        }
    }

    printf("System translates into\n");
    printf("\t%10.5lf = %10.5lf\n", x.back().first, Laba4::f(x.back().second));
    printf("\t%10.5lf = %10.5lf\n", x.back().second, Laba4::g(x.back().first));
}


//Find inverse to 2 by 2 matrix
vector < vector < double > > CalculateInverseAt(pair <double, double> p) {
    double x = p.first;
    double y = p.second;
    vector < vector < double > > mat(2, vector < double > (2));
    mat[0][0] = 2 * y;
    mat[0][1] = -cos(x + y);
    mat[1][0] = -2 * x;
    mat[1][1] = cos(x + y) - 1.4;
    double det = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    for (auto &i : mat) {
        for (auto &j : i) {
            j /= det;
        }
    }
    return mat;
}

pair<double, double> F(pair<double, double> x) {
    return make_pair(sin(x.first + x.second) - 1.4 * x.first, pow(x.first, 2) + pow(x.second, 2) - 1);
}

pair < double, double > Mult(vector < vector < double > > invW, pair<double, double> F) {
    return make_pair(invW[0][0] * F.first + invW[0][1] * F.second,
            invW[1][0] * F.first + invW[1][1] * F.second);
}

void SolveByNewtonMethod() {
    vector < pair<double, double> > x;
    if (bool Correct = true; Correct == true) {
        x.push_back(make_pair(0.7, 0.7));
    } else {
        x.push_back(make_pair(-5, 10));
    }

    for (;;) {
        auto nextappr = Laba4::Subtract(x.back(), Mult(CalculateInverseAt(*x.begin()), F(x.back())));
        double diff = max(abs(nextappr.first - x.back().first), abs(nextappr.second - x.back().second));
        if (diff < Laba4::eps) {
            x.push_back(nextappr);
            break;
        }
        x.push_back(nextappr);
    }

    for (int i = 0; i < x.size(); i++) {
        printf("%d-th approximation:\n", i);
        printf("\tx, y = %10.5lf, %10.5lf\n", x[i].first, x[i].second);
        if (i > 0) {
            printf("\tdiff  =  %10.5lf\n", max(abs(x[i].first - x[i - 1].first), abs(x[i].second - x[i - 1].second)));
        }
    }

    printf("System translates into\n");
    printf("\t%10.5lf = %10.5lf\n", sin(x.back().first + x.back().second) - 1.4 * x.back().first, 0.0);
    printf("\t%10.5lf = %10.5lf\n", pow(x.back().first, 2) + pow(x.back().second, 2) - 1, 0.0);

}