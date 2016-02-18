\section{圆弧的离散化}
\subsection{圆面积并}
\begin{lstlisting}
ct dd eps=1e-8;
ct dd pi=acos(-1.0);
struct pt{
    dd x,y;
    pt(){}
    pt(dd x,dd y):x(x),y(y){}
    void get(){scanf("%lf%lf",&x,&y);}
    pt op+(cpt p)ct{rt pt(x+p.x,y+p.y);}
    pt op-(cpt p)ct{rt pt(x-p.x,y-p.y);}
    dd op^(cpt p)ct{rt x*p.y-y*p.x;}
    dd abs()ct{rt sqrt(x*x+y*y);}
};
dd eve[3000];
int e,id[3000];
struct cc{
    pt o;
    dd r;
    void get(){
        o.get();
        scanf("%lf",&r);
    }
    bool in(ct cc &c){
        rt (o-c.o).abs()<r-c.r+eps;
    }
    pt get_pt(dd v)ct{
        rt o+pt(r*cos(v),r*sin(v));
    }
    void c_c(ct cc& c){
        pt dir=c.o-o;
        dd d=dir.abs();
        if(r+c.r<d+eps)rt;
        dd v=atan2(dir.y,dir.x);//(-pi,pi]
        dd add=acos(((d*d+r*r-c.r*c.r)/d)/(r+r));//[0,pi]
        eve[e++]=v-add,eve[e++]=v+add;
    }
}c[1010];
bool cmp(int a,int b){rt eve[a]<eve[b];}
struct min_cc{
    dd area;
    cc *c;
    int n;
    min_cc(){}
    min_cc(cc _c[],int _n){
        area=0;
        c=_c,n=_n;
        for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(i>=0&&i!=j&&c[j].in(c[i]))
                c[i--]=c[--n];
        for(int i=0;i<n;i++){
            e=0;
            for(int j=0;j<n;j++)
                if(i!=j)c[i].c_c(c[j]);
            radar(c[i]);
        }
        area*=.5;
    }
    void radar(ct cc &c){
        for(int i=0,t=e;i<t;i+=2){
            if(eve[i]<-pi){
                eve[i]+=pi*2;
                eve[i+1]+=pi*2;
            }
            if(eve[i+1]>pi){
                eve[e++]=-pi;
                eve[e++]=eve[i+1]-pi*2;
                eve[i+1]=pi;
            }
        }
        eve[e++]=-pi,eve[e++]=pi;
        for(int i=0;i<e;i++)id[i]=i;
        sort(id,id+e,cmp);
        int cnt=0;
        for(int i=0;i<e;i++){
            if(cnt==1){
                int a=id[i-1],b=id[i];
                dd v=eve[b]-eve[a];
                if(v>eps)
                    area+=(c.get_pt(eve[a])^c.get_pt(eve[b]))+c.r*c.r*(v-sin(v));
            }
            if(id[i]&1)cnt--;
            else cnt++;
        }
    }
};
int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        c[i].get();
        if(c[i].r<eps)i--,n--;
    }
    printf("%.3lf\n",min_cc(c,n).area);
    rt 0;
} 
\end{lstlisting}
\subsection{圆面积交}
同上，输出覆盖了[1，n]次的面积,各种题目变形的时候注意数据预处理。
\begin{lstlisting}
struct cc{
    pt o;
    dd r;
    void get(){
        o.get();
        scanf("%lf",&r);
    }
    pt get_pt(dd v)ct{
        rt o+pt(r*cos(v),r*sin(v));
    }
    void c_c(ct cc& c){
        pt dir=c.o-o;
        dd d=dir.abs();
        if(c.r-r>d-eps){
            eve[e++]=-pi,eve[e++]=pi;rt;
        }
        if(r-c.r>d-eps||r+c.r<d+eps)rt;
        dd v=atan2(dir.y,dir.x);//(-pi,pi]
        dd add=acos(((d*d+r*r-c.r*c.r)/d)/(r+r));//[0,pi]
        eve[e++]=v-add,eve[e++]=v+add;
    }
}c[1010];
dd s2[1010];
void radar(ct cc &c){
    for(int i=0,t=e;i<t;i+=2){
        if(eve[i]<-pi){
            eve[i]+=pi*2;
            eve[i+1]+=pi*2;
        }
        if(eve[i+1]>pi){
            eve[e++]=-pi;
            eve[e++]=eve[i+1]-pi*2;
            eve[i+1]=pi;
        }
    }
    eve[e++]=-pi,eve[e++]=pi;
    for(int i=0;i<e;i++)id[i]=i;
    sort(id,id+e,cmp);
    int cnt=0;
    for(int i=0;i<e;i++){
        if(cnt){
            int a=id[i-1],b=id[i];
            dd v=eve[b]-eve[a];
            if(v>eps)
                s2[cnt]+=(c.get_pt(eve[a])^c.get_pt(eve[b]))+c.r*c.r*(v-sin(v));
        }
        if(id[i]&1)cnt--;
        else cnt++;
    }
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++)c[i].get();
    memset(s2,0,sizeof(s2));
    for(int i=0;i<n;i++){
        e=0;
        for(int j=0;j<n;j++)
            if(i!=j)
                c[i].c_c(c[j]);
        radar(c[i]);
    }
    for(int i=1;i<=n;i++)
        printf("[%d] = %.3lf\n",i,(s2[i]-s2[i+1])*.5);
    rt 0;
}
\end{lstlisting}
\subsection{矩形框类有若干相离的圆，求还能放入的最大圆}
二分半径，膨胀圆，通过圆弧离散化可以判断是否有空间。
\begin{lstlisting}
dd eve[200];
int e,id[200];
struct cc{
    pt o;
    dd r;
    void get(){
        o.get();
        scanf("%lf",&r);
    }
    void c_c(ct cc& c){
        pt dir=c.o-o;
        dd d=dir.abs();
        if(r+c.r<d+eps)rt;//相离，不处理全包含
        if(c.r>r-eps&&c.r-r>d+eps){//包含，处理全包含
            eve[e++]=-pi,eve[e++]=pi;
            rt;
        }
        dd v=atan2(dir.y,dir.x);//(-pi,pi]
        dd add=acos(((d*d+r*r-c.r*c.r)/d)/(r+r));//[0,pi]
        eve[e++]=v-add,eve[e++]=v+add;//(-2pi,2pi]&&a<b&&(b-a)[0,pi]
    }
    void c_c(cpt a,cpt b){//覆盖顺时针方向的弧a->b
        dd d=(o.X(a,b)/(b-a).abs());
//        if(d>r-eps||d<-r+eps)rt;//不处理全包含
        if(d>r-eps)rt;//离
        if(d<-r+eps){//反向离，处理全包含
            eve[e++]=-pi,eve[e++]=pi;
            rt;
        }
        pt dir=(a-b).TR();
        dd v=atan2(dir.y,dir.x),add=acos(d/r);
        eve[e++]=v-add,eve[e++]=v+add;
    }
}c[100],cp[100];
dd W,H,R;
bool cmp(int a,int b){
    rt eve[a]<eve[b];
}
struct min_cc{
    cc *c;
    int n;
    bool res;
    min_cc(){}
    min_cc(cc _c[],int _n){
        res=0;
        c=_c,n=_n;
        for(int i=0;i<n;i++){
            e=0;
            for(int j=0;j<n;j++)
                if(i!=j)c[i].c_c(c[j]);
            pt p[5];
            p[4]=p[0]=pt(R,R),p[1]=pt(W-R,R),p[2]=pt(W-R,H-R),p[3]=pt(R,H-R);
            for(int j=0;j<4;j++)c[i].c_c(p[j],p[j+1]);
            res|=radar(c[i]);
            if(res==1)rt;
        }
    }
    bool radar(ct cc &c){
        for(int i=0,t=e;i<t;i+=2){
            if(eve[i]<-pi){
                eve[i]+=pi*2;
                eve[i+1]+=pi*2;
            }
            if(eve[i+1]>pi){
                eve[e++]=-pi;
                eve[e++]=eve[i+1]-pi*2;
                eve[i+1]=pi;
            }
        }
        eve[e++]=-pi,eve[e++]=pi;
        for(int i=0;i<e;i++)id[i]=i;
        sort(id,id+e,cmp);
        int cnt=0;
        for(int i=0;i<e;i++){
            if(cnt==1&&eve[id[i]]-eve[id[i-1]]>eps)rt 1;
            if(id[i]&1)cnt--;
            else cnt++;
        }
        rt 0;
    }
};
int n;
bool judge(dd r){
    R=r;
    for(int i=0;i<n;i++){
        cp[i]=c[i];
        cp[i].r+=r;
    }
    rt n==0||min_cc(cp,n).res;
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%lf%lf",&W,&H);
        scanf("%d",&n);
        for(int i=0;i<n;i++)c[i].get();
        dd l=0,r=(min(H,W))*.5;
        while(l+(1e-6)<r){
            dd m=(l+r)*.5;
            if(judge(m))l=m;
            else r=m;
        }
        printf("%.10lf\n",r);
    }
    return 0;
}
\end{lstlisting}