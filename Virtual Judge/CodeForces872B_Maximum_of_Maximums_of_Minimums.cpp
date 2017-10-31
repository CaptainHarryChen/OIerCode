#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005;
int A[MAXN];
int main()
{
	int n,k,mn=0x7FFFFFFF,mx=-0x7FFFFFFF;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",A+i);
		mn=min(mn,A[i]);
		mx=max(mx,A[i]);
	}
	if(k==1)
		printf("%d\n",mn);
	else if(k==2)
	{
		int ans1=A[1],ans2=A[n];
		for(int i=2;i<=n;i++)
			if(A[i]<ans1)
				break;
		for(int i=n-1;i>0;i--)
			if(A[i]<ans2)
				break;
		printf("%d\n",max(ans1,ans2));
	}
	else if(k>2)
		printf("%d\n",mx);
	return 0;
}
