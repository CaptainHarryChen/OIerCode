#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define MAXN 1005
int N,D;
struct Cp{int x,y;}pc[MAXN];
bool fixed[MAXN];
int Set[MAXN];
int Root(int x)
{return Set[x]==x?x:Set[x]=Root(Set[x]);}
bool connect(int a,int b)
{
	return 1.0*sqrt(1.0*(pc[a].x-pc[b].x)*(pc[a].x-pc[b].x)+
	(pc[a].y-pc[b].y)*(pc[a].y-pc[b].y))<=D;
}
int main()
{
	scanf("%d%d",&N,&D);
	for(int i=1;i<=N;i++)Set[i]=i;
	for(int i=1;i<=N;i++)
		scanf("%d%d",&pc[i].x,&pc[i].y);
	char op[3];
	int id,id2;
	while(~scanf("%s%d",op,&id))
	{
		switch(op[0])
		{
			case 'O':
			{
				fixed[id]=1;
				for(int i=1;i<=N;i++)
					if(fixed[i]&&i!=id&&connect(id,i)&&Root(i)!=Root(id))
						Set[Root(id)]=Root(i);
				break;
			}
			case 'S':
			{
				scanf("%d",&id2);
				if(Root(id)==Root(id2))
					printf("SUCCESS\n");
				else
					printf("FAIL\n");
			}
		}
	}
	return 0;
}
