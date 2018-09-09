#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=200005;

int n;
vector<int> adj[MAXN];
int W[MAXN];

bool cmp(int a,int b)
{return W[a]>W[b];}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i=1;i<=n;i++)
        scanf("%d",&W[i]);
    for(int i=1;i<=n;i++)
        sort(adj[i].begin(),adj[i].end(),cmp);
    long long ans1=0,ans2=0;
    for(int i=1;i<=n;i++)
        if((int)adj[i].size()>=2)
        {
            ans1=max(ans1,1LL*W[adj[i][0]]*W[adj[i][1]]);
            long long sum1=0,sum2=0;
            for(int j=0;j<(int)adj[i].size();j++)
            {
                sum1+=W[adj[i][j]];
                sum2+=W[adj[i][j]]*W[adj[i][j]];
            }
            ans2+=sum1*sum1-sum2;
        }
    printf("%lld %lld\n",ans1,ans2%10007);
    return 0;
}
