#include<cstdio>
#include<cstring>
const int MAXN=5000006,MOD=1000000000;

int fa[MAXN*2],val[MAXN*2];
bool vis[MAXN*2];
int Root(int u)
{
	if(fa[u]==0)
		return u;
	int f=Root(fa[u]);
	val[u]^=val[fa[u]];
	fa[u]=f;
	return f;
}

int n,m,k;
int x[MAXN],y[MAXN],c[MAXN];

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++)
		scanf("%d%d%d",&x[i],&y[i],&c[i]);
	int ans1=0,ans2=0;
	bool flag1=true,flag2=true;
	for(int i=1;i<=k;i++)
	{
		if(x[i]==1&&y[i]==1)
		{
			if(c[i]==0)
				continue;
			else
			{flag1=false;break;}
		}
		int r1=Root(n-x[i]+1),r2=Root(y[i]+n-1),z;
		if(x[i]==1||y[i]==1)
			z=c[i];
		else
			z=c[i]^(x[i]%2==1||y[i]%2==1)^1;
		if(r1==r2)
		{
			if((val[n-x[i]+1]^val[y[i]+n-1])!=z)
			{flag1=false;break;}
			continue;
		}
		fa[r1]=r2;
		val[r1]=(val[n-x[i]+1]^val[y[i]+n-1])^z;
	}
	for(int i=1;i<n+m;i++)
		if(!vis[Root(i)]&&Root(i)!=Root(n))
		{
			vis[Root(i)]=true;
			ans1++;
		}
	
	memset(vis,0,sizeof vis);
	memset(fa,0,sizeof fa);
	memset(val,0,sizeof val);
	
	for(int i=1;i<=k;i++)
	{
		if(x[i]==1&&y[i]==1)
		{
			if(c[i]==1)
				continue;
			else
			{flag2=false;break;}
		}
		int r1=Root(n-x[i]+1),r2=Root(y[i]+n-1),z;
		if(x[i]==1||y[i]==1)
			z=c[i]^1;
		else
			z=c[i]^(x[i]%2==1||y[i]%2==1);
		if(r1==r2)
		{
			if((val[n-x[i]+1]^val[y[i]+n-1])!=z)
			{flag2=false;break;}
			continue;
		}
		fa[r1]=r2;
		val[r1]=(val[n-x[i]+1]^val[y[i]+n-1])^z;
	}
	for(int i=1;i<n+m;i++)
		if(!vis[Root(i)]&&Root(i)!=Root(n))
		{
			vis[Root(i)]=true;
			ans2++;
		}

	int p1,p2;
	if(!flag1)
		p1=0;
	else
	{
		p1=1;
		while(ans1--)
			p1=(p1*2LL)%MOD;
	}
	if(!flag2)
		p2=0;
	else
	{
		p2=1;
		while(ans2--)
			p2=(p2*2LL)%MOD;
	}
	int ans=(p1+p2)%MOD;
	printf("%d\n",ans);
	
	return 0;
}
