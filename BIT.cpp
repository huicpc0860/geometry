\section{树状数组}
\subsection{树状数组上二分查找}
记录数值为i的数的个数，利用树状数组查找第k大的数。\\
\begin{lstlisting}
#define N 100010
#define max(a,b) (a>b?a:b)
int n,T,a[N],c[N],cas=1;
void update(int i,int x){
    while(i<=n){
        c[i]+=x;
        i+=i&-i;
    }
}
void add(int i,int x){
    while(i<=n){
        c[i]=max(c[i],x);
        i+=i&-i;
    }
}
int get(int i){
    int ans=0;
    while(i){
       ans=max(c[i],ans);
       i-=i&-i;
    }
    return ans;
}
int kth(int k){
    int ret=0;
    for(int i=17;i>=0;i--){//注意范围
        ret+=(1<<i);
        if(ret>n||c[ret]>=k)ret-=(1<<i);
        else k-=c[ret];
    }
    return ret+1;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=n;i>0;i--)c[i]=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            update(i,1);
        }
        for(int i=n;i>0;i--){
            a[i]=kth(a[i]+1);
            update(a[i],-1);
        }
        printf("Case #%d:\n",cas++);
        for(int i=n;i>0;i--)c[i]=0;
        int ret=0;
        for(int i=1;i<=n;i++){
            int t=get(a[i])+1;
            if(t>ret)ret=t;
            add(a[i],t);
            printf("%d\n",ret);
        }
        puts("");
    }
    return 0;
}
\end{lstlisting}
\subsection{多维树状数组}
\begin{lstlisting}
#define N 110
using namespace std;
int c[N][N][N];
int n; //important
#define dec(i,x) for(int i=x;i>0;i-=i&-i)
#define inc(i,x) for(int i=x;i<=n;i+=i&-i)

void update(int x, int y, int z) {
    dec(i, x)dec(j, y)dec(k, z)c[i][j][k] = !c[i][j][k];
}

int sum(int x, int y, int z) {
    int s = 0;
    inc(i, x)inc(j, y)inc(k, z)s ^= c[i][j][k];
    return s;
}

int main() {
    int m, op, x1, y1, z1, x2, y2, z2, ans;
    while (~scanf("%d%d", &n, &m)) {
        memset(c, 0, sizeof (c));
        while (m--) {
            scanf("%d%d%d%d", &op, &x1, &y1, &z1);
            if (op == 1) {
                x1--, y1--, z1--;
                scanf("%d%d%d", &x2, &y2, &z2);
                update(x2, y2, z2);
                update(x2, y1, z2);
                update(x1, y2, z2);
                update(x2, y2, z1);
				
                update(x1, y1, z2);
                update(x2, y1, z1);
                update(x1, y2, z1);
                update(x1, y1, z1);
            } else {
                ans = sum(x1, y1, z1);
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}
\end{lstlisting}
\subsection{区间更新，区间求和}
\begin{lstlisting}
struct BIT{//[l,r]
    int n;
    LL a[N],b[N];
    BIT(int x=0){
        n=x+2;
        for(int i=n;i>0;i--)a[i]=b[i]=0;
    }
    void add1(int x,LL d){
        while(x<=n){a[x]+=d;x+=x&-x;}
    }
    LL cal1(int x){
        LL s=0;
        while(x){s+=a[x];x-=x&-x;}
        return s;
    }
    int add2(int x,LL d){
        while(x){b[x]+=d;x-=x&-x;}
    }
    LL cal2(int x){
        LL s=0;
        while(x<=n){s+=b[x];x+=x&-x;}
        return s;
    }
    void add3(int x,LL d){
        add1(x,d*x);add2(x-1,d);
    }
    LL cal3(int x){
        return cal1(x)+cal2(x)*x;
    }
    void add(int l,int r,LL d){
        l+=2;r+=2;
        add3(l-1,-d);add3(r,d);
    }
    LL cal(int l,int r){
        l+=2;r+=2;
        return cal3(r)-cal3(l-1);
    }
};// BIT bit(n);
\end{lstlisting}