#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=2666666,MAXL=11;
const long long MAX=10000000000LL;

int siz,m;
pair<long long,long long> hjb[MAXN];
long long val[MAXN],way[MAXN];
long long pow10[MAXL];

void dfs(int step,int len,long long x,long long num)
{
    if(x>MAX)
        return;
    if(step*2>=len)
    {
        hjb[++siz]=make_pair(x,num);
        return;
    }
    bool flag=(step*2==len-1);
    for(int i=min(flag,(step==0));i<=(flag?9:18);i++)
    {
        int tmp=1;
        if(!flag)
        {
            if(i<=9)
                tmp=i+(step!=0);
            else
                tmp=18-i+1;
        }
        if(tmp<=0)
            continue;
        dfs(step+1,len,x+(pow10[step]+pow10[len-step-1])*i,num*tmp);
    }
}

int main()
{
    pow10[0]=1;
    for(int i=1;i<MAXL;i++)
        pow10[i]=pow10[i-1]*10;
    for(int i=1;i<MAXL;i++)
        dfs(0,i,0,1);
    sort(hjb+1,hjb+siz+1);
    for(int last=1,i=2;i<=siz+1;i++)
        if(hjb[i].first!=hjb[i-1].first)
        {
            val[++m]=hjb[last].first;
            for(int j=last;j<i;j++)
                way[m]+=hjb[j].second;
            last=i;
        }
    //for(int i=1;i<=m;i++)
    //    printf("(%lld,%lld)\n",val[i],way[i]);
    for(int i=1;i<=m;i++)
    {
        long long x=val[i],rval=0;
        while(x)
            rval=rval*10+x%10,x/=10;
        rval+=val[i];
        if(rval<=MAX)
            way[lower_bound(val+1,val+m+1,rval)-val]+=way[i];
    }
    for(int i=1;i<=m;i++)
    {
        //printf("(%lld,%lld)\n",val[i],way[i]);
        way[i]+=way[i-1];
    }
    int Q;
    scanf("%d",&Q);
    long long hmm=0;
    while(Q--)
    {
        long long l,r,p;
        scanf("%lld%lld%lld",&l,&r,&p);
        long long ans=way[upper_bound(val+1,val+m+1,r)-val-1]-way[lower_bound(val+1,val+m+1,l)-val-1]+r-l+1;
        ans%=p;
        //printf("%lld\n",ans);
        hmm^=ans;
    }
    printf("%lld\n",hmm);

    return 0;
}
