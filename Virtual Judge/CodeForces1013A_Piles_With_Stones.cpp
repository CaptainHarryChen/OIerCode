#include<cstdio>
const int MAXN=55;

int n;

int main()
{
	scanf("%d",&n);
	int s1=0,s2=0;
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		s1+=x;
	}
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		s2+=x;
	}
	if(s1>=s2)
		puts("YES");
	else
		puts("NO");
	return 0;
}
