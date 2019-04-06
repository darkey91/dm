#include <cstdio>
#include <vector>
#include <cmath>
 
double EPS = 1e-5;
 
int main() {
    FILE *in, *out;
    in = fopen("markchain.in", "r");
    out = fopen("markchain.out", "w");
 
    int n;
    fscanf(in, "%d", &n);
 
    std::vector<std::vector<double>> p(n + 1), a(n + 1);
    p[0] = std::vector<double>(n + 1, 1);
 
    double tmp;
    for (int i = 1; i <= n; ++i) {
        p[i] = std::vector<double>(n + 1, 0);
    }
 
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= n; ++j) {
            fscanf(in, "%lf", &tmp);
            p[j][i] = tmp;
            if (i == (j - 1)) {
                p[j][i ] -= 1;
            }
        }
    }
/*
    for (int i = 0; i <= n; ++i) {
        // double del = p[i][i];
        for (int j = i + 1; j <= n; ++j) {
            double del = p[j][i] / (-1) * p[i][i];
            for (int k = i; k <= n; ++k) {
                p[j][k] += p[i][k] * del;
            }
        }
    }*/
 
 
    int j;
    for (int i = 0; i < n; ++i) {
        double del = p[i][i];
        for (j = n; j >= i; --j) {
            p[i][j] /= del;
        }
        for (j = i + 1; j <= n; ++j) {
            del = p[j][i];
            for (int k = n; k >= i; --k) {
                p[j][k] -= del * p[i][k];
            }
        }
    }
 
    std::vector <double> u(n);
    u[n - 1] = p[n - 1][n];
 
    for (int i = n - 2; i >= 0; --i) {
        u[i] = p[i][n] ;
        for (int j = i + 1; j < n; ++j) {
            u[i] -= p[i][j] * u[j];
        }
    }
 
 
    for (int i = 0; i < n; ++i) {
        fprintf(out, "%.5lf\n", u[i]);
    }
 
    return 0;
}
