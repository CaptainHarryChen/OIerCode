#include<cstdio>
#include<vector>
#include<functional>
#include<algorithm>
using namespace std;
const int MAXN=100005;

struct Query
{
	int a,b,id;
	Query(){}
	bool operator < (const Query &t)const
	{return a<t.a||(a==t.a&&b<t.b);}
};

int n,m;
int h[MAXN],L[MAXN],lval[MAXN],R[MAXN];
int stk[MAXN],val[MAXN],top;
int ans[MAXN];
Query Q[MAXN];

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			scanf("%d",&h[i]);
		stk[top=1]=n;
		R[n]=1;
		for(int i=n-1;i>0;i--)
		{
			while(top&&h[stk[top]]<=h[i])
				top--;
			stk[++top]=i;
			R[i]=top;
		}
		L[1]=1;
		lval[1]=h[1];
		int now=h[1];
		for(int i=2;i<=n;i++)
		{
			L[i]=L[i-1];
			if(h[i]>now)
				L[i]++,now=h[i];
			lval[i]=now;
		}
		for(int i=1;i<=m;i++)
			scanf("%d%d",&Q[i].a,&Q[i].b),Q[i].id=i;
		sort(Q+1,Q+m+1);
		top=0;
		for(int i=m,j=n;i>0;i--)
		{
			while(j>=Q[i].a+1)
			{
				while(top&&h[stk[top]]<=h[j])
					top--;
				stk[++top]=j;
				val[top]=h[j];
				j--;
			}
			int c=max(Q[i].b,lval[Q[i].a-1]);
			int id=lower_bound(val+1,val+top+1,c,greater<int>())-val;
			id--;
			ans[Q[i].id]=L[Q[i].a-1]+(c>lval[Q[i].a-1])+R[stk[id]];
		}
		for(int i=1;i<=m;i++)
			printf("%d\n",ans[i]);
	}
	return 0;
}
