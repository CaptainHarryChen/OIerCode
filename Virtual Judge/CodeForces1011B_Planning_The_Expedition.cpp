#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=105;

int n,m;
int cnt[MAXN];
vector<pair<int,int> > food;

bool check(int x)
{
	static vector<pair<int,int> > tmp;
	tmp=food;
	int i=1,j=0;
	while(i<=n&&j<tmp.size())
	{
		while(j<tmp.size()&&tmp[j].first<x)
			j++;
		if(j>=tmp.size())
			return false;
		tmp[j].first-=x;
		i++;
	}
	return true;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int a;
		scanf("%d",&a);
		cnt[a]++;
	}
	for(int i=1;i<=100;i++)
		if(cnt[i])
			food.push_back(make_pair(cnt[i],i));
	sort(food.begin(),food.end(),greater<pair<int,int> >());
	int L=0,R=100;
	while(L<R)
	{
		int mid=(L+R+1)/2;
		if(check(mid))
			L=mid;
		else
			R=mid-1;
	}
	printf("%d\n",L);
	
	return 0;
}
