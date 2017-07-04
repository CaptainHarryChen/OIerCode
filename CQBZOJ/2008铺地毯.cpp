#include<cstdio>
#define MAXN 10005
struct Rect
{
	int a,b,g,k;
}r[MAXN];
int main()
{
	int x,y,n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d%d",&r[i].a,&r[i].b,&r[i].g,&r[i].k);
	scanf("%d%d",&x,&y);
	int ans=-1;
	for(int i=n;i>0;i--)
		if(r[i].a<=x&&r[i].b<=y&&r[i].a+r[i].g>=x&&r[i].b+r[i].k>=y)
		{
			ans=i;
			break;
		}
	printf("%d\n",ans);
	return 0;
}
