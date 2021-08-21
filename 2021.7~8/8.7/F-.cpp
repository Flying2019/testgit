#include<bits/stdc++.h>
using namespace std;
typedef long double db;

const int n = 1 << 8;
void add(db a[][n + 1], int u, int v, db K) {
    for (int i = 0; i <= n; i++) a[v][i] += K * a[u][i];
}

int id[n];

void Gauss(db a[][n + 1]) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n && abs(a[i][i]) < 1e-10; j++)
            if (abs(a[j][i]) > 1e-10) swap(a[i], a[j]), swap(id[i], id[j]);
        for (int j = i + 1; j < n; j++) {
            db K = a[j][i] / a[i][i];
            add(a, i, j, -K);
        }
    }
}

db a[n][n + 1];
int inline c(int s, int i) { return (s >> i) & 1; }
db f[n];

int main() {
    for (int i = 0; i < 1 << 8; i++) id[i] = i;
    for (int s = 0; s < 1 << 8; s++) {
        a[s][s] = 1;
        int ss = s, len = 8;
        while (1) {
            int u = -1;
            for (int i = 0; i < len - 2; i++)
                if (c(ss, i) == c(ss, i + 1) && c(ss, i + 1) == c(ss, i + 2))
                    { u = i; break; }
            if (u == -1) break;
            int v = u;
            while (v < len && c(ss, v) == c(ss, u)) v++;
            a[ss][1 << 8] += (v - u) * (v - u);
            int ss0 = ss & ((1 << u) - 1);
            for (int i = v; i < len; i++)
                ss0 |= c(ss, i) << (u + i - v);
            len -= v - u;
            ss = ss0;
        }
        if (len == 8) continue;
        int L = 1 << (8 - len); db iL = 1.0 / L;
        for (int s1 = 0; s1 < L; s1++)
            a[s][ss | (s1 << len)] += -iL;
    }
    // for (int i = 0; i < 1 << 8; i++) {
    //     for (int j = 0; j < 1 << 8; j++)
    //         printf("%.6Lf ", a[i][j]);
    //     printf("\n");
    // }

    Gauss(a);
    for (int s = n - 1; s >= 0; s--) {
        f[id[s]] = a[s][1 << 8];
        for (int s0 = s + 1; s0 < 1 << 8; s0++)
            f[id[s]] -= a[s][s0] * f[id[s0]];
        f[id[s]] /= a[s][s];
    }

    int T; scanf("%d", &T);
    while (T--) {
        int s = 0;
        for (int i = 0; i < 8; i++) {
            int x; scanf("%1d", &x);
            s |= x << i;
        }
        printf("%.6Lf\n", f[s]);
    }
}