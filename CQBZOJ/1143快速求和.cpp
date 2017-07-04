#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 100100
#define INF 2147483647
char s[25];
int n,len,ans=INF;
int get_num(int x,int y)
{
	int sum=0;
	for(int i=x;i<=y;i++)
		sum=sum*10+s[i]-'0';
	return sum;
}
void dfs(int x,int last_add,int sum,int cnt)
{
	if(x==len)
	{
		sum+=get_num(last_add+1,x);
		if(sum==n)
			ans=min(ans,cnt);
		return;
	}
	dfs(x+1,last_add,sum,cnt);
	int S=sum+get_num(last_add+1,x);
	if(S<=n)
		dfs(x+1,x,S,cnt+1);
}
int main()
{
	scanf("%s%d",s+1,&n);
	len=strlen(s+1);
	dfs(1,0,0,0);
	printf("%d\n",ans==INF?-1:ans);
	return 0;
}
