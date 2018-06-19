#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=131100,MOD=998244353,ROOT=3;

int PowMod(int a,int b)
{
	int ret=1;
	while(b)
	{
		if(b&1)
			ret=(1LL*a*ret)%MOD;
		b>>=1;
		a=(1LL*a*a)%MOD;
	}
	return ret;
}

void NTT(int A[],int n,int mode)
{
	for(int i=0,j=0;i<n;i++)
	{
		if(i<j)
			swap(A[i],A[j]);
		int k=n>>1;
		while(k&&(k&j))
			j^=k,k>>=1;
		j^=k;
	}
	for(int i=1;i<n;i<<=1)
	{
		for(int j=0;j<n;j+=(i<<1))
		{
			int w1=PowMod(ROOT,(MOD-1)/(i*2)),w=1;
			if(mode==-1)
				w1=PowMod(w1,MOD-2);
			for(int l=j,r=j+i;l<j+i;l++,r++,w=(1LL*w1*w)%MOD)
			{
				int temp=(1LL*A[r]*w)%MOD;
				A[r]=(A[l]-temp+MOD)%MOD;
				A[l]=(A[l]+temp)%MOD;
			}
		}
	}
	if(mode==-1)
	{
		int inv=PowMod(n,MOD-2);
		for(int i=0;i<n;i++)
			A[i]=(1LL*A[i]*inv)%MOD;
	}
}

int r[MAXN],c[MAXN],d[MAXN];
int t1[MAXN],t2[MAXN];

int main()
{
	//freopen("a.txt","w",stdout);
	int T,R,C,N;
	long long ans;
	scanf("%d",&T);
	for(int cas=1;cas<=T;cas++)
	{
		scanf("%d%d%d",&R,&C,&N);
		memset(r,0,sizeof r);
		memset(c,0,sizeof c);
		memset(d,0,sizeof d);
		ans=0;
		int cntr=0,cntc=0;
		for(int i=1;i<=N;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			if(r[x]==0)cntr++;
			if(c[y]==0)cntc++;
			r[x]=1;c[y]=1;d[y-x+R]=1;
		}
		for(int i=1;i<=R;i++)
			ans+=r[i]*C;
		for(int i=1;i<=C;i++)
			ans+=c[i]*(R-cntr);
		
		//Mul
		int len=1;
		while(len<R+C)
			len<<=1;
		for(int i=0;i<=R;i++)t1[R-i]=r[i];
		for(int i=R+1;i<len;i++)t1[i]=0;
		for(int i=0;i<=C;i++)t2[i]=c[i];
		for(int i=C+1;i<len;i++)t2[i]=0;
		NTT(t1,len,1);
		NTT(t2,len,1);
		for(int i=0;i<len;i++)
			t1[i]=(1LL*t1[i]*t2[i])%MOD;
		NTT(t1,len,-1);
		
		for(int i=1;i<=R;i++)
			r[i]+=r[i-1];
		for(int i=1;i<=C;i++)
			c[i]+=c[i-1];
		for(int i=1;i<R+C;i++)
			if(d[i])
			{
				ans+=min(min(i,R+C-i),min(R,C));
				ans-=(c[min(i,C)]-c[max(i-R,0)]);
				ans-=(r[min(R+C-i,R)]-r[max(R-i,0)]);
				ans+=t1[i];
			}
		printf("Case %d: %lld\n",cas,1LL*R*C-ans);
	}
	return 0;
}
