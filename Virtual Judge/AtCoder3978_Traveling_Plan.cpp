#include<cstdio>
#include<cstdlib>
const int MAXN=100005;

int l[MAXN],r[MAXN];
int A[MAXN];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",A+i);
	for(int i=1;i<=n;i++)
		l[i]=l[i-1]+abs(A[i]-A[i-1]);
	for(int i=n;i>0;i--)
		r[i]=r[i+1]+abs(A[i]-A[i+1]);
	for(int i=1;i<=n;i++)
		printf("%d\n",l[i-1]+abs(A[i+1]-A[i-1])+r[i+1]);
	return 0;
}
