\section{Splay tree}
具体题目修改push down,push up,newnode,op,make等\\
\subsection{替代常规线段树}
pushdown的时候注意更新所有pushup需要的变量\\
\begin{lstlisting}
#include <stdio.h>
#define N 10010
#define key (ch[ch[root][1]][0])
#define oo 2000000000
typedef long long LL;
int need[20];
int mi[N],exp[N],lev[N],add[N],mxl[N],mx[N];
int ch[N][2],pre[N],sz[N];//固有变量
int root,id;
#define min(a,b) ((a)<(b)?(a):(b))
inline void update_mx(int &x,int &id,int xx,int iid){
    if(x<xx)x=xx,id=iid;
}
inline void update_exp(int &x,int &k,int c){
    x+=k*c;
    while(x>=need[k+1])k++;
}
void push_down(int x){
    if(add[x]){
        update_exp(exp[x],lev[x],add[x]);
        update_exp(mx[x],mxl[x],add[x]);
        mi[x]-=add[x];//
        int l=ch[x][0],r=ch[x][1];
        if(l)add[l]+=add[x];
        if(r)add[r]+=add[x];
        add[x]=0;//
    }
}
void push_up(int x){
    int l=ch[x][0],r=ch[x][1];
    push_down(x);
    if(l){
        if(add[l]>=mi[l])push_up(l);//递归更新，特殊～～
        else push_down(l);
    }
    if(r){
        if(add[r]>=mi[r])push_up(r);
        else push_down(r);
    }
    sz[x]=1+sz[l]+sz[r];
    mx[x]=exp[x],mxl[x]=lev[x];//splay的某些值不能滞留
    update_mx(mx[x],mxl[x],mx[l],mxl[l]);
    update_mx(mx[x],mxl[x],mx[r],mxl[r]);
    mi[x]=(need[lev[x]+1]-exp[x]-1)/lev[x]+1;//去滞留
    mi[x]=min(mi[x],mi[l]);
    mi[x]=min(mi[x],mi[r]);
}
int newnode(int f){
    int x=id++;//这里包括空节点的信息
    mi[x]=oo,mxl[x]=lev[x]=1,exp[x]=add[x]=mx[x]=0;
    ch[x][0]=ch[x][1]=0;
    sz[x]=1;
    pre[x]=f;
    return x;
}
int make(int l,int r,int f){
    if(l>r)return 0;
    int m=(l+r)>>1,x=newnode(f);
    ch[x][0]=make(l,m-1,x);
    ch[x][1]=make(m+1,r,x);
    push_up(x);
    return x;
}
void rot(int x,int f){
    int y=pre[x],z=pre[y];
    push_down(y);
    push_down(x);
    ch[y][!f]=ch[x][f];
    pre[ch[x][f]]=y;
    pre[x]=z;
    if(z)ch[z][ch[z][1]==y]=x;
    ch[x][f]=y;
    pre[y]=x;
    push_up(y);
}
void splay(int x,int goal){
    push_down(x);
    while(pre[x]!=goal){
        int y=pre[x],z=pre[y];
        if(z==goal){
            rot(x,ch[y][0]==x);
        }else{
            int f=(ch[z][0]==y);
            (ch[y][f]==x)?rot(x,!f):rot(y,f);
            rot(x,f);
        }
    }
    push_up(x);
    if(goal==0)root=x;
}
void init(int n){
    id=0;
    newnode(0);
    sz[0]=0;
    root=newnode(0);
    ch[root][1]=newnode(root);
    key=make(0,n-1,ch[root][1]);
    splay(key,0);
}
int getk(int k,int x){
    push_down(x);
    if(sz[ch[x][0]]==k)return x;
    if(sz[ch[x][0]]>k)return getk(k,ch[x][0]);
    return getk(k-sz[ch[x][0]]-1,ch[x][1]);
}
void rotk(int k,int goal){
    splay(getk(k,root),goal);
}
char s[2];
void op(){
    int l,r,e;
    scanf("%s%d%d",s,&l,&r);
    rotk(l-1,0);
    rotk(r+1,root);
    if(s[0]=='W'){
        scanf("%d",&e);
        add[key]+=e;
    }else printf("%d\n",mx[key]);
}
int main(){
    int T,n,m,q,cas=1;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d",&n,&m,&q);
        need[1]=0,need[m+1]=oo;
        for(int i=2;i<=m;i++)scanf("%d",&need[i]);
        init(n);
        printf("Case %d:\n",cas++);
        while(q--)op();
        puts("");
    }
    return 0;
}
\end{lstlisting}
\subsection{插入 删除 修改 翻转 求和 求最大子列}
erase:删除包括x及其子节点在内的所有节点，注意孩子更为0\\
\begin{lstlisting}
#include <stdio.h>
#include <limits.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define N 600010
#define inf 100000000
#define key (ch[ch[root][1]][0])
 
int ch[N][2];
int pre[N];
int sz[N];
int val[N];
int top1, top2, root;
int ss[N], q[N];
 
bool same[N];
bool rev[N];
int sum[N];
int ma[N], ml[N], mr[N];
 
void push_down(int x) {
    int l = ch[x][0], r = ch[x][1];
    if (same[x]) {
        same[x] = 0;
        same[l] = 1;
        same[r] = 1;
        val[l] = val[r] = val[x];
        sum[x] = val[x] * sz[x];
        ma[x] = ml[x] = mr[x] = max(val[x], sum[x]);
    }
    if (rev[x]) {
        rev[x] = 0;
        rev[l] = !rev[l];
        rev[r] = !rev[r];
        swap(ch[x][0], ch[x][1]);
        swap(ml[x], mr[x]);
    }
}
 
void push_up(int x) {
    int l = ch[x][0], r = ch[x][1];
    push_down(x);
    if(l)push_down(l);
    if(r)push_down(r);
    sz[x] = 1 + sz[l] + sz[r];
    sum[x] = val[x] + sum[l] + sum[r];
    ml[x]=max(ml[l],sum[l]+val[x]+max(0,ml[r]));
    mr[x]=max(mr[r],sum[r]+val[x]+max(0,mr[l]));
    ma[x]=max(ma[l],ma[r]);
    ma[x]=max(ma[x],max(ml[x],mr[x]));
    ma[x]=max(ma[x],val[x]+max(0,mr[l])+max(0,ml[r]));
}
 
void erase(int x) {
    ss[top2++] = x;
    if (ch[x][0])erase(ch[x][0]);
    if (ch[x][1])erase(ch[x][1]);
}
 
int newnode(int f) {
    int x;
    if (top2)x = ss[--top2];
    else x = ++top1;
    ch[x][0] = ch[x][1] = rev[x] = same[x] = 0;
    sz[x] = 1;
    pre[x] = f;
    return x;
}
 
int make(int l, int r, int f) {//新建f的子树
    if (l > r)return 0;
    int m = (l + r) >> 1;
    int x = newnode(f);
    ch[x][0] = make(l, m - 1, x);
    scanf("%d", &val[x]);
    ch[x][1] = make(m + 1, r, x);
    push_up(x);
    return x;
}
 
void rot(int x, int f) {
    int y = pre[x], z = pre[y];
    push_down(y);
    push_down(x);
    ch[y][!f] = ch[x][f];
    pre[ch[x][f]] = y;
    pre[x] = z;
    if (z)ch[z][ch[z][1] == y] = x;
    ch[x][f] = y;
    pre[y] = x;
    push_up(y);
}
 
void splay(int x, int goal) {
    push_down(x);
    while (pre[x] != goal) {
        int y = pre[x], z = pre[y];
        if (z == goal) {
            rot(x, ch[y][0] == x);
        } else {
            int f = (ch[z][0] == y);
            (ch[y][f] == x) ? rot(x, !f) : rot(y, f);
            rot(x, f);
        }
    }
    push_up(x);
    if (goal == 0)root = x;
}
 
void init(int n) {//初始化
    val[0] = ma[0] = ml[0] = mr[0] = -inf;//空节点信息很重要 
    sum[0] = sz[0]= 0;
    top1 = top2 = 0;
    root = newnode(0);
    val[root] = -inf;//bug
    ch[root][1] = newnode(root);
    val[ch[root][1]] = -inf; //bug
    key = make(0, n - 1, ch[root][1]);
    splay(key, 0);
}
 
int getk(int k, int x) {
    push_down(x);
    if (sz[ch[x][0]] == k)return x;
    if (sz[ch[x][0]] > k)return getk(k, ch[x][0]);
    return getk(k - sz[ch[x][0]] - 1, ch[x][1]);
}
 
void rotk(int k, int goal) {
    splay(getk(k, root), goal);
}
 
void insert() {
    int x, n;
    scanf("%d%d", &x, &n);
    rotk(x, 0);
    rotk(x + 1, root);
    key = make(0, n - 1, ch[root][1]);
    splay(key, 0);
}
 
void del() {
    int x, k;
    scanf("%d%d", &x, &k);
    rotk(x - 1, 0);
    rotk(x + k, root);
    erase(key);
    key = 0;
    splay(ch[root][1], 0);
}
 
void make_same() {
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    rotk(x - 1, 0);
    rotk(x + y, root);
    x = key;
    same[x] = 1;
    val[x] = z;
    splay(key, 0);
}
 
void reverse() {
    int x, k;
    scanf("%d%d", &x, &k);
    rotk(x - 1, 0);
    rotk(x + k, root);
    rev[key] = !rev[key];
    splay(key, 0);
}
 
void get_sum() {//区间和
    int x, k;
    scanf("%d%d", &x, &k);
    rotk(x - 1, 0);
    rotk(x + k, root);
    printf("%d\n", sum[key]);
}
 
void max_sum() {//最大子段和
    push_down(root);
    push_up(root);
    printf("%d\n", ma[root]);
}
 
void debug(int x) {
    if (x == 0)return;
    push_down(x);
    debug(ch[x][0]);
    printf("id=%2d l=%2d r=%2d sz=%2d val=%2d sum=%2d ml=%2d mr=%2d ma=%2d\n", 
		   x, ch[x][0], ch[x][1], sz[x], val[x], sum[x], ml[x], mr[x], ma[x]);
    debug(ch[x][1]);
}
 
void debug() {
    printf("root=%d\n", root);
    debug(root);
}
 
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    init(n);
    //st.debug();
    while (m--) {
        char s[100];
        scanf("%s", s);
        if (strcmp(s, "INSERT") == 0) {
            insert();
        } else if (strcmp(s, "DELETE") == 0) {
            del();
        } else if (strcmp(s, "MAKE-SAME") == 0) {
            make_same();
        } else if (strcmp(s, "REVERSE") == 0) {
            reverse();
        } else if (strcmp(s, "GET-SUM") == 0) {
            get_sum();
        } else if (strcmp(s, "MAX-SUM") == 0) {
            max_sum();
        }
        //debug();
    }
}
\end{lstlisting}
