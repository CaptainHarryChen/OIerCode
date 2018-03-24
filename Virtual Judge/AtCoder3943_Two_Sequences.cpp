#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=300005,MAXL=28;
 
int n;
int A[MAXN],B[MAXN];
int a[MAXN],b[MAXN];
 
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",A+i);
	for(int i=1;i<=n;i++)
		scanf("%d",B+i);
	
	int ans=0;
	for(int k=0;k<=MAXL;k++)
	{
		memcpy(a,A,sizeof(int)*(n+1));
		memcpy(b,B,sizeof(int)*(n+1));
		int T=1<<k;
		for(int i=1;i<=n;i++)
		{
			a[i]%=2*T;
			b[i]%=2*T;
		}
		sort(b+1,b+n+1);
		int res=0;
		for(int i=1;i<=n;i++)
		{
			int *l=lower_bound(b+1,b+n+1,T-a[i]);
			int *r=lower_bound(b+1,b+n+1,T*2-a[i]);
			res^=((r-l)&1);
		}
		for(int i=1;i<=n;i++)
		{
			int *l=lower_bound(b+1,b+n+1,T*3-a[i]);
			int *r=lower_bound(b+1,b+n+1,T*4-a[i]);
			res^=((r-l)&1);
		}
		if(res)
			ans^=T;
	}
	
	printf("%d\n",ans);
	
	return 0;
}
