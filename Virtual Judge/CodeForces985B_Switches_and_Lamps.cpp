#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<bitset>
using namespace std;
const int MAXN=2005;

bitset<MAXN> sw[MAXN];
int cnt[MAXN];

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1,x;j<=m;j++)
		{
			scanf("%1d",&x);
			sw[i][j]=x;
			if(x)
				cnt[j]++;
		}
		
	for(int i=1;i<=n;i++)
	{
		bool flag=true;
		for(int j=1;j<=m;j++)
			if(cnt[j]==1&&sw[i][j]==1)
			{flag=false;break;}
		if(flag)
		{
			puts("YES");
			return 0;
		}
	}
	puts("NO");
	
	return 0;
}
