#include<cstdio>
#include<map>
using namespace std;
const int MAXN=405;

long long encode(long long a,long long b,long long c,long long d)
{
	return (a<<30LL)|(b<<20LL)|(c<<10LL)|d;
}

map<long long,long long> cnt;
void Add(long long c,int delta)
{
	for(int i=0;i<4;i++)
	{
		cnt[c]+=delta;
		c=(c>>10LL)|((c&1023LL)<<30LL);
	}
}

int n;
int c[MAXN][4];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d%d",c[i],c[i]+1,c[i]+2,c[i]+3);
		Add(encode(c[i][0],c[i][1],c[i][2],c[i][3]),1);
	}
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		Add(encode(c[i][0],c[i][1],c[i][2],c[i][3]),-1);
		for(int j=i+1;j<=n;j++)
		{
			Add(encode(c[j][0],c[j][1],c[j][2],c[j][3]),-1);
			for(int k=0;k<4;k++)
			{
				long long u[4]=
				{encode(c[i][1],c[i][0],c[j][(k+1)&3],c[j][(k+0)&3]),
				 encode(c[i][0],c[i][3],c[j][(k+2)&3],c[j][(k+1)&3]),
				 encode(c[i][3],c[i][2],c[j][(k+3)&3],c[j][(k+2)&3]),
				 encode(c[i][2],c[i][1],c[j][(k+0)&3],c[j][(k+3)&3])
				};
				if(cnt[u[0]]&&cnt[u[1]]&&cnt[u[2]]&&cnt[u[3]])
				{
					long long tmp=1;
					for(int l=0;l<4;l++)
						tmp*=cnt[u[l]],Add(u[l],-1);
					for(int l=0;l<4;l++)
						Add(u[l],1);
					ans+=tmp;
				}
			}
			Add(encode(c[j][0],c[j][1],c[j][2],c[j][3]),1);
		}
	}
	printf("%lld\n",ans);
	
	return 0;
}
