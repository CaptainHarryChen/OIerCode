#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=200005,MAXS=20,MAXMASK=(1<<MAXS);

int n;
long long X,Y,A[MAXN];

void Factorize(long long N,vector<pair<long long,int> > &ans)
{
	for(long long d=2;d<1000000&&d<=N;d++)
		if(N%d==0)
		{
			int cnt=0;
			while(N%d==0)
				N/=d,cnt++;
			ans.push_back(make_pair(d,cnt));
		}
	if(N>1)
	{
		long long p=sqrt(N);
		if(p*p==N)
			ans.push_back(make_pair(p,2));
		else
		{
			for(int i=1;i<=n;i++)
			{
				p=__gcd(N,A[i]);
				if(p!=1&&p!=N)
					break;
			}
			if(p==1||p==N)
				p=__gcd(N,X);
			if(p==1||p==N)
				p=__gcd(N,Y);
			if(p!=1&&p!=N)
			{
				ans.push_back(make_pair(p,1));
				ans.push_back(make_pair(N/p,1));
			}
			else
				ans.push_back(make_pair(p,1));
		}
	}
	sort(ans.begin(),ans.end());
}
void CntFactors(long long N,const vector<pair<long long,int> > &fac,int cnt[])
{
	for(int i=0;i<(int)fac.size();i++)
	{
		long long d=fac[i].first;
		cnt[i]=0;
		while(N%d==0)
			N/=d,cnt[i]++;
	}
}

vector<pair<long long,int> > facY,facs;
int cntX[MAXS],cntY[MAXS],fcnt;
int tmp[MAXS];
int mx[MAXN],mn[MAXN];
int cnt[MAXMASK];

int main()
{
	scanf("%d%I64d%I64d",&n,&X,&Y);
	for(int i=1;i<=n;i++)
		scanf("%I64d",&A[i]);
	
	if(Y%X!=0)
	{puts("0");return 0;}
	
	Factorize(Y,facY);
	fcnt=facY.size();
	for(int i=0;i<fcnt;i++)
		cntY[i]=facY[i].second;//printf("[%I64d,%d]\n",facY[i].first,facY[i].second);
	CntFactors(X,facY,cntX);
	
	for(int i=0;i<fcnt;i++)
		if(cntX[i]<cntY[i])
			facs.push_back(facY[i]);
	fcnt=facs.size();
	for(int i=0;i<fcnt;i++)
		cntY[i]=facs[i].second;//printf("[%I64d,%d]\n",facs[i].first,facs[i].second);
	CntFactors(X,facs,cntX);
	
	memset(mn,-1,sizeof mn);
	memset(mx,-1,sizeof mx);
	for(int i=1;i<=n;i++)
	{
		CntFactors(A[i],facs,tmp);
		if(A[i]%X==0)
		{
			mn[i]=0;
			for(int k=0;k<fcnt;k++)
				if(tmp[k]>cntX[k])
					mn[i]|=(1<<k);
		}
		if(Y%A[i]==0)
		{
			mx[i]=0;
			for(int k=0;k<fcnt;k++)
				if(tmp[k]<cntY[k])
					mx[i]|=(1<<k);
		}
		if(mn[i]!=-1)
			cnt[mn[i]]++;
	}
	
	long long ans=0;
	for(int i=1;i<=n;i++)
		if(mx[i]!=-1)
		{
			int mask=((1<<fcnt)-1)^mx[i];
			for(int s=mask;s>0;s=(s-1)&(mask))
				ans+=cnt[s];
			ans+=cnt[0];
		}
	
	printf("%I64d\n",ans);
	
	return 0;
}
