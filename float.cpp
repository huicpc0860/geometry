\section{计算几何之浮点数}
\begin{lstlisting}
extern float frexp(float x, int *exp);
//把浮点数x分解成尾数和指数.
extern float hypot(float x, float y);
//对于给定的直角三角形的两个直角边，求其斜边的长度。
extern float modf(float num, float *i);
//将浮点数num分解成整数部分和小数部分。
extern float sinh(float x);
//计算x（弧度表示）的双曲正弦值。sinh(x)=(e^x-e^(-x))/2。
extern float cosh(float x);
//求x的双曲余弦值,cosh(x)=(e^x+e^(-x))/2
extern float tanh(float x);
//求x的双曲正切值,tanh(x)=(e^x-e^(-x))/(e^2+e^(-x))
\end{lstlisting}
\subsection{浮点数修正}
\begin{lstlisting}
inline dd fix(dd x,int t=0){
    if(t==0)rt x>-eps?x+eps:x-eps; //output for double
    if(t==1){ //for sqrt & log
        rt x+(x<eps?eps:0);
    }
    if(t==2){ //for sin & cos
        if(x>1)rt 1;
        if(x<-1)rt -1;
        rt x;
    }
}
\end{lstlisting}
\subsection{读入优化}
万不得已时用，计算规则和scanf有出入，可能会出错。
\begin{lstlisting}
inline void in(dd &x){
    x=0;
    char c;
    while(c=getchar(),(c<'0'||c>'9')&&c!='-'&&c!='.');
    dd f=1;
    if(c!='.'){
        if(c=='-')f=-1;
        else x=c-'0';
        while(c=getchar(),c>='0'&&c<='9')x=x*10+c-'0';
    }
    if(c=='.'){
        dd t=1;
        while(c=getchar(),c>='0'&&c<='9')t*=0.1,x+=t*(c-'0');
    }
    x=f*x;
}
\end{lstlisting} 
