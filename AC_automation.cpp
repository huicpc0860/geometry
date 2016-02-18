\section{AC自动机}
有矩阵乘法也不要忘记DP\\
在自己构造串的时候可能因为具体的原因不会超内存。\\
注意初始化map，ID=0,newnode(),bfs()\\
\begin{lstlisting}
#define clr(a) memset(a,0,sizeof(a))
#define N 100
#define D 4
int ID,next[N][D],fail[N],type[N],q[N],map[128];

inline int newnode(){
    clr(next[ID]);
    fail[ID]=type[ID]=0;
    return ID++;
}
inline void insert(char *s){
    int p=0;
    for(int c;*s;p=next[p][c],s++){
        c=map[*s];
        if(!next[p][c])next[p][c]=newnode();
    }
    type[p]=1;
}
void bfs(){
    int *s=q,*e=q;
    *e++=0;
    while(s!=e)
        for(int i=0,p=*s++;i<D;i++)
            if(next[p][i]){
                int t=next[p][i];
                *e++=t;
                if(p){
                    fail[t]=next[fail[p]][i];
                    type[t]|=type[fail[t]];
                }
            }else next[p][i]=next[fail[p]][i];
}
\end{lstlisting}
\subsection{包含至少两个关键串的个数，矩阵乘法}
每到达一次转移到新的字典树上
\begin{lstlisting}
//cnt[t]+=cnt[fail[t]];
int a[N][N],b[N][N],c[N][N];
void make(int a[][N],int b[][N]){
    clr(c);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            for(int k=0;k<n;k++){
                c[i][j]+=a[i][k]*b[k][j];
                c[i][j]%=mod;
            }
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            a[i][j]=c[i][j];
}
int main(){
    map['A']=0;
    map['T']=1;
    map['C']=2;
    map['G']=3;
    int L;
    while(~scanf("%d%d",&n,&L)){
        ID=0;
        newnode();
        for(int i=0;i<n;i++){
            scanf("%s",s);
            insert(s);
        }
        bfs();
        clr(a);
        clr(b);
        for(int i=0;i<ID;i++){
            for(int j=0;j<D;j++){
                int k=next[i][j];
                a[i+ID+ID][k+ID+ID]++;
                if(cnt[k])a[i+ID][k+ID+ID]++;
                else a[i+ID][k+ID]++;
                if(cnt[i])continue;
                if(cnt[k]){
                    if(cnt[k]>1)a[i][ID+ID+k]++;
                    else a[i][ID+k]++;
                }else  a[i][k]++;
            }
        }
        n=ID+ID+ID;
        for(int i=0;i<n;i++)b[i][i]=1;
        while(L){
            if(L&1)make(b,a);
            make(a,a);
            L>>=1;
        }
        int ans=0;
        for(int i=0;i<ID;i++){
            ans+=b[0][ID+ID+i];
            ans%=mod;
        }
        printf("%d\n",ans);
    }
    return 0;
}
\end{lstlisting}
\subsection{最长被包含字符串}
\begin{lstlisting}
void bfs(){
    int *s=q,*e=q;
    *e++=0;
    while(s!=e)
        for(int i=0,p=*s++;i<D;i++)
            if(next[p][i]){
                int t=next[p][i];
                *e++=t;
                if(p){
                    fail[t]=next[fail[p]][i];
                    f[t]=max(f[p],f[fail[t]])+type[t];
                    type[t]|=type[fail[t]];
                }else f[t]=type[t];
                ans=max(ans,f[t]);
            }else next[p][i]=next[fail[p]][i];
}
int main(){
    for(int i=0;i<D;i++)map[i+'a']=i;
    int n;
    while(scanf("%d",&n),n){
        getchar();
        memset(f,0,sizeof(f));
        ID=0;
        newnode();
        ans=0;
        while(n--){
            gets(s);
            insert(s);
        }
        bfs();
        printf("%d\n",ans);
    }
    return 0;
}
\end{lstlisting}
\subsection{给定字母个数给定包括最多给定串的排列}
任意进制的写法
\begin{lstlisting}
char s[100];
int f[N][11*11*11*11],c[4];
void Max(int &a,int b){
    if(b>a)a=b;
}
int main(){
    map['A']=0;
    map['C']=1;
    map['G']=2;
    map['T']=3;
    int n,cas=1;
    while(scanf("%d",&n),n){
        ID=0;
        newnode();
        for(int i=0;i<n;i++){
            scanf("%s",s);
            insert(s);
        }
        bfs();
        scanf("%s",s);
        n=strlen(s);
        int t[4]={};
        c[0]=1;
        for(int i=0;i<n;i++)
            t[map[s[i]]]++;
        for(int i=1;i<5;i++)
            c[i]=c[i-1]*(t[i-1]+1);
        memset(f,-1,sizeof(f));
        f[0][c[4]-1]=0;
        for(int i=c[4]-1;i>0;i--){
            for(int j=0;j<ID;j++){
                if(f[j][i]<0)continue;
                for(int k=0;k<D;k++)
                    if(i%c[k+1]/c[k])Max(f[next[j][k]][i-c[k]],f[j][i]+cnt[next[j][k]]);
            }
        }
        int ans=0;
        for(int i=0;i<ID;i++)Max(ans,f[i][0]);
        printf("Case %d: %d\n",cas++,ans);
    }
    return 0;
}
\end{lstlisting}
\subsection{用到fail指针转移的dp}
有用到fail指针转移的DP，罐子分裂。
\begin{lstlisting}
#define mod 10007
inline void insert(char *s){
    int p=0;
    for(int c,i=0;s[i];p=next[p][c],i++,d[p]=i){//需要记录节点深度的写法
        c=map[s[i]];
        if(!next[p][c])next[p][c]=newnode();
    }
    type[p]=1;
}
char s[100];
char str[20];
int f[2][N][110],len;
bool match(char *s){
    int p=0;
    for(int c;*s;s++){
        c=map[*s];
        p=next[p][c];
        if(type[p])return 0;
    }
    f[0][p][len]=1;
    return 1;
}
void add(int &a,int b){
    a+=b;
    if(a>=mod)a-=mod;
}
int main(){
    for(int i=0;i<D;i++)map[i+'a']=i;
    ID=0;
    newnode();
    d[0]=0;
    int p,n;
    scanf("%s%d%d",s,&p,&n);
    len=strlen(s);
    while(n--){
        scanf("%s",str);
        insert(str);
    }
    bfs();
    memset(f,0,sizeof(f));
    if(match(s)==0){
        puts("0 1");
        return 0;
    }
    int now=0,a=0,b=0;
    for(int i=0;i<p;now=!now,i++){//days
        for(int j=0;j<ID;j++){//sta
            if(type[ID])continue;
            for(int k=min(100,len+p);k>0;k--){//len
                int *inc=&f[now][j][k];
                if(*inc==0)continue;
                if(k-1<d[j]) add(f[!now][fail[j]][k-1],*inc);
                else add(f[!now][j][k-1],*inc);
                for(int r=0;r<D;r++)//next
                    if(type[next[j][r]])add(b,*inc);
                    else add(f[!now][next[j][r]][k+1],*inc);
                *inc=0;
            }
        }
        add(a,f[!now][0][0]);
        f[!now][0][0]=0;
    }
    printf("%d %d\n",a,b);
    return 0;
}
\end{lstlisting}