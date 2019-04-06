#include <cstdio>
#include <vector>
 
int main() {
    FILE *in, *out;
    in = fopen("exam.in", "r");
    out = fopen("exam.out", "w");
 
    int n, k;
 
    fscanf(in, "%d%d", &k, &n);
 
    double answer = 0;
 
    for (int i = 0; i < k; i++) {
        double p, m;
        fscanf(in, "%lf%lf", &p, &m);
        answer += p * m;
    }
    answer /= (100 * (double)n);
 
    fprintf(out, "%lf", answer );
 
 
    return 0;
}
