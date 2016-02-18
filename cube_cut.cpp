\section{矩形切割}
\subsection{二分计数}
\begin{lstlisting}
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long LL;
#define D 2
struct cube{
    int s[D],e[D];
    int c;
    cube(){}
    cube(cube &t,int m,int c):c(c){
        for(int i=0;i<D;i++){
            s[i]=t.s[i]-m;
            e[i]=t.e[i]+m;
        }
    }
    LL area(cube &t){
        if(!cross(t))return 0;
        LL k=1;
        for(int i=0;i<D;i++)
            k*=(LL)(min(e[i],t.e[i])-max(s[i],t.s[i]));
        return k;
    }
    bool cross(cube &t){
        for(int i=0;i<D;i++)
            if(s[i]>=t.e[i]||e[i]<=t.s[i])return 0;
        return 1;
    }
    bool contains(cube &t){
        for(int i=0;i<D;i++)
            if(s[i]>t.s[i]||e[i]<t.e[i])return 0;
        return 1;
    }
}p[30],big;
cube c[1000],d[1000];
int q;
struct CUT{
    int cn,dn;
    void broke(cube &a,cube &b){
        cube t;
        for(int i=0;i<D;i++){
            if(b.s[i]>a.s[i]&&b.s[i]<a.e[i]){
                t=a;
                t.e[i]=b.s[i];
                d[dn++]=t;
                a.s[i]=b.s[i];
            }
            if(b.e[i]>a.s[i]&&b.e[i]<a.e[i]){
                t=a;
                t.s[i]=b.e[i];
                d[dn++]=t;
                a.e[i]=b.e[i];
            }
        }
    }
    void insert(cube &t){
        dn=0;
        for(int i=0;i<cn;i++){
            if(t.cross(c[i]))broke(c[i],t);
            else d[dn++]=c[i];
        }
        cn=0;
        c[cn++]=t;
        for(int i=0;i<dn;i++)c[cn++]=d[i];
    }
    void push(int m,int c){
        for(int i=0;i<q;i++){
            cube t(p[i],m,c);
            insert(t);
        }
    }
    LL area(cube &t){
        LL ans=0;
        for(int i=0;i<cn;i++)
           ans+=c[i].area(t);
        return ans;
    }
    void refush(){
        int n=0;
        for(int i=0;i<cn;i++)
            if(c[i].c)c[n++]=c[i];
        cn=n;
    }
}cut;
void solve(){
    LL n;
    cin>>n;
    int l=0,r=max(big.e[0],big.e[1]);
    while(l<r){
        cut.cn=0;
        int m=(l+r)>>1;
        cut.push(m,1);
        if(cut.area(big)-q<n)l=m+1;
        else r=m;
    }
    cut.cn=0;
    cut.push(l-1,1);
    n-=(cut.area(big)-q);
    cut.cn=0;
    cut.push(l,1);
    cut.push(l-1,0);
    cut.refush();
    cube res=big;
    l=0,r=big.e[1];
    while(l<r){
        res.e[1]=(l+r)>>1;
        if(cut.area(res)<n)l=res.e[1]+1;
        else r=res.e[1];
    }
    res.e[1]=l-1;
    n-=cut.area(res);
    res.s[1]=l-1;
    res.e[1]=l;
    l=0,r=big.e[0];
    while(l<r){
        res.e[0]=(l+r)>>1;
        if(cut.area(res)<n)l=res.e[0]+1;
        else r=res.e[0];
    }
    printf("%d %d\n",res.e[1],l);
}
int main(){
    while(scanf("%d%d%d",&big.e[1],&big.e[0],&q),big.e[0]||big.e[1]||q){
        big.s[0]=big.s[1]=0;
        for(int i=0;i<q;i++){
            for(int j=D-1;j>=0;j--){
                scanf("%d",&p[i].e[j]);
                p[i].s[j]=p[i].e[j]-1;
            }
        }
        int Q;
        scanf("%d",&Q);
        while(Q--)solve();
        puts("-");
    }
    return 0;
}
\end{lstlisting}