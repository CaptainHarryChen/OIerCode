#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005;
int N,Q;
struct SegTree
{
	int cnt[MAXN*4],lcnt[MAXN*4],rcnt[MAXN*4];
	int lnum[MAXN*4],rnum[MAXN*4];
	void Build(const int num[],int id=1,int l=1,int r=N)
	{
		if(l==r)
		{
			cnt[id]=lcnt[id]=rcnt[id]=1;
			lnum[id]=rnum[id]=num[l];
			return;
		}
		Build(num,id*2,l,(l+r)/2);
		Build(num,id*2+1,(l+r)/2+1,r);
		lnum[id]=lnum[id*2];
		rnum[id]=rnum[id*2+1];
		lcnt[id]=lcnt[id*2];
		if(lcnt[id]==(l+r)/2-l+1&&lnum[id*2+1]==lnum[id])
			lcnt[id]+=lcnt[id*2+1];
		rcnt[id]=rcnt[id*2+1];
		if(rcnt[id]==r-(l+r)/2&&rnum[id*2]==rnum[id])
			rcnt[id]+=rcnt[id*2];
		cnt[id]=max(cnt[id*2],cnt[id*2+1]);
		cnt[id]=max(cnt[id],lcnt[id]);
		cnt[id]=max(cnt[id],rcnt[id]);
		if(rnum[id*2]==lnum[id*2+1])
			cnt[id]=max(cnt[id],rcnt[id*2]+lcnt[id*2+1]);
	}
	int Query(int L,int R,int id=1,int l=1,int r=N,int *lc=NULL,int *rc=NULL)
	{
		if(r<L||l>R)
		{
			if(lc)*lc=0;
			if(rc)*rc=0;
			return 0;
		}
		if(L<=l&&r<=R)
		{
			if(lc)*lc=lcnt[id];
			if(rc)*rc=rcnt[id];
			return cnt[id];
		}
		int q1,q2,lc1,lc2,rc1,rc2,ret;
		q1=Query(L,R,id*2,l,(l+r)/2,&lc1,&rc1);
		q2=Query(L,R,id*2+1,(l+r)/2+1,r,&lc2,&rc2);
		ret=max(q1,q2);
		if(rnum[id*2]==lnum[id*2+1])
			ret=max(ret,rc1+lc2);
		if(lc)
		{
			*lc=lc1;
			if(lc1==(l+r)/2-l+1&&lnum[id*2+1]==lnum[id])
				*lc+=lc2;
		}
		if(rc)
		{
			*rc=rc2;
			if(rc2==r-(l+r)/2&&rnum[id*2]==rnum[id])
				*rc+=rc1;
		}
		return ret;
	}
};
int a[MAXN];
SegTree Tr;
int main()
{
	while(1)
	{
		scanf("%d",&N);
		if(!N)
			break;
		scanf("%d",&Q);
		for(int i=1;i<=N;i++)
			scanf("%d",a+i);
		Tr.Build(a);
		for(int i=1,x,y;i<=Q;i++)
		{
			scanf("%d%d",&x,&y);
			printf("%d\n",Tr.Query(x,y));
		}
	}
	return 0;
}
