#include<cstdio>
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;

class ThreeColorability
{
    const static int MAXN=105;

    struct DSU
    {
        int fa[MAXN];
        int Root(int x)
        {return fa[x]==0?x:(fa[x]=Root(fa[x]));}
        bool Union(int x,int y)
        {
            int r1=Root(x),r2=Root(y);
            if(r1==r2)
                return false;
            fa[r1]=r2;
            return true;
        }
    };

    DSU D;

    vector<int> adj[MAXN];

    bool conf[MAXN][MAXN];
    bool vis[MAXN];
    char col[MAXN];

    bool Paint(int u,char c)
    {
        vis[u]=true;
        if(col[u])
        {
            if(col[u]!=c)
                return false;
            return true;
        }
        col[u]=c;
        for(int i=0;i<(int)adj[u].size();i++)
            if(!Paint(adj[u][i],c=='N'?'Z':'N'))
                return false;
        return true;
    }

public:
    vector<string> lexSmallest(const vector<string> &cells)
    {
        int n=cells.size(),m=cells[0].length();
        vector<string> ans;
        for(int i=0;i<n;i++)
        {
            ans.push_back(string());
            for(int j=0;j<m;j++)
                ans[i]+=' ';
        }
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                if(cells[i][j]!='?')
                    for(int k=j+1;k<m;k++)
                        if(cells[i][k]!='?')
                        {
                            if(cells[i][j]!=cells[i][k])
                                conf[j][k]=conf[k][j]=true;
                            else
                                D.Union(j,k);
                        }
        for(int j=0;j<m;j++)
            for(int k=0;k<m;k++)
                if(conf[j][k])
                    adj[D.Root(j)].push_back(D.Root(k));

        for(int j=0;j<m;j++)
            if(cells[0][j]!='?')
                if(!Paint(D.Root(j),cells[0][j]))
                    return vector<string>{};
        for(int j=0;j<m;j++)
            if(!vis[D.Root(j)])
                if(!Paint(D.Root(j),'N'))
                    return vector<string>{};
        for(int j=0;j<m;j++)
            ans[0][j]=col[D.Root(j)];
        for(int i=1;i<n;i++)
        {
            int flag=-1;
            for(int j=0;j<m;j++)
                if(cells[i][j]!='?')
                    flag=(cells[i][j]!=ans[0][j]);
            if(flag==-1)
                flag=(ans[0][0]=='Z');
            if(flag)
                for(int j=0;j<m;j++)
                    ans[i][j]=(ans[0][j]=='N'?'Z':'N');
            else
                for(int j=0;j<m;j++)
                    ans[i][j]=(ans[0][j]=='N'?'N':'Z');
        }
        return ans;
    }
};
