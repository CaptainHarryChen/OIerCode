#include<cstdio>
const int MAXN=1005;

int gcd(int a,int b)
{
	if(b==0)
		return a;
	return gcd(b,a%b);
}
int lcm(int a,int b)
{return a/gcd(a,b)*b;}

int n,ans;
int p[MAXN];
bool vis[MAXN];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",p+i);
	ans=1;
	for(int i=1;i<=n;i++)
	{
		if(vis[i])
			continue;
		int cnt=0;
		for(int j=i;!vis[j];j=p[j])
		{
			cnt++;
			vis[j]=true;
		}
		ans=lcm(ans,cnt);
	}
	printf("%d\n",ans);
	
	return 0;
}
