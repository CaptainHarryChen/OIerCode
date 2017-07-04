#include<cstdio>
#include<cstring>
#define MAXN 200005
int T,s,n,S[MAXN],cnt[MAXN];
bool f[MAXN];
bool check(int x)
{
	for(int i=x;i-s<=n;i+=s)
		if(!f[i])
			return 0;
	return 1;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&s,&n);
		memset(S,0,sizeof S);
		for(int i=1;i<=n;i++)
			scanf("%d",&S[i]);
		memset(f,0,sizeof f);
		memset(cnt,0,sizeof cnt);
		int i=1,j,flag=0;
		for(j=i;j<=s;j++)
		{
			cnt[S[j]]++;
			flag+=(cnt[S[j]]==2&&S[j]!=0);
			f[j]=(!flag);
		}
		j--;
		for(;i<=n;)
		{
			cnt[S[i]]--;
			if(cnt[S[i]]==1)flag--;
			i++;
			j++;
			cnt[S[j]]++;
			if(cnt[S[j]]==2&&S[j]!=0)
				flag++;
			f[j]=(!flag);
		}
		int ans=0;
		for(int i=1;i<=s;i++)
		{ 
			if(!check(i))continue;
			ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
