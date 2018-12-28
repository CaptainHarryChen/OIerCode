#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=100005;
const double EPS=1e-10;

struct Section
{
    int l,r;
    bool operator < (const Section &t)const
    {return make_pair(l,r)<make_pair(t.l,t.r);}
};

int n;
Section s[MAXN];

bool check(double len)
{
    double last=0.0;
    for(int i=1;i<=n;i++)
    {
        last=max(last,1.0*s[i].l);
        if(last+len>s[i].r)
            return false;
        last+=len;
    }
    return true;
}

int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        double L=0,R=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&s[i].l,&s[i].r);
            R=max(1.0*s[i].r-s[i].l,R);
        }
        sort(s+1,s+n+1);

        while(R-L>EPS)
        {
            double mid=(L+R)/2;
            if(check(mid))
                L=mid;
            else
                R=mid;
        }

        double ans=L,best=1e100;
        int p,q;

        for(int i=1;i<MAXN;i++)
        {
            double tmp=ans*i;
            int a=floor(tmp+0.5);
            if(fabs(tmp-a)<best)
            {
                best=fabs(tmp-a);
                p=a;
                q=i;
            }
        }
        printf("%d/%d\n",p,q);
    }

    return 0;
}
