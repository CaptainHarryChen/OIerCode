#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 200005
#define lowbit(x) (x&(-x))
int n,f[MAXN*2],sum[2][MAXN*2],z[MAXN];
int s[MAXN][2],num;
int get(int flag,int x)
{
	int ret=0;
	for(int i=x;i;i-=lowbit(i))
		ret+=sum[flag][i];
	return ret;
}
void add(int flag,int x,int y)
{
	for(int i=x;i<=num;i+=lowbit(i))
		sum[flag][i]+=y;
}
int main()
{
	int test=0;
	while(~scanf("%d",&n))
	{
		int tot=0;
		memset(f,0,sizeof f);
		memset(sum,0,sizeof sum);
		memset(z,0,sizeof z);
		memset(s,0,sizeof s);
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&z[i],&s[i][0]);
			if(!z[i])
			{
				f[++tot]=s[i][0];
				s[i][1]=s[i][0]+(++tot)/2;
				f[tot]=s[i][1];
			}
			else
			{
				s[i][1]=f[s[i][0]*2];
				s[i][0]=f[s[i][0]*2-1];
			}
		}
		sort(f+1,f+tot+1);
		num=unique(f+1,f+tot+1)-f;
		printf("Case #%d:\n",++test);
		for(int i=1;i<=n;i++)
		{
			int u=lower_bound(f+1,f+num,s[i][0])-f;
			int v=lower_bound(f+1,f+num,s[i][1])-f;
			if(!z[i])
				printf("%d\n",get(1,v)-get(0,u-1));
			add(0,u,z[i]?-1:1);
			add(1,v,z[i]?-1:1);
		}
	}
	return 0;
}
