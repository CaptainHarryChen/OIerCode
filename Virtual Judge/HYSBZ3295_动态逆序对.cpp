#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005;

struct Data
{
	int x,t,y;
};

int sum[MAXN];
void Add(int pos,int val)
{
	while(pos<MAXN)
	{
		sum[pos]+=val;
		pos+=(pos&(-pos));
	}
}
int Get(int pos)
{
	int res=0;
	while(pos>0)
	{
		res+=sum[pos];
		pos-=(pos&(-pos));
	}
	return res;
}

int N;
int ans1[MAXN],ans2[MAXN];
Data A[MAXN];

void CDQ(int L,int R)
{
	if(L>=R)
		return;
	
	int mid=(L+R)/2,itl=L,itr=mid+1;
	
	static Data temp[MAXN];
	
	for(int i=L;i<=R;i++)
		if(A[i].t<=mid)
			temp[itl++]=A[i];
		else
			temp[itr++]=A[i];
	for(int i=L;i<=R;i++)
		A[i]=temp[i];
	
	itl=L;
	for(int i=mid+1;i<=R;i++)
	{
		while(itl<=mid&&A[itl].x<A[i].x)
		{
			Add(A[itl].y,1);
			itl++;
		}
		ans1[A[i].t]+=itl-L-Get(A[i].y);
	}
	for(int i=L;i<itl;i++)
		Add(A[i].y,-1);
	
	itl=mid;
	for(int i=R;i>mid;i--)
	{
		while(itl>=L&&A[itl].x>A[i].x)
		{
			Add(A[itl].y,1);
			itl--;
		}
		ans2[A[i].t]+=Get(A[i].y-1);
	}
	for(int i=mid;i>itl;i--)
		Add(A[i].y,-1);
	
	CDQ(L,mid);
	CDQ(mid+1,R);
}

long long ans[MAXN];
int pos[MAXN];

int main()
{
	int D;
	scanf("%d%d",&N,&D);
	for(int i=1,x;i<=N;i++)
	{
		scanf("%d",&x);
		A[i].x=i;
		A[i].y=x;
		pos[x]=i;
	}
	int tim=N;
	for(int i=1,x;i<=D;i++)
	{
		scanf("%d",&x);
		A[pos[x]].t=tim--;
	}
	for(int i=1;i<=N;i++)
		if(A[i].t==0)
			A[i].t=tim--;
	
	CDQ(1,N);
	
	for(int i=1;i<=N;i++)
		ans[i]=ans[i-1]+ans1[i]+ans2[i];
	for(int i=N;i>N-D;i--)
		printf("%lld\n",ans[i]);
	
	return 0;
}
