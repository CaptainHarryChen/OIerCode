#include<cstdio>
#include<cstring>
const int MAXN=1005;

int n,m;
char A[MAXN],B[MAXN];
int fail[MAXN];

int main()
{
	while(scanf("%s%s",A+1,B+1)==2)
	{
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
				ans++,j=0;
		}
		printf("%d\n",ans);
	}
	return 0;
}
