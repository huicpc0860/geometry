\section{回文子串Manacher(O(n))算法}
\begin{lstlisting}
#define N 400010
char s[N];
int p[2*N];

bool cmp(int a,int b){
    if(a<0)return 0;
    if(((a|b)&1)==0)return 1;
    return s[a>>1]==s[b>>1];
}

void mana(int n) {//#a#
    int mx = 0, id;
    for (int i = 0; i <= n; i++) {
        p[i] = i < mx ? min(p[(id << 1) - i], mx - i) : 1;
        while (cmp(i - p[i],i + p[i]))p[i]++;
        if (i + p[i] > mx) {
            mx = i + p[i];
            id = i;
        }
    }
}
\end{lstlisting}
\subsection{查询区间[l,r]的最长回文子串}
二分+RMQ
\begin{lstlisting}
struct RMQ {//下标由0开始
    int R[32], dp[20][N], n;

    RMQ() {
        for (int i = 0; R[i] = 1 << i, R[i] < N; i++);
    }

    void RM(int *a, int n) {
        for (int i = 0; i < n; i++)dp[0][i] = a[i];
        for (int i = 1; R[i] <= n; i++)
            for (int j = 0; j + R[i] <= n; j++)
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j + R[i - 1]]);
    }

    int Q(int s, int e) {
        int i = 0, h = (e - s + 1) >> 1;
        while (R[i] <= h)i++;
        return max(dp[i][e - R[i] + 1], dp[i][s]);
    }
} rmq;

int main() {
    int T,n;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s);
		n = strlen(s) << 1;
        mana(n);
        rmq.RM(p, n);
        int q;
        scanf("%d", &q);
        while (q--) {
            int a, b;
            scanf("%d%d", &a, &b);
            a = (a << 1) - 2;
            b = (b << 1);
            int l = 0, r = (b - a) / 2 + 1;
            while (l < r) {
                int m = (l + r) >> 1;
                if (rmq.Q(a + m, b - m) - 1 < m)r = m;
                else l = m + 1;
            }
            printf("%d\n", l - 1);
        }
    }
}
\end{lstlisting}
\subsection{求不同回文子串的个数}
不同串长的冲突问题，双关键字hash。
\begin{lstlisting}
#include <cstdio>
#include<algorithm>
#include <set>
using namespace std;
typedef long long LL;
#define clr(a) memset(a,0,sizeof(a))
#define N 100100
#define mod 100000007
char s[N];
int n,cnt;
LL c[N],z[N];
int p[N<<1];
set<int>h[N];
inline void judge(int a,int b){
    if(((a|b)&1)==0)return;
    a>>=1,b>>=1;
    int hash=(c[b+1]-c[a]+mod)*z[n-a]%mod;
    if(h[b-a].size()==0||h[b-a].find(hash)==h[b-a].end()){
        h[b-a].insert(hash);
        cnt++;
    }
}
inline bool cmp(int a,int b){
    if(a<0)return 0;
    if(((a|b)&1)==0)return 1;
    return s[a>>1]==s[b>>1];
}
void mana(int n){
    int mx=0,id;
    for(int i=0;i<n;i++){
        p[i]=i<mx?min(p[(id<<1)-i],mx-i):1;
        judge(i-p[i]+1,i+p[i]-1);
        while(cmp(i-p[i],i+p[i])){
            judge(i-p[i],i+p[i]);
            p[i]++;
        }
        if(i+p[i]>mx){
            mx=i+p[i];
            id=i;
        }
    }
}
int main(){
    z[0]=1;
    z[1]=29;
    for(int i=2;i<N;i++)z[i]=(z[i-1]*z[1])%mod;
    int T,cas=1;
    scanf("%d\n",&T);
    while(T--){
        for(int i=0;i<n;i++)h[i].clear();
        n=0;
        while(s[n]=getchar(),s[n]!='\n')n++;
        cnt=0;
        c[0]=0;
        for(int i=0;i<n;i++){
            c[i+1]=((s[i]-'a'+1)*z[i]+c[i])%mod;
        }
        mana(n<<1);
        printf("Case #%d: %d\n",cas++,cnt);
    }
    return 0;
}
\end{lstlisting}