#include<cstdio>
#include<cstring>
#include<cmath>
#include<map>
#include<algorithm>
using namespace std;
const int MOD=998244353;

class WrongBase
{
    map<int,int> mp;
    int PowMod(int a,int b)
    {
        int res=1;
        for(;b;b>>=1,a=1LL*a*a%MOD)
            if(b&1)
                res=1LL*res*a%MOD;
        return res;
    }
    int LogMod(int a,int b)
    {
        int m=ceil(sqrt(MOD+0.5));
        int z=PowMod(PowMod(a,m),MOD-2),x=1,y=b;
        mp.clear();
        mp[1]=0;
        for(int i=1;i<m;i++)
        {
            x=1LL*x*a%MOD;
            if(mp.count(x)==0)
                mp[x]=i;
        }
        for(int i=0;i<m;i++)
        {
            if(mp.count(y))
                return i*m+mp[y];
            y=1LL*y*z%MOD;
        }
        return -1;
    }
public:
    int getSum(int g,int h,int a,int d,int n)
    {
        if(h==0)
            return 0;
        int e=LogMod(g,h);
        int res=0;
        for(int i=1;i<=n;i++,a+=d)
            res=(res+PowMod(a,e))%MOD;
        return res;
    }
};
/*
WrongBase solver;

int main()
{
    int a,b,c,d,e;
    scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);
    printf("%d\n",solver.getSum(a,b,c,d,e));
    return 0;
}
*/