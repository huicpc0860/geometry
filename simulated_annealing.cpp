\section{模拟退火}
\subsection{最小球覆盖}
\begin{lstlisting}
//最小球覆盖，要往离自己最远的方向走。爬山法
const double eps=1e-10;
struct point{
    double x,y,z;
	...
}p[110];
int main(){
    int n;
    while(~scanf("%d",&n)){
        for(int i=0;i<n;i++)p[i].get();
        point o=p[0];
        double ans=1e10,step=10000;
        while(step>eps){
            double max_d=0;
            int id;
            for(int i=0;i<n;i++){
                double dis=(p[i]-o).abs2();
                if(dis>max_d){
                    id=i;
                    max_d=dis;
                }
            }
            if(max_d<ans)ans=max_d;
            if(fabs(max_d)<eps)break;
            o=o+(p[id]-o)*(step/sqrt(max_d));
            step*=0.999;
        }
        o.out();
    }
    return 0;
}
\end{lstlisting}
\subsection{区域内最优点，并行}
注意淘汰区域外的尝试。可能忽略边界上的解，必要的话需要枚举边界点\\
(P,L,delta,eps)\\
区域内最近距离最远，点数1000，题目精度要求 0.1，（ 10 20 0.9 0.01 ）\\
费马点，点数100，要求保留整数，（ 1 3 0.7 0.1 ）\\
点到圆的视角相同，圆数3，使用方差做评估函数，精度 0.01，（ 5 10 0.8 0.001 ）
\begin{lstlisting}
const int P=5,L=10;
dd rand_f(){rt 1.0*rand()/(RAND_MAX-1);}//[0,1]
struct pt{
    dd x,y,r;
    pt(){}
    pt(dd x,dd y):x(x),y(y),r(0){}
    ...
    void get(){scanf("%lf%lf%lf",&x,&y,&r);}
    void out(){printf("%.2lf %.2lf\n",x,y);}
    bool pre(){rt x||y||r;}
}pos[P],c[3],s,e;
pt rand_pt(dd X,dd Y){
    rt pt(rand_f()*X,rand_f()*Y);
}
pt rand_dir(dd k){
    dd v=pi*2*rand_f();
    rt pt(k*cos(v),k*sin(v));
}
int X,Y,n;
dd calc(cpt t){
    dd a[3];
    dd sum=0,res=0;
    for(int i=0;i<3;i++){
        a[i]=(c[i]-t).abs()/c[i].r;
        sum+=a[i];
    }
    sum/=3.0;
    for(int i=0;i<3;i++)
        res+=(sum-a[i])*(sum-a[i]);
    rt res;
}
bool check(cpt t){
    rt t.x>=s.x&&t.x<=e.x&&t.y>=s.y&&t.y<=e.y;
}
int main(){
    srand(time(0));
    while(true){
        for(int i=0;i<3;i++){
            c[i].get();
            if(i){
                s.x=min(s.x,c[i].x);
                s.y=min(s.y,c[i].y);
                e.x=max(e.x,c[i].x);
                e.y=max(e.y,c[i].y);
            }else s=e=c[0];
        }
        if((c[0].pre()||c[1].pre()||c[2].pre())==0)break;
        e=e-s;
        for(int i=0;i<P;i++){
            pos[i]=s+rand_pt(e.x,e.y);
            pos[i].r=calc(pos[i]);
        }
        dd step=max(e.x,e.y);
        while(step>0.001){
            for(int i=0;i<P;i++)
                for(int j=0;j<L;j++){
                    pt t=pos[i]+rand_dir(step);
                    if(!check(t))continue;
                    t.r=calc(t);
                    if(t.r<pos[i].r)pos[i]=t;
                }
            step*=0.8;
        }
        int id=0;
        for(int i=1;i<P;i++)
            if(pos[i].r<pos[id].r)id=i;
        if(pos[id].r<0.001)pos[id].out();
        else puts("No solution");
    }
    return 0;
}
\end{lstlisting}