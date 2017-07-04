#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 100010
#define MAX_NUM 256
namespace SuffixArray
{
	int A[MAXN],B[MAXN],cntA[MAXN],cntB[MAXN];
	int tsa[MAXN];
	void getSa(char str[],int n,int sa[],int rank[])
	{
		str[++n]=0;
		memset(cntA,0,sizeof cntA);
		for(int i=1;i<=n;i++)
			cntA[(int)str[i]]++;
		for(int i=1;i<MAX_NUM;i++)
			cntA[i]+=cntA[i-1];
		for(int i=n;i>0;i--)
			sa[--cntA[(int)str[i]]]=i;
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
			for(int i=1;i<n;i++)
				rank[sa[i]]=rank[sa[i-1]]+(A[sa[i-1]]!=A[sa[i]]||B[sa[i-1]]!=B[sa[i]]);
		}
	}
	void getHeight(char str[],int n,int sa[],int rank[],int h[])
	{
		for(int i=1,j=0;i<=n;i++)
		{
			if(j)j--;
			while(str[i+j]==str[sa[rank[i]+1]+j])j++;
			h[rank[i]]=j;
		}
	}
}
char S[MAXN];
int Sa[MAXN],R[MAXN],H[MAXN];
int Min[MAXN][22];
int main()
{
	int n,q,l,r;
	scanf("%s%d",S+1,&q);
	n=strlen(S+1);
	SuffixArray::getSa(S,n,Sa,R);
	SuffixArray::getHeight(S,n,Sa,R,H);
	n--;
	memset(Min,0x7F,sizeof Min);
	for(int i=1;i<=n;i++)
		Min[i][0]=H[i];
	for(int j=1;(1<<j)-1<=n;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			Min[i][j]=min(Min[i][j-1],Min[i+(1<<(j-1))][j-1]);
	for(int i=1,Log;i<=q;i++)
	{
		scanf("%d%d",&l,&r);
		if(l==r){printf("%d\n",n-l+2);continue;}
		l=R[l],r=R[r];
		if(l>r)swap(l,r);
		r--;
		Log=0;
		while(l+(1<<(Log+1))-1<=r)Log++;
		printf("%d\n",min(Min[l][Log],Min[r-(1<<Log)+1][Log]));
	}
	return 0;
}
