#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1000005;

int T,n;
char S[MAXN];
int fail[MAXN];
bool flag[MAXN];

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",S+1);
		n=strlen(S+1);
		fail[0]=-1;
		for(int i=1;i<=n;i++)
		{
			int u=fail[i-1];
			while(u!=-1&&S[u+1]!=S[i])
				u=fail[u];
			fail[i]=u+1;
		}
		memset(flag,0,sizeof flag);
		int x=fail[n];
		while(x)
		{
			flag[x]=true;
			x=fail[x];
		}
		int ans=0;
		for(int i=n;i>=1;i--)
		{
			int j=i;
			while(j)
			{
				if(flag[j]&&i>=j*2&&i+j<=n)
				{
					ans=max(ans,j);
					break;
				}
				j=fail[j];
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
