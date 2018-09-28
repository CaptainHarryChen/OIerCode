#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005;

int N,Q,tp;
long long q[MAXN],stk[MAXN];
long long sum[MAXN],cnt[MAXN];

int main()
{
    scanf("%d%d",&N,&Q);
    for(int i=1;i<=Q;i++)
        scanf("%lld",&q[i]);
    stk[tp=1]=N;
    for(int i=1;i<=Q;i++)
    {
        while(tp&&stk[tp]>=q[i])
            tp--;
        stk[++tp]=q[i];
    }

	cnt[tp]=1;
	for(int i=tp;i>0;i--)
	{
		long long k=stk[i];
		int p=i-1;
		while(p)
		{
			cnt[p]+=(k/stk[p])*cnt[i];
			k%=stk[p];
			p=lower_bound(stk+1,stk+p,k)-stk;
			p--;
		}
		sum[1]+=cnt[i];
		sum[k+1]-=cnt[i];
		//printf("Add(1,%lld)\n",k);
	}
	long long ans=0;
	for(int i=1;i<=N;i++)
	{
		ans+=sum[i];
		printf("%lld\n",ans);
	}

    fclose(stdin);
    fclose(stdout);
    return 0;
}
