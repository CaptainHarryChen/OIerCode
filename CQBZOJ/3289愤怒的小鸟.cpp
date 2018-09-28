#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=20,MAXS=(1<<18)+10;
const double EPS=1e-8;

int dcmp(double a,double b)
{
    if(fabs(a-b)<=EPS)
        return 0;
    return a>b?1:-1;
}

int T,n,m;
int step[MAXS];
int kill[MAXN*MAXN+MAXN],kcnt;
bool vis[MAXN];
double X[MAXN],Y[MAXN];

int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%lf%lf",&X[i],&Y[i]);
        kcnt=0;
        memset(vis,0,sizeof vis);
        for(int i=1;i<=n;i++)
            for(int j=i+1;j<=n;j++)
            {
                double u1=X[i]*X[i],v1=X[i],w1=Y[i];
                double u2=X[j]*X[j],v2=X[j],w2=Y[j];
                double a,b;
                if(dcmp(u1-u2*v1/v2,0.0)!=0)
                {
                    a=(w1-w2*v1/v2)/(u1-u2*v1/v2);
                    b=(w1-u1*a)/v1;
                }
                else if(dcmp(v1-v2*u1/u2,0.0)!=0)
                {
                    b=(w1-w2*u1/u2)/(v1-v2*u1/u2);
                    a=(w1-v1*b)/u1;
                }
                else
                    continue;
                int st=0;
                if(dcmp(a,0.0)>=0)
                    continue;
                for(int k=1;k<=n;k++)
                    if(dcmp(a*X[k]*X[k]+b*X[k],Y[k])==0)
                        st|=(1<<(k-1)),vis[k]=true;
                kill[++kcnt]=st;
            }
        memset(step,0x3F,sizeof step);
        step[0]=0;
        for(int i=1;i<=n;i++)
            if(!vis[i])
                kill[++kcnt]=(1<<(i-1));
        for(int s=0;s<(1<<n);s++)
            for(int i=1;i<=kcnt;i++)
                step[s|kill[i]]=min(step[s|kill[i]],step[s]+1);
        printf("%d\n",step[(1<<n)-1]);
    }

    return 0;
}
