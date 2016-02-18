\section{后缀数组}
\subsection{倍增算法}
rk从0开始\\
sa从1开始,因为最后一个字符(最小的)排在第0位\\
hi从2开始,因为表示的是sa[i-1]和sa[i]\\
sa[i]排第i位的后缀的下标\\
rk[i]下标为i的后缀排第几\\
\begin{lstlisting}
#define N 200010
int dp[20][N],R[32];
struct RMQ {//下标由0开始,注意min和max
    RMQ(){for(int i=0;R[i]=1<<i,R[i]<N;i++);}
    void RM(int *a,int n) {
        for(int i=0;i<n;i++)dp[0][i]=a[i];
        for(int i=1;R[i]<=n;i++)
            for(int j=0;j+R[i]<=n;j++)
                dp[i][j]=min(dp[i-1][j],dp[i-1][j+R[i-1]]);
    }
    int Q(int s,int e){
        int i=0,h=(e-s+1)>>1;
        while(R[i]<=h)i++;
        return min(dp[i][e-R[i]+1],dp[i][s]);
    }
} rmq;
#define inc(i,n) for(i=0;i<n;i++)
#define dec(i,n) for(i=n-1;i>=0;i--)
int bu[N],X[N],Y[N],sa[N],rk[N],hi[N],r[N];
bool cmp(int *r,int a,int b,int l){return r[a]==r[b]&&r[a+l]==r[b+l];}
#define busort(t)\
inc(i,m)bu[i]=0;\
inc(i,n)bu[x[t]]++;\
inc(i,m)bu[i+1]+=bu[i];\
dec(i,n)sa[--bu[x[t]]]=t;
//r[n-1]=0,suffix(r,n,200)
void suffix(int *r,int n,int m){
    int i,j,p,*x=X,*y=Y,*t;
    inc(i,n)x[i]=r[i];
    busort(i);
    for(j=1,p=1;p<n;m=p,j<<=1){
        inc(p,j)y[p]=n-j+p;//bug
        inc(i,n)if(sa[i]>=j)y[p++]=sa[i]-j;
        busort(y[i]);
        for(t=x,x=y,y=t,x[sa[0]]=0,i=1,p=1;i<n;i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
    inc(i,n)rk[sa[i]]=i;//calhigh()
    for(int i=0,k=0;i<n-1;hi[rk[i++]]=k)
        for(k?k--:0,j=sa[rk[i]-1];r[i+k]==r[j+k];k++);
    rmq.RM(hi,n);
}
int lcp(int a,int b){
    a=rk[a],b=rk[b];
    if(a>b)swap(a,b);
    return rmq.Q(++a,b);
}
/subsection{版本二，处理字符集很大的情况}
bool sp(int a,int b){rt r[a]<r[b];}
void SA(int *r,int n){
    int m,i,j,p,*x=X,*y=Y,*t;
    inc(i,n)x[i]=r[i],sa[i]=i;
    sort(sa,sa+n,sp);
    for(j=1;;j<<=1){
        for(t=x,x=y,y=t,x[sa[0]]=0,i=1,p=1;i<n;i++)
           x[sa[i]]=cmp(y,sa[i-1],sa[i],j>>1)?p-1:p++;
        m=p;if(p>=n)break;
        inc(p,j)y[p]=n-j+p;
        inc(i,n)if(sa[i]>=j)y[p++]=sa[i]-j;
        inc(i,m)bu[i]=0;
        inc(i,n)bu[x[y[i]]]++;
        inc(i,m)bu[i+1]+=bu[i];
        dec(i,n)sa[--bu[x[y[i]]]]=y[i];
    }
}
\end{lstlisting}
\subsection{不同回文子串的个数}
\begin{lstlisting}
#define ff(i,n) for(int i=0;i<n;i++)
char s[N];
int main(){
    int T,cas=1;
    scanf("%d",&T);
    while(T--){
        scanf("%s",s);
        int n=strlen(s);
        ff(i,n)r[i]=s[i];
        r[n]=127;
        ff(i,n)r[1+i+n]=r[n-i-1];
        n=n*2+2;
        r[n-1]=0;
        suffix(r,n,128);
        int da[2]={},cnt=0;
        ff(i,n)ff(j,2){
            int res=lcp(sa[i],n-sa[i]-1-j);//最长公共前缀
            if(da[j]>hi[i])da[j]=hi[i];
            cnt+=max(0,res-da[j]);
            if(da[j]<res)da[j]=res;
        }
        printf("Case #%d: %d\n",cas++,cnt);
    }
    return 0;
}
\end{lstlisting}
\subsection{不同子矩阵的个数}
不是整数类型，无法用桶放，第一次的排序所用快排
\begin{lstlisting}
#include <stdio.h>
#include <algorithm>
using namespace std;
#define N 130
#define N2 N*N
#define rt return
char s[N];
int a[N][N];
const long long p=117,mod=1000000007;
#define inc(i,n) for(i=0;i<n;i++)
#define dec(i,n) for(i=n-1;i>=0;i--)
typedef pair<int,int> Hash;
Hash r[N2];
int bu[N2],X[N2],Y[N2],sa[N2],rk[N2],hi[N2];
bool cmp(int *r,int a,int b,int l){rt r[a]==r[b]&&r[a+l]==r[b+l];}
bool sp(int a,int b){rt r[a]<r[b];}
void SA(int n){
    int m,i,j,p,*x=X,*y=Y,*t;
    inc(i,n)sa[i]=i;
    sort(sa,sa+n,sp);
    for(i=1,p=1,x[sa[0]]=0;i<n;i++)
        x[sa[i]]=(r[sa[i-1]]==r[sa[i]]?p-1:p++);
    for(j=1,m=p,p=1;p<n;m=p,j<<=1){
        inc(p,j)y[p]=n-j+p;
        inc(i,n)if(sa[i]>=j)y[p++]=sa[i]-j;
        inc(i,m)bu[i]=0;
        inc(i,n)bu[x[y[i]]]++;
        inc(i,m)bu[i+1]+=bu[i];
        dec(i,n)sa[--bu[x[y[i]]]]=y[i];
        for(t=x,x=y,y=t,x[sa[0]]=0,i=1,p=1;i<n;i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
    inc(i,n)rk[sa[i]]=i;
    for(int i=0,k=0;i<n-1;hi[rk[i++]]=k)
        for(k?k--:0,j=sa[rk[i]-1];r[i+k]==r[j+k];k++);
}
int main(){
    int T,n,m,cas=1;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++){
            scanf("%s",s);
            for(int j=0;j<m;j++)a[i][j]=s[j]-'A'+1;
        }
        int cnt=0;
        for(int h=0;h<n;h++){
            int sz=0;
            for(int i=0;i+h<n;i++,sz++){
                for(int j=0;j<m;j++,sz++){
                    if(h==0)r[sz]=make_pair(a[i+h][j],a[i+h][j]);
                    else r[sz]=make_pair((p*r[sz].first+a[i+h][j])%mod,r[sz].second+a[i+h][j]);
                }
                if(h==0)r[sz]=make_pair(mod+i,mod+i);
            }
            r[sz-1]=make_pair(0,0);
            SA(sz);
            cnt+=(1+m)*m/2*(n-h);
            for(int i=2;i<sz;i++)cnt-=hi[i];
        }
        printf("Case #%d: %d\n",cas++,cnt);
    }
}
\end{lstlisting}
\subsection{DC3算法}
\begin{lstlisting}
#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
int wa[maxn],wb[maxn],wv[maxn],ws[maxn];
int c0(int *r,int a,int b)
{return r[a]==r[b]&&r[a+1]==r[b+1]&&r[a+2]==r[b+2];}
int c12(int k,int *r,int a,int b)
{if(k==2) return r[a]<r[b]||r[a]==r[b]&&c12(1,r,a+1,b+1);
 else return r[a]<r[b]||r[a]==r[b]&&wv[a+1]<wv[b+1];}
void sort(int *r,int *a,int *b,int n,int m)
{
     int i;
     for(i=0;i<n;i++) wv[i]=r[a[i]];
     for(i=0;i<m;i++) ws[i]=0;
     for(i=0;i<n;i++) ws[wv[i]]++;
     for(i=1;i<m;i++) ws[i]+=ws[i-1];
     for(i=n-1;i>=0;i--) b[--ws[wv[i]]]=a[i];
     return;
}
void dc3(int *r,int *sa,int n,int m)
{
     int i,j,*rn=r+n,*san=sa+n,ta=0,tb=(n+1)/3,tbc=0,p;
     r[n]=r[n+1]=0;
     for(i=0;i<n;i++) if(i%3!=0) wa[tbc++]=i;
     sort(r+2,wa,wb,tbc,m);
     sort(r+1,wb,wa,tbc,m);
     sort(r,wa,wb,tbc,m);
     for(p=1,rn[F(wb[0])]=0,i=1;i<tbc;i++)
     rn[F(wb[i])]=c0(r,wb[i-1],wb[i])?p-1:p++;
     if(p<tbc) dc3(rn,san,tbc,p);
     else for(i=0;i<tbc;i++) san[rn[i]]=i;
     for(i=0;i<tbc;i++) if(san[i]<tb) wb[ta++]=san[i]*3;
     if(n%3==1) wb[ta++]=n-1;
     sort(r,wb,wa,ta,m);
     for(i=0;i<tbc;i++) wv[wb[i]=G(san[i])]=i;
     for(i=0,j=0,p=0;i<ta && j<tbc;p++)
     sa[p]=c12(wb[j]%3,r,wa[i],wb[j])?wa[i++]:wb[j++];
     for(;i<ta;p++) sa[p]=wa[i++];
     for(;j<tbc;p++) sa[p]=wb[j++];
     return;
}
\end{lstlisting}