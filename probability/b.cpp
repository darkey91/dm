#include <cstdio>
#include <vector>
#include <cmath>
 
int main() {
    FILE *in, *out;
    in = fopen("shooter.in", "r");
    out = fopen("shooter.out", "w");
 
    int n, m, k;
    fscanf(in, "%d%d%d", &n, &m, &k);
 
    std::vector<double> p(n + 1);
 
    double P = 0;
    for (int i = 1; i <= n; i++) {
        fscanf(in, "%lf", &p[i]);
        p[i] = pow((1 - p[i]), m) ;
        P += p[i];
    }
 
    double answer = p[k] / P;
    fprintf(out, "%.13lf", answer);
    return 0;
 
 
}
