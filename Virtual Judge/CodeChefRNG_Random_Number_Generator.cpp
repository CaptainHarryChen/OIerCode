#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXK=30005,MOD=104857601,ROOT=3;
typedef int Poly[MAXK*5];

int PowMod(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1)
			res=(1LL*res*a)%MOD;
		a=(1LL*a*a)%MOD;
		b>>=1;
	}
	return res;
}

void NTT(Poly &a,int n,int mode)
{
	for(int i=0,j=0;i<n;i++)
	{
		if(i<j)
			swap(a[i],a[j]);
		int k=n>>1;
		while(k&&(k&j))
			j^=k,k>>=1;
		j^=k;
	}
	for(int i=1;i<n;i<<=1)
	{
		int w1=PowMod(ROOT,(MOD-1)/(i<<1)),w=1;
		if(mode==-1)
			w1=PowMod(w1,MOD-2);
		for(int j=0;j<i;j++,w=(1LL*w*w1)%MOD)
			for(int l=j,r=l+i;l<n;l+=(i<<1),r=l+i)
			{
				int temp=(1LL*a[r]*w)%MOD;
				a[r]=(a[l]-temp+MOD)%MOD;
				a[l]=(a[l]+temp)%MOD;
			}
	}
	if(mode==-1)
	{
		int inv=PowMod(n,MOD-2);
		for(int i=0;i<n;i++)
			a[i]=(1LL*a[i]*inv)%MOD;
	}
}
void Inv(Poly &a,Poly &i,int n)
{
	static Poly temp;
	if(n==1)
	{
		i[0]=PowMod(a[0],MOD-2);
		return;
	}
	Inv(a,i,(n+1)/2);
	int len=1;
	while(len<n*2-1)
		len<<=1;
	copy(a,a+n,temp);
	fill(temp+n,temp+len,0);
	NTT(temp,len,1);
	fill(i+n,i+len,0);
	NTT(i,len,1);
	for(int j=0;j<len;j++)
		i[j]=1LL*i[j]*((2LL-1LL*temp[j]*i[j]%MOD+MOD)%MOD)%MOD;
	NTT(i,len,-1);
	fill(i+n,i+len,0);
}
void Mod(Poly &a,const Poly &p,int n,int m)
{
	static Poly temp,p0,p1,c;
	copy(a,a+n,temp);
	reverse(temp,temp+n);
	copy(p,p+m,p0);
	reverse(p0,p0+m);
	Inv(p0,p1,n-m+1);
	int len=1;
	while(len<(n-m+1)*2-1)
		len<<=1;
	fill(temp+n-m+1,temp+len,0);
	NTT(temp,len,1);
	fill(p1+n-m+1,p1+len,0);
	NTT(p1,len,1);
	for(int i=0;i<len;i++)
		c[i]=(1LL*temp[i]*p1[i])%MOD;
	NTT(c,len,-1);
	fill(c+n-m+1,c+len,0);
	reverse(c,c+n-m+1);
	len=1;
	while(len<n)
		len<<=1;
	NTT(c,len,1);
	fill(p0+m,p0+len,0);
	reverse(p0,p0+m);
	NTT(p0,len,1);
	for(int i=0;i<len;i++)
		c[i]=(1LL*c[i]*p0[i])%MOD;
	NTT(c,len,-1);
	for(int i=0;i<n;i++)
		a[i]=(a[i]-c[i]+MOD)%MOD;
}
void MulMod(Poly &a,const Poly &b,const Poly &p,int n)
{
	static Poly temp;
	copy(b,b+n,temp);
	int len=1;
	while(len<n*2)
		len<<=1;
	fill(a+n,a+len,0);
	fill(temp+n,temp+len,0);
	NTT(a,len,1);
	NTT(temp,len,1);
	for(int i=0;i<len;i++)
		a[i]=(1LL*a[i]*temp[i])%MOD;
	NTT(a,len,-1);
	Mod(a,p,n*2-1,n);
}
void PowMod(Poly &res,Poly &a,long long b,const Poly &p,int n)
{
	fill(res,res+n,0);
	res[0]=1;
	while(b)
	{
		if(b&1LL)
			MulMod(res,a,p,n);
		MulMod(a,a,p,n);
		b>>=1LL;
	}
}

Poly A,C,p,t,f;
int main()
{
	long long N;
	int K;
	scanf("%d%lld",&K,&N);
	for(int i=0;i<K;i++)
		scanf("%d",&A[i]);
	for(int i=0;i<K;i++)
		scanf("%d",&C[i]);
	
	p[K]=1;
	for(int i=0;i<K;i++)
		p[i]=(MOD-C[K-i-1])%MOD;
	t[1]=1;
	PowMod(f,t,N-1,p,K+1);
	
	int ans=0;
	for(int i=0;i<K;i++)
		ans=(ans+(1LL*A[i]*f[i])%MOD)%MOD;
	printf("%d\n",ans);
	
	return 0;
}
