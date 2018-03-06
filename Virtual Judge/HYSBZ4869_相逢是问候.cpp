#include<cstdio>
const int MAXN=50005,MAXOP=35;

int n,m,p[MAXOP],c,mxop;
int a[MAXN];

int pow_mod(int a,int b,int p)
{
	int ret=1;
	while(b)
	{
		if(b&1)
		{
			if(1LL*ret*a>=p)
				ret=(1LL*ret*a)%p+p;
			else
				ret*=a;
		}
		b>>=1;
		if(1LL*a*a>=p)
			a=(1LL*a*a)%p+p;
		else
			a=a*a;
	}
	return ret;
}

int phi(int x)
{
	int ret=x;
	for(int i=2;1LL*i*i<=x;i++)
		if(x%i==0)
		{
			ret=ret/i*(i-1);
			while(x%i==0)
				x/=i;
		}
	if(x!=1)
		ret=ret/x*(x-1);
	return ret;
}

int sum[MAXN*4],opcnt[MAXN];
bool done[MAXN*4];
void PushUp(int id)
{
	sum[id]=(sum[id*2]+sum[id*2+1])%p[0];
	done[id]=(done[id*2]&&done[id*2+1]);
}
void Build(int id=1,int L=1,int R=n)
{
	if(L==R)
	{
		sum[id]=a[L]%p[0];
		return;
	}
	int mid=(L+R)/2;
	Build(id*2,L,mid);
	Build(id*2+1,mid+1,R);
	PushUp(id);
}
void Modify(int l,int r,int id=1,int L=1,int R=n)
{
	if(done[id])
		return;
	if(L==R)
	{
		opcnt[L]++;
		sum[id]=a[L];
		for(int i=opcnt[L]-1;i>=0;i--)
			sum[id]=pow_mod(c,sum[id],p[i]);
		sum[id]%=p[0];
		if(opcnt[L]>=mxop)
			done[id]=true;
		return;
	}
	int mid=(L+R)/2;
	if(l<=mid)Modify(l,r,id*2,L,mid);
	if(mid<r)Modify(l,r,id*2+1,mid+1,R);
	PushUp(id);
}
int Query(int l,int r,int id=1,int L=1,int R=n)
{
	if(l<=L&&R<=r)
		return sum[id];
	int mid=(L+R)/2,ans=0;
	if(l<=mid)ans+=Query(l,r,id*2,L,mid);
	if(mid<r)ans+=Query(l,r,id*2+1,mid+1,R);
	ans%=p[0];
	return ans;
}

int main()
{
	scanf("%d%d%d%d",&n,&m,&p[0],&c);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
		
	for(mxop=0;p[mxop]!=1;mxop++)
		p[mxop+1]=phi(p[mxop]);
	p[++mxop]=1;
	
	Build();
	for(int i=1,op,l,r;i<=m;i++)
	{
		scanf("%d%d%d",&op,&l,&r);
		if(op==0)
			Modify(l,r);
		else
			printf("%d\n",Query(l,r));
	}
	
	return 0;
}
