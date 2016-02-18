\section{扫描线}
\subsection{set，光源能照亮周围的木棒的数量}
以光线和木棒的交点到光源的距离作事件比较,极扫描\\
\begin{lstlisting}
struct pt{
    dd x,y;
    void get(){scanf("%lf%lf",&x,&y);}
    pt(dd x=0,dd y=0):x(x),y(y){}
    pt op+(cpt p)ct{rt pt(x+p.x,y+p.y);}
    pt op-(cpt p)ct{rt pt(x-p.x,y-p.y);}
    pt op*(dd v)ct{rt pt(x*v,y*v);}
    dd op^(cpt p)ct{rt x*p.y-y*p.x;}
    pt(cpt a,cpt b,cpt c,cpt d){
        dd t=(d-c^a-c)/(b-a^d-c);
        *this=a*(1-t)+b*t;
    }
    double abs2(){rt x*x+y*y;}
}o,A,B,p[20010];

struct event{
    pt *a,*b;
    dd v;
    int id;
    bool type;
    event(){}
    event(pt *a,pt *b,int id,dd v,bool type):a(a),b(b),id(id),v(v),type(type){}
    bool op<(ct event &e)ct{
        if(a==e.a&&b==e.b)rt 0;
        rt pt(A,B,*a,*b).abs2()<pt(A,B,*e.a,*e.b).abs2();
    }
    bool judge(){
        if(type==0)rt 0;
        pt t(pt(),pt(1,0),*a,*b);
        rt t.x<0&&t.y<a->y&&t.y>b->y;
    }
}eve[20010];
set<event> radar;
bool v[10010];
bool cmp(ct event &a,ct event &b){
    rt a.v<b.v;
}
int main(){
    int n;
    while(~scanf("%d",&n)){
        o.get();
        int e=0;
        for(int i=0;i<n;i++){
            p[i].get();
            p[i]=p[i]-o;
            p[i+n].get();
            p[i+n]=p[i+n]-o;
            if((p[i]^p[i+n])<0)swap(p[i],p[i+n]);
            eve[e++]=event(&p[i],&p[i+n],i,atan2(p[i].y,p[i].x),1);
            eve[e++]=event(&p[i],&p[i+n],i,atan2(p[i+n].y,p[i+n].x),0);
        }
        sort(eve,eve+e,cmp);
        fill(v,v+n,0);
        radar.clear();
        B=pt(-1,0);
        for(int i=0;i<e;i++){\\去周期
            if(eve[i].judge()){
                radar.insert(eve[i]);
            }
        }
        for(int i=0;i<e;i++){
            if(eve[i].type){
                B=*(eve[i].a);
                radar.insert(eve[i]);
            }else{
                B=*(eve[i].b);
                radar.erase(eve[i]);
            }
            if(!radar.empty()){
                v[radar.begin()->id]=1;
            }
        }
        int cnt=0;
        for(int i=0;i<n;i++)if(v[i])cnt++;
        printf("%d\n",cnt);
    }
    rt 0;
}
\end{lstlisting}
\subsection{set，最近圆对}
最近圆对，水平扫描，垂直比较，直接判两个圆是否相交
\begin{lstlisting}
typedef long long LL;
const double eps=1e-8;
struct cc{
    double x,y,r;
    void get(){scanf("%lf%lf%lf",&x,&y,&r);}
    bool operator<(const cc &p)const{return y<p.y||y==p.y&&x<p.x;}
}c[50010];
struct event{
    double x;
    int id;
    bool v;
    event(){}
    event(double x,int id,bool v):x(x),id(id),v(v){}
    bool operator <(const event &p)const{return x<p.x;}
}eve[100010];
bool inter(cc a,cc b,double &r){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)<(a.r+b.r+r+r)*(a.r+b.r+r+r)+eps;
}
set<cc>line;
typedef set<cc>::iterator IT;
int T,n,e;
bool judge(double d){
    line.clear();
    e=0;
    for(int i=0;i<n;i++){
        eve[e++]=event(c[i].x-d-c[i].r,i,1);
        eve[e++]=event(c[i].x+d+c[i].r,i,0);
    }
    sort(eve,eve+e);
    for(int i=0;i<e;i++){
        if(eve[i].v){
            IT it=line.insert(c[eve[i].id]).first,s=it,e=it;
            if(s--!=line.begin())
                if(inter(*s,*it,d))return 1;
            if(++e!=line.end())
                if(inter(*e,*it,d))return 1;
        }else line.erase(c[eve[i].id]);//此处有bug，要判断erase
    }
    return 0;
}

int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=0;i<n;i++)c[i].get();
        double l=0,r=100000;
        while(l+eps<r){
            double m=(l+r)/2;
            if(judge(m))r=m;
            else l=m;
        }
        printf("%lf\n",l+r);
    }
}
\end{lstlisting}
\subsection{set，极扫描圆}
求点集的联通分量，之间有圆为障碍物，枚举点为中心极扫描，比较为切点到圆的\\
\begin{lstlisting}
struct point{
    double x,y;
    int id;
    void get(int t){scanf("%lf%lf",&x,&y);id=t;}
}p[1001];
struct circle{
    point p;
    double r;
    void get(){scanf("%lf%lf%lf",&p.x,&p.y,&r);}
}c[1001];
int f[1001],n,m;
struct event{
    double v,d;
    int id;
    event(){}
    event(double v,double d,int id):v(v),d(d),id(id){}
    bool operator<(const event &e)const{return v<e.v;}
}eve[6003];
inline double dis2(point &a,point &b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
int find(int x){
    if(x!=f[x])f[x]=find(f[x]);
    return f[x];
}
set <double> line;
int main(){
    while(~scanf("%d%d",&n,&m)){
        for(int i=0;i<n;i++)p[i].get(i),f[i]=i;
        for(int i=0;i<m;i++)c[i].get();
        for(int i=0;i<n;i++){
            swap(p[0],p[i]);
            int e=0;
            for(int j=1;j<n;j++)
                if(find(i)!=find(j))eve[e++]=event(atan2(p[j].y-p[0].y,p[j].x-p[0].x),sqrt(dis2(p[0],p[j])),p[j].id);
            for(int j=0;j<m;j++){
                double  dv=asin(c[j].r/sqrt(dis2(p[0],c[j].p))),
                        ds=sqrt(dis2(p[0],c[j].p)-c[j].r*c[j].r),//切线长度
                        tv=atan2(c[j].p.y-p[0].y,c[j].p.x-p[0].x);
                eve[e++]=event(tv-dv,ds,-2);
                eve[e++]=event(tv+dv,ds,-1);
                if(tv-dv<-pi){
                    eve[e++]=event(tv-dv+2*pi,ds,-2);
                    eve[e++]=event(tv+dv+2*pi,ds,-1);
                }
                if(tv+dv>pi){
                    eve[e++]=event(tv-dv-2*pi,ds,-2);
                    eve[e++]=event(tv+dv-2*pi,ds,-1);
                }
            }
            sort(eve,eve+e);
            line.clear();
            for(int j=0;j<e;j++){
                if(eve[j].id==-2)line.insert(eve[j].d);
                else if(eve[j].id==-1)line.erase(eve[j].d);
                else {
                    int x=find(i),y=find(eve[j].id);
                    if(x!=y&&line.size()==0||eve[j].d<*line.begin())f[x]=find(y);
                }
            }
        }
        int cnt=-1;
        for(int i=0;i<n;i++)if(i==find(i))cnt++;
        printf("%d\n",cnt);
    }
    return 0;
}
\end{lstlisting}
\subsection{set，求有多少个不被包含的圆}
注意sqrt里面为负数
\begin{lstlisting}
double L;
const double eps=1e-8;
struct circle{
    double x,y,r;
    bool v;
    void get(){scanf("%lf%lf%lf",&r,&x,&y);}
    double Y(bool f){
        double t=sqrt(r*r-(L-x)*(L-x)+eps);//
        return y+(f?t:-t);
    }
}c[40001];
struct node{
    int p;
    bool v;
    node(){}
    node(int p,bool v):p(p),v(v){}
    bool operator<(const node &other)const{
        double y1=c[p].Y(v)*100,y2=c[other.p].Y(other.v)*100;
        return y1>y2||y1==y2&&v>other.v;
    }
};
set<node> line;
typedef set<node>::iterator IT;
struct event{
    double x,y;
    int p;
    bool v;
    event(){}
    event(double x,double y,int p,bool v):x(x),y(y),p(p),v(v){}
    bool operator<(const event &other)const{
        return x<other.x||x==other.x&&y>other.y;
    }
}eve[80002];
int main(){
    int m=0,n,cnt=0;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        c[i].get();
        eve[m++]=event(c[i].x-c[i].r,c[i].y,i,1);
        eve[m++]=event(c[i].x+c[i].r,c[i].y,i,0);
    }
    sort(eve,eve+m);
    for(int i=0;i<m;i++){
        L=eve[i].x;
        if(eve[i].v){
            IT it=line.insert(node(eve[i].p,0)).first,st=it,ed=it;
            if(st--==line.begin()||++ed==line.end())c[it->p].v=1,cnt++;
            else{
                if(st->p==ed->p)c[it->p].v=0;
                else c[it->p].v=c[st->p].v&&c[ed->p].v,cnt+=c[it->p].v;
            }
            line.insert(node(eve[i].p,1));
        }else{
            line.erase(node(eve[i].p,0));
            line.erase(node(eve[i].p,1));
        }
    }
    printf("%d\n",cnt);
    for(int i=0;i<n;i++)if(c[i].v)printf("%d ",i+1);
    return 0;
}
\end{lstlisting}
\subsection{BIT，求各个矩形中的点的数目}
水平扫描线，求矩形中的点的数目，结构为树状数组
\begin{lstlisting}
struct pt{
    int x,y,z;
    void get(){
        double t;
        scanf("%d%d%lf",&x,&y,&t);
        t*=100.0;
        z=(int)(t>0?t+0.1:t-0.1);
    }
    bool operator<(const pt &p)const{return y<p.y;}
}p[60010];
struct cube{
    int x1,y1,z1,x2,y2,z2;
    void get(){
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        y1--;
        z1=z2=0;
    }
    void out(){
        printf("%.2lf/%d\n",(double)z1/100.0,z2);
    }
}q[20010];

#define get_id(a) ((a)=(lower_bound(x,x+nx,a)-x+1))
int x[100010],y[40010],id[40010],v[100010],c[100010],nx,ny;
bool cmp(int a,int b){
    return y[a]<y[b];
}
void add(int i,int x){
    while(i<=nx){
        v[i]+=x;
        c[i]++;
        i+=i&-i;
    }
}
void calc(int i,int &x,int &y){
    x=y=0;
    while(i){
        x+=v[i];
        y+=c[i];
        i-=i&-i;
    }
}
int main(){
    int n,m;
    while(~scanf("%d%d",&n,&m)){
        nx=0,ny=0;
        for(int i=0;i<n;i++){
            p[i].get();
            x[nx++]=p[i].x;
        }
        for(int i=0;i<m;i++){
            q[i].get();
            x[nx++]=q[i].x1;
            x[nx++]=q[i].x2;
            id[ny]=ny;
            y[ny++]=q[i].y1;
            id[ny]=ny;
            y[ny++]=q[i].y2;
        }
        sort(x,x+nx);
        nx=unique(x,x+nx)-x;
        for(int i=0;i<n;i++)get_id(p[i].x);
        for(int i=0;i<m;i++){
            get_id(q[i].x1);
            get_id(q[i].x2);
        }
        fill(v,v+nx+1,0);
        fill(c,c+nx+1,0);
        sort(p,p+n);
        sort(id,id+ny,cmp);
        for(int i=0,j=0;i<ny;i++){
            int t=id[i];
            while(j<n&&p[j].y<=y[t]){
                add(p[j].x,p[j].z);
                j++;
            }
            int t1,t2,t3,t4;
            calc(q[t>>1].x1-1,t1,t2),calc(q[t>>1].x2,t3,t4);
            q[t>>1].z1+=(t&1)?t3-t1:t1-t3;
            q[t>>1].z2+=(t&1)?t4-t2:t2-t4;
        }
        for(int i=0;i<m;i++)q[i].out();
    }
    return 0;
}
\end{lstlisting}