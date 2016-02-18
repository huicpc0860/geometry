\section{搜索}
\subsection{8数码双向广搜}
记得初始化\\
\begin{lstlisting}
int fac[10],ans=-1,v[362880]={0},dir[4]={-3,-1,1,3},mulfac[9][9];
bool forbid[9][4]={
	{1,1,0,0},
	{1,0,0,0},
	{1,0,1,0},
	{0,1,0,0},
	{0,0,0,0},
	{0,0,1,0},
	{0,1,0,1},
	{0,0,0,1},
	{0,0,1,1}
};
struct point{
    int a[9],id,x;
    void get(){
        for(int i=0,t;i<9;i++){
            scanf("%d",&t);
            if(t==0)x=i;
            a[i]=t;
        }
        map();
    }
    void swap(int y){
        int t=a[y];
        a[y]=a[x];
        a[x]=t;
        x=y;
    }
    void map(){
        id=0;
        for(int i=1;i<9;i++){
            int c=0;
            for(int j=0;j<i;j++)
                if(a[j]>a[i])c++;
            id+=mulfac[c][i];
        }
    }
    int res(){
        int cnt=0;
        for(int i=0;i<9;i++){
            if(a[i]==0)continue;
            for(int j=0;j<i;j++)
                if(a[j]>a[i])cnt++;}
        return cnt&1;
    }
};
struct queue{
    int fg,step;
    point q[10000],*s,*e;
    int init(int x){
        s=q;
        e=q+1;
        fg=x;
        s->get();
        v[s->id]=fg;
        step=0;
        return s->res();
    }
    int promote(){
        for(point *t=e;s!=t;s++){
            for(int i=0;i<4;i++){
                if(forbid[s->x][i])continue;
                point p=*s;
                p.swap(p.x+dir[i]);
                p.map();
                if(!v[p.id]){
                    v[p.id]=fg;
                    *e++=p;
                }else if(v[p.id]!=fg)return 0;
            }
        }
        step++;
        return 1;
    }
}q1,q2;
int main(){
    fac[0]=1;
    for(int i=1;i<9;i++)
        fac[i]=i*fac[i-1];
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++)
            mulfac[i][j]=i*fac[j];
    }
    if(q1.init(1)==q2.init(2)){
        if(q1.s->id==q2.s->id)ans=0;
        else{
            while(q1.promote()&&q2.promote());
            ans=q1.step+q2.step+1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
\end{lstlisting}
\subsection{15数码IDA*}
\begin{lstlisting}
int a[16], k, p;
char path[100];
char ch[] = {'L', 'U', 'D', 'R'};
int dir[] = {-1, -4, 4, 1};
int m[16][16] = {0};
bool go[][4] = {
    0, 0, 1, 1,
    1, 0, 1, 1,
    1, 0, 1, 1,
    1, 0, 1, 0,
    0, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 0,
    0, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 0,
    0, 1, 0, 1,
    1, 1, 0, 1,
    1, 1, 0, 1,
    1, 1, 0, 0,
};

struct point {
    int x, y;

    bool operator<(const point & p)const {
        return x < p.x;
    }
};

void swap(int i) {
    a[p] = a[p + dir[i]];
    a[p += dir[i]] = 0;
}

bool dfs(int step, int mht, int x) {
    if (mht == 0) {
        path[step] = 0;
        puts(path);
        return 1;
    }
    int cnt = 0;
    point c[4];
    for (int i = 0; i < 4; i++) {
        if (!go[p][i] || i == x)continue;
        int t = p + dir[i];
        c[cnt].x = mht + m[p][a[t] - 1] - m[t][a[t] - 1];
        if (c[cnt].x + step <= k)c[cnt++].y = i;
    }
    sort(c, c + cnt);
    for (int i = 0; i < cnt; i++) {
        path[step] = ch[c[i].y];
        swap(c[i].y);
        if (dfs(step + 1, c[i].x, 3 - c[i].y))return 1;
        swap(3 - c[i].y);
    }
    return 0;
}

int main() {
    for (int i = 0; i < 16; i++)
        for (int j = i + 1; j < 16; j++)
            m[i][j] = m[j][i] = abs(i / 4 - j / 4) + abs(i % 4 - j % 4);
    int T;
    scanf("%d", &T);
    while (T--) {
        int cnt = 0;
        for (int i = 0; i < 16; i++) {
            scanf("%d", &a[i]);
            if (a[i] == 0)p = i;
            for (int j = 0; j < i; j++)
                cnt += a[j] > a[i];
        }
        if (((cnt + m[p][15])&1) == 0)
            puts("This puzzle is not solvable.");
        else {
            int mht = 0;
            for (int i = 0; i < 16; i++)
                if (a[i]) mht += m[i][a[i] - 1];
            for (k = mht; k < 51 && !dfs(0, mht, -1); k++);
        }
    }
    return 0;
}
\end{lstlisting}
\subsection{使用回滚函数}
\begin{lstlisting}
int cnt[500];
int a[500];
vector<int> ans[10000];
vector<int> res;
int id, l, r, suml, sumr;
int m, n;

void rollback(int pos, bool type) {
    if (type == 0) {
        int x = 0;
        for (int i = l; i > pos; i--) {
            x += res[i];
            cnt[x]++;
        }
    } else {
        int x = 0;
        for (int i = l; i >= 0; i--) {
            x += res[i];
            cnt[x]++;
        }
        x = 0;
        for (int i = r; i < pos; i++) {
            x += res[i];
            cnt[x]++;
        }
    }
}

bool check(int x, bool type) {
    if (type == 0) {
        if (x <= sumr)return 0;
        res[r] = x - sumr;
        res[l] = a[m - 1] - x - suml;
        if (res[l] <= 0)return 0;
    } else {
        if (x <= suml)return 0;
        res[l] = x - suml;
        res[r] = a[m - 1] - x - sumr;
        if (res[r] <= 0)return 0;
    }
    x = 0;
    for (int i = l; i >= 0; i--) {
        x += res[i];
        if (cnt[x] == 0) {
            rollback(i, 0);
            return 0;
        }
        cnt[x]--;
    }
    x = 0;
    for (int i = r; i < n; i++) {
        x += res[i];
        if (cnt[x] == 0) {
            rollback(i, 1);
            return 0;
        }
        cnt[x]--;
    }
    return 1;
}

void dfs(int lim) {
    if (l == r) {
        ans[id++] = res;
        return;
    }
    while (cnt[a[lim]] == 0)lim--;
    if (check(a[lim], 0)) {
        suml += res[l];
        l++;
        dfs(lim);
        l--;
        suml -= res[l];
        res[r] = a[lim] - sumr;
        rollback(n, 1);
    }
    if (check(a[lim], 1)) {
        sumr += res[r];
        r--;
        dfs(lim);
        r++;
        sumr -= res[r];
        res[l] = a[lim] - suml;
        rollback(n, 1);
    }
}

int main() {
    while (scanf("%d", &n), n) {
        memset(cnt, 0, sizeof (cnt));
        m = n * (n - 1) / 2;
        n--;
        for (int i = 0; i < m; i++) {
            scanf("%d", &a[i]);
            cnt[a[i]]++;
        }
        sort(a, a + m);
        m = unique(a, a + m) - a;
        id = 0;
        res.resize(n);
        l = 0, r = n - 1, suml = 0, sumr = 0;
        cnt[a[m-1]]--;
        res[0]=a[m-1];
        dfs(m - 1);
        sort(ans, ans + id);
        id = unique(ans, ans + id) - ans;
        for (int i = 0; i < id; i++) {
            for (int j = 0; j < n; j++) {
                printf(j == n - 1 ? "%d\n" : "%d ", ans[i][j]);
            }
        }
        puts("-----");
    }
    return 0;
}
\end{lstlisting}
