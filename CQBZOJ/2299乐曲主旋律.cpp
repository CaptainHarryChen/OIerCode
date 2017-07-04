#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 500005
#define MAX_NUM 200
namespace SuffixArray
{
	int cntA[MAXN],cntB[MAXN];
	int A[MAXN],B[MAXN],tsa[MAXN];
	void getSa(int str[],int n,int sa[],int rank[])
	{
		str[++n]=0;
		memset(cntA,0,sizeof cntA);
		for(int i=1;i<=n;i++)
			cntA[str[i]]++;
		for(int i=1;i<MAX_NUM;i++)
			cntA[i]+=cntA[i-1];
		for(int i=n;i>0;i--)
			sa[--cntA[str[i]]]=i;
		rank[sa[0]]=0;
		for(int i=1;i<n;i++)
			rank[sa[i]]=rank[sa[i-1]]+(str[sa[i]]!=str[sa[i-1]]);
		for(int len=1;rank[sa[n-1]]<n-1;len<<=1)
		{
			memset(cntA,0,sizeof cntA);
			memset(cntB,0,sizeof cntB);
			for(int i=0;i<n;i++)
			{
				cntA[A[i]=rank[i]]++;
				cntB[B[i]=(i+len<=n?rank[i+len]:0)]++;
			}
			for(int i=1;i<n;i++)
			{
				cntA[i]+=cntA[i-1];
				cntB[i]+=cntB[i-1];
			}
			for(int i=n-1;i>=0;i--)
				tsa[--cntB[B[i]]]=i;
			for(int i=n-1;i>=0;i--)
				sa[--cntA[A[tsa[i]]]]=tsa[i];
			rank[sa[0]]=0;
			for(int i=0;i<n;i++)
				rank[sa[i]]=rank[sa[i-1]]
				+(A[sa[i]]!=A[sa[i-1]]||B[sa[i]]!=B[sa[i-1]]);
		}
	}
	void getHeight(int str[],int n,int sa[],int rank[],int height[])
	{
		for(int i=1,k=0;i<=n;i++)
		{
			if(k)k--;
			while(str[i+k]==str[sa[rank[i]+1]+k])
				k++;
			height[rank[i]]=k;
		}
	}
}
int A[MAXN],Sa[MAXN],R[MAXN],H[MAXN];
bool check(int h,int n)
{
	int mx=0,mn=0x7FFFFFFF;
	for(int i=1;i<=n;i++)
		if(H[i]>=h)
		{
			mx=max(mx,Sa[i]);
			mn=min(mn,Sa[i]);
			if(mx-mn>=h)return 1;
		}
		else
			mx=Sa[i],mn=Sa[i];
	return 0;
}
int main()
{
	int N,l,r,mid;
	while(~scanf("%d",&N))
	{
		if(!N)break;
		for(int i=1;i<=N;i++)
			scanf("%d",&A[i]);
		for(int i=1;i<N;i++)
			A[i]=A[i+1]-A[i]+100;
		A[N--]=0;
		SuffixArray::getSa(A,N,Sa,R);
		SuffixArray::getHeight(A,N,Sa,R,H);
		l=1;r=N;
		while(l<r)
		{
			mid=(l+r+1)>>1;
			if(check(mid,N))
				l=mid;
			else
				r=mid-1;
		}
		printf("%d\n",l+1);
	}
	return 0;
}
