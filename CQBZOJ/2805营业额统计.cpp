#include<cstdio>
#include<cstdlib>
#define min(a,b) (a>b?b:a)
#define max(a,b) (a>b?a:b)
#define MAXN 100005
#define LUCKY_NUM 20172701
#define INF 0x3FFFFFFF
int n,_new=0,root=1;
struct Node
{
	int v,pri;
	int son[2];
	Node(){son[0]=son[1]=0;}
	Node(int _v)
	{v=_v;pri=rand();son[0]=son[1]=0;}
}T[MAXN];
int Find(int key)
{
	int now=root;
	while(now)
	{
		if(T[now].v==key)return now;
		now=T[now].son[key>T[now].v?1:0];
	}
	return -1;
}
void Rotate(int &x,int d)
{
	int y=T[x].son[!d];
	T[x].son[!d]=T[y].son[d];
	T[y].son[d]=x;
	x=y;
}
void Insert(int &now,int key)
{
	if(_new==0)T[++_new]=Node(key);
	if(!now)
	{now=++_new;T[_new]=Node(key);}
	else
	{
		int d=key<T[now].v?0:1;
		Insert(T[now].son[d],key);
		if(T[now].pri>T[T[now].son[d]].pri)
			Rotate(now,!d);
	}
}
int Next(int now,int key)
{
	now=T[now].son[1];
	if(!now)return INF;
	while(T[now].son[0])
		now=T[now].son[0];
	return T[now].v;
}
int Last(int now,int key)
{
	now=T[now].son[0];
	if(!now)return -INF;
	while(T[now].son[1])
		now=T[now].son[1];
	return T[now].v;
}
int main()
{
	srand(LUCKY_NUM);
	scanf("%d",&n);
	int ans=0;
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		if(Find(x)==-1)
			Insert(root,x);
		else continue;
		if(i==1)ans+=x;
		else
		{
			int now=root,nx=INF,la=-INF;
			while(now)
			{
				if(T[now].v==x)break;
				if(T[now].v>x)nx=min(nx,T[now].v);
				if(T[now].v<x)la=max(la,T[now].v);
				now=T[now].son[x>T[now].v?1:0];
			}
			int a=Next(now,x),b=Last(now,x);
			nx=min(nx,a);la=max(la,b);
			int add=INF;
			if(nx!=INF)add=nx-x;
			if(la!=-INF)add=min(add,x-la);
			if(add!=INF)
				ans+=add;
		}
	}
	printf("%d\n",ans);
	return 0;
}
