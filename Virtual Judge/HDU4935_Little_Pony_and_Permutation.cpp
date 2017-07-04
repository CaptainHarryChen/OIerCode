#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 100005
int num[MAXN],id[MAXN],n;
int temp[MAXN];
int main()
{
	while(~scanf("%d",&n))
	{
		for(int i=1;i<=n;i++)
		{
			scanf("%d",num+i);
			id[i]=0;
		}
		int cnt=0,cur=0;
		for(int i=1,x;i<=n;i++)
			if(!id[i])
			{
				cnt++;
				x=i;
				cur=0;
				do
				{
					temp[++cur]=x;
					id[x]=cnt;
					x=num[x];
				}while(!id[x]);
				printf("(");
				for(int i=1;i<cur;i++)
					printf("%d ",temp[i]);
				printf("%d)",temp[cur]);
			}
		puts("");
	}
	return 0;
}
