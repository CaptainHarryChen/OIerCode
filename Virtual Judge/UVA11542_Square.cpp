#include<cstdio>
#include<cstring>
#include<algorithm>
using std::swap;
long long N,prime[100],pri_cnt;
bool isprime[505];
long long x_cnt,pr_id[505];
typedef bool Matrix[105][105];
Matrix A;
void getPrime()
{
	for(long long i=2;i<=500;i++)
	if(!isprime[i])
	{
		prime[pri_cnt++]=i;
		for(long long j=i*i;j<=500;j+=i)
			isprime[j]=1;
	}
}
void Init()
{
	x_cnt=0;
	memset(pr_id,0,sizeof pr_id);
	memset(A,0,sizeof A);
	long long a;
	scanf("%lld",&N);
	for(long long i=1,k;i<=N;i++)
	{
		scanf("%lld",&a);
		k=0;
		while((a>500||isprime[a])&&a!=1)
		{
			if(a%prime[k]==0&&pr_id[prime[k]]==0)
				pr_id[prime[k]]=++x_cnt;
			while(a%prime[k]==0)
			{
				a/=prime[k];
				A[pr_id[prime[k]]][i]^=1;
			}
			k++;
		}
		if(a!=1)
		{
			if(pr_id[a]==0)
				pr_id[a]=++x_cnt;
			A[pr_id[a]][i]^=1;
		}
	}
}
void Gauss()
{
	long long r,c,n=x_cnt,m=N,mxr;
	for(r=1,c=1;r<=n&&c<=m;r++,c++)
	{
		for(mxr=r;!A[mxr][c]&&mxr<=n;mxr++);
		if(mxr>n){r--;continue;}
		if(mxr!=r)swap(A[mxr],A[r]);
		for(long long i=1;i<=n;i++)
			if(i!=r&&A[i][c])
				for(long long j=1;j<=m;j++)
					A[i][j]^=A[r][j];
	}
	long long ans=1LL<<(m-r+1);
	ans--;
	printf("%lld\n",ans);
}
int main()
{
	long long T;
	scanf("%lld",&T);
	getPrime();
	while(T--)
	{
		Init();
		Gauss();
	}
	return 0;
}