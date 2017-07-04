#include<cstdio>
#include<cstring>
#define MAXN 2005
#define MAX_NUM 256
char S[MAXN];
namespace SuffixArray
{
	int A[MAXN],B[MAXN],cntA[MAXN],cntB[MAXN],tsa[MAXN];
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
			rank[sa[i]]=rank[sa[i-1]]+(str[sa[i-1]]!=str[sa[i]]);
		for(int len=1;rank[sa[n-1]]<n-1;len<<=1)
		{
			memset(cntA,0,sizeof cntA);
			memset(cntB,0,sizeof cntB);
			for(int i=0;i<n;i++)
			{
				cntA[A[i]=rank[i]]++;
				cntB[B[i]=i+len<n?rank[i+len]:0]++;
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
				rank[sa[i]]=rank[sa[i-1]]
				+(A[sa[i]]!=A[sa[i-1]]
				||B[sa[i]]!=B[sa[i-1]]);
		}
	}
	void getHeight(char str[],int n,int sa[],int rank[],int Height[])
	{
		for(int i=1,k=0;i<=n;i++)
		{
			k=k>0?k-1:0;
			while(str[i+k]==str[sa[rank[i]+1]+k])
				k++;
			Height[rank[i]]=k;
		}
	}
}
int R[MAXN],Sa[MAXN],H[MAXN];
int main()
{
	freopen("SuffixArray_data.in","r",stdin);
	int n;
	scanf("%s",S+1);
	n=strlen(S+1);
	SuffixArray::getSa(S,n,Sa,R);
	SuffixArray::getHeight(S,n,Sa,R,H);
	for(int i=1;i<=n;i++)
	{
		printf("Sa[%2d]=%2d:  ",i,Sa[i]);
		for(int j=Sa[i];j<=n;j++)
			printf("%c",S[j]);
		printf("\n");
	}
	printf("\n");
	for(int i=1;i<n;i++)
		printf("Hight[%d~%d]=%d\n",i,i+1,H[i]);
	return 0;
}
