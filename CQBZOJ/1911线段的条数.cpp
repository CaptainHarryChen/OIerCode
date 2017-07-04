#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define MAXN 100100
using namespace std;
int order[MAXN][2],n,p,cnt;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&order[i][0],&order[i][1]);
	scanf("%d",&p);
	for(int i=1;i<=n;i++)
		if(order[i][0]<=p&&order[i][1]>=p+1)
			cnt++;
	printf("%d\n",cnt);
	return 0;
}
