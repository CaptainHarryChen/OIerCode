#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=400005,MOD=998244353,G=3;

int A[MAXN],B[MAXN];

int main()
{
	freopen("NTT_data.in","r",stdin);
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		scanf("%d",A+i);
	for(int i=0;i<m;i++)
		scanf("%d",B+i);
	mul(A,n,B,m,A);
	for(int i=0;i<n+m-2;i++)
		printf("%d ",A[i]);
	printf("%d\n",A[n+m-2]);
	return 0;
}
