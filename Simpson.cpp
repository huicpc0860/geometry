\section{Simpson公式}
数据大时可以找事件点，数据小或事件点难以确定可以二分区间利用Simpson公式自适应找寻事件点。
\subsection{拟柱体剖分求体积}
x轴扫描面，求水平棱镜和竖直棱镜的体积交，离散x相邻x形状为拟柱体，点数少，所以O(n*n)处理,这种图形在之间的要特别注意两边的边界情况。\\
\begin{lstlisting}
#define Max(a,b) (a=((a)>(b)?(a):(b)))
#define Min(a,b) (a=((a)<(b)?(a):(b)))
const double eps=1e-8;
int sig(double x){
    return (x>eps)-(x<-eps);
}
struct pt{
    int x,y;
    void get(){
        scanf("%d%d",&x,&y);
    }
}a[110],b[110];
int na,nb;
inline double length(pt p[],int n,double x){
    double l=200,r=-200;
    for(int i=0;i<n;i++){
        pt a=p[i],b=p[i+1];
        if(a.x==b.x)continue;
        if(x+eps>a.x&&x<b.x+eps||x+eps>b.x&&x<a.x+eps){
            double y=1.0*(a.y-b.y)/(a.x-b.x)*(x-a.x)+a.y;
            Min(l,y);
            Max(r,y);
        }
    }
    if(l>r)return 0;
    return r-l;
}
inline double area(double x){
    return length(a,na,x)*length(b,nb,x);
}
int eve[200];
int main(){
    while(scanf("%d%d",&na,&nb),na||nb){
        int e=0;
        int l1=200,r1=-200,l2=200,r2=-200;
        for(int i=0;i<na;i++){
            a[i].get();
            Max(r1,a[i].x);
            Min(l1,a[i].x);
            eve[e++]=a[i].x;
        }
        for(int i=0;i<nb;i++){
            b[i].get();
            Max(r2,b[i].x);
            Min(l2,b[i].x);
            eve[e++]=b[i].x;
        }
        a[na]=a[0];
        b[nb]=b[0];
        int l=Max(l1,l2),r=Min(r1,r2);
        for(int i=0;i<e;i++){
            if(eve[i]<l||eve[i]>r)
                eve[i--]=eve[--e];
        }
        sort(eve,eve+e);
        e=unique(eve,eve+e)-eve;
        double v=0,s1=area(eve[0]);
        for(int i=1;i<e;i++){
            double s2=area(eve[i]);
            v+=(s1+s2+4*area((eve[i]+eve[i-1])*.5))*(eve[i]-eve[i-1]);
            s1=s2;
        }
        printf("%lf\n",v/6.0);
    }
    return 0;
}
\end{lstlisting}
\subsection{梯形剖分求面积}
也可以用拟柱体。
\begin{lstlisting}
struct seg{
    pt a,b;
    dd k;
    void get(){
        a.get();
        b.get();
        k=(b.y-a.y)/(b.x-a.x);
    }
    dd high(dd x){
        rt a.y+k*(x-a.x);
    }
    dd A2(){
        rt (a.y+b.y)*(b.x-a.x);
    }
}s[110];
int n,k;
dd length(dd x){
    dd low=0;
    for(int i=0;i<k;i++)
        if(x>s[i].a.x-eps&&x<s[i].b.x+eps)
            low=max(low,s[i].high(x));
    rt max(0.0,s[k].high(x)-low);
}
dd area(dd l,dd r){
    rt (length(l)+length(r))*(r-l);
}
dd dfs(dd l,dd r,dd v,int k){
    dd m=(l+r)*.5;
    dd v1=area(l,m),v2=area(m,r);
    if(sig(v1+v2-v)==0&&k>4)rt v;//避免空白区域的影响
    rt dfs(l,m,v1,k+1)+dfs(m,r,v2,k+1);
}
int main(){
    while(~scanf("%d",&n)){
        for(k=0;k<n;k++){
            s[k].get();
            printf("%.8lf\n",dfs(s[k].a.x,s[k].b.x,area(s[k].a.x,s[k].b.x),0)/s[k].A2());
        }
    }
    return 0;
}
\end{lstlisting}
\subsection{圆面积并，常数优化Simpson}
\begin{lstlisting}
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
#define dd double
#define rt return
#define ct const
#define cpt ct pt&
ct dd eps=1e-8;
inline int sig(dd x){rt (x>eps)-(x<-eps);}
struct cc{
    dd x,y,r;
    void get(){scanf("%lf%lf%lf",&x,&y,&r);}
    bool in(ct cc &c){
        rt sqrt((x-c.x)*(x-c.x)+(y-c.y)*(y-c.y))<r-c.r+eps;
    }
}c[1010];
#define sim(l,r,sl,sr,sm) ((sl+sr+4.0*sm)*(r-l)/6.0)
dd eve[2010];
int id[2010];
bool cmp(int a,int b){rt eve[a]<eve[b];}
struct merge_cc{
    dd area;
    cc *c;
    int n;
    merge_cc();
    merge_cc(cc _c[],int _n){
        c=_c,n=_n;
        area=0;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(i>=0&&i!=j&&c[j].in(c[i]))
                    c[i--]=c[--n];
        dd l=c[0].x-c[0].r,r=c[0].x+c[0].r;
        for(int i=1;i<n;i++){
            l=min(c[i].x-c[i].r,l);
            r=max(c[i].x+c[i].r,r);
        }
        dd m=(l+r)*.5;
        dd sl=calc(l),sr=calc(r),sm=calc(m);
        area=dfs(l,r,m,sl,sr,sm,sim(l,r,sl,sr,sm),0);
    }
    dd dfs(dd l,dd r,dd m,dd sl,dd sr,dd sm,dd v,int k){
        dd lm=(l+m)*.5,rm=(m+r)*.5;
        dd slm=calc(lm),srm=calc(rm);
        dd vl=sim(l,m,sl,sm,slm),vr=sim(m,r,sm,sr,srm);
        if(sig(vl+vr-v)==0&&k>4)rt v;
        rt dfs(l,m,lm,sl,sm,slm,vl,k+1)+dfs(m,r,rm,sm,sr,srm,vr,k+1);
    }
    dd calc(dd x){
        int e=0;
        for(int i=0;i<n;i++){
            dd t=c[i].r*c[i].r-(x-c[i].x)*(x-c[i].x);
            if(t<eps)continue;
            t=sqrt(t);
            eve[e++]=c[i].y-t;
            eve[e++]=c[i].y+t;
        }
        for(int i=0;i<e;i++)id[i]=i;
        sort(id,id+e,cmp);
        int cnt=0;
        dd s=0;
        for(int i=0;i<e;i++){
            if(cnt)s+=eve[id[i]]-eve[id[i-1]];
            if(id[i]&1)cnt--;
            else cnt++;
        }
        rt s;
    }
};
int main(){
    int n;
    while(~scanf("%d",&n)){
        for(int i=0;i<n;i++){
            c[i].get();
            if(c[i].r<eps)i--,n--;
        }
        printf("%.3lf\n",merge_cc(c,n).area);
    }
    rt 0;
}
\end{lstlisting}
\subsection{5个球和四面体的体积并}
在三维问题里面，精度有些问题，速度不快。
\begin{lstlisting}
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define dd double
#define rt return
#define ct const
#define cpt ct pt&
#define op operator
ct dd eps=1e-6;
ct dd pi=acos(-1.0);
inline int sig(dd x){rt (x>eps)-(x<-eps);}
#define sim(l,r,sl,sr,sm) ((sl+sr+4.0*sm)*(r-l)/6.0)
dd eve[100];
int id[100];
struct pt{
    dd x,y,z;
    void get(){scanf("%lf%lf%lf",&x,&y,&z);}
    void out(){printf("%lf %lf %lf\n",x,y,z);}
    bool get_pt(cpt a,cpt b,dd zz){
        if(sig(a.z-b.z)==0||zz>a.z+eps&&zz>b.z+eps||zz<a.z-eps&&zz<b.z-eps)rt 0;
        x=(zz-a.z)*(b.x-a.x)/(b.z-a.z)+a.x;
        y=(zz-a.z)*(b.y-a.y)/(b.z-a.z)+a.y;
        z=0;
        rt 1;
    }

};
struct poly{
    pt p[4];
    void get(){
        for(int i=0;i<4;i++)p[i].get();
    }
    bool calc(dd x,dd z,dd &a,dd &b){
        a=1e100,b=-1e100;
        int n=0;
        pt tp[5];
        for(int i=0;i<4;i++)
            for(int j=i+1;j<4;j++)
                if(tp[n].get_pt(p[i],p[j],z))n++;
        if(n==0)rt 0;
        for(int i=0;i<n;i++)
            for(int j=i+1;j<n;j++){
                if(sig(tp[i].x-tp[j].x)==0||x<tp[i].x-eps&&x<tp[j].x-eps||x>tp[i].x+eps&&x>tp[j].x+eps)continue;
                dd y=(x-tp[i].x)*(tp[j].y-tp[i].y)/(tp[j].x-tp[i].x)+tp[i].y;
                a=min(a,y);
                b=max(b,y);
            }
        rt a<b;
    }
}g[10];
struct cc{
    pt o;
    dd r;
    void get(){o.get(),scanf("%lf",&r);}
    bool calc(dd x,dd z,dd &a,dd &b){
        dd r2=r*r-(o.z-z)*(o.z-z);
        if(r2<eps*eps)rt 0;
        r2-=(o.x-x)*(o.x-x);
        if(r2<eps*eps)rt 0;
        r2=sqrt(r2);
        a=o.y-r2,b=o.y+r2;
        rt 1;
    }
}c[10];
int n,m;
bool cmp(int a,int b){rt eve[a]<eve[b];}
dd calc(dd x,dd z){
    int e=0;
    for(int i=0;i<n;i++)
        if(g[i].calc(x,z,eve[e],eve[e+1]))e+=2;
    for(int i=0;i<m;i++)
        if(c[i].calc(x,z,eve[e],eve[e+1]))e+=2;
    for(int i=0;i<e;i++)id[i]=i;
    sort(id,id+e,cmp);
    int cnt=0;
    dd s=0;
    for(int i=0;i<e;i++){
        if(cnt)s+=eve[id[i]]-eve[id[i-1]];
        if(id[i]&1)cnt--;
        else cnt++;
    }
    rt s;
}
dd dfs(dd l,dd r,dd m,dd sl,dd sr,dd sm,dd v,dd z,int k){
    dd lm=(l+m)*.5,rm=(m+r)*.5;
    dd slm=calc(lm,z),srm=calc(rm,z);
    dd vl=sim(l,m,sl,sm,slm),vr=sim(m,r,sm,sr,srm);
    if(sig(vl+vr-v)==0&&k>4)rt v;
    rt dfs(l,m,lm,sl,sm,slm,vl,z,k+1)+dfs(m,r,rm,sm,sr,srm,vr,z,k+1);
}
dd area(dd z){
    dd l=-8,r=8,m=0;//x边界
    dd sl=calc(l,z),sr=calc(r,z),sm=calc(m,z);
    rt dfs(l,r,m,sl,sr,sm,sim(l,r,sl,sr,sm),z,0);
}
dd dfs(dd l,dd r,dd m,dd sl,dd sr,dd sm,dd v,int k){
    dd lm=(l+m)*.5,rm=(m+r)*.5;
    dd slm=area(lm),srm=area(rm);
    dd vl=sim(l,m,sl,sm,slm),vr=sim(m,r,sm,sr,srm);
    if(sig(vl+vr-v)==0&&k>4)rt v;
    rt dfs(l,m,lm,sl,sm,slm,vl,k+1)+dfs(m,r,rm,sm,sr,srm,vr,k+1);
}
dd vol(){
    dd l=-8,r=8,m=0;//z边界
    dd sl=area(l),sr=area(r),sm=area(m);
    rt dfs(l,r,m,sl,sr,sm,sim(l,r,sl,sr,sm),0);
}
int main(){
    while(scanf("%d%d",&n,&m),n||m){
        for(int i=0;i<n;i++)g[i].get();
        for(int i=0;i<m;i++)c[i].get();
        printf("%.3lf\n",vol());
    }
    rt 0;
}
\end{lstlisting}
\subsection{多边形面积并}
和确定做法有一定误差，速度也不是很快。
\begin{lstlisting}
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define dd double
#define rt return
#define ct const
#define cpt ct pt&
#define op operator
ct dd eps=1e-8;
inline int sig(dd x){rt (x>eps)-(x<-eps);}
#define sim(l,r,sl,sr) ((sl+sr)*(r-l)/2.0)
dd eve[220];
int id[220];
struct pt{
    dd x,y;
    void get(){scanf("%lf%lf",&x,&y);}
}p[110][4];
int n;
bool cmp(int a,int b){rt eve[a]+eps<eve[b];}
bool SS(pt p[],dd x,dd &a,dd &b){
    a=1e100,b=-1e100;
    for(int i=0;i<3;i++){
        if(p[i].x==p[i+1].x||x<p[i].x-eps&&x<p[i+1].x-eps||x>p[i].x+eps&&x>p[i+1].x+eps)continue;
        dd y=(x-p[i].x)*(p[i+1].y-p[i].y)/(p[i+1].x-p[i].x)+p[i].y;
        a=min(a,y);
        b=max(b,y);
    }
    rt a<b+eps;
}
dd calc(dd x){
    int e=0;
    for(int i=0;i<n;i++)
        if(SS(p[i],x,eve[e],eve[e+1]))e+=2;
    for(int i=0;i<e;i++)id[i]=i;
    sort(id,id+e,cmp);
    int cnt=0;
    dd s=0;
    for(int i=0;i<e;i++){
        if(cnt)s+=eve[id[i]]-eve[id[i-1]];
        if(id[i]&1)cnt--;
        else cnt++;
    }
    rt s;
}
dd dfs(dd l,dd r,dd sl,dd sr,dd v,int k){
    dd m=(l+r)*.5,sm=calc(m);
    dd vl=sim(l,m,sl,sm),vr=sim(m,r,sm,sr);
    if(sig(vl+vr-v)==0&&k>9)rt v;
    rt dfs(l,m,sl,sm,vl,k+1)+dfs(m,r,sm,sr,vr,k+1);
}
dd area(dd l,dd r){
    if(l>r)rt 0;
    dd sl=calc(l),sr=calc(r);
    rt dfs(l,r,sl,sr,sim(l,r,sl,sr),0);
}
int main(){
    int T,cas=1;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        dd l=1e100,r=-1e100;
        for(int i=0;i<n;i++){
            for(int j=0;j<3;j++){
                p[i][j].get();
                l=min(l,p[i][j].x);
                r=max(r,p[i][j].x);
            }
            p[i][3]=p[i][0];
        }
        printf("Case %d: %.3lf",cas++,area(l,r));
    }
    rt 0;
}
\end{lstlisting}