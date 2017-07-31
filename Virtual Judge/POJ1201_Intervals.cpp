#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=50005;
struct SegTree
{
	int sum[MAXN*4];
	void Insert(int L,int R,int l=0,int r=50000,int id=1)
	{
		if(r<L||R<l)
			return;
		if(L<=l&&r<=R)
		{
			sum[id]=r-l+1;
			return;
		}
		if(sum[id]==r-l+1)
		{
			sum[id*2]=(l+r)/2-l+1;
			sum[id*2+1]=r-(l+r)/2;
		}
		Insert(L,R,l,(l+r)/2,id*2);
		Insert(L,R,(l+r)/2+1,r,id*2+1);
		sum[id]=sum[id*2]+sum[id*2+1];
	}
	int Query(int L,int R,int l=0,int r=50000,int id=1)
	{
		if(r<L||R<l)
			return 0;
		if(L<=l&&r<=R)
			return sum[id];
		if(sum[id]==r-l+1)
		{
			sum[id*2]=(l+r)/2-l+1;
			sum[id*2+1]=r-(l+r)/2;
		}
		int ret=0;
		ret+=Query(L,R,l,(l+r)/2,id*2);
		ret+=Query(L,R,(l+r)/2+1,r,id*2+1);
		return ret;
	}
};
struct Sec
{
	int l,r,num;
	bool operator < (const Sec &t) const
	{return r<t.r||(r==t.r&&l<t.l);}
};
Sec s[MAXN];
SegTree ST;
int chosen[MAXN][2],cnt;
int main()
{
	int N;
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
		scanf("%d%d%d",&s[i].l,&s[i].r,&s[i].num);
	sort(s+1,s+N+1);
	int ans=0,tmp;
	for(int i=1;i<=N;i++)
	{
		tmp=ST.Query(s[i].l,s[i].r);
		if(tmp<s[i].num)
		{
			int l=s[i].r-s[i].num+tmp+1;
			while(cnt>0&&chosen[cnt][1]>=l)
			{
				l=chosen[cnt][0]-(chosen[cnt][1]-l+1);
				cnt--;
			}
			ST.Insert(l,s[i].r);
			chosen[++cnt][0]=l;
			chosen[cnt][1]=s[i].r;
			ans+=s[i].num-tmp;
		}
	}
	printf("%d\n",ans);
	return 0;
}
