#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;

class Egalitarianism2
{
    static const int MAXN=22,MAXM=405;

    struct Edge
    {
        static double ave;
        int u,v;
        double d;
        Edge(){}
        Edge(int _u,int _v,double _d)
        {u=_u;v=_v;d=_d;}
        bool operator < (const Edge &b)const
        {return (d-ave)*(d-ave)<(b.d-ave)*(b.d-ave);}
    };
    struct DSU
    {
        int fa[MAXN];
        void Clear()
        {memset(fa,-1,sizeof fa);}
        int Root(int x)
        {
            if(fa[x]==-1)
                return x;
            return fa[x]=Root(fa[x]);
        }
        bool Union(int x,int y)
        {
            int r1=Root(x),r2=Root(y);
            if(r1==r2)
                return false;
            fa[r1]=r2;
            return true;
        }
    };

    int n,m,p;
    Edge edges[MAXM];
    int use[MAXM];
    double val[MAXM*MAXM];
    DSU D;
public:
    double minStdev(const vector<int> &x,const vector<int> &y)
    {
        n=x.size();
        m=0;
        for(int i=0;i<n;i++)
            for(int j=i+1;j<n;j++)
                edges[++m]=Edge(i,j,sqrt(1.0*(x[i]-x[j])*(x[i]-x[j])+1.0*(y[i]-y[j])*(y[i]-y[j])));
        p=0;
        for(int i=1;i<=m;i++)
            for(int j=i+1;j<=m;j++)
                val[++p]=(edges[i].d+edges[j].d)/2.0;
        double ans=1e100;
        for(int i=1;i<=p;i++)
        {
            Edge::ave=val[i];
            sort(edges+1,edges+m+1);
            D.Clear();
            for(int j=1;j<=m;j++)
                if(D.Union(edges[j].u,edges[j].v))
                    use[j]=i;
            double ave=0.0,sum=0.0;
            for(int j=1;j<=m;j++)
                if(use[j]==i)
                    ave+=edges[j].d;
            ave/=(n-1);
            for(int j=1;j<=m;j++)
                if(use[j]==i)
                    sum+=(edges[j].d-ave)*(edges[j].d-ave);
            sum=sqrt(sum/(n-1));
            ans=min(ans,sum);
        }
        return ans;
    }
};
double Egalitarianism2::Edge::ave;
/*
int main()
{
    vector<int> x,y;
    Egalitarianism2 *solver;
    int T,n;
    scanf("%d",&T);
    while(T--)
    {
        x.clear();
        y.clear();
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            int t;
            scanf("%d",&t);
            x.push_back(t);
        }
        for(int i=1;i<=n;i++)
        {
            int t;
            scanf("%d",&t);
            y.push_back(t);
        }
        solver=new Egalitarianism2;
        printf("%.9lf\n",solver->minStdev(x,y));
        delete solver;
    }

    return 0;
}
*/
