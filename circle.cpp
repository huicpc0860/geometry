\section{圆的基本操作}
\begin{lstlisting}
struct cc{
    dd r;
    pt o;
    void get(){o.get(),scanf("%lf",&r);}
    cc(){}
    cc(cpt a,cpt b,cpt c){//外接圆,保证不共线
        pt u=b-a,v=c-a;
        o=a+pt(u,u+u.TR(),v,v+v.TR())*.5;
        r=(a-o).abs();
    }
    cc(cpt a,cpt b,cpt c){//内切圆
		dd A=(b-c).abs(),B=(a-c).abs(),C=(a-b).abs();
		o=(a*A+b*B+c*C)/(A+b+C)
		r=(a-o).abs();
    }
    cc(int n,int k){//random_shuffle(p,p+n);cc c(n,0);
        if(k==0)r=-1;
        else if(k==1)o=tr[0],r=0;
        else if(k==2)o=(tr[0]+tr[1])*.5,r=(tr[0]-o).abs();
        else if(k==3){
            *this=cc(tr[0],tr[1],tr[2]);
            rt;
        }
        for(int i=0;i<n;i++)
            if((p[i]-o).abs()>r+eps){
                tr[k]=p[i];
                *this=cc(i,k+1);
                pt t=p[i];
                for(int j=i;j>0;j--)p[j]=p[j-1];
                p[0] = t;
            }
    }
    //用于求交点，不用于判相交面积，情况过多，比如内接多边形。
    void inter_me(cpt a,cpt b,pt p[],int &n){
        n=0;
        pt ab=b-a,oa=a-o;
        dd A=ab*ab,B=ab*oa,C=oa*oa-r*r,D=B*B-A*C;
        if(D>eps){
            D=sqrt(D);
            dd t1=(-B-D)/A;
            if(t1>0&&t1<1)p[n++]=a*(1-t1)+b*t1;
            dd t2=(-B+D)/A;
            if(t2>0&&t2<1)p[n++]=a*(1-t2)+b*t2;
        }
    }
    void inter_me(cc &t,pt p[],int &n){
        n=0;
        pt e=(t.o-o);
        dd d=e.abs();
        if(sig(d)){
            dd x=(d*d-t.r*t.r+r*r)/(d+d),h=r*r-x*x;
            if(sig(h)>=0){
				h=sqrt(h);
                e=e*(1/d);
                pt no=e.TR();
                p[n++]=o+e*x+no*h;
                if(sig(h))p[n++]=o+e*x-no*h;
            }
        }
    }
    void c_c(ct cc& c){//圆覆盖了某圆的弧度起点与重点
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
    void c_c(cpt a,cpt b){//直线覆盖ab顺时针方向的弧
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
    dd A2(cpt a,cpt b){//圆与三角形交,注意三角函数的参数
        dd A=(b-o).abs(),B=(a-o).abs(),C=(b-a).abs(),s=o.X(a,b);
        if(A<r&&B<r)rt s;
        if(A<r&&B>=r){
            dd x=(b.O(a,o)+sqrt(r*r*C*C-s*s))/C;
            return asin(s*(1-x/C)/r/B)*r*r+s*x/C;
        }
        if(A>=r&&B<r){
            dd y=(a.O(b,o)+sqrt(r*r*C*C-s*s))/C;
            rt asin(s*(1-y/C)/r/A)*r*r+s*y/C;
        }
        if(fabs(s)>=r*C||a.O(b,o)<=0||b.O(a,o)<=0){
            dd si=asin(fix(s/A/B,2))*r*r;
            if(o.O(a,b)<0){
                dd co=acos(-1.0)*r*r;
				rt -si+(s<0?-co:co);
            }
            rt si;
        }
        dd x=(b.O(a,o)+sqrt(r*r*C*C-s*s))/C,y=(a.O(b,o)+sqrt(r*r*C*C-s*s))/C;
        rt asin(s*(1-x/C)/r/B)*r*r+s*x/C+asin(s*(1-y/C)/r/A)*r*r+s*y/C-s;
    }
};
bool make_tri(dd a,dd b,dd c,pt p[]){//三边长确定三角形
    if(a>b)swap(a,b);
    if(b>c)swap(b,c);
    if(a>b)swap(a,b);
    if(a+b<=c)return 0;
    p[0]=pt(0,0);
    p[1]=pt(c,0);
    p[2].x=0.5*(c*c-a*a+b*b)/c;
    p[2].y=sqrt(b*b-p[2].x*p[2].x);
    return 1;
}
dd gong(dd r,dd x){//(半径，高(可以为负))
    rt r*r*acos(x/r)-sqrt(r*r-x*x)*x;
}
dd c_c(dd r,dd R,dd c){//c为圆心距
    if(r>R)swap(r,R);
    if(r+R<c+eps)rt 0;
    if(R-r+eps>c)rt r*r*pi;
    dd t=(R*R-r*r)/c;
    dd x=(c-t)*0.5,y=(c+t)*0.5;
    rt gong(r,x)+gong(R,y);
}
\end{lstlisting} 
