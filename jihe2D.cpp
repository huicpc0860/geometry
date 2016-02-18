\subsection{最近点对}
\begin{lstlisting}
pt p[N];
int on,o[N],n;
bool c_x(cpt a,cpt b){rt a.x+eps<b.x;}
bool c_y(ct int &a,ct int &b){rt p[a].y+eps<p[b].y;}
dd c_pair(int l,int r){
    dd ret=1e100;
    if(l>=r)rt ret;
    int m=(l+r)>>1,i;
    for(i=m;i>=l&&!sig(p[i].x-p[m].x);i--);
    ret=c_pair(l,i);
    for(i=m;i<=r&&!sig(p[i].x-p[m].x);i++);
    ret=min(ret,c_pair(i,r));
    on=0;
    for(i=m;i>=l&&sig(p[m].x-p[i].x-ret)<=0;i--)o[++on]=i;
    for(i=m+1;i<=r&&sig(p[i].x-p[m].x-ret)<=0;i++)o[++on]=i;
    sort(o+1,o+on+1,c_y);
    for(i=1;i<=on;i++)
        for(int j=1;j<9&&i+j<=on;j++)
          ret=min(ret,(p[o[i]]-p[o[i+j]]).abs());
    rt ret;
}
dd c_pair(){
  sort(p,p+n,c_x);
  rt c_pair(0,n-1);
}
\end{lstlisting}
\section{pick定理}
面积=内部点+边界点/2-1
\begin{lstlisting}
int gcd(int a,int b){
  rt b?gcd(b,a%b):a;
}
int gird_onedge(){
  int cnt=0;p[n]=p[0];
  for(int i=0;i<n;i++)
      cnt+=gcd(abs(p[i].x-p[i+1].x),abs(p[i].y-p[i+1].y));
  rt cnt;
}
int grid_inside(){
  int cnt=0;p[n]=p[0];p[n+1]=p[1];
  for(int i=0;i<n;i++)
      cnt+=p[i+1].y*(p[i].x-p[i+2].x);
  rt (abs(cnt)-gird_onedge())/2+1;
}
\end{lstlisting}
