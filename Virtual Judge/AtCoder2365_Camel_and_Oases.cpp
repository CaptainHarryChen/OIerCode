#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=200005,INF=0x3F3F3F3F,MAXLG=25;

int N,V,lgV,X[MAXN];
int f1[MAXN*4],f2[MAXN*4];
vector<int> seg[MAXLG];
bool ans[MAXN];

int main()
{
	scanf("%d%d",&N,&V);
	for(int i=1;i<=N;i++)
		scanf("%d",&X[i]);
	X[0]=-INF;
	X[N+1]=INF;

	for(int d=V;;d/=2)
	{
		lgV++;
		for(int i=1;i<=N+1;i++)
			if(X[i]-X[i-1]>d)
				seg[lgV].push_back(i-1);
		seg[lgV].push_back(N+1);
		if(d==0)
			break;
	}

	if((int)seg[1].size()-2>lgV)
	{
		for(int i=1;i<=N;i++)
			puts("Impossible");
		return 0;
	}

	f1[0]=0;
	for(int s=1;s<(1<<lgV);s++)
		for(int i=1;i<=lgV;i++)
			if((s&(1<<(i-1))))
			{
				int ts=s^(1<<(i-1));
				f1[s]=max(f1[s],f1[ts]);
				if(f1[s]==N)
					continue;
				auto it=upper_bound(seg[i].begin(),seg[i].end(),f1[ts]);
				f1[s]=max(f1[s],*it);
			}
	memset(f2,0x3F,sizeof f2);
	f2[0]=N+1;
	for(int s=1;s<(1<<lgV);s++)
		for(int i=1;i<=lgV;i++)
			if((s&(1<<(i-1))))
			{
				int ts=s^(1<<(i-1));
				f2[s]=min(f2[s],f2[ts]);
				if(f2[s]==1)
					continue;
				auto it=lower_bound(seg[i].begin(),seg[i].end(),f2[ts]-1);
				if(it==seg[i].begin())
                    continue;
                it--;
				f2[s]=min(f2[s],*it+1);
			}

    for(int i=1;i<(int)seg[1].size()-1;i++)
	{
		int l=seg[1][i-1]+1,r=seg[1][i];
		for(int s=0;s<(1<<lgV);s+=2)
		{
			int ts=((1<<lgV)-1)^s^1;
			if(f1[s]>=l-1&&f2[ts]<=r+1)
			{
				ans[i]=true;
				break;
			}
		}
	}
	for(int i=1,j=1;i<=N;i++,j=(i>seg[1][j]?j+1:j))
		puts(ans[j]?"Possible":"Impossible");

	return 0;
}
