#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005;

long long C(int n,int m)
{
	long long ret=1;
	for(int i=1;i<=m;i++)
		ret*=(n-i+1);
	for(int i=1;i<=m;i++)
		ret/=i;
	return ret;
}
bool check(int a,int b,int c)
{
	if((a&1)&&(b&2)&&(c&4))
		return true;
	if((a&1)&&(c&2)&&(b&4))
		return true;
	if((b&1)&&(a&2)&&(c&4))
		return true;
	if((b&1)&&(c&2)&&(a&4))
		return true;
	if((c&1)&&(a&2)&&(b&4))
		return true;
	if((c&1)&&(b&2)&&(a&4))
		return true;
	return false;
}

int n;
int q[MAXN],m;
int sta[MAXN],use[10],cnt[10];

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T,X,Y,Z;
	scanf("%d",&T);
	long long ans;
	while(T--)
	{
		scanf("%d%d%d",&X,&Y,&Z);
		m=0;
		for(int i=1;1LL*i*i<=X;i++)
			if(X%i==0)
			{
				sta[i]|=1,q[++m]=i;
				sta[X/i]|=1,q[++m]=X/i;
			}
		for(int i=1;1LL*i*i<=Y;i++)
			if(Y%i==0)
			{
				sta[i]|=2,q[++m]=i;
				sta[Y/i]|=2,q[++m]=Y/i;
			}
		for(int i=1;1LL*i*i<=Z;i++)
			if(Z%i==0)
			{
				sta[i]|=4,q[++m]=i;
				sta[Z/i]|=4,q[++m]=Z/i;
			}
		sort(q+1,q+m+1);
		m=unique(q+1,q+m+1)-q-1;
		memset(cnt,0,sizeof cnt);
		for(int i=1;i<=m;i++)
			cnt[sta[q[i]]]++;
		
		ans=0;
		for(int a=1;a<8;a++)
			for(int b=a;b<8;b++)
				for(int c=b;c<8;c++)
					if(check(a,b,c))
					{
						memset(use,0,sizeof use);
						use[a]++;use[b]++;use[c]++;
						long long tmp=1;
						for(int i=1;i<8;i++)
							if(use[i])
								tmp*=C(cnt[i]+use[i]-1,use[i]);
						if(tmp>0)
							ans+=tmp;
					}
		
		printf("%I64d\n",ans);
		
		for(int i=1;i<=m;i++)
			sta[q[i]]=0;
	}
	
	return 0;
}
