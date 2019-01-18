#include<cstdio>
#include<cstring>
const int MAXN=1000005;

int n,m;
char A[MAXN],B[MAXN];
int fail[MAXN];

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s%s",B+1,A+1);
		n=strlen(A+1);
		m=strlen(B+1);
		fail[0]=-1;
		for(int i=1;i<=m;i++)
		{
			int u=fail[i-1];
			while(u!=-1&&B[u+1]!=B[i])
				u=fail[u];
			fail[i]=u+1;
		}
		int ans=0;
		for(int i=1,j=0;i<=n;i++)
		{
			while(j&&A[i]!=B[j+1])
				j=fail[j];
			if(A[i]==B[j+1])
				j++;
			if(j==m)
				ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
