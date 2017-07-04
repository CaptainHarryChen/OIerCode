#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 30005
int father[MAXN],son[MAXN][2];
bool perfer[MAXN],rev[MAXN];
int value[MAXN],sum[MAXN],siz[MAXN];
void Update(int x)
{
	sum[x]=value[x];siz[x]=1;
	if(son[x][0]){sum[x]+=sum[son[x][0]];siz[x]+=siz[son[x][0]];}
	if(son[x][1]){sum[x]+=sum[son[x][1]];siz[x]+=siz[son[x][1]];}
}
void Flip(int x)
{
	swap(son[x][0],son[x][1]);
	if(son[x][0])rev[son[x][0]]=!rev[son[x][0]];
	if(son[x][1])rev[son[x][1]]=!rev[son[x][1]];
	rev[x]=0;
}
void Rotate(int x,int d)
{
	int y=father[x];
	father[x]=father[y];
	perfer[x]=perfer[y];
	if(father[y]&&perfer[y])
		son[father[y]][son[father[y]][1]==y]=x;
	perfer[y]=1;
	son[y][!d]=son[x][d];
	if(son[x][d])
		father[son[x][d]]=y;
	son[x][d]=y;
	father[y]=x;
	Update(y);
}
void Splay(int x)
{
	int y,z;
	while(perfer[x])
	{
		y=father[x];z=father[y];
		if(rev[z])Flip(z);
		if(rev[y])Flip(y);
		if(rev[x])Flip(x);
		if(!perfer[y])
		{
			Rotate(x,son[y][0]==x);
			break;
		}
		if((son[z][0]==y)==(son[y][0]==x))
		{
			Rotate(y,son[z][0]==y);
			Rotate(x,son[y][0]==x);
		}
		else
		{
			Rotate(x,son[y][0]==x);
			Rotate(x,son[z][0]==x);
		}
	}
	if(rev[x])Flip(x);
	Update(x);
}
void Access(int x)
{
	int last=0;
	while(x)
	{
		Splay(x);
		perfer[son[x][1]]=0;
		son[x][1]=last;
		if(last)perfer[last]=1;
		Update(x);
		last=x;
		x=father[last];
	}
}
void MakeRoot(int x)
{
	Access(x);
	Splay(x);
	rev[x]=!rev[x];
}
int FindRoot(int x)
{
	Access(x);
	Splay(x);
	int u=x;
	while(son[u][0])
		u=son[u][0];
	Splay(u);
	return u;
}
void Link(int x,int y)
{
	MakeRoot(x);
	father[x]=y;
}
void Change(int x,int y)
{
	value[x]=y;
	Access(x);
}
int Query_Dist(int x,int y)
{
	Access(x);
	int last=0,ans=0;
	while(y)
	{
		Splay(y);
		if(!father[y])
			ans=sum[last]+sum[son[y][1]]+value[y];
		perfer[son[y][1]]=0;
		son[y][1]=last;
		if(last)perfer[last]=1;
		Update(y);
		last=y;
		y=father[last];
	}
	return ans;
}
int main()
{
	char op[20];
	int x,y;
	int n,Q;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&value[i]);
	scanf("%d",&Q);
	while(Q--)
	{
		scanf("%s%d%d",op,&x,&y);
		if(op[0]=='e')
		{
			if(FindRoot(x)!=FindRoot(y))
				printf("impossible\n");
			else
				printf("%d\n",Query_Dist(x,y));
		}
		else if(op[0]=='p')
			Change(x,y);
		else
		{
			if(FindRoot(x)==FindRoot(y))
				printf("no\n");
			else
			{
				Link(x,y);
				printf("yes\n");
			}
		}
	}
	return 0;
}
