#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=10005,MAXT=86400;
struct sche
{
	int T1,T2,S;
	sche(){}
	sche(int t1,int t2,int s)
	{
		T1=t1;
		T2=t2;
		S=s;
	}
};
class SegmentTree
{
	int Min[MAXT*4];
public:
	SegmentTree()
	{
		memset(Min,0x7F,sizeof Min);
	}
	void insert(int pos,int val,int id=1,int l=0,int r=MAXT-1)
	{
		if(r<pos||l>pos)
			return;
		if(l==r)
		{
			Min[id]=min(val,Min[id]);
			return;
		}
		insert(pos,val,id*2,l,(l+r)/2);
		insert(pos,val,id*2+1,(l+r)/2+1,r);
		Min[id]=min(Min[id*2],Min[id*2+1]);
	}
	int get(int L,int R,int id=1,int l=0,int r=MAXT-1)
	{
		if(r<L||R<l)
			return 0x7F7F7F7F;
		if(L<=l&&r<=R)
			return Min[id];
		return min(get(L,R,id*2,l,(l+r)/2),get(L,R,id*2+1,(l+r)/2+1,r));
	}
};
bool cmp(const sche &a,const sche &b)
{
	return a.T2<b.T2||(a.T2==b.T2&&a.T1<b.T1);
}
sche cow[MAXN];
int dp[MAXN];
SegmentTree ST;
int main()
{
	int N,M,E;
	scanf("%d%d%d",&N,&M,&E);
	for(int i=1;i<=N;i++)
		scanf("%d%d%d",&cow[i].T1,&cow[i].T2,&cow[i].S);
	sort(cow+1,cow+N+1,cmp);
	memset(dp,0x7F,sizeof dp);
	ST.insert(M,0);
	for(int i=1;i<=N;i++)
	{
		dp[i]=min(dp[i],ST.get(cow[i].T1-1,cow[i].T2)+cow[i].S);
		ST.insert(cow[i].T2,dp[i]);
	}
	int ans=0x7F7F7F7F;
	for(int i=1;i<=N;i++)
		if(cow[i].T2>=E)
			ans=min(ans,dp[i]);
	if(ans==0x7F7F7F7F)
		printf("-1\n");
	else
		printf("%d\n",ans);
	return 0;
}
