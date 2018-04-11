#include<cstdio>
#include<cstring>
const int MOD=142857;

int pow_mod(int a,int b,int p)
{
	int res=1;
	while(b)
	{
		if(b&1)
			res=(res*a)%p;
		b>>=1;
		a=(a*a)%p;
	}
	return res;
}
void exgcd(int a,int b,int &x,int &y)
{
	if(b==0)
		x=1,y=0;
	else
	{
		int x1,y1;
		exgcd(b,a%b,x1,y1);
		x=y1;
		y=x1-(a/b)*y1;
	}
}

int _inv[MOD+10][40];
int inv(int x,int p)
{
	if(_inv[x][p]!=-1)
		return _inv[x][p];
	int i,t;
	exgcd(x,p,i,t);
	i=(i%p+p)%p;
	_inv[x][p]=i;
	return i;
}

int fac[1428600][40];
int fac2[40];
int Fac(int n,int pk,int p)
{
	if(n==0)
		return 1;
	if(n<MOD*10&&fac[n][p]!=0)
		return fac[n][p];
	int ans=1;
	if(n/pk)
	{
		int temp=fac2[p];
		ans=pow_mod(temp,n/pk,pk);
	}
	for(int i=1;i<=n%pk;i++)
		if(i%p!=0)
			ans=(ans*i)%pk;
	ans=(ans*Fac(n/p,pk,p))%pk;
	if(n<MOD*10)
		fac[n][p]=ans;
	return ans;
}
int C(int n,int r,int pk,int p)
{
	if(n<r)
		return 0;
	int a=Fac(n,pk,p),b=Fac(r,pk,p),c=Fac(n-r,pk,p);
	int k=0;
	for(int i=n;i;i/=p)
		k+=i/p;
	for(int i=r;i;i/=p)
		k-=i/p;
	for(int i=n-r;i;i/=p)
		k-=i/p;
	int ans=a*inv(b,pk)%pk*inv(c,pk)%pk*pow_mod(p,k,pk)%pk;
	return ans;
}

int main()
{
	fac2[3]=1;
	for(int i=1;i<27;i++)
		if(i%3)
			fac2[3]=(fac2[3]*i)%27;
	fac2[11]=1;
	for(int i=1;i<11;i++)
		if(i%11)
			fac2[11]=(fac2[11]*i)%11;
	fac2[13]=1;
	for(int i=1;i<13;i++)
		if(i%13)
			fac2[13]=(fac2[13]*i)%13;
	fac2[37]=1;
	for(int i=1;i<37;i++)
		if(i%37)
			fac2[37]=(fac2[37]*i)%37;
	
	memset(_inv,-1,sizeof _inv);
	int T,n,r,m,ans;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&r);
		
		m=MOD;
		ans=0;
		int c=C(n,r,27,3);
		ans=(ans+c*(MOD/27)%MOD*inv(MOD/27,27)%MOD)%MOD;
		c=C(n,r,11,11);
		ans=(ans+c*(MOD/11)%MOD*inv(MOD/11,11)%MOD)%MOD;
		c=C(n,r,13,13);
		ans=(ans+c*(MOD/13)%MOD*inv(MOD/13,13)%MOD)%MOD;
		c=C(n,r,37,37);
		ans=(ans+c*(MOD/37)%MOD*inv(MOD/37,37)%MOD)%MOD;
		
		printf("%d\n",ans);
	}
	return 0;
}
