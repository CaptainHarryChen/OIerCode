#include<cstdio>
#include<cstring>
#include<set>
#include<algorithm>
using namespace std;
const int MAXN=205,MAXM=50005;
struct Edge
{
	int u,v,id;
	long long g,s;
	bool operator < (const Edge &t)const
	{return g<t.g||(g==t.g&&s<t.s);}
};
struct UFS
{
	int S[MAXN];
	void clear()
	{
		memset(S,0,sizeof S);
	}
	int Find(int x)
	{
		if(S[x]==0)
			return x;
		return S[x]=Find(S[x]);
	}
	void Union(int a,int b)
	{
		int r1=Find(a),r2=Find(b);
		if(r1==r2)return;
		S[r1]=r2;
	}
};
Edge E[MAXM];
struct cmp
{
	bool operator () (const int a,const int b)const
	{return E[a].s<E[b].s||(E[a].s==E[b].s&&E[a].id<E[b].id);}
};
UFS S;
set<int,cmp> Q;
long long Kruskal(int n)
{
	long long ans=-1;
	int r1,r2,cnt=0;
	S.clear();
	set<int,cmp>::iterator it;
	for(it=Q.begin();it!=Q.end()&&cnt<n-1;)
	{
		r1=S.Find(E[*it].u);
		r2=S.Find(E[*it].v);
		if(r1!=r2)
		{
			S.Union(r1,r2);
			cnt++;
			ans=max(ans,E[*it].s);
			it++;
		}
		else
			Q.erase(it++);
	}
	if(cnt<n-1)
		return -1;
	return ans;
}
int main()
{
	int N,M;
	long long G,S,ans=0x7FFFFFFFFFFFFFFFLL,temp;
	scanf("%d%d%I64d%I64d",&N,&M,&G,&S);
	for(int i=1;i<=M;i++)
	{
		scanf("%d%d%I64d%I64d",&E[i].u,&E[i].v,&E[i].g,&E[i].s);
		E[i].id=i;
		E[i].g*=G;
		E[i].s*=S;
	}
	sort(E+1,E+M+1);
	for(int i=1,k;i<=M;)
	{
		k=i;
		do
		{
			Q.insert(i);
			i++;
		}
		while(E[i].g==E[i-1].g&&i<=M);
		temp=Kruskal(N);
		if(temp!=-1)
			ans=min(ans,E[k].g+temp);
	}
	if(ans==0x7FFFFFFFFFFFFFFFLL)
		printf("-1\n");
	else
		printf("%I64d\n",ans);
	return 0;
}
