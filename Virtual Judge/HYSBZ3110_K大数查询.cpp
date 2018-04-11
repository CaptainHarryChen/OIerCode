#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=50005;

template<class T> void Read(T &x)
{
	char c;
	bool flag=false;
	while(c=getchar(),c!=EOF)
	{
		if(c=='-')
			flag=true;
		else if('0'<=c&&c<='9')
		{
			x=c-'0';
			while(c=getchar(),'0'<=c&&c<='9')
				x=x*10+c-'0';
			if(flag)
				x=-x;
			return;
		}
	}
}

struct Operation
{
	int type;
	int a,b;
	long long c;
	int id;
	int key;
	bool operator < (const Operation &t)const
	{return key<t.key||(key==t.key&&id<t.id);}
};
bool IdCmp(const Operation &a,const Operation &b)
{
	return a.id<b.id;
}

int N,M;

namespace SegmentTree
{
	int tim;
	int ti[MAXN*4];
	long long num[MAXN*4];
	int add[MAXN*4];
	inline void Clear(int i)
	{
		if(ti[i]!=tim)
		{add[i]=0;num[i]=0;ti[i]=tim;}
	}
	inline void PushDown(int i,int L,int R,int mid)
	{
		Clear(i*2);Clear(i*2+1);
		add[i*2]+=add[i];num[i*2]+=1LL*(mid-L+1)*add[i];
		add[i*2+1]+=add[i];num[i*2+1]+=1LL*(R-mid)*add[i];
		add[i]=0;
	}
	void Add(int l,int r,int L=1,int R=N,int i=1)
	{
		Clear(i);
		if(l<=L&&R<=r)
		{
			add[i]++;
			num[i]+=1LL*(R-L+1);
			return;
		}
		int mid=(L+R)/2;
		PushDown(i,L,R,mid);
		if(l<=mid)
			Add(l,r,L,mid,i*2);
		if(mid<r)
			Add(l,r,mid+1,R,i*2+1);
		num[i]=num[i*2]+num[i*2+1];
	}
	long long Query(int l,int r,int L=1,int R=N,int i=1)
	{
		Clear(i);
		if(l<=L&&R<=r)
			return num[i];
		int mid=(L+R)/2;
		PushDown(i,L,R,mid);
		int ret=0;
		if(l<=mid)
			ret+=Query(l,r,L,mid,i*2);
		if(mid<r)
			ret+=Query(l,r,mid+1,R,i*2+1);
		return ret;
	}
}

Operation op[MAXN];
int ans[MAXN];

void solve(int L,int R,int valL,int valR)
{
	if(L>=R)
		return;
	if(valL==valR)
	{
		for(int i=L;i<=R;i++)
			if(op[i].type==2)
				ans[op[i].id]=valL;
		return;
	}
	SegmentTree::tim++;
	int Mid=0,valMid=(valL+valR)/2;
	if(valL+valR<0)
		valMid=(valL+valR-1)/2;
	for(int i=L;i<=R;i++)
	{
		if(op[i].type==1)
		{
			if(op[i].c>valMid)
			{
				SegmentTree::Add(op[i].a,op[i].b);
				op[i].key=1;
			}
			else
				op[i].key=0,Mid++;
		}
		else
		{
			long long rank=SegmentTree::Query(op[i].a,op[i].b);
			if(rank<op[i].c)
				op[i].key=0,Mid++,op[i].c-=rank;
			else
				op[i].key=1;
		}
	}
	sort(op+L,op+R+1);
	solve(L,L+Mid-1,valL,valMid);
	solve(L+Mid,R,valMid+1,valR);
}

int main()
{
	Read(N);Read(M);
	long long mx=-MAXN,mn=MAXN;
	for(int i=1;i<=M;i++)
	{
		Read(op[i].type);Read(op[i].a);Read(op[i].b);Read(op[i].c);
		op[i].id=i;
		if(op[i].type==1)
		{
			mx=max(mx,op[i].c);
			mn=min(mn,op[i].c);
		}
	}
	solve(1,M,mn,mx);
	sort(op+1,op+M+1,IdCmp);
	for(int i=1;i<=M;i++)
		if(op[i].type==2)
			printf("%d\n",ans[i]);
	
	return 0;
}
