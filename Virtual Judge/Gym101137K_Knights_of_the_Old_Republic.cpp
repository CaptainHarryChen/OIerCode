#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=300005,MAXM=300005;
struct Edge
{
	int u,v,val;
	bool operator < (const Edge &t)const
	{return val<t.val;}
};
class UFset
{
public:
	int fa[MAXN];
	int Find(int x)
	{
		if(fa[x]==0)
			return x;
		return fa[x]=Find(fa[x]);
	}
};
int mxp[MAXN],mnc[MAXN];
long long s[MAXN];
Edge E[MAXM];
UFset U;
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	long long ans=0LL;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",mxp+i,mnc+i);
		s[i]=1LL*mxp[i]*mnc[i];
	}
	int r1,r2,np,nc;
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].val);
	sort(E+1,E+m+1);
	for(int i=1;i<=m;i++)
	{
		r1=U.Find(E[i].u);
		r2=U.Find(E[i].v);
		if(r1!=r2)
		{
			U.fa[r1]=r2;
			np=max(E[i].val,max(mxp[r1],mxp[r2]));
			nc=min(mnc[r1],mnc[r2]);
			s[r2]=min(s[r1]+s[r2],1LL*np*nc);
			mxp[r2]=np;
			mnc[r2]=nc;
		}
	}
	for(int i=1;i<=n;i++)
		if(U.Find(i)==i)
			ans+=s[i];
	printf("%I64d\n",ans);
	return 0;
}
