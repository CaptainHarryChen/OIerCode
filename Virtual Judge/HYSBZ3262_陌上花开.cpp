#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXK=200005;

struct Triad
{
	int a,b,c,id,num;
	bool operator == (const Triad &t)const
	{
		return a==t.a&&b==t.b&&c==t.c;
	}
};
bool cmp1(Triad x,Triad y)
{
	if(x.a<y.a)
		return true;
	if(x.a>y.a)
		return false;
	return x.b<y.b||(x.b==y.b&&x.c<y.c);
}
bool cmp2(Triad x,Triad y)
{
	if(x.b<y.b)
		return true;
	if(x.b>y.b)
		return false;
	return x.a<y.a||(x.a==y.a&&x.c<y.c);
}

int sum[MAXK];
void Add(int pos,int val)
{
	while(pos<MAXK)
	{
		sum[pos]+=val;
		pos+=(pos&(-pos));
	}
}
int Get(int pos)
{
	int val=0;
	while(pos)
	{
		val+=sum[pos];
		pos-=(pos&(-pos));
	}
	return val;
}

Triad A[MAXN],backup[MAXN];
Triad temp[MAXN];
int ans[MAXN];
int cnt[MAXN];

void CDQ(int L,int R)
{
	if(L==R)
		return;
	int mid=(L+R)/2;
	CDQ(L,mid);
	CDQ(mid+1,R);
	sort(A+L,A+mid+1,cmp2);
	sort(A+mid+1,A+R+1,cmp2);
	int it=L;
	for(int i=mid+1;i<=R;i++)
	{
		while(it<=mid&&A[it].b<=A[i].b)
		{
			Add(A[it].c,A[it].num);
			it++;
		}
		ans[A[i].id]+=Get(A[i].c);
	}
	for(int i=L;i<it;i++)
		Add(A[i].c,-A[i].num);
}

int main()
{
	int N,K;
	scanf("%d%d",&N,&K);
	for(int i=1;i<=N;i++)
	{
		scanf("%d%d%d",&A[i].a,&A[i].b,&A[i].c);
		A[i].id=i;
	}
	sort(A+1,A+N+1,cmp1);
	copy(A+1,A+N+1,backup+1);
	int m=unique(A+1,A+N+1)-A-1;
	for(int i=1,j=1;i<=m;i++)
	{
		while(j<=N&&backup[j]==A[i])
			A[i].num++,j++;
		ans[A[i].id]=A[i].num-1;
	}
	CDQ(1,m);
	for(int i=1;i<=m;i++)
		cnt[ans[A[i].id]]+=A[i].num;
	for(int i=0;i<N;i++)
		printf("%d\n",cnt[i]);
	
	return 0;
}
