\section{点的基本操作}
\begin{lstlisting}
//椭球体积 sqrt(a*b*sqrt(c))*pi*160.0
//e^ix=cosx+isinx
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <time.h>
using namespace std;
#define cpt ct pt&
#define op operator
#define dd double
#define rt return
#define ct const
ct dd eps=1e-8;
ct dd pi=acos(-1.0);
inline int sig(ct dd &x){rt (x>eps)-(x<-eps);}
struct pt{
    dd x,y;
    pt(){}
    pt(dd x,dd y):x(x),y(y){}
    void get(){scanf("%lf%lf",&x,&y);}
    void out(){printf("%lf %lf\n",x,y);}
    pt op+(cpt p)ct{rt pt(x+p.x,y+p.y);}
    pt op-(cpt p)ct{rt pt(x-p.x,y-p.y);}
    pt op*(dd v)ct{rt pt(x*v,y*v);}
    dd op*(cpt p)ct{rt x*p.x+y*p.y;}
    dd op^(cpt p)ct{rt x*p.y-y*p.x;}
    bool op<(cpt p)ct{rt y+eps<p.y||y<p.y+eps&&x+eps<p.x;}
    dd X(cpt a,cpt b)ct{rt a-*this^b-*this;}
    dd O(cpt a,cpt b)ct{rt (a-*this)*(b-*this);}
    dd abs2()ct{rt x*x+y*y;}
    dd abs()ct{rt sqrt(x*x+y*y);}
    bool op==(cpt p)ct{rt sig(x-p.x)==0&&sig(y-p.y)==0;}
    pt TR()ct{rt pt(-y,x);}
    pt norm()ct{rt pt(y,-x)*(1/abs());}/*顺时针单位向量*/
    pt(cpt a,cpt b,cpt c,cpt d){
        dd t=(d-c^a-c)/(b-a^d-c);
        *this=a*(1-t)+b*t;
    }
    pt R(pt o,dd v)ct{
        dd s=sin(v),c=cos(v);
        pt t=*this-o;
        pt p=pt(t.x*c-t.y*s,t.x*s+t.y*c);
        rt p+o;
    }
    pt Z(pt a,pt b,dd n1,dd n2){
        dd v=atan2(X(a,b),O(a,b));
        dd v1=asin(sin(pi/2-v)*n1/n2);
        rt b.R(*this,sig(v)*(pi/2+v1));
    }
    pt F(pt a,pt b){
        dd v=atan2(X(a,b),O(a,b));
        rt b.R(*this,pi+v);
    }
    pt pro(cpt a,cpt b){
        rt a+(b-a)*(a.O(b,*this)/a.O(b,b));
    }
    pt D(cpt a,cpt b){
        rt pro(a,b)*2-*this;
    }
    bool on(cpt a,cpt b){
        rt sig(X(a,b))==0&&sig(O(a,b))<=0;
    }
    bool SS(cpt a,cpt b,cpt c,cpt d){
        dd u=(b-a^d-c);
        if(!sig(u))rt 0;
        dd t=c.X(d,a)/u,s=a.X(c,b)/u;
        if(t<0||t>1||s<0||s>1)rt 0;/*eps !!!*/
        *this=a*(1-t)+b*t;
        rt 1;
    }
    dd dis_line(cpt a,cpt b)ct{
        rt fabs(X(a,b))/(a-b).abs();
    }
    dd dis_seg(cpt p,cpt q)ct{
        if(sig(p.O(*this,q)<=0))rt (*this-p).abs();
        if(sig(q.O(*this,p)<=0))rt (*this-q).abs();
        rt dis_line(p,q);
    }
};
dd angle(cpt u,cpt v){/*vector*/
    rt atan2(u^v,u*v);
}
dd seg_seg(cpt a,cpt b,cpt c,cpt d){
    rt min(min(a.dis_seg(c,d),b.dis_seg(c,d)),min(c.dis_seg(a,b),d.dis_seg(a,b)));
}
\end{lstlisting}