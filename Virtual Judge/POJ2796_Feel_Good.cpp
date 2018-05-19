#include<cstdio>
#include<algorithm>
using namespace std;
const long long MAXN=100005;

long long n,h[MAXN],s[MAXN];
long long l[MAXN],r[MAXN];
long long stk[MAXN],tp;

int main()
{
	while(scanf("%lld",&n)!=EOF)
	{
		for(long long i=1;i<=n;i++)
		{
			scanf("%lld",h+i);
			s[i]=s[i-1]+h[i];
		}
		l[1]=1;
		stk[1]=1;tp=1;
		for(long long i=2;i<=n;i++)
		{
			while(tp>0&&h[stk[tp]]>=h[i])
				tp--;
			l[i]=tp==0?1:stk[tp]+1;
			stk[++tp]=i;
		}
		r[n]=n;
		stk[1]=n;tp=1;
		for(long long i=n-1;i>=1;i--)
		{
			while(tp>0&&h[stk[tp]]>=h[i])
				tp--;
			r[i]=tp==0?n:stk[tp]-1;
			stk[++tp]=i;
		}
		long long ans=-1;
		long long ll=1,rr=1;
		for(long long i=1;i<=n;i++)
			if(ans<1LL*(s[r[i]]-s[l[i]-1])*h[i])
				ans=1LL*(s[r[i]]-s[l[i]-1])*h[i],ll=l[i],rr=r[i];
		printf("%lld\n",ans);
		printf("%lld %lld\n",ll,rr);
	}

	return 0;
}
