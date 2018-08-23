#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=12;

int K,N,ans1,ans2;
char str[MAXN];
void dfs1(int id,int step)
{
	if(id>=N||step>=K)
	{
		int tmp;
		sscanf(str,"%d",&tmp);
		ans1=min(ans1,tmp);
		return;
	}
	dfs1(id+1,step);
	for(int i=id+1;i<N;i++)
		if(str[id]>str[i]&&(id!=0||str[i]!='0'))
		{
			swap(str[id],str[i]);
			dfs1(id+1,step+1);
			swap(str[id],str[i]);
		}
}
void dfs2(int id,int step)
{
	if(id>=N||step>=K)
	{
		int tmp;
		sscanf(str,"%d",&tmp);
		ans2=max(ans2,tmp);
		return;
	}
	dfs2(id+1,step);
	for(int i=id+1;i<N;i++)
		if(str[id]<str[i]&&(id!=0||str[i]!='0'))
		{
			swap(str[id],str[i]);
			dfs2(id+1,step+1);
			swap(str[id],str[i]);
		}
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s%d",str,&K);
		N=strlen(str);
		sscanf(str,"%d",&ans1);
		ans2=ans1;
		dfs1(0,0);
		dfs2(0,0);
		printf("%d %d\n",ans1,ans2);
	}
	return 0;
}
