#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005;
int c[MAXN],temp[MAXN];
int main()
{
	int n,k,ans;
	scanf("%d%d",&n,&k);
	if(k>=n)
	{
		puts("0");
		return 0;
	}
	for(int i=1;i<=n;i++)
		scanf("%d",c+i);
	sort(c+1,c+n+1);
	ans=c[n]-c[1];
	for(int i=1;i<n;i++)
		temp[i]=c[i]-c[i+1];
	sort(temp+1,temp+n);
	for(int i=1;i<k;i++)
		ans+=temp[i];
	printf("%d\n",ans);
	return 0;
}
