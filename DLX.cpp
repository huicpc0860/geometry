\section{Dancing links}
resume和remove容易敲错
遍历顺序很有影响，必要时候可以更改顺序
可以对列计数器做特判，以减少时间
\begin{lstlisting}
#define N -1
#define D -1
int l[N],r[N],u[N],d[N],x[N],y[N],c[N],id,col;
#define ff(i,d,t) for(int i=d[t];i!=t;i=d[i])
void link(int i,int j,int &k){
    c[j]++;
	x[id]=i;//行标,保存决策，非必要
    y[id]=d[id]=j;
    u[id]=u[j];
    u[j]=d[u[j]]=id;
    r[id]=id-k;
    l[id-k]=id;
    if(k){
        l[id]=id-1;
        r[id-1]=id;
    }
    k++;
    id++;
}
void init(int m){
    col=m;
    for(int i=0;i<=col;i++){
        l[i]=i-1;
        r[i]=i+1;
        u[i]=d[i]=y[i]=i;
        c[i]=0;
    }
    l[0]=col;
    r[col]=0;
    id=col+1;
	best=10000;//重复覆盖需要初始化
}
\end{lstlisting}
\subsection{精确覆盖}
\begin{lstlisting}
inline void remove(int t){
    ff(i,d,t){
        if(i>col)ff(j,r,i)
        u[d[j]]=u[j],d[u[j]]=d[j],c[y[j]]--;
        l[r[i]]=l[i],r[l[i]]=r[i];
    }
}
inline void resume(int t){
    ff(i,u,t){
        l[r[i]]=r[l[i]]=i;
        if(i>col)ff(j,l,i)
        u[d[j]]=d[u[j]]=j,++c[y[j]];
    }
}
bool dfs(int k){
    if(r[0]==0){cnt=k;return 1;}
    int t=r[0];
    ff(i,r,0)if(c[i]<c[t])t=i;
    if(c[t]==0)return 0;
    ff(i,d,t){
        remove(i);
        ff(j,r,i)remove(j);
        o[k]=x[i];
        bool f=dfs(k+1);
        ff(j,l,i)resume(j);
        resume(i);
        if(f)return 1;
    }
    return 0;
}
\end{lstlisting}
\subsection{重复覆盖}
\begin{lstlisting}
inline void remove(int t){
    ff(i,d,t)l[r[i]]=l[i],r[l[i]]=r[i];
}
inline void resume(int t){
    ff(i,u,t)l[r[i]]=r[l[i]]=i;
}
int astar(){
    int cnt=0;
    bool h[D]={};//*********列的数目
    ff(t,r,0)if(!h[t]){
        h[t]=1,cnt++;
        ff(i,d,t)ff(j,r,i)h[y[j]]=1;
    }
    return cnt;
}
void dfs(int k){
    if(k+astar()>=best)return;
    if(r[0]==0){best=k;return;}
    int t=r[0];
    ff(i,r,0)if(c[i]<c[t])t=i;
	if(c[t]==0)return;
    ff(i,d,t){
        remove(i);
        ff(j,r,i)remove(j);
        dfs(k+1);
        ff(j,l,i)resume(j);
        resume(i);
    }
}
\end{lstlisting}
\subsection{选取最少的行使得某些列覆盖至少一次某些列至多一次}
sz[n]以前的列至少一次
\begin{lstlisting}
int astar(){
    int cnt=0;
    bool h[55]={};
    for(int t=r[0];t<sz[n];t=r[t])//
        if(!h[t]){
            h[t]=1,cnt++;
            ff(i,d,t)ff(j,r,i)h[y[j]]=1;
        }
    return cnt;
}
void dfs(int k){
    if(k+astar()>=best)return;
    if(r[0]>=sz[n]||r[0]==0){best=k;return;}
    int t=r[0];
    for(int i=r[0];i<sz[n];i=r[i])
        if(c[i]<c[t])t=i;
    if(c[t]==0)return;
    ff(i,d,t){
        remove(i);
        ff(j,r,i)if(y[j]>=sz[n])exremove(j);
        else remove(j);
        dfs(k+1);
        ff(j,l,i)if(y[j]>=sz[n])exresume(j);
        else resume(j);
        resume(i);
    }
}
\end{lstlisting}
\subsection{数独问题}
\begin{lstlisting}
#define N 1000000
char s[20][20];
int cnt,o[300];
int D=16,dd=4;
int main(){
    while(~scanf("%s",s[0])){
        for(int i=1;i<D;i++)scanf("%s",s[i]);
        init(D*D*4);
        int row=0;
        for(int k=0;k<D;k++){
            int t=k*D*3+1;
            for(int i=0;i<D;i++)
                for(int j=0,cnt=0;j<D;j++,row++){
                    if(s[i][j]!='-'&&s[i][j]!='A'+k)continue;
                    link(row,t+i,cnt);
                    link(row,t+D+j,cnt);
                    link(row,t+D+D+(i/dd)*dd+j/dd,cnt);
                    link(row,1+D*D*3+i*D+j,cnt);
                }
        }
        dfs(0);
        for(int i=0;i<cnt;i++)
            s[o[i]/D%D][o[i]%D]=o[i]/(D*D)+'A';
        for(int i=0;i<D;i++)
            puts(s[i]);
        puts("");
    }
    return 0;
}
\end{lstlisting}