#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=200005;

int n,m,k,s;
int a[MAXN],b[MAXN],mina[MAXN],minb[MAXN],aid[MAXN],bid[MAXN],ans;

struct gadget
{
	int type,val,id;
	bool operator < (const gadget &t)const
	{
		long long v1=(type==1?1LL*mina[ans]*val:1LL*minb[ans]*val);
		long long v2=(t.type==1?1LL*mina[ans]*t.val:1LL*minb[ans]*t.val);
		return v1<v2;
	}
}G[MAXN];

int main()
{
	scanf("%d%d%d%d",&n,&m,&k,&s);
	mina[0]=0x7F7F7F7F;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",a+i);
		if(mina[i-1]<=a[i])
			mina[i]=mina[i-1],aid[i]=aid[i-1];
		else
			mina[i]=a[i],aid[i]=i;
	}
	minb[0]=0x7F7F7F7F;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",b+i);
		if(minb[i-1]<=b[i])
			minb[i]=minb[i-1],bid[i]=bid[i-1];
		else
			minb[i]=b[i],bid[i]=i;
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&G[i].type,&G[i].val);
		G[i].id=i;
	}
	
	int L=1,R=n;
	while(L<R)
	{
		int mid=(L+R)/2;
		ans=mid;
		sort(G+1,G+m+1);
		long long sum=0;
		for(int i=1;i<=k;i++)
			sum+=(G[i].type==1?1LL*G[i].val*mina[ans]:1LL*G[i].val*minb[ans]);
		if(sum>s)
			L=mid+1;
		else
			R=mid;
	}
	ans=L;
	sort(G+1,G+m+1);
	long long sum=0;
	for(int i=1;i<=k;i++)
		sum+=(G[i].type==1?1LL*G[i].val*mina[ans]:1LL*G[i].val*minb[ans]);
	if(sum>s)
		puts("-1");
	else
	{
		printf("%d\n",ans);
		for(int i=1;i<=k;i++)
			printf("%d %d\n",G[i].id,G[i].type==1?aid[ans]:bid[ans]);
	}
	
	return 0;
}
