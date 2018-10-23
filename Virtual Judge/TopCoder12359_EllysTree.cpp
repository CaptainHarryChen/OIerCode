#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class EllysTree
{
    static const int MAXN=105;

    int n,fa[MAXN],dep[MAXN];
    bool vis[MAXN];
    vector<int> son[MAXN];

    int dp[MAXN],siz[MAXN];
    bool has[MAXN];

    void DFS(int u)
    {
        for(int i=0;i<(int)son[u].size();i++)
        {
            int v=son[u][i];
            dep[v]=dep[u]+1;
            DFS(v);
        }
    }
    void DP(int s,int u)
    {
        dp[u]=siz[u]=0;
        has[u]=false;
        for(int i=0;i<(int)son[u].size();i++)
        {
            int v=son[u][i];
            DP(s,v);
            siz[u]+=siz[v];
            dp[u]+=dp[v];
            has[u]|=has[v];
        }
        if(!vis[u])
        {
            if(u==s)
                has[u]=true;
            if(siz[u]==0&&u!=s)
                dp[u]++;
            if(siz[u]&&dp[u])
            {
                dp[u]--;
                if(!has[u])
                    dp[u]=max(dp[u],1);
            }
            siz[u]++;
        }
    }
    bool check(int x,int y)
    {
        if(dep[x]>dep[y])
            swap(x,y);
        while(dep[x]<dep[y])
            y=fa[y];
        return x==y;
    }

public:
    vector<int> getMoves(const vector<int> &pa)
    {
        vector<int> ans;
        n=pa.size()+1;
        for(int i=2;i<=n;i++)
        {
            fa[i]=pa[i-2]+1;
            son[fa[i]].push_back(i);
        }
        DFS(1);
        DP(1,1);
        vis[1]=true;
        if(dp[1]!=0)
            return ans;
        int last=1;
        for(int i=1;i<n;i++)
        {
            for(int j=2;j<=n;j++)
                if(!vis[j]&&check(last,j))
                {
                    DP(j,1);
                    vis[j]=true;
                    if(dp[1]==0)
                    {
                        ans.push_back(j-1);
                        last=j;
                        break;
                    }
                    vis[j]=false;
                }
        }
        return ans;
    }
};