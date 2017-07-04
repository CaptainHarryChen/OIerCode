#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 1000010
int n,k,num[MAXN],t[MAXN];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&num[i]);
		t[i]=num[i];
	}
	sort(t+1,t+n+1);
	int v=t[k];
	for(int i=1;i<=n;i++)
		if(num[i]==v)
		{printf("%d\n",i);break;}
	return 0;
}
