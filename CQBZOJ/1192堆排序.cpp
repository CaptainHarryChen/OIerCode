#include<cstdio>
#include<algorithm>
using std::swap;
const int MAXN=100005;
void sort(int A[],int l,int r)
{
	if(l>=r)return;
	int mid=(l+r)/2;
	swap(A[mid],A[r]);
	int i=l-1;
	for(int j=l;j<r;j++)
		if(A[j]<=A[r])
		{
			swap(A[i+1],A[j]);
			i++;
		}
	swap(A[i+1],A[r]);
	sort(A,l,i);
	sort(A,i+2,r);
}
int A[MAXN];
int main()
{
	int N;
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
		scanf("%d",A+i);
	sort(A,1,N);
	for(int i=1;i<N;i++)
		printf("%d ",A[i]);
	printf("%d\n",A[N]);
	return 0;
}
