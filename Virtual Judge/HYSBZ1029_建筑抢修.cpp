#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
const int MAXN=150005;

struct Node
{
	int a,b;
	bool operator < (const Node &t)const
	{return b<t.b;}
}A[MAXN];

priority_queue<int> Q;

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&A[i].a,&A[i].b);
	sort(A+1,A+n+1);
	int ans=0,ti=0;
	for(int i=1;i<=n;i++)
	{
		if(ti+A[i].a<=A[i].b)
		{
			Q.push(A[i].a);
			ti+=A[i].a;
			ans++;
		}
		else
		{
			int tp=Q.top();
			if(tp>A[i].a)
				Q.pop(),Q.push(A[i].a),ti=ti-tp+A[i].a;
		}
	}
	printf("%d\n",ans);
	
	return 0;
}
