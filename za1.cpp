\section{小}
\subsection{最小表示法}
可判断字符串同构，寻找字典序最小的循环串 
\begin{lstlisting}
int minishow(char *s){//返回最小表示的起始位置 
	int i=0,j=1,k=0,n=strlen(s),m=(n>>1);
	while(i<m&&j<m&&k<m){
		if(s[i+k]==s[j+k])k++;
		else{
			if(s[i+k]>s[j+k])i+=(k+1);//若是<，则取的是最大表示 
			else j+=(k+1);
			if(i==j)j++;
			k=0;
		}
	}
	return min(i,j);
}
\end{lstlisting}
\subsection{构建指定序列的二叉树}
\begin{lstlisting}
#include <cstdio>
#include <stack>
#define MAXN 100010
using namespace std;

int h[MAXN]; 
int l[MAXN]; 
int r[MAXN]; 
int ls[MAXN];//左儿子
int rs[MAXN];//右儿子
int n;

bool check(int a, int b) {
	if(b<1||n<b) return false;
	return h[a]<h[b];
}

void erase(int x) {
	l[r[x]] = l[x];
	r[l[x]] = r[x];
}

int main() {
	scanf("%d", &n);
	stack<int> s;
	for(int x, i=1; i<=n; ++i) {
		scanf("%d", &x);
		h[x] = i;
		s.push(x);
	}
	for(int i=1; i<=n; ++i) {
		l[i] = i-1;
		r[i] = i+1;
	}
	int x;
	while(!s.empty()) {
		x = s.top();
		s.pop();
		if(check(x, l[x])) {
			ls[x] = l[x];
			erase(ls[x]);
		} else ls[x] = 0;
		if(check(x, r[x])) {
			rs[x] = r[x];
			erase(rs[x]);
		} else rs[x] = 0;
	}
	bool flag = false;
	s.push(x);
	while(!s.empty()) {
		x = s.top();
		s.pop();
		if(x==0) continue;
		if(flag) printf(" ");
		flag = true;
		printf("%d", x);
		s.push(rs[x]);
		s.push(ls[x]);
	}
	printf("\n");
}
\end{lstlisting}
\subsection{heap 最小堆}
\begin{lstlisting}
#include <functional>
#include <queue>
#include <vector>
priority_queue< int, vector<int>, greater<int> > pri_qa;//最小堆
priority_queue< int, vector<int>, less<int> >pri_qb;//最大堆
#define cp(a,b) ((a)<(b))
struct heap {
    int h[N];
    int n,p,c;
    void ins(int e){
        for(p=++n;p>1&&cp(e,h[p>>1]);h[p]=h[p>>1],p>>=1);
        h[p]=e;
    }
    int del(int &e){
        if(!n)return 0;
        for(e=h[p=1],c=2;c<n&&cp(h[c+=(c<n-1&&cp(h[c+1],h[c]))],h[n]);h[p]=h[c],p = c,c<<=1);
        h[p]=h[n--];
        return 1;
    }
};
heap p;
p.n=0;
\end{lstlisting}
\subsection{多维曼哈顿距离}
\begin{lstlisting}
#include <stdio.h>
int n;
double a[5],ma[32],mi[32];
int main(){
    scanf("%d",&n);
    for(int i=0;i<32;i++)mi[i]=2000000000,ma[i]=-2000000000;
    while(n--){
        for(int i=0;i<5;i++)scanf("%lf",&a[i]);
        for(int i=0;i<32;i++){
            double sum=0;
            for(int j=0;j<5;j++){
                if((i>>j)&1)sum+=a[j];
                else sum-=a[j];
            }
            if(sum>ma[i])ma[i]=sum;
            if(sum<mi[i])mi[i]=sum;
        }
    }
    double ans=0;
    for(int i=0;i<32;i++)
        if(ans<ma[i]-mi[i])ans=ma[i]-mi[i];
    printf("%.2lf\n",ans);
    return 0;
}
\end{lstlisting}
\subsection{前中推后序遍历}
\begin{lstlisting}
#include <stdio.h>
#include <string.h>
char pre[27],in[27];
void post(int s,int e ,int r){
	if(s>e)return;
	int i;
	for(i=s;i<=e&&pre[r]!=in[i];i++);
	post(s,i-1,r+1);
	post(i+1,e,r-s+i+1);
	printf("%c",pre[r]);
}
int main(){
	while(scanf("%s%s",pre,in)!=EOF){
		post(0,strlen(pre)-1,0);
		printf("\n");
	}
	return 0;
}
\end{lstlisting}
\subsection{匹配次数}
\begin{lstlisting}
void get_next(char t[],int len){
    for(int i=0,j=-1;i<=len;i++,j++){
        next[i]=j;
        while(j!=-1&&t[i]!=t[j])j=next[j];
    }
}
int kmp(char s[],char t[]){
    int len=strlen(t)-1,tim=0;
    for(int i=0,j=0;s[i];i++,j++){
        if(j==len&&s[i]==t[j]){j=next[j];tim++;}
        while(j!=-1&&s[i]!=t[j])j=next[j];
    }
    return tim;
}
//最大循环
//int ans=1;
//if(len%(len-next[len])==0)ans=len/(len-next[len]);
\end{lstlisting}
\subsection{二维RMQ}
\begin{lstlisting}
for(int i=0;R[i]=1<<i,R[i]<MAXN;i++);
void RM(){
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            dp[0][0][i][j]=a[i][j];
    for(int i=0;R[i]<=n;i++)
        for(int j=0;R[j]<=m;j++)
            if(i||j)
                for(int ii=0;ii+R[i]<=n;ii++)
                    for(int jj=0;jj+R[j]<=m;jj++)
                        if(i)dp[i][j][ii][jj]=min(dp[i-1][j][ii][jj],dp[i-1][j][ii+R[i-1]][jj]);
                        else dp[i][j][ii][jj]=min(dp[i][j-1][ii][jj],dp[i][j-1][ii][jj+R[j-1]]);
}
int Q(int r1,int c1,int r2,int c2){
    int i=0,j=0,h=(r2-r1+1)>>1,w=(c2-c1+1)>>1;
    while(R[i]<=h)i++;
    while(R[j]<=w)j++;
    int ii=r2-R[i]+1,jj=c2-R[j]+1;
    return min(min(dp[i][j][ii][c1],dp[i][j][r1][jj]),min(dp[i][j][r1][c1],dp[i][j][ii][jj]));
}
\end{lstlisting}