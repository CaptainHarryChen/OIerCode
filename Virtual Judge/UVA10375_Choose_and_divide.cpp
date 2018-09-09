#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
using namespace std;
const int MAXN=10005;

int cnt[MAXN];
vector<pair<int,int>> pfac[MAXN];

int main()
{
	for(int i=2;i<MAXN;i++)
	{
		int t=i;
		for(int j=2;j*j<=t;j++)
			if(t%j==0)
			{
			    int cnt=0;
				while(t%j==0)
					t/=j,cnt++;
                pfac[i].push_back(make_pair(j,cnt));
			}
		if(t!=1)
			pfac[i].push_back(make_pair(t,1));
	}
	int p,q,r,s;
	while(scanf("%d%d%d%d",&p,&q,&r,&s)!=EOF)
	{
		memset(cnt,0,sizeof cnt);
		for(int i=p-q+1;i<=p;i++)
			for(auto j:pfac[i])
				cnt[j.first]+=j.second;
		for(int i=1;i<=q;i++)
			for(auto j:pfac[i])
				cnt[j.first]-=j.second;
		for(int i=r-s+1;i<=r;i++)
			for(auto j:pfac[i])
				cnt[j.first]-=j.second;
		for(int i=1;i<=s;i++)
			for(auto j:pfac[i])
				cnt[j.first]+=j.second;
		double ans=1;
		for(int i=1;i<MAXN;i++)
			ans*=pow(1.0*i,1.0*cnt[i]);
		printf("%.5f\n",ans);
	}

	return 0;
}
