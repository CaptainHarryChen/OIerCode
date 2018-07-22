#include<cstdio>
const int MAXN=1005;

int a[MAXN],c[MAXN];

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",c+i);
	for(int i=1;i<=m;i++)
		scanf("%d",a+i);
	
	int x=1,ans=0;
	for(int i=1;i<=n;i++)
		if(x<=m&&c[i]<=a[x])
			ans++,x++;
	printf("%d\n",ans);
	
	return 0;
}
