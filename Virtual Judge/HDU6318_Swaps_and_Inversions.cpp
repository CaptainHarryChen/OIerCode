#include<cstdio>
const int MAXN=100005;

int n;
long long x,y;
int A[MAXN];

long long merge_sort(int A[],int L,int R)
{
	static long long tmp[MAXN];
	if(L==R)
		return 0;
	int mid=(L+R)/2,l=L,r=mid+1;
	long long ret=0;
	ret+=merge_sort(A,L,mid);
	ret+=merge_sort(A,mid+1,R);
	for(int i=L;i<=R;i++)
		if(r>R||(A[l]<=A[r]&&l<=mid))
			tmp[i]=A[l++];
		else
		{
			tmp[i]=A[r++];
			ret+=mid-l+1;
		}
	for(int i=L;i<=R;i++)
		A[i]=tmp[i];
	return ret;
}

int main()
{
	while(scanf("%d%I64d%I64d",&n,&x,&y)!=EOF)
	{
		for(int i=1;i<=n;i++)
			scanf("%d",A+i);
		long long inv=merge_sort(A,1,n);
		if(x<y)
			printf("%I64d\n",x*inv);
		else
			printf("%I64d\n",y*inv);
	}
	return 0;
}
