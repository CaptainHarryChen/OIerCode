#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
#define MAXN 100005
int n,ans=1;
bool ed[MAXN];
struct Height
{
	int h,id;
}num[MAXN];
bool cmp(Height a,Height b){return a.h<b.h||(a.h==b.h&&a.id<b.id);}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&num[i].h);
		num[i].id=i;
	}
	sort(num+1,num+n+1,cmp);
	int last=n,cnt=0;
	for(int water=n;water>=1;water--)
	{
		while(num[water].h<=num[last].h&&last>=1)
		{
			int u=num[last].id;
			ed[u]=1;
			if(ed[u-1]&&ed[u+1])cnt--;
			else if(!ed[u-1]&&!ed[u+1])cnt++;
			last--;
		}
		ans=max(ans,cnt);
	}
	printf("%d\n",ans);
	return 0;
}
