#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=50005,INF=0x3F3F3F3F;

int val[MAXN],N;
int sum[MAXN*4],mxl[MAXN*4],mxr[MAXN*4],mx[MAXN*4];

void PushUp(int u)
{
	sum[u]=sum[u*2]+sum[u*2+1];
	mxl[u]=max(mxl[u*2],mxl[u*2+1]+sum[u*2]);
	mxr[u]=max(mxr[u*2+1],mxr[u*2]+sum[u*2+1]);
	mx[u]=max(mx[u*2],mx[u*2+1]);
	mx[u]=max(mx[u],mxr[u*2]+mxl[u*2+1]);
}
void Build(int u=1,int L=1,int R=N)
{
	if(L==R)
	{
		sum[u]=mxl[u]=mxr[u]=mx[u]=val[L];
		return;
	}
	int mid=(L+R)/2;
	Build(u*2,L,mid);
	Build(u*2+1,mid+1,R);
	PushUp(u);
}
void Modify(int pos,int nval,int u=1,int L=1,int R=N)
{
	if(L==pos&&pos==R)
	{
		sum[u]=mxl[u]=mxr[u]=mx[u]=nval;
		return;
	}
	int mid=(L+R)/2;
	if(pos<=mid)
		Modify(pos,nval,u*2,L,mid);
	if(pos>mid)
		Modify(pos,nval,u*2+1,mid+1,R);
	PushUp(u);
}
int Query(int l,int r,int &ml,int &mr,int &s,int u=1,int L=1,int R=N)
{
	if(l<=L&&R<=r)
	{
		ml=mxl[u];mr=mxr[u];s=sum[u];
		return mx[u];
	}
	int res=-INF,mid=(L+R)/2,ml1=-INF,mr1=-INF,ml2=-INF,mr2=-INF,s1=0,s2=0;
	if(l<=mid)
		res=max(res,Query(l,r,ml1,mr1,s1,u*2,L,mid));
	if(r>mid)
		res=max(res,Query(l,r,ml2,mr2,s2,u*2+1,mid+1,R));
	res=max(res,mr1+ml2);
	ml=max(ml1,s1+ml2);
	mr=max(mr2,s2+mr1);
	s=s1+s2;
	return res;
}

int main()
{
	int Q,a,b,op;
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
		scanf("%d",val+i);
	Build();
	scanf("%d",&Q);
	int x,y,z;
	for(int i=1;i<=Q;i++)
	{
		scanf("%d%d%d",&op,&a,&b);
		if(op==0)
			Modify(a,b);
		else
			printf("%d\n",Query(a,b,x,y,z));
	}
	return 0;
}
