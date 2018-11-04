#include<cstdio>
#include<cstring>
#include<set>
#include<algorithm>
using namespace std;
const int MAXN=100005;

long long MulMod(long long a,long long b,long long p)
{
    long long res=0;
    while(b)
    {
        if(b&1)
            res=(res+a)%p;
        a=(a+a)%p;
        b>>=1;
    }
    return res;
}

long long gcd(long long a,long long b)
{return b==0?a:gcd(b,a%b);}
void exgcd(long long a,long long b,long long &x,long long &y)
{
    if(b==0)
    {
        x=1;y=0;
        return;
    }
    exgcd(b,a%b,y,x);
    y-=x*(a/b);
}

int n,m;
long long a[MAXN],p[MAXN],rew[MAXN],atk[MAXN],t[MAXN];

multiset<long long> sword;

void Clear()
{
    sword.clear();
}

bool GetEquation()
{
    for(int i=1;i<=n;i++)
    {
        set<long long>::iterator choose=sword.lower_bound(a[i]);
        if(*choose!=a[i]&&choose!=sword.begin())
            choose--;
        atk[i]=*choose;
        long long d=gcd(atk[i],p[i]);
        if(a[i]%d!=0)
            return false;
        long long x,y;
        p[i]/=d;
        exgcd(atk[i]/d,p[i],x,y);
        x=MulMod(x,a[i]/d,p[i]);
        x=(x+p[i])%p[i];
        t[i]=x;
        sword.erase(choose);
        sword.insert(rew[i]);
    }
    return true;
}
bool SolveEquation(pair<long long,long long> &ans)
{
    long long A=p[1],B=t[1];
    for(int i=2;i<=n;i++)
    {
        long long g=gcd(A,p[i]),l=A/g*p[i];
        if((t[i]-B)%g!=0)
            return false;
        long long k,tmp;
        exgcd(A,p[i],k,tmp);
        k=(MulMod(k,(((t[i]-B)/g)%p[i]+p[i])%p[i],p[i])+p[i])%p[i];
        B=(MulMod(A,k,l)+B)%l;
        A=l;
    }
    ans.first=B;
    ans.second=A;
    return true;
}

int main()
{
	int T;
    scanf("%d",&T);
    while(T--)
    {
        Clear();

        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%lld",&a[i]);
        for(int i=1;i<=n;i++)
            scanf("%lld",&p[i]);
        for(int i=1;i<=n;i++)
            scanf("%lld",&rew[i]);
        for(int i=1;i<=m;i++)
        {
            long long x;
            scanf("%lld",&x);
            sword.insert(x);
        }

        if(!GetEquation())
        {
            puts("-1");
            continue;
        }
        pair<long long,long long> ans;
        if(!SolveEquation(ans))
        {
            puts("-1");
            continue;
        }

        for(int i=1;i<=n;i++)
            if(ans.first*atk[i]<a[i])
                ans.first+=((a[i]-ans.first*atk[i]+atk[i]-1)/atk[i]);

        printf("%lld\n",ans.first);
    }
    return 0;
}
