\section{老模板，主要是DP}
\begin{lstlisting}
//背包变形，有交易限制
int f0[100010],f1[100010],cost[60],num[60],c[60][110],w[60][110];
int main(){
    int n,v,tp,i,j,s;
    while(scanf("%d%d",&n,&v)!=EOF){
        memset(f0,0,sizeof(f0[0])*(v+1));
        for(i=0;i<n;i++){
            scanf("%d%d",&cost[i],&num[i]);
            for(j=0;j<num[i];j++)
                scanf("%d%d",&c[i][j],&w[i][j]);
        }
        for(i=0;i<n;i++){
            memset(f1,-63,sizeof(f1[0])*(v+1));
            for(j=0;j<num[i];j++)
                for(s=v;s>=c[i][j];s--){
                    tp=s-c[i][j];
                    if(f1[s]<f1[tp]+w[i][j])f1[s]=f1[tp]+w[i][j];
                    tp-=cost[i];
                    if(tp>=0&&f1[s]<f0[tp]+w[i][j])f1[s]=f0[tp]+w[i][j];
                }
            for(j=0;j<=v;j++)
                if(f0[j]<f1[j])f0[j]=f1[j];
        }
        int ans=0;
        for(i=0;i<=v;i++)
            if(ans<f0[i])ans=f0[i];
        printf("%d\n",ans);
    }
    return 0;
}
//背包求组合数量
#include<stdio.h>
#include<string.h>
int p[2261],f[4][20010]={0};
int g[20005];
void sieve(){
    int i,j;
    for(i=3;i*i<=20000;i+=2)
        if(g[i]==0){
            for(j=i*i;j<=20000;j+=i)
                g[j]=1;
        }
    j=0;
    for(i=3;i<=20000;i+=2)
        if(g[i]==0)
            p[j++]=i;
}
int main(){
    int n,i,ans,j,x,y;
    sieve();
    f[0][0]=1;
    for(int i=0;i<2261;i++)
        for(int j=3;j>0;j--)
            for(int k=20000;k>=p[i];k--)
                    f[j][k]+=f[j-1][k-p[i]];
    while(scanf("%d",&y)!=EOF){
        if(y&1)printf("%d\n",f[3][y]);
        else printf("%d\n",f[2][y]);
    }
    return 0;
}
//排序背包，手里钱钱数不能少于一定值，与转移顺序有关
#include <stdio.h>
#include <string.h>
#include <algorithm>
#define N 5001
using namespace std;
int f[N];
struct bag{
    int p,q,v;
}b[N];
bool operator <(bag x,bag y){
    return (x.q-x.p)<(y.q-y.p);
}
int main(){
    int n,m;
    while(~scanf("%d%d",&n,&m)){
        for(int i=0;i<=m;i++)f[i]=0;
        for(int i=0;i<n;i++)
            scanf("%d%d%d",&b[i].p,&b[i].q,&b[i].v);
        sort(b,b+n);
        for(int i=0;i<n;i++)
            for(int j=m;j>=b[i].q;j--){
                int t=f[j-b[i].p]+b[i].v;
                if(f[j]<t)f[j]=t;
            }
        printf("%d\n",f[m]);
    }
    return 0;
}
//单调队列
#include <stdio.h>
#define N 1000010
#define max(a,b) (a>b?a:b)
int q1[N],q2[N],id1[N],id2[N];
int main(){
    int n,m,k,t;
    while(~scanf("%d%d%d",&n,&m,&k)){
        int l1=0,l2=0,r1=-1,r2=-1,ans=0,flag=0;
        for(int i=0;i<n;i++){
            scanf("%d",&t);
            while(l1<=r1&&q1[r1]>t)r1--;
            q1[++r1]=t,id1[r1]=i;
            while(l2<=r2&&q2[r2]<t)r2--;
            q2[++r2]=t,id2[r2]=i;
            if(q2[l2]-q1[l1]<m||q2[l2]-q1[l1]>k){
                ans=max(ans,i-flag);
                if(q2[l2]-q1[l1]>k){
                    flag++;
                    if(l1<=r1&&id1[l1]<flag)l1++;
                    if(l2<=r2&&id2[l2]<flag)l2++;
                }
            }
        }
        ans=max(ans,n-flag);
        if(m>k)ans=0;
        printf("%d\n",ans);
    }
    return 0;
}
//求树中最长路条数
#include <stdio.h>
#include <vector>
using namespace std;
#define N 10010
int n[N], v[N], tn[N], tv[N], f[N], len[N], ans_n, ans_v;

struct node {
    int cost, next;

    node() {
    }

    node(int x, int y) : cost(x), next(y) {
    }
};
vector <node> t[N];

void dfs(int x) {
    f[x] = 1;
    int s1 = 1, s2 = 1, s3 = 1, m1 = 0, m2 = 0, flag = 0;
    for (int i = 0; i < t[x].size(); i++) {
        int j = t[x][i].next;
        if (!f[j]) {
            dfs(j);
            v[j] += t[x][i].cost;
            if (v[j] > m1)m2 = m1, s2 = s1, m1 = v[j], s1 = n[j], s3 = s1 * s1, flag = 1;
            else if (v[j] == m1)s1 += n[j], s3 += n[j] * n[j], flag = 0;
            else if (v[j] > m2)m2 = v[j], s2 = n[j];
            else if (v[j] == m2)s2 += n[j];
        }
    }
    if (flag) tn[x] = s1 * s2, tv[x] = m1 + m2;
    else tn[x] = (s1 * s1 - s3) / 2, tv[x] = m1 + m1;
    n[x] = s1, v[x] = m1;
    if (tv[x] > ans_v)ans_v = tv[x], ans_n = tn[x];
    else if (tv[x] == ans_v)ans_n += tn[x];
}

int main() {
    int m, x, y, a;
    while (~scanf("%d", &m)) {
        for (int i = 1; i <= m; i++)t[i].clear(), f[i] = 0;
        for (int i = 1; i < m; i++) {
            scanf("%d%d%d", &x, &y, &a);
            t[x].push_back(node(a, y));
            t[y].push_back(node(a, x));
        }
        ans_v = ans_n = 0;
        dfs(1);
        printf("%d %d\n", ans_v, ans_n);
    }
    return 0;
}
//各种背包
#include <stdio.h>
#include <string.h>
#define max(a,b) ((a)>(b)?(a):(b))
int n,v,m,t,w,c,f[101][101];
int main(){
    while(~scanf("%d%d",&n,&v)){
        memset(f,-31,sizeof(f));
        f[0][0]=0;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&m,&t);
            while(m--){
                scanf("%d%d",&w,&c);
                if(t)for(int j=0;j<=v;j++)
                    f[i][j]=max(f[i][j],f[i-1][j]);
                for(int j=v;j>=w;j--){
                    if(t==0)f[i][j]=max(f[i][j],max(f[i-1][j-w],f[i][j-w])+c);
                    else if(t==1)f[i][j]=max(f[i][j],f[i-1][j-w]+c);
                    else f[i][j]=max(f[i][j],f[i][j-w]+c);
                }
            }
        }
        int ans=-1;
        for(int i=0;i<=v;i++)ans=max(ans,f[n][i]);
        printf("%d\n",ans);
    }
    return 0;
}
//以差值做状态
#include <stdio.h>
#include <string.h>
int T,cs=1,n,c,f[101][2001];
inline int max(int a,int b,int c){
    a=(a>c)?a:c;
    return a>b?a:b;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        memset(f,-31,sizeof(f));
        f[0][0]=0;
        int s=0,flag=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&c);
            s+=c;
            if(!c)flag=1;
            for(int j=0;j<=s;j++)
                if(c<j)
                    f[i][j]=max(f[i-1][j],f[i-1][j+c]+c,f[i-1][j-c]);
                else
                    f[i][j]=max(f[i-1][j],f[i-1][c-j]+c-j,f[i-1][j+c]+c);
        }
        if(!f[n][0]&&!flag)f[n][0]=-1;
        printf("Case %d: %d\n",cs++,f[n][0]);
    }
    return 0;
}
//四边不等等式
#include<iostream>
using namespace std;
const int INF=1000000000;
const int maxn=1005;
int dp[maxn][maxn],s[maxn][maxn],a[maxn],n,x[maxn],y[maxn];
typedef struct point
{
    int x,y;
    point(){};
    point(int xx,int yy){x=xx;y=yy;}
    }point;
inline int cost(point a,point b){return abs(a.x-b.x)+abs(a.y-b.y);}
int main()
{
    int i,j,k,t,w;
    while(scanf("%d",&n)!=EOF)
    {
          for(i=1;i<=n;i++)scanf("%d%d",&x[i],&y[i]);
          for(i=1;i<=n;i++){dp[i][i]=0;s[i][i]=i;}

          for(t=2;t<=n;t++)
          {
              for(i=1;i<=n-t+1;i++)
              {
                  j=i+t-1;dp[i][j]=INF;
                  for(k=s[i][j-1];k<=s[i+1][j];k++)
                  {
                      w=cost(point(x[i],y[k-1]),point(x[k],y[j]));
                      if(dp[i][j]>dp[i][k-1]+dp[k][j]+w)
                      {
                         dp[i][j]=dp[i][k-1]+dp[k][j]+w;
                         s[i][j]=k;
                         }
                      }
                  }
              }
          printf("%d\n",dp[1][n]);
          }
    return 0;
}
//24点
char s[4];
const int n=1<<4;
set<double>f[n];
set<double>::iterator ii,jj,it;
int main(){
    while(~scanf("%s",s)){
        for(int i=0;i<n;i++)f[i].clear();
        for(int i=0,t;i<4;i++){
            if(s[0]<='9'&&s[0]>'1')t=s[0]-'0';
            else if(s[0]=='1')t=10;
            else if(s[0]=='A')t=1;
            else if(s[0]=='J')t=11;
            else if(s[0]=='Q')t=12;
            else t=13;
            f[1<<i].insert(t);
            if(i<3)scanf("%s",s);
        }
        for(int i=1;i<n;i++)
            for(int j=1;j<=(i>>1);j++)
                if((i&j)==j){
                    for(ii=f[j].begin();ii!=f[j].end();ii++)
                        for(jj=f[i^j].begin();jj!=f[i^j].end();jj++){
                            f[i].insert(*ii+*jj);
                            f[i].insert(*ii-*jj);
                            f[i].insert(*jj-*ii);
                            f[i].insert((*ii)*(*jj));
                            if(*ii)f[i].insert(*jj/(*ii));
                            if(*jj)f[i].insert(*ii/(*jj));
                            if(i==n-1){
                                it=f[n-1].find(24);
                                if(it!=f[n-1].end()){
                                    puts("YES");
                                    goto loop;
                                }
                            }
                        }
                }
        puts("NO");
loop:   ;
    }
}
//树形多重背包，合并思想，up，down。the more the better
int v[201],f[201][201];
vector<int > t[201];
inline int max(int a,int b){
    return a>b?a:b;
}
void dfs(int i,int c){
    if(c<=0)return;
    for(int r=0;r<t[i].size();r++){
        int j=t[i][r];
        for(int k=0;k<c;k++)f[j][k]=f[i][k];
        dfs(j,c-1);
        for(int k=1;k<=c;k++)f[i][k]=max(f[i][k],f[j][k-1]+v[j]);
    }
}
int main(){
    int n,m,x;
    while(scanf("%d%d",&n,&m),n||m){
        for(int i=0;i<=n;i++){
            t[i].clear();
            for(int j=0;j<=m;j++)f[i][j]=0;
        }
        for(int i=1;i<=n;i++){
            scanf("%d%d",&x,&v[i]);
            t[x].push_back(i);
        }
        dfs(0,m);
        printf("%d\n",f[0][m]);
    }
    return 0;
}
//对叶子进行优化，省去叶子节点的空间
#include <stdio.h>
int c[100001],v[100001],f[501][10001],t[501],p[101000][2],q;
#define max(a,b) (a>b?a:b)
#define push(a,b) p[q][0]=b;p[q][1]=t[a];t[a]=q++
void dfs(int i,int s){
    if(s<1)return;
    int q=t[i];
    while(q){
        int j=p[q][0];
        if(j<501&&t[j]){
            for(int k=s-c[j];k>=0;k--)f[j][k]=f[i][k];
            dfs(j,s-c[j]);
            for(int k=c[j];k<=s;k++)f[i][k]=max(f[i][k],f[j][k-c[j]]+v[j]);
        }else for(int k=s;k>=c[j];k--)f[i][k]=max(f[i][k],f[i][k-c[j]]+v[j]);
        q=p[q][1];
    }
}
int main(){
    int n,g,x;
    while(~scanf("%d%d",&n,&g)){
        for(int i=500;i>=0;i--){
            for(int j=0;j<=g;j++)f[i][j]=0;
            t[i]=0;
        }
        q=1;
        for(int i=1;i<=n;i++){
            scanf("%d%d%d",&c[i],&v[i],&x);
            if(x==i)x=0;
            push(x,i);
        }
        dfs(0,g);
        printf("%d\n",f[0][g]);

    }
    return 0;
}
//状态压缩，彩色石头
int dp[101][6][160];
int max(int a,int b){return a>b?a:b;}
int main(){
    int m,k;
    while(scanf("%d%d",&m,&k),m||k){
        memset(dp,0,sizeof(dp));
        int n=1<<k,ans=0,a;
        for(int i=1;i<=m;i++){
            scanf("%d",&a);a--;
            for(int j=0;j<k;j++)
                for(int s=0;s<n;s++)
                    if((s>>a)&1){
                        if(a==j) dp[i][j][s]=max(dp[i][j][s],dp[i-1][j][s]+1);
                        else dp[i][j][s]=max(dp[i][j][s],dp[i-1][j][s]);
                    }
                    else{
                        dp[i][a][s|(1<<a)]=max(dp[i][a][s|(1<<a)],dp[i-1][j][s]+1);
                        dp[i][j][s]=max(dp[i][j][s],dp[i-1][j][s]);
                    }
        }
        for(int i=0;i<k;i++)
            for(int j=0;j<n;j++)
                ans=max(ans,dp[m][i][j]);
        printf("%d\n",m-ans);
    }
    return 0;
}
//状态压缩dp，瓷砖覆盖
const int N=1<<11;
__int64 y[N],x[N];
int n,m,t;
bool check(int x){
    while(x){
        if(x&1){
            x>>=1;
            if(x&1)x>>=1;
            else return 0;
        }else x>>=1;
    }
    return 1;
}
bool judge(int now,int last){
    int tmp=t&(~last);
    if((now&tmp)==tmp&&check(now-tmp))return 1;
    return 0;
}
int main(){
    while(scanf("%d%d",&n,&m),n||m){
        if((n&1)&&(m&1)){puts("0");continue;}
        if(n<m)n^=m,m^=n,n^=m;
        int s=1<<m;
        t=s-1;
        __int64 sum=0;
        for(int i=0;i<s;i++)y[i]=check(i);
        for(int i=1;i<n;i++){
            for(int j=0;j<s;j++)
                for(int k=0;k<s;k++)
                    if(judge(j,k))x[j]+=y[k];
            memcpy(y,x,sizeof(x[0])*s);
            memset(x,0,sizeof(x[0])*s);
        }
        for(int i=0;i<s;i++)
            if(judge(0,i))sum+=y[i];
        printf("%I64d\n",sum);
    }
    return 0;
}
//一个整数分解为 1，2,4,。。。这种 2 的倍数的分解方式有多少种。
int f[1000001]={0},t;
int main(){
	f[0]=1;
	scanf("%d",&t);
	for(int i=1;i<=t;i++){
		if(i&1)f[i]=f[i-1];
		else f[i]=f[i-2]+f[i>>1];
		if(f[i]>=1000000000)f[i]%=1000000000;
	}
	printf("%d\n",f[t]);
	return 0;
}
//最长公共子序列
int m,n,r[300],s[300];
char a[300],b[300];
int main(){
    while(scanf("%s%s",a,b)!=EOF){
        m=strlen(a);n=strlen(b);
        memset(r,0,sizeof(r));s[0]=0;
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++)
                if(a[i-1]==b[j-1]) s[j]=r[j-1]+1;
                    else s[j]=r[j]>s[j-1]?r[j]:s[j-1];
            for(int k=1;k<=n;k++)r[k]=s[k];
        }
        printf("%d\n",r[n]);
    }
    return 0;
}
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const LL oo=1ll<<60;
struct point{
    int x,y;
    void get(){scanf("%d%d",&x,&y);}
    bool operator<(const point &p)const{
        return x>p.x||x==p.x&&y>p.y;
    }
}a[50001],b[50001];
int s[101][50001];
LL f[101][50001];
//f[i][j]=min(f[i-1][k]+w(k+1,j))
//s[i-1][j]<=s[i][j]<=s[i][j+1]
int main(){
    int cnt,m,k;
    while(~scanf("%d%d",&cnt,&m)){
        for(int i=0;i<cnt;i++)b[i].get();
        sort(b,b+cnt);
        int n=0;
        a[++n]=b[0];
        for(int i=1;i<cnt;i++)
            if(b[i].y>a[n].y)
                a[++n]=b[i];
        for(int i=1;i<=m;i++)s[i][n+1]=n-1;
        for(int i=1;i<=n;i++){
            f[1][i]=(LL)a[1].x*a[i].y;
            s[1][i]=1;
        }
        for(int i=2;i<=m;i++)
            for(int j=n;j>=i;j--){
                f[i][j]=+oo;
                int l=max(s[i-1][j],i-1),r=min(s[i][j+1],j-1);
                for(int k=l;k<=r;k++){
                    LL t=f[i-1][k]+(LL)a[k+1].x*a[j].y;
                    if(f[i][j]>t){
                        f[i][j]=t;
                        s[i][j]=k;
                    }
                }
            }
        LL ans=+oo;
        for(int i=m;i>0;i--)
            ans=min(ans,f[i][n]);
        cout<<ans<<endl;
    }
    return 0;
}
\end{lstlisting}