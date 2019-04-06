#include <cstdio>
 
int main() {
    FILE *in, *out;
    in = fopen("lottery.in", "r");
    out = fopen("lottery.out", "w");
 
    int n, m;
    fscanf(in, "%d%d", &n, &m);
 
    double tmp, tmp2, answer = 0, win_prev = 1, money_prev ;
 
    for (int i = 0; i < (int)m; ++i) {
        fscanf(in, "%lf%lf", &tmp, &tmp2);
        answer += (tmp - 1)* money_prev/(win_prev * tmp) ;
        money_prev = tmp2;
        win_prev *= tmp;
 
    }
    answer += money_prev/win_prev;
 
    fprintf(out, "%.8lf", n - answer);
 
    return 0;
}
