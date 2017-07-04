#include<cstdio>
#define MAXN 205
bool m[5][5]={
{0,0,1,1,0},
{1,0,0,1,0},
{0,1,0,0,1},
{0,0,1,0,1},
{1,1,0,0,0}
};
int main()
{
	int n,na,nb,sa=0,sb=0;
	int a[MAXN],b[MAXN];
	scanf("%d%d%d",&n,&na,&nb);
	for(int i=0;i<na;i++)
		scanf("%d",&a[i]);
	for(int i=0;i<nb;i++)
		scanf("%d",&b[i]);
	for(int i=1,p=0,q=0;i<=n;i++)
	{
		sa+=m[a[p]][b[q]];
		sb+=m[b[q]][a[p]];
		p=(p+1)%na;
		q=(q+1)%nb;
	}
	printf("%d %d\n",sa,sb);
	return 0;
}
