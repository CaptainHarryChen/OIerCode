#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=200005;

int n,m,h[MAXN],H[MAXN],len[MAXN];

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		memset(h,0,sizeof h);
		memset(H,0,sizeof H);
		memset(len,0,sizeof len);
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&h[i]);
		m=0;
		H[++m]=-2;H[++m]=-1;
		for(int i=1;i<=n;i++)
			H[++m]=h[i],H[++m]=-1;
		H[++m]=-3;
		len[1]=1;
		int far=1,pos=1;
		for(int i=2;i<=m;i++)
		{
			if(i<=far)
				len[i]=min(far-i+1,len[pos*2-i]);
			else
				len[i]=1;
			while(H[i+len[i]]==H[i-len[i]]&&(H[i+len[i]]<=H[i+len[i]-2]||H[i+len[i]]==-1))
				len[i]++;
			if(i+len[i]-1>=far)
				far=i+len[i]-1,pos=i;
		}
		
		int ans=0;
		for(int i=1;i<=m;i++)
			ans=max(ans,len[i]-1);
		printf("%d\n",ans);
	}
	return 0;
}
