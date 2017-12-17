#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=200005;

int A[MAXN];
bool del[MAXN];
int main()
{
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	if(k==1){printf("%d\n",n);return 0;}
	for(int i=1;i<=n;i++)
		scanf("%d",A+i);
	sort(A+1,A+n+1);
	int c=1,l=1,r=1,ans=0;
	while(r<=n)
	{
		if(A[r]-A[l]+1<=m&&c>=k)
		{
			del[r]=1;
			r++;
			ans++;
			continue;
		}
		if(A[r]-A[l]+1<=m&&c<k)
		{
			r++;
			c++;
			continue;
		}
		if(A[r]-A[l]+1>m)
		{
			c--;
			do
				l++;
			while(del[l]==1);
		}
	}
	printf("%d\n",ans);
	return 0;
}
