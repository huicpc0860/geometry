\section{随机增量}
\subsection{点集最小周长三角形}
grid 与 key 作为成员函数，并且表示点与格点两种信息，使用时有key(){grid()}的错误,重复hash。\\
i点如果可以更新最优值，更新hash表，否则加入i点。\\
\begin{lstlisting}
#define F 971
#define H 65535
#define ct const
#define cpt ct pt&
#define rt return
#define dd double
#define op operator
dd ans;
struct pt{
    int x,y;
    void get(){scanf("%d%d",&x,&y);}
    void out(){printf("%d %d\n",x,y);}
    pt(int x=0,int y=0):x(x),y(y){}
    pt op+(cpt p)ct{rt pt(x+p.x,y+p.y);}
    pt op-(cpt p)ct{rt pt(x-p.x,y-p.y);}
    dd abs(){rt sqrt(1.0*x*x+1.0*y*y);}
    pt grid()ct{
        int size=ans/2;
        rt pt(x/size+1,y/size+1);
    }
    int key(){
        rt (x*F+y)&H;
    }
}p[20010],dir[9];
int n;
int head[H];
pt ss[20010];
int ID;
void insert(int id){
    int key=p[id].grid().key();
    ss[ID].x=id;
    ss[ID].y=head[key];
    head[key]=ID++;
}
void refresh(int n){
    memset(head,-1,sizeof(head));
    ID=0;
    for(int i=0;i<n;i++){
        insert(i);
    }
}

int eve[20010];
int e;
void get_pt(cpt t){
    pt grid=t.grid();
    e=0;
    for(int i=0;i<9;i++){
        int key=(grid+dir[i]).key();
        for(int j=head[key];~j;j=ss[j].y){
            if((t-p[ss[j].x]).abs()<ans/2){
                eve[e++]=ss[j].x;
            }
        }
    }
}

dd calc(cpt a,cpt b,cpt c){
    rt (a-b).abs()+(b-c).abs()+(a-c).abs();
}

int main(){
    srand(time(0));
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++){
            dir[i*3+j]=pt(i-1,j-1);
        }
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=0;i<n;i++){
            p[i].get();
        }
        for(int i=0;i<n;i++){
            swap(p[i],p[rand()%n]);
        }
        ans=calc(p[0],p[1],p[2]);
        refresh(3);
        for(int i=3;i<n;i++){
            get_pt(p[i]);
            dd now=1e100;
            for(int j=0;j<e;j++){
                if(i==eve[j])continue;
                for(int k=j+1;k<e;k++){
                    if(i==eve[k]||eve[j]==eve[k])continue;
                    now=min(now,calc(p[i],p[eve[j]],p[eve[k]]));
                }
            }
            if(now<ans){
                ans=now;
                refresh(i+1);
            }else{
                insert(i);
            }
        }
        printf("%.3lf\n",ans);
    }
}
\end{lstlisting}