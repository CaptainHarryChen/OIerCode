#include<cstdio>
const int MAXN=1000005;

int n;
int out[MAXN],ans[MAXN];
int son[MAXN][2],fa[MAXN];
char type[MAXN][5];
bool noeff[MAXN];

void dfs1(int u)
{
	if(son[u][0])
		dfs1(son[u][0]);
	if(son[u][1])
		dfs1(son[u][1]);
	if(type[u][0]=='I')
		return;
	if(type[u][0]=='A')
	{
		out[u]=(out[son[u][0]] and out[son[u][1]]);
		if(out[son[u][0]]==0)
			noeff[son[u][1]]=true;
		if(out[son[u][1]]==0)
			noeff[son[u][0]]=true;
	}
	if(type[u][0]=='O')
	{
		out[u]=(out[son[u][0]] or out[son[u][1]]);
		if(out[son[u][0]]==1)
			noeff[son[u][1]]=true;
		if(out[son[u][1]]==1)
			noeff[son[u][0]]=true;
	}
	if(type[u][0]=='X')
		out[u]=(out[son[u][0]] xor out[son[u][1]]);
	if(type[u][0]=='N')
		out[u]=(not out[son[u][0]]);
}
void dfs2(int u,bool eff=true)
{
	if(type[u][0]=='I')
		ans[u]=out[1]^eff;
	if(son[u][0])
		dfs2(son[u][0],(!noeff[son[u][0]])&&eff);
	if(son[u][1])
		dfs2(son[u][1],(!noeff[son[u][1]])&&eff);
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",type[i]);
		if(type[i][0]=='N')
		{
			scanf("%d",&son[i][0]);
			fa[son[i][0]]=i;
		}
		else if(type[i][0]=='I')
			scanf("%d",&out[i]);
		else
		{
			scanf("%d%d",&son[i][0],&son[i][1]);
			fa[son[i][0]]=i;
			fa[son[i][1]]=i;
		}
	}
	dfs1(1);
	dfs2(1);
	
	for(int i=1;i<=n;i++)
		if(type[i][0]=='I')
			printf("%d",ans[i]);
	puts("");
	
	return 0;
}
