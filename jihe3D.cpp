\section{三维几何基础}
浮点乘法不重载不报错!!\\
注意初始化N\\
I'm not sure about this.\\
椭球体积 sqrt(a*b*sqrt(c))*pi*160.0\\
参数v多是向量\\
法向量注意可能为0\\
台体体积：上底面S1，下底面S2，中间截面S0，高H，\\
V=(S1+sqrt(S1*S2)+S2)*H/3,2sqrt(S0)=sqrt(S1)+sqrt(S2);\\
拟柱体体积：V=(S1+4*S0+S2)*H/6;\\
\subsection{基本操作}
\begin{lstlisting}
struct pt{
    dd x,y,z;
    pt(dd x=0,dd y=0,dd z=0):x(x),y(y),z(z){}
    void get(){scanf("%lf%lf%lf",&x,&y,&z);}
    void out(){printf("%lf %lf %lf\n",x,y,z);}
    pt op+(cpt p)ct{rt pt(x+p.x,y+p.y,z+p.z);}
    pt op-(cpt p)ct{rt pt(x-p.x,y-p.y,z-p.z);}
    pt op*(dd v)ct{rt pt(x*v,y*v,z*v);}
    dd op*(cpt p)ct{rt x*p.x+y*p.y+z*p.z;}
    pt op^(cpt p)ct{rt pt(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);}
    pt X(cpt a,cpt b)ct{rt a-*this^b-*this;}
    dd O(cpt a,cpt b)ct{rt (a-*this)*(b-*this);}
    bool op<(cpt p)ct{rt x+eps<p.x||x<p.x+eps&&(y+eps<p.y||y<p.y+eps&&z+eps<p.z);}
    bool op==(cpt p)ct{rt sig(x-p.x)==0&&sig(y-p.y)==0&&sig(z-p.z)==0;}
    dd V6(cpt a,cpt b,cpt c)ct{rt a.X(b,c)*(*this-a);}
    dd V6(cpt b,cpt c)ct{rt (b^c)*(*this);}
    dd A2(cpt b,cpt c)ct{rt X(b,c).abs();}
    int side(cpt a,cpt b,cpt c)ct{rt sig(V6(a,b,c));}
    dd abs2(){rt x*x+y*y+z*z;}
    dd abs(){rt sqrt(x*x+y*y+z*z);}
    dd abs(cpt v){rt sig(*this*v)*abs();}//相对有向
    dd dis_line(cpt a,cpt b){rt X(a,b).abs()/(a-b).abs();}
    bool on(cpt a,cpt b)ct{
        rt X(a,b).abs()<eps&&O(a,b)<eps;
    }
    //绕过原点的单位向量v旋转角度v后得到的点,注意旋转轴构造的特殊情况
    void R(dd v,pt r[]){
        *this=(*this)*(1/abs());
        dd c=cos(v),s=sin(v);
        r[0]=pt(c+(1-c)*x*x,  (1-c)*x*y-s*z, (1-c)*x*z+s*y);
        r[1]=pt((1-c)*y*x+s*z, c+(1-c)*y*y,  (1-c)*y*z-s*x);
        r[2]=pt((1-c)*z*x-s*y, (1-c)*z*y+s*x, c+(1-c)*z*z);
    }
    pt(cpt a,cpt b,cpt c,cpt d){//一定有交
        pt to=(b-a^d-c);
        dd u=to.abs();
        dd t=c.X(d,a).abs(to)/u;
        *this=a*(1-t)+b*t;
    }
    bool SS(cpt a,cpt b,cpt c,cpt d){
        if(a.side(b,c,d))rt 0;//异面
        pt to=(b-a^d-c);
        dd u=to.abs();
        if(!sig(u))rt 0;//平行
        dd t=c.X(d,a).abs(to)/u,s=a.X(c,b).abs(to)/u;
        *this=a*(1-t)+b*t;
        rt t>=0&&t<=1&&s>=0&&s<=1;
    }
    pt TR(cpt b,cpt c){//(b,c)的逆时针垂直向量
        rt (b+X(b,c)).X(c,b);
    }
    pt TL(cpt b,cpt c){
        rt (b+X(b,c)).X(b,c);
    }
};
bool T(pt a,pt b){
    rt sig(a*b)==0;
}
bool H(pt a,pt b){
    rt sig((a^b).abs2())==0;
}
dd line_line(cpt a,cpt b,cpt c,cpt d){/*必须是异面*/
    pt to=(a-b)^(c-d);
    rt fabs((a-c)*to)/to.abs();
}
dd sc(pt a,pt b){/*cos for line_line,sin for line_face*/
    rt a*b/a.abs()/b.abs();
}
struct face{
    pt a,b,c,d;
    face(pt a,pt b,pt c):a(a),b(b),c(c),d(a.X(b,c)){}
    bool on_me(cpt p){/*在三角形上,包括边界*/
        rt sig(a.A2(b,c)-p.A2(a,b)-p.A2(b,c)-p.A2(c,a))==0;
    }
    bool in_me(cpt p){/*在三角形上,不包括边界*/
        int v=sig(p.X(a,b)*d);
        rt v==sig(p.X(b,c)*d)&&v==sig(p.X(c,a)*d);
    }
    dd dis_me(cpt p){
        rt fabs(d*(p-a)/(d.abs()));
    }
    bool SF_inter(cpt p,cpt v,pt &x){
        dd t=d*v;
        if(sig(t)==0)rt 0;//平行
        t=d*(a-p)/t;
        if(t<0||t>1)rt 0;
        x=p+v*t;
        rt on_me(x);
        rt in_me(x);
    }
    pt LP_inter(cpt p,pt v){/*不能平行*/
        rt p+v*(d*(a-p)/(d*v));
    }
    bool PP_inter(face s,pt p,pt v){
        v=d^s.d;
        if(!sig(v.abs2()))rt 0;
        p=T(a-b,s.d)?s.LP_inter(a,c-a):s.LP_inter(a,b-a);
    }
};
pt get_T(cpt p,cpt a,cpt b){/*shunshizhen*/
  rt p+((b-a)^p.X(a,b));
}
bool SB_inter(cpt A,cpt B,cpt C,dd r){
  dd a=(B-C).abs(),b=(A-C).abs(),c=(A-B).abs();
  rt acos((a*a+b*b-c*c)/(2*a*b))-acos(r/b)-acos(r/a)>=0;
}
struct cc{//bad
    dd r;
    pt o;
    void get(){o.get(),scanf("%lf",&r);}
    cc(){}
    cc(cpt a,cpt b,cpt c){//外接圆
        pt u=b-a,v=c-a;
        o=a+pt(u,u+c.TR(a,b),v,v+b.TR(c,a))*.5;
        r=(a-o).abs();
    }
    bool in_me(cpt p){//算边上
        rt (p-o).abs()<r+eps;
    }
    void refresh(pt p[],int n){
        pt t=p[n];
        for(int i=n;i>0;i--)p[i]=p[i-1];
        p[0]=t;
    }
    cc(pt p[],int n){
        random_shuffle(p,p+n);//srand(time(0));
        o=p[0],r=0;
        for(int i=1;i<n;i++){
            if(in_me(p[i]))continue;
            o=p[i],r=0;
            for(int j=0;j<i;j++){
                if(in_me(p[j]))continue;
                o=(p[i]+p[j])*.5,r=(p[j]-o).abs();
                for(int k=0;k<j;k++){
                    if(in_me(p[k]))continue;
                    *this=cc(p[i],p[j],p[k]);
                    refresh(p,k);
                }
                refresh(p,j);
            }
            refresh(p,i);
        }
    }
};
\end{lstlisting}
\subsection{三维凸包}
\begin{lstlisting}
struct convex{
  int n,to[N][N];
  pt *p;
  struct face{
      int a,b,c;
      bool ok;
  }f[N*10],add;
  int side(cpt t,face &f){
      rt sig(p[f.a].X(p[f.b],p[f.c])*(t-p[f.a]));
  }
  convex(){}
  void fixed(){/*注意共线共面*/
      add.a=0,add.b=1,add.c=2;
      int flag;
      for(flag=2;!sig(p[flag].X(p[0],p[1]).abs());flag++);
      swap(p[2],p[flag]);
      for(flag=3;!side(p[flag],add);flag++);
      swap(p[3],p[flag]);
  }
  convex(pt s[],int m){
      n=0;p=s;
      if(m<4)rt;
      fixed();
      for(int i=0;i<4;i++){
          add.a=(i+1)%4,add.b=(i+2)%4,add.c=(i+3)%4,add.ok=1;
          if(side(p[i],add)>0)swap(add.b,add.c);
          to[add.a][add.b]=to[add.b][add.c]=to[add.c][add.a]=n;
          f[n++]=add;
      }
      for(int i=4;i<m;i++){
          for(int j=0;j<n;j++){
              if(f[j].ok&&side(p[i],f[j])>0){
                  dfs(i,j);
                  break;
              }
          }
      }
  }
  void deal(int i,int a,int b){
      int c=to[a][b];
      if(f[c].ok){
          if(side(p[i],f[c])>0)dfs(i,c);
          else{
              add.a=b,add.b=a,add.c=i,add.ok=1;
              to[i][b]=to[a][i]=to[b][a]=n;
              f[n++]=add;
          }
      }
  }
  void dfs(int i,int j){
      f[j].ok=0;
      deal(i,f[j].b,f[j].a);
      deal(i,f[j].c,f[j].b);
      deal(i,f[j].a,f[j].c);
  }
  pt get_myheart(){
      pt s;
      dd v=0;
      for(int i=0;i<n;i++)
          if(f[i].ok){
              dd t=p[f[i].a].V6(p[f[i].b],p[f[i].c]);
              v+=t;
              s=s+(p[f[i].a]+p[f[i].b]+p[f[i].c])*t;
          }
      rt s*(1/(v*4));
  }
  dd min_dis(){
      pt t=get_myheart();
      dd s=1e50;
      for(int i=0;i<n;i++)
          if(f[i].ok){
              pt tem=p[f[i].a].X(p[f[i].b],p[f[i].c]);
              dd ret=fabs(tem*(p[f[i].a]-t)/(tem.abs()));
              if(s>ret)s=ret;
          }
      rt s;
  }
  bool v[N*10];
  bool coface(int i,int j){
      rt (p[f[i].a].X(p[f[i].b],p[f[i].c])
              ^p[f[j].a].X(p[f[j].b],p[f[j].c])).abs()<eps;
  }
  void color(int i){
      v[i]=0;
      int a=f[i].a,b=f[i].b,c=f[i].c;
      if(v[to[b][a]]&&coface(i,to[b][a]))color(to[b][a]);
      if(v[to[a][c]]&&coface(i,to[a][c]))color(to[a][c]);
      if(v[to[c][b]]&&coface(i,to[c][b]))color(to[c][b]);
  }
  int n_face(){
      int cnt=0;
      for(int i=0;i<n;i++)v[i]=f[i].ok;
      for(int i=0;i<n;i++)
          if(v[i]){
              color(i);
              cnt++;
          }
      rt cnt;
  }
};
\end{lstlisting}