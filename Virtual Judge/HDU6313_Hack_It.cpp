#include<cstdio>
const int MAXN=2005;

int A[MAXN][MAXN];

int main()
{
	//freopen("ldb.txt","w",stdout);
	for(int k=1;(k-1)*47<=2000;k++)
	{
		for(int i=1;i<=47&&i+(k-1)*47<=2000;i++)
		{
			int s=0;
			for(int j=1;(j-1)*47+(s+k-1)%47+1<=2000;j++,s=(s+i)%47)
				A[(k-1)*47+i][(j-1)*47+(s+k-1)%47+1]=1;
		}
	}
	int cnt=0;
	printf("%d\n",2000);
	for(int i=1;i<=2000;i++)
	{
		for(int j=1;j<=2000;j++)
			printf("%d",A[i][j]),cnt+=A[i][j];
		puts("");
	}
	//fprintf(stderr,"%d\n",cnt);
	
	return 0;
}
