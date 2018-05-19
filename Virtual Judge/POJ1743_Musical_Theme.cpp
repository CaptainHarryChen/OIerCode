#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=500005;

int sa[MAXN],ra[MAXN],h[MAXN];
int cntA[MAXN],cntB[MAXN];
int x[MAXN],y[MAXN];
int tsa[MAXN];
int A[MAXN];
void GetSa(int N)
{
	A[N+1]=0;
	memset(cntA,0,sizeof cntA);
	for(int i=1;i<=N;i++)
		cntA[A[i]]++;
	for(int i=1;i<200;i++)
		cntA[i]+=cntA[i-1];
	for(int i=N;i>=1;i--)
		sa[cntA[A[i]]--]=i;
	ra[sa[1]]=1;
	for(int i=2;i<=N;i++)
		ra[sa[i]]=ra[sa[i-1]]+(A[sa[i]]!=A[sa[i-1]]);
	for(int len=1;ra[sa[N]]<N;len<<=1)
	{
		memset(cntA,0,sizeof cntA);
		memset(cntB,0,sizeof cntB);
		for(int i=1;i<=N;i++)
		{
			cntA[x[i]=ra[i]]++;
			cntB[y[i]=(i+len<=N?ra[i+len]:0)]++;
		}
		for(int i=1;i<=N;i++)
		{
			cntA[i]+=cntA[i-1];
			cntB[i]+=cntB[i-1];
		}
		for(int i=N;i>=1;i--)
			tsa[cntB[y[i]]--]=i;
		for(int i=N;i>=1;i--)
			sa[cntA[x[tsa[i]]]--]=tsa[i];
		ra[sa[1]]=1;
		for(int i=2;i<=N;i++)
			ra[sa[i]]=ra[sa[i-1]]+(x[sa[i]]!=x[sa[i-1]]||y[sa[i]]!=y[sa[i-1]]);
	}
}
void GetH(int N)
{
	int k=0;
	for(int i=1;i<=N;i++)
	{
		k=(k==0?0:k-1);
		while(A[i+k]==A[sa[ra[i]-1]+k])
			k++;
		h[ra[i]]=k;
	}
}
bool Check(int res,int n)
{
	int l=n+1,r=0;
	for(int i=1;i<=n;i++)
		if(h[i]>=res)
		{
			l=min(l,sa[i]);
			r=max(r,sa[i]);
			if(r-l>=res)
				return true;
		}
		else
			l=r=sa[i];
	return false;
}

int main()
{
	int N;
	for(;;)
	{
		scanf("%d",&N);
		if(N==0)
			break;
		for(int i=1;i<=N;i++)
			scanf("%d",A+i);
		for(int i=1;i<N;i++)
			A[i]=A[i+1]-A[i]+100;
		A[N--]=0;
		GetSa(N);
		GetH(N);
		int L=1,R=N;
		while(L<R)
		{
			int mid=(L+R+1)/2;
			if(Check(mid,N))
				L=mid;
			else
				R=mid-1;
		}
		if(L+1<5)
			L=-1;
		printf("%d\n",L+1);
	}
	
	return 0;
}
