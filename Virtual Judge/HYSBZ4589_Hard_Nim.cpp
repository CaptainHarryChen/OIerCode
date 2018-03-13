#include<cstdio>
#include<cstring>
const int MAXM=100005,MOD=1000000007,INV2=(MOD+1)/2;

int pow_mod(int a,int b)
{
	int ret=1;
	while(b)
	{
		if(b&1)
			ret=(1LL*ret*a)%MOD;
		a=(1LL*a*a)%MOD;
		b>>=1;
	}
	return ret;
}

void FWT(int A[],int n,int mode)
{
	for(int i=1;i<n;i<<=1)
		for(int j=0;j<i;j++)
			for(int l=j,r=j+i;l<n;l+=(i<<1),r=l+i)
			{
				int x=A[l],y=A[r];
				A[l]=(x+y)%MOD;A[r]=(x-y+MOD)%MOD;
				if(mode==-1)
				{
					A[l]=(1LL*A[l]*INV2)%MOD;
					A[r]=(1LL*A[r]*INV2)%MOD;
				}
			}
}

bool npr[MAXM];
int prime[MAXM],pcnt;
void get_prime()
{
	npr[0]=npr[1]=true;
	for(int i=2;i<MAXM;i++)
	{
		if(npr[i]==false)
			prime[++pcnt]=i;
		for(int j=1;j<=pcnt&&1LL*i*prime[j]<MAXM;j++)
		{
			npr[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
		}
	}
}

int g[MAXM];

int main()
{
	get_prime();
	int n,m;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		memset(g,0,sizeof g);
		for(int i=0;i<=m;i++)
			g[i]=(npr[i]^1);  
		int len=1;
		while(len<=m)
			len<<=1;
		FWT(g,len,1);
		for(int i=0;i<len;i++)
			g[i]=pow_mod(g[i],n);
		FWT(g,len,-1);
		printf("%d\n",g[0]);
	}
	return 0;
}
