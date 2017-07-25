#include<cstdio>
const int MAXN=500005;
class BIT
{
	int sum[MAXN];
public:
	void add(int x,int val)
	{
		for(;x<MAXN;x+=(x&(-x)))
			sum[x]+=val;
	}
	int get(int x)
	{
		int ret=0;
		for(;x>0;x-=(x&(-x)))
			ret+=sum[x];
		return ret;
	}
};
int prime[41540],pcnt,sig[MAXN],pp[MAXN],ind[MAXN];
bool noprime[MAXN];
void list_sig()
{
	noprime[1]=1;
	sig[1]=1;
	pp[1]=1;
	for(int i=2;i<MAXN;i++)
	{
		if(!noprime[i])
		{
			prime[++pcnt]=i;
			sig[i]=2;
			ind[i]=1;
			pp[i]=i;
		}
		for(int j=1;j<=pcnt&&1LL*i*prime[j]<MAXN;j++)
		{
			noprime[i*prime[j]]=1;
			if(i%prime[j]==0)
			{
				ind[i*prime[j]]=ind[i]+1;
				pp[i*prime[j]]=pp[i]*prime[j];
				if(pp[i*prime[j]]==i*prime[j])
					sig[i*prime[j]]=ind[i*prime[j]]+1;
				else
					sig[i*prime[j]]=sig[pp[i*prime[j]]]*sig[i*prime[j]/pp[i*prime[j]]];
				break;
			}
			sig[i*prime[j]]=sig[i]*2;
			ind[i*prime[j]]=1;
			pp[i*prime[j]]=prime[j];
		}
	}
}
char name[MAXN][15];
int card[MAXN];
BIT cnt;
int main()
{
	list_sig();
	int N,K,now;
	while(scanf("%d%d",&N,&K)!=EOF)
	{
		for(int i=1;i<=N;i++)
		{
			scanf("%s%d",name[i],card+i);
			cnt.add(i,1);
		}
		int step=0,ans=0;
		for(int i=1;i<=N;i++)
			if(sig[i]>ans)
			{
				ans=sig[i];
				step=i;
			}
		now=0;
		int tmp,l,r,mid;
		for(int i=1;i<=step;i++)
		{
			if(K>0)
				K=(K-1)%(N-i+1)+1;
			else
			{
				K=(K+1)%(N-i+1)-1;
				K+=(N-i+2);
			}
			tmp=cnt.get(N)-cnt.get(now);
			if(tmp<K)
			{
				K-=tmp;
				now=0;
			}
			l=now;r=N;
			while(l<r)
			{
				mid=(l+r)>>1;
				if(cnt.get(mid)-cnt.get(now)>=K)
					r=mid;
				else
					l=mid+1;
			}
			now=l;
			K=card[now];
			cnt.add(now,-1);
		}
		printf("%s %d\n",name[now],ans);
	}
	return 0;
}
