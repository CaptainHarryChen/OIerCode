#include<cstdio>
#include<algorithm>
using namespace std;
const long long MAXN=100005;

long long A,B,C;
long long st[MAXN],sb[MAXN];
long long n,m,t[MAXN],b[MAXN];

int main()
{
	scanf("%lld%lld%lld%lld%lld",&A,&B,&C,&n,&m);
	for(long long i=1;i<=n;i++)
		scanf("%lld",t+i);
	for(long long i=1;i<=m;i++)
		scanf("%lld",b+i);
	sort(t+1,t+n+1);
	sort(b+1,b+m+1);
	for(long long i=1;i<=n;i++)
		st[i]=st[i-1]+t[i];
	for(long long i=1;i<=m;i++)
		sb[i]=sb[i-1]+b[i];
	
	long long ans=0;
	long long T=b[m],last=m,wait=lower_bound(t+1,t+n+1,T)-t-1;
	ans=C*(wait*T-st[wait]);
	
	if(C>=1000000000000000LL)
	{
		ans=0x7FFFFFFFFFFFFFFFLL;
		T=t[1]+1;
	}
	
	for(T--;T>=t[1];T--)
	{
		while(wait>0&&t[wait]>=T)
			wait--;
		while(last>0&&b[last]>T)
			last--;
		
		long long add=0,unhap=0;
		if(A>=B)
			add=(sb[m]-sb[last]-T*(m-last))*B;
		else
		{
			long long l=T*last-sb[last],r=sb[m]-sb[last]-T*(m-last);
			if(l>=r)
				add=r*A;
			else
				add=l*A+(r-l)*B;
		}
		
		unhap=C*(wait*T-st[wait]);
		unhap+=add;
		
		ans=min(ans,unhap);
	}
	
	printf("%lld\n",ans);
	
	return 0;
}
