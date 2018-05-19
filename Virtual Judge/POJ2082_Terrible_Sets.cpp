#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=50005;

int n,w[MAXN],h[MAXN];
int l[MAXN],r[MAXN];
int stk[MAXN],tp;

int main()
{
	for(;;)
	{
		scanf("%d",&n);
		if(n==-1)
			break;
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",w+i,h+i);
			w[i]+=w[i-1];
		}
		l[1]=1;
		stk[1]=1;tp=1;
		for(int i=2;i<=n;i++)
		{
			while(tp>0&&h[stk[tp]]>=h[i])
				tp--;
			l[i]=tp==0?1:stk[tp]+1;
			stk[++tp]=i;
		}
		r[n]=n;
		stk[1]=n;tp=1;
		for(int i=n-1;i>=1;i--)
		{
			while(tp>0&&h[stk[tp]]>=h[i])
				tp--;
			r[i]=tp==0?n:stk[tp]-1;
			stk[++tp]=i;
		}
		long long ans=0;
		for(int i=1;i<=n;i++)
			ans=max(ans,1LL*(w[r[i]]-w[l[i]-1])*(min(h[i],min(h[l[i]],h[r[i]]))));
		printf("%lld\n",ans);
	}
	return 0;
}
