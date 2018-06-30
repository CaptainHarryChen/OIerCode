#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=25005;

int N;
vector< pair<int,int> > A,B;
bool cmp(const pair<int,int> &a,const pair<int,int> &b)
{return a.second>b.second||(a.second==b.second&&a.first>b.second);}

int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if(x<=y)
			A.push_back(make_pair(x,y));
		else
			B.push_back(make_pair(x,y));
	}
	
	sort(A.begin(),A.end());
	sort(B.begin(),B.end(),cmp);
	long long t1=0,t2=0;
	for(int i=0;i<(int)A.size();i++)
	{
		t1+=A[i].first;
		t2=max(t2,t1);
		t2+=A[i].second;
	}
	for(int i=0;i<(int)B.size();i++)
	{
		t1+=B[i].first;
		t2=max(t2,t1);
		t2+=B[i].second;
	}
	printf("%lld\n",t2);
	return 0;
}
