\section{小}
\subsection{点集分割}
n*n枚举所有把点集分成两份等量的方法
\begin{lstlisting}
struct pt{
    int x,y;
    int id;
    pt(){}
    pt(int x,int y):x(x),y(y){}
    void get(int t){scanf("%d%d",&x,&y);id=t;}
    pt op+(cpt p)ct{rt pt(x+p.x,y+p.y);}
    pt op-(cpt p)ct{rt pt(x-p.x,y-p.y);}
    int op^(cpt p)ct{rt x*p.y-y*p.x;}
    bool op<(cpt p)ct{rt y<p.y||y==p.y&&x<p.x;}
}p[2222];
int n,B,W;
#define inc(x) (((x)?B:W)++)
#define dec(x) (((x)?B:W)--)
bool update(int &s,int &e,bool type){
    pt M=p[e]-p[s],R;
    int id=-1;
    bool t;
    for(int i=0;i<n;i++){
        if(i==s||i==e)continue;
        pt U=(p[i]-p[s]);
        if((M^U)<0){
            U.x=-U.x,U.y=-U.y;
            if(id==-1||(U^R)>0)R=U,id=i,t=0;
        }else if(id==-1||(U^R)>0)R=U,id=i,t=1;
    }
    if(type)inc(p[e].id);
    if(t==0){
        e=s;
        s=id;
        if(type)dec(p[s].id);
    }else{
        e=id;
        if(!type)dec(p[e].id);
    }
    rt t;
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int n1;
        scanf("%d",&n1);
        n=n1<<1;
        int p1=0,p2=n;
        for(int i=0;i<n;i++){
            p[i].get(i<n1);
            if(p[i]<p[p1])p1=i;
        }
        p[n]=p[p1]+pt(10,0);
        update(p1,p2,1);
        B=0,W=0;
        while(B+W!=n1-1)
            update(p1,p2,1);
        int s=p1,e=p2,cnt=0,n2=n1>>1;
        while(true){
            if(W==n2&&B+p[s].id==n2)cnt++;
            if(W+!p[e].id==n2&&B==n2)cnt++;
            if(update(e,s,0))
                while(!update(s,e,1));
            if(s==p1&&e==p2)break;
        }
        printf("%d\n",cnt/2);
    }
    rt 0;
}
\end{lstlisting}
\subsection{二元一次方程}
\begin{lstlisting}
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
#define cpt ct pt&
#define op operator
#define dd double
#define rt return
#define ct const
ct dd eps=1e-8;
inline int sig(ct dd &x){rt (x>eps)-(x<-eps);}
struct pt{
    dd x,y,r;
    pt(dd x=0,dd y=0,dd r=0):x(x),y(y),r(r){}
    void get(){scanf("%lf%lf%lf",&x,&y,&r);}
    void out(){printf("%lf %lf %lf\n",x,y,r);}
    dd getc()ct{rt x*x+y*y-r*r;}
    bool op==(cpt p)ct{rt x==p.x&&y==p.y&&r==p.r;}
    bool op<(cpt p)ct{rt r<p.r;}
    pt op-(cpt p)ct{rt pt(x-p.x,y-p.y);}
    dd abs2()ct{rt x*x+y*y;}
    dd abs()ct{rt sqrt(abs2());}
}p[100010];
int n;
int calc(ct pt& a,ct pt& b,ct pt& c,pt &d){
    dd a1=2*(a.x-b.x),b1=2*(a.y-b.y),c1=a.getc()-b.getc();
    dd a2=2*(a.x-c.x),b2=2*(a.y-c.y),c2=a.getc()-c.getc();
    if(a1*b2==a2*b1){
        if(a1*c2==a2*c1&&b1*c2==b2*c1)return -2;
        else return -1;
    }
    d.x=(b2*c1-b1*c2)/(b2*a1-b1*a2);
    d.y=(a2*c1-a1*c2)/(a2*b1-a1*b2);
    d.r=sqrt((d-a).abs2()-a.r*a.r);
    if(sig(d.r)==0)return -1;
    for(int i=0;i<n;i++){
        if(sig(sqrt((d-p[i]).abs2()-p[i].r*p[i].r)-d.r))return -1;
    }
    return 0;
}
void judge(){
    if(n==1){
        puts("-2");
        return;
    }
    if(n==2){
        if(p[0].x==p[1].x&&p[0].y==p[1].y)
            puts("-1");
        else puts("-2");
        return;
    }
    int type;
    pt d;
    for(int i=2;i<n;i++){
        type=calc(p[i-2],p[i-1],p[i],d);
        if(type==-1){
            puts("-1");
            return;
        }
        if(type==0){
            d.out();
            return;
        }
    }
    puts("-2");
}
int main() {
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=0;i<n;i++){
            p[i].get();
        }
        sort(p,p+n);
        n=unique(p,p+n)-p;
        judge();
    }
    return 0;
}
\end{lstlisting}
