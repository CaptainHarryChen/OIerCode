#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=15;
int A[MAXN],B[MAXN];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",A+i);
	for(int i=1;i<=m;i++)
		scanf("%d",B+i);
	int mn=10;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(A[i]==B[j])
				mn=min(mn,A[i]);
	if(mn!=10)
	{
		printf("%d\n",mn);
		return 0;
	}
	int ma=10,mb=10;
	for(int i=1;i<=n;i++)
		ma=min(ma,A[i]);
	for(int i=1;i<=m;i++)
		mb=min(mb,B[i]);
	if(ma>mb)
		swap(ma,mb);
	printf("%d\n",ma*10+mb);
	return 0;
}
