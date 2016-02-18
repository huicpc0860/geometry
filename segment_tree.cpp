\section{线段树}
\subsection{矩形覆盖k层面积}
\begin{lstlisting}
#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define N 30010
int e;
int hush[N * 2];
#define get_id(x) (lower_bound(hush+1,hush+n,x)-hush)

struct event {
    int x, y1, y2, c;

    event() {
    }

    event(int x, int y1, int y2, int c) : x(x), y1(y1), y2(y2), c(c) {
    }

    bool operator<(const event & p)const {
        return x < p.x;
    }
} eve[N * 2];
int c[N * 6][11] = {};
int L, R, C, n, k;

void insert(int l, int r, int i) {
    int m = (l + r) >> 1, lc = i << 1, rc = lc + 1;
    if (L <= l && r <= R) {
        c[i][0] += C;
    } else {
        if (L < m)insert(l, m, lc);
        if (R > m)insert(m, r, rc);
    }
    for (int j = 1; j <= k; j++) {
        if (c[i][0] >= j)c[i][j] = hush[r] - hush[l];
        else if (l + 1 == r)c[i][j] = 0;
        else c[i][j] = c[lc][j - c[i][0]] + c[rc][j - c[i][0]];
    }
}

void insert(event & e) {
    L = get_id(e.y1), R = get_id(e.y2);
    C = e.c;
    insert(1, n, 1);
}

int main() {
    int T, cas = 1;
    scanf("%d", &T);
    while (T--) {
        n = 1;
        e = 0;
        int m;
        scanf("%d%d", &m, &k);
        for (int i = 0; i < m; i++) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            x2++, y2++;
            hush[n++] = y1;
            hush[n++] = y2;
            eve[e++] = event(x1, y1, y2, 1);
            eve[e++] = event(x2, y1, y2, -1);
        }
        sort(hush + 1, hush + n);
        n = unique(hush + 1, hush + n) - hush;
        sort(eve, eve + e);
        long long ans = 0;
        for (int i = 0; i < e; i++) {
            insert(eve[i]);
            ans += 1ll * c[1][k]*(eve[i + 1].x - eve[i].x);
        }
        cout << "Case " << (cas++) << ": " << ans << endl;
    }
    return 0;
}
\end{lstlisting}