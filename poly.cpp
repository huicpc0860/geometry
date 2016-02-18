\section{多边形基本操作,p[n]=p[0]}
\subsection{分式线性变换}
二维变换的终极利器，不用三角函数
\begin{lstlisting}
void RST(cpt a,cpt b,cpt c,cpt d,pt ch[]){//c-d-->a-b
	pt ab=b-a,cd=d-c;
	dd s=cd*cd,u=(ab*cd)/s,v=(cd^ab)/s;
	for(int i=0;i<n;i++){
		dd x=ch[i].x-c.x,y=ch[i].y-c.y;
		p[i]=pt(u*x-v*y,v*x+u*y)+a;
	}
}
\end{lstlisting}
\subsection{半平面交}
a->b的顺时针,平移 t=(b-a).norm()*r,a=a+t,b=b+t; 逆时针a=a-t,b=b-t;
\begin{lstlisting}
void cut(cpt a,cpt b,pt ch[],int &m){/*=*/
	int n=0;
	for(int i=0;i<m;i++){
		int u=sig(a.X(b,ch[i])),v=sig(a.X(b,ch[i+1]));
		if(u>=0)p[n++]=ch[i];/*>= 逆时针*/
		if(u*v<0)p[n++]=pt(a,b,ch[i],ch[i+1]);/*< 逆时针*/
	}
	m=n;
	for(int i=0;i<m;i++)ch[i]=p[i];
	ch[m]=ch[0];
}
//用于成员函数
bool cut(cpt a,cpt b,pt ch[],int m){/*=*/
	n=0;
	for(int i=0;i<m;i++){
		int u=sig(a.X(b,ch[i])),v=sig(a.X(b,ch[i+1]));
		if(u>=0)p[n++]=ch[i];/*>= 逆时针*/
		if(u*v<0)p[n++]=pt(a,b,ch[i],ch[i+1]);/*< 逆时针*/
	}
	p[n]=p[0];
	rt n!=0;
}
\end{lstlisting}
\subsection{凸包，水平序}
\begin{lstlisting}
void convex1(pt ch[],int m){/*不要边上的点*/
	n=0;
	sort(ch,ch+m);
	for(int i=0;i<m;i++){
		while(n>1&&sig(p[n-2].X(p[n-1],ch[i]))<=0)n--;
		p[n++]=ch[i];
	}
	int k=n;
	for(int i=m-2;i>=0;i--){
		while(n>k&&sig(p[n-2].X(p[n-1],ch[i]))<=0)n--;
			p[n++]=ch[i];
	}
	if(m>1)n--;
	p[n]=p[0];
}
void convex2(pt ch[],int m){/*要边上的点*/
	n=0;
	sort(ch,ch+m);
	for(int i=0;i<m;i++){
		while(n>1&&sig(p[n-2].X(p[n-1],ch[i]))<0)n--;
		p[n++]=ch[i];
	}
	if(n==m)rt;
	int k=n;
	for(int i=m-2;i>=0;i--){
		while(n>k&&sig(p[n-2].X(p[n-1],ch[i]))<0)n--;
		p[n++]=ch[i];
	}
	if(m>0)n--;
	p[n]=p[0];
}
\end{lstlisting}
\subsection{凸包，graham}
\begin{lstlisting}
pt pk;
bool g_c(cpt a,cpt b){
    int u=sig(pk.X(a,b));
    rt u>0||u==0&&sig(pk.O(a,a)-pk.O(b,b))<0;
}
void convex(){/*不要边上的点*/
	int k=0;
	for(int i=1;i<n;i++)
		if(p[i].y+eps<p[k].y||p[i].y<p[k].y+eps&&p[i].x+eps<p[k].x)k=i;
	pk=p[k];
	sort(p,p+n,g_c);
	if(n<=1){rt;}
	if(sig(p[0].X(p[1],p[n-1]))==0){
		p[1]=p[n-1];n=2;rt;
	}
	p[n++]=p[0];
	int m=n;
	n=1;
	for(int i=2;i<m;i++){
		while(n>0&&sig(p[n-1].X(p[n],p[i]))<=0)n--;
		p[++n]=p[i];
	}
	p[n]=p[0];
}
void convex(){/*要边上的点*/
	int k=0;
	for(int i=1;i<n;i++)
		if(p[i].y+eps<p[k].y||p[i].y<p[k].y+eps&&p[i].x+eps<p[k].x)k=i;
	pk=p[k];
	sort(p,p+n,g_c);
	if(n>0&&sig(p[0].X(p[1],p[n-1]))){
		int t=n-1;
		while(sig(p[0].X(p[n-1],p[t]))==0)t--;
		reverse(p+t+1,p+n);
	}
	int m=n;
	n=0;
	for(int i=0;i<m;i++){
		while(n>=2&&sig(p[n-2].X(p[n-1],p[i]))<0)n--;
		p[n++]=p[i];
	}
	p[n]=p[0];
}
\end{lstlisting}
\subsection{点在多边形内}
\begin{lstlisting}
bool inside_me(cpt c){//on?，o(n)
	bool in=0;
	for(int i=0;i<n;i++){
		pt a=p[i],b=p[i+1];
		if(((b.x<c.x)^(a.x<c.x))&&((b.y-a.y)*abs(c.x-a.x)<(c.y-a.y)*abs(b.x-a.x)))in=!in;
	}
	rt in;
}
bool inside_me(cpt c){//on?,log(n)
	if(n<3)rt c.on(p[0],p[1]);
	int l=1,r=n-1;
	if(p[0].X(p[r],c)<=0&&p[0].X(p[l],c)>=0){
		while(l+1<r){
			int m=(l+r)>>1;
			if(p[0].X(p[m],c)>=0)l=m;
			else r=m;
		}
	}else rt 0;
	rt p[l].X(p[l+1],c)>=0;
}
\end{lstlisting}
\subsection{面积，重心等}
\begin{lstlisting}
dd _area(){/*-+-+-+*/
	dd s=0;p[n]=p[0];
	for(int i=0;i<n;i++)s+=(p[i]^p[i+1]);
	rt s*0.5;
}
pt heart(){
	pt t(0,0);
	dd sum=0,s;
	for(int i=0;i<n;i++,sum+=s){
		s=(p[i]^p[i+1]);
		t=t+(p[i]+p[i+1])*s;
	}
	rt t*(1/(3*sum));
}
dd D2(){//p[n]=p[0];max(p[i+1].O(p[j+1],p[j+1]);
	dd s=0;
	for(int i=0,j=1;i<n;i++){
		while(p[i].X(p[i+1],p[j])<p[i].X(p[i+1],p[j+1]))j=(j+1)%n;
		s=max(s,p[i].O(p[j],p[j]));
	}
	rt s;
}
dd rotcal(poly &b) {
	dd s=1e100;
	for(int i=0,j=0,t;i<n;i++){
		while(t=sig(p[i].X(p[i+1],b.p[j+1])-p[i].X(p[i+1],b.p[j])),t>0)j=(j+1)%b.n;
		if(t)s=min(s,b.p[j].dis_seg(p[i],p[i+1]));
		else s=min(s,seg_seg(p[i],p[i+1],b.p[j],b.p[j+1]));
	}
	rt s;
}
\end{lstlisting}
\subsection{区间操作}
不会扫描线的时候写的，没什么用
\begin{lstlisting}
dd length(){
	dd l=0,r=0,sum=0;
	for(int i=0;i<n;i++)
		if(sig(p[i].x-r)<=0)r=max(r,p[i].y);
		else{
			sum+=(r-l);
			l=p[i].x,r=p[i].y;
		}
	rt sum+(r-l);
}
void merge(){
	if(n==0)rt;
	sort(p,p+n);
	int k=n;n=0;
	pt t=p[0];
	for(int i=1;i<k;i++)
		if(sig(p[i].x-t.y)<=0)t.y=max(t.y,p[i].y);
		else {
			p[n++]=t;
			t=p[i];
		}
	p[n++]=t;
}
void join(poly &a,poly &b){
	n=0;
	for(int i=0,j=0;i<a.n&&j<b.n;){
		if(a.p[i].y<b.p[j].x+eps)i++;
		else if(b.p[j].y<a.p[i].x+eps)j++;
		else if(a.p[i].y+eps<b.p[j].y)p[n++]=pt(max(a.p[i].x,b.p[j].x),a.p[i].y),i++;
		else if(b.p[j].y+eps<a.p[i].y)p[n++]=pt(max(a.p[i].x,b.p[j].x),b.p[j].y),j++;
		else p[n++]=pt(max(a.p[i].x,b.p[j].x),b.p[j].y),j++,i++;
	}
	if(a.n==0)*this=b;
}
\end{lstlisting}
