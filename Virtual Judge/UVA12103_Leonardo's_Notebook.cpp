#include<cstdio>
#include<cstring>
const int MAXN=30;

int n;
int p[MAXN];
bool vis[MAXN];
char str[MAXN];
int cnt[MAXN];

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		n=26;
		scanf("%s",str);
		for(int i=1;i<=n;i++)
			p[i]=str[i-1]-'A'+1;
		memset(cnt,0,sizeof cnt);
		memset(vis,0,sizeof vis);
		for(int i=1;i<=n;i++)
		{
			if(vis[i])
				continue;
			int step=0;
			for(int j=i;!vis[j];j=p[j])
			{
				step++;
				vis[j]=true;
			}
			cnt[step]++;
		}
		bool flag=true;
		for(int i=0;i<=n&&flag;i+=2)
			flag=(cnt[i]%2==0);
		if(flag)
			puts("Yes");
		else
			puts("No");
	}
	
	return 0;
}
