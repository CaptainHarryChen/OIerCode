#include<cstdio>
const int MAXP=100005;

long long temp[30];

long long pow_mod(long long a,long long b,long long p)
{
	long long res=1LL;
	while(b)
	{
		if(b&1LL)
			res=(res*a)%p;
		b>>=1LL;
		a=(a*a)%p;
	}
	return res;
}
void exgcd(long long a,long long b,long long &x,long long &y)
{
	if(b==0)
		x=1,y=0;
	else
	{
		long long x1,y1;
		exgcd(b,a%b,x1,y1);
		x=y1;
		y=x1-(a/b)*y1;
	}
}
long long inv(long long x,long long p)
{
	long long i,t;
	exgcd(x,p,i,t);
	i=(i%p+p)%p;
	if(i==0)
		i=p;
	return i;
}


long long Fac(long long n,long long pk,long long p,long long id)
{
	if(n==0)
		return 1;
	long long ans=1;
	if(n/pk)
		ans=pow_mod(temp[id],n/pk,pk);
	for(long long i=1;i<=n%pk;i++)
		if(i%p!=0)
			ans=(ans*i)%pk;
	ans=(ans*Fac(n/p,pk,p,id))%pk;
	return ans;
}
long long C(long long n,long long r,long long pk,long long p,long long id)
{
	if(n<r)
		return 0;
	long long a=Fac(n,pk,p,id),b=Fac(r,pk,p,id),c=Fac(n-r,pk,p,id);
	long long k=0;
	for(long long i=n;i;i/=p)
		k+=i/p;
	for(long long i=r;i;i/=p)
		k-=i/p;
	for(long long i=n-r;i;i/=p)
		k-=i/p;
	long long ans=a*inv(b,pk)%pk*inv(c,pk)%pk*pow_mod(p,k,pk)%pk;
	return ans;
}

long long fac[30],ind[30],faci=0;
void GetFac(long long x)
{
	for(long long p=2;p*p<=x;p++)
		if(x%p==0)
		{
			fac[++faci]=p;
			ind[faci]=1;
			while(x%p==0)
				x/=p,ind[faci]*=p;
		}
	if(x!=1)
		fac[++faci]=x,ind[faci]=x;
}
void Init()
{
	for(int i=1;i<=faci;i++)
	{
		temp[i]=1;
		for(int j=1;j<ind[i];j++)
			if(j%fac[i])
				temp[i]=(temp[i]*j)%ind[i];
	}
}
long long C(long long N,long long R,long long M)
{
	long long ans=0;
	for(long long i=1;i<=faci;i++)
	{
		long long pk=ind[i],p=fac[i];
		long long c=C(N,R,pk,p,i);
		ans=(ans+c*(M/pk)%M*inv(M/pk,pk)%M)%M;
	}
	return ans;
}

long long w[7];

int main()
{
	long long P,N,M,sum=0;
	scanf("%lld%lld%lld",&P,&N,&M);
	GetFac(P);
	Init();
	for(int i=1;i<=M;i++)
	{
		scanf("%lld",w+i);
		sum+=w[i];
	}
	if(sum>N)
		puts("Impossible");
	else
	{
		long long ans=1;
		for(int i=1;i<=M;N-=w[i],i++)
			ans=(ans*C(N,w[i],P))%P;
		printf("%lld\n",ans);
	}
	return 0;
}
