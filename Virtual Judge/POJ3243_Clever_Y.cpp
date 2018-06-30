#include<cstdio>
#include<cmath>
#include<cstring>
const long long HASHSIZE=31643,MAXNODE=31650;

namespace Hash
{
	long long id[MAXNODE],val[MAXNODE],nxt[MAXNODE];
	long long head[HASHSIZE],ncnt;
	void Clear()
	{
		ncnt=0;
		memset(head,-1,sizeof head);
	}
	void Insert(long long i,long long v)
	{
		id[ncnt]=i;
		val[ncnt]=v;
		nxt[ncnt]=head[i%HASHSIZE];
		head[i%HASHSIZE]=ncnt++;
	}
	long long Get(long long i)
	{
		for(long long u=head[i%HASHSIZE];u!=-1;u=nxt[u])
			if(id[u]==i)
				return val[u];
		return -1;
	}
}

long long gcd(long long a,long long b)
{
	if(b==0)
		return a;
	return gcd(b,a%b);
}
void exgcd(long long a,long long b,long long &x,long long &y)
{
	if(b==0)
	{
		x=1;y=0;
		return;
	}
	long long tx,ty;
	exgcd(b,a%b,tx,ty);
	x=ty;
	y=tx-(a/b)*ty;
}
long long PowMod(long long a,long long b,long long P)
{
	long long ret=1;
	while(b)
	{
		if(b&1)
			ret=(1LL*ret*a)%P;
		b>>=1;
		a=(1LL*a*a)%P;
	}
	return ret;
}
long long inv(long long a,long long P)
{
	long long x,y;
	exgcd(a,P,x,y);
	x=(x%P+P)%P;
	return x;
}

long long exBSGS(long long A,long long B,long long P)//A^X=B (mod P)
{
	long long k=0,d,a2=1;
	B%=P;
	A%=P;
	if(B==1)
		return 0;
	if(A==B)
		return 1;
	for(;;)
	{
		d=gcd(A,P);
		if(B%d!=0)
			return -1;
		if(d==1)
			break;
		B/=d;P/=d;
		a2=(1LL*a2*A/d)%P;
		k++;
		if(a2==B)
			return k;
	}
	Hash::Clear();
	long long m=ceil(sqrt(P));
	long long s=B%P,iA=inv(A,P),Am=PowMod(A,m,P);
	for(long long j=0;j<=m;j++)
	{
		if(Hash::Get(s)==-1)
			Hash::Insert(s,j);
		s=(1LL*s*iA)%P;
	}
	s=a2;
	for(long long i=0;i<=m;i++)
	{
		long long j=Hash::Get(s);
		if(j!=-1)
			return i*m+j+k;
		s=(1LL*s*Am)%P;
	}
	return -1;
}

int main()
{
	long long A,B,P,ans;
	for(;;)
	{
		scanf("%lld%lld%lld",&A,&P,&B);
		if(A==0&&P==0&&B==0)
			break;
		ans=exBSGS(A,B,P);
		if(ans==-1)
			puts("No Solution");
		else
			printf("%lld\n",ans);
	}
	return 0;
}
