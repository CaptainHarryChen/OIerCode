#include<cstdio>
#define MAXN 100100
int n,num[MAXN],t[MAXN];
long long cnt;
void merge(int l,int mid,int r)
{
	int i=l,j=mid+1,k=1;
	while(i<=mid&&j<=r)
	{
		if(num[i]<=num[j])
			t[k++]=num[i++];
		else
		{
			t[k++]=num[j++];
			cnt+=(mid-i+1);
		}
	}
	while(i<=mid)
		t[k++]=num[i++];
	while(j<=r)
		t[k++]=num[j++];
	k--;
	while(k>0)
	{
		num[k-1+l]=t[k];
		k--;
	}
}
void merge_sort(int l,int r)
{
	if(r==l)
		return;
	int mid=(l+r)/2;
	merge_sort(l,mid);
	merge_sort(mid+1,r);
	merge(l,mid,r);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&num[i]);
	merge_sort(1,n);
	printf("%lld",cnt);
	return 0;
}
