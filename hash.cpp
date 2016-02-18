\section{HASH}
hash值一般可以到int，保证相乘不超LL，bool数组不能表示可以用set\\
不同长度的字符串hash冲突很大，可以考虑用加入长度用双关键字hash。\\
比如set[len].insert(hash)或set.insert(pt(len,hash))\\
\subsection{矩阵二维hash}
n*m的矩阵按k*k的小块hash
\begin{lstlisting}
LL d[1100][1100];
LL p1[110];
LL p2[110];
LL mod1=1000007,mod2=1000000009LL;
int n,m,k;
int init(){
    p1[0]=p2[0]=1;
    p1[1]=23;
    p2[1]=29;
    for(int i=2;i<110;i++){
        p1[i]=(p1[i-1]*p1[1])%mod1;
        p2[i]=(p2[i-1]*p2[1])%mod2;
    }
}
void hush(LL a[][1100],LL b[][1100],int n,int m,int k){
    for(int i=0;i<n;i++)
        for(int j=0;j<=m-k;j++)
            if(j){
                d[i][j]=(((d[i][j-1]-a[i][j-1]*p1[k-1])*p1[1]+a[i][j+k-1])%mod1+mod1)%mod1;
            }else{
                d[i][0]=0;
                for(int r=0;r<k;r++){
                    d[i][0]+=(a[i][r]*p1[k-r-1])%mod1;
                    d[i][0]%=mod1;
                }
            }
    for(int j=0;j<=m-k;j++)
        for(int i=0;i<=n-k;i++)
            if(i){
                b[i][j]=(((b[i-1][j]-d[i-1][j]*p2[k-1])*p2[1]+d[i+k-1][j])%mod2+mod2)%mod2;
            }else{
                b[0][j]=0;
                for(int r=0;r<k;r++){
                    b[0][j]+=(d[r][j]*p2[k-r-1])%mod2;
                    b[0][j]%=mod2;
                }
            }
}
\end{lstlisting}