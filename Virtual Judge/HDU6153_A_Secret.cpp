#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1000005,MOD=1000000007;

int T,n,m;
char A[MAXN],B[MAXN];

int nxt[MAXN],ext[MAXN];
void GetNext()
{
	memset(nxt,0,sizeof nxt);
	int far=0,pos=0;
	nxt[1]=m;
	for(int i=2;i<=m;i++)
	{
		if(i<=far)
			nxt[i]=min(nxt[i-pos+1],far-i+1);
		while(nxt[i]<m&&B[i+nxt[i]]==B[nxt[i]+1])
			nxt[i]++;
		if(i+nxt[i]-1>far)
			far=i+nxt[i]-1,pos=i;
	}
}
void GetExtend()
{
	memset(ext,0,sizeof ext);
	int far=0,pos=0;
	for(int i=1;i<=n;i++)
	{
		if(i<=far)
			e
		nxt[i]=min(nxt[i-pos+1],far-i+1);
		while(ext[i]<m&&A[i+ext[i]]==B[ext[i]+1])
			ext[i]++;
		if(i+ext[i]-1>far)
			far=i+ext[i]-1,pos=i;
	}
}

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s%s",A+1,B+1);
		n=strlen(A+1);
		m=strlen(B+1);
		reverse(A+1,A+n+1);
		reverse(B+1,B+m+1);
		GetNext();
		GetExtend();
		int ans=0;
		for(int i=1;i<=n;i++)
			ans=(ans+(1LL*ext[i]*(ext[i]+1)/2))%MOD;
		printf("%d\n",ans);
	}
	
	return 0;
}
