#include<cstdio>
#include<algorithm>
using namespace std;
const long long MAXN=5,MOD=1000000007;

struct Matrix
{
    long long h,w,a[MAXN][MAXN];
    Matrix(){h=w=0;}
    Matrix(long long h,long long w,long long *A=NULL):h(h),w(w)
    {
        for(long long i=0;i<h;i++)
            for(long long j=0;j<w;j++)
                a[i][j]=(A==NULL)?0:(*(A+(i*w)+h));
    }
    long long * operator [] (int i)
    {return a[i];}
    Matrix operator * (const Matrix &t)const
    {
        Matrix res(0,0,NULL);
        long long l=t.h;
        if(l!=this->w)
            return res;
        long long h=this->h;
        long long w=t.w;
        res=Matrix(h,w);
        for(long long i=0;i<h;i++)
            for(long long j=0;j<w;j++)
                for(long long k=0;k<l;k++)
                    res.a[i][j]=(res.a[i][j]+a[i][k]*t.a[k][j]%MOD)%MOD;
        return res;
    }
    Matrix pow(long long b)const
    {
        Matrix res(0,0);
        if(h!=w)
            return res;
        Matrix d=*this;
        res=Matrix(h,w);
        for(long long i=0;i<h;i++)
            res.a[i][i]=1;
        while(b)
        {
            if(b&1)
                res=res*d;
            d=d*d;
            b>>=1;
        }
        return res;
    }
    void debug()
    {
        puts("---debug---");
        for(long long i=0;i<h;i++)
        {
            for(long long j=0;j<w;j++)
                printf("%I64d ",a[i][j]);
            puts("");
        }
        puts("===debug===");
    }
};

Matrix g,f;

int main()
{
    int T,A,B,C,D,P,n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d%d%d",&A,&B,&C,&D,&P,&n);
        if(n==1)
        {
            printf("%d\n",A);
            continue;
        }
        if(n==2)
        {
            printf("%d\n",B);
            continue;
        }
        f=Matrix(3,3);
        f[0][0]=D;f[0][1]=C;f[0][2]=1;
        f[1][0]=1;f[2][2]=1;
        //f.debug();
        int nxt=0;
        g=Matrix(3,1);
        g[0][0]=B;g[1][0]=A;
        //g.debug();
        for(int i=3;i<=n;i=nxt+1)
        {
            if(P<i)
                nxt=n;
            else
                nxt=min(n,(P/(P/i)));
            g[2][0]=P/i;
            g=f.pow(nxt-i+1)*g;
            //g.debug();
        }
        printf("%I64d\n",g[0][0]);
    }
    
    return 0;
}
