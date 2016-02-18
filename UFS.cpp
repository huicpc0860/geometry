\section{并查集}
按秩合并，一般不用
void Union(int a,int b){
	a=Find(a);b=Find(b);
	if(a==b) return;
	if(r[a]>r[b]) p[b]=a;
	else{
		p[a]=b;
		if(r[a]==r[b]) r[b]++;
	}
}
\subsection{判奇圈，A Bug's Life}
\begin{lstlisting}
int p[3000];
bool r[3000];

int find(int x) {
    if (x != p[x]) {
        int t = p[x];
        p[x] = find(p[x]);
        r[x] = r[x]^r[t];
    }
    return p[x];
}
int main() {
    int t, n, m, a, b, x, y;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        bool f = 0;
        scanf("%d%d", &n, &m);
        for (int j = 1; j <= n; j++)p[j] = j, r[j] = 0;
        while (m--) {
            scanf("%d%d", &a, &b);  
            if (!f) {
                x = find(a), y = find(b);
                if (x == y) {
                    if (r[a] == r[b])f = 1;
                } else {
                    p[x] = y;
                    r[x] = !(r[a]^r[b]);
                }
            }
        }
        printf("Scenario #%d:\n", i);
        if (f)puts("Suspicious bugs found!\n");
        else puts("No suspicious bugs found!\n");
    }
    return 0;
}
\end{lstlisting}
\subsection{食物链}
\begin{lstlisting}
int p[50001],r[50001]={0};
int find(int x){
	if(p[x]!=x){
		int t=p[x];
		p[x]=find(p[x]);
		r[x]=(r[x]+r[t])%3;
	}
	return p[x];
}
int main(){
	int n,k,d,a,b,t=0;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)p[i]=i;
	while(k--){
		scanf("%d%d%d",&d,&a,&b);
		if(a>n||b>n){
			t++;
			continue;
		}
		int x=find(a),y=find(b);
		if(x==y)t+=((r[b]+d+2)%3!=r[a]);
		else {
			p[x]=y;
			r[x]=(r[b]-r[a]+2+d)%3;
		}
	}
	printf("%d\n",t);
	return 0;
}
\end{lstlisting}
\subsection{简单区间合并}
\begin{lstlisting}
int p[10000001];
int find(int x){
    if(x!=p[x])x=find(p[x]);
    return p[x];
}
LL mpow(LL x, LL k){
    LL ret=1;
    while(k){
        if(k&1)ret=(ret*x)%1000000007;
        k>>=1;
        x=(x*x)%1000000007;
    }
    return ret;
}
int main(){
    int n,m,x,y,l,r;
    while(~scanf("%d%d",&n,&m)){
        for(int i=n+1;i>0;i--)p[i]=i;
        int ans=n;
        while(m--){
            scanf("%d%d",&l,&r);
            x=find(l);
            y=find(r+1);
            if(x!=y){
                ans--;
                p[x]=y;
            }
        }
        printf("%lld\n",mpow(26,ans));
    }
    return 0;
}
\end{lstlisting}
\subsection{区间染色}
求不可见颜色数
\begin{lstlisting}
#define N 10000
struct rectan{
    int l,b,r,t;
    void get(){scanf("%d%d%d%d",&l,&b,&r,&t);}
}rec[N];
int p[N],cor[N],ans[N];
void init(int x){
    for(int i=1;i<=x;i++){
        p[i]=i+1;
        cor[i]=0;
    }
}
int color(int l,int r,int c){
    if(!cor[l])cor[l]=c;
    if(p[l]<=r){
        p[l]=color(p[l],r,c);
    }
    return p[l];
}
int main(){
    int r,c,m,x,a,y,b;
    while(~scanf("%d%d%d",&c,&r,&m)){
        for(int i=1;i<=m;i++){
            ans[i]=0;
            rec[i].get();
        }
        for(int i=1;i<=r;i++){
            init(c);
            for(int j=m;j>0;j--)
                if(rec[j].b<=i&&rec[j].t>=i)
                    color(rec[j].l,rec[j].r,j);
            for(int j=c;j>0;j--)ans[cor[j]]=1;
        }
        int an=0;
        for(int i=m;i>0;i--)if(!ans[i])an++;
        printf("%d\n",an);
    }
}
\end{lstlisting}