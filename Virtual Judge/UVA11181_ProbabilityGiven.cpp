#include<cstdio>
const int MAXN=22;
int n,r;
double p[MAXN];
double pr,pi;
void dfs1(int i,int k,double P)
{
	if(k==0&&i>n)
	{
		pr+=P;
		return;
	}
	if(i>n)return;
	dfs1(i+1,k-1,P*p[i]);
	dfs1(i+1,k,P*(1-p[i]));
}
void dfs2(int use,int i,int k,double P)
{
	if(k==0&&i>n)
	{
		pi+=P;
		return;
	}
	if(i>n)return;
	dfs2(use,i+1,k-1,P*p[i]);
	if(i!=use)
		dfs2(use,i+1,k,P*(1-p[i]));
}
int main()
{
	for(int cas=1;scanf("%d%d",&n,&r)!=EOF&&(n!=0||r!=0);cas++)
	{
		printf("Case %d:\n",cas);
		for(int i=1;i<=n;i++)
			scanf("%lf",&p[i]);
		pr=0;
		dfs1(1,r,1);
		for(int i=1;i<=n;i++)
		{
			pi=0;
			dfs2(i,1,r,1);
			printf("%.6lf\n",pi/pr);
		}
	}
	return 0;
}
