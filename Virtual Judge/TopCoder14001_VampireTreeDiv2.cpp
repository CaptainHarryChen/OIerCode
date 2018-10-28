#include<iostream>
#include<vector>
using namespace std;

class VampireTreeDiv2
{
    static const int MAXN=1005,MOD=1000000007;

    int n,m;
    vector<int> adj[MAXN];
    vector<int> sp;
    int st[MAXN];

    int dp[MAXN][2],cal[MAXN][2];

    void DP(int u,int fa)
    {
        for(auto v:adj[u])
            if(v!=fa)
                DP(v,u);
        if(st[u]!=2)
        {
            dp[u][0]=0;
            cal[u][0]=1;
            for(auto v:adj[u])
                if(v!=fa)
                {
                    dp[u][0]+=dp[v][1];
                    cal[u][0]=1LL*cal[u][0]*cal[v][1]%MOD;
                    if(dp[u][0]>=0x3F3F3F3F)
                    {
                        dp[u][0]=0x3F3F3F3F;
                        break;
                    }
                }
        }
        else
            dp[u][0]=0x3F3F3F3F,cal[u][0]=0;
        if(st[u]!=1)
        {
            dp[u][1]=1;
            cal[u][1]=1;
            for(auto v:adj[u])
                if(v!=fa)
                {
                    int a=dp[v][0],b=dp[v][1],c=cal[v][0],d=cal[v][1];
                    if(a>b)
                        swap(a,b),swap(c,d);
                    if(a==b)
                        c=(c+d)%MOD;
                    dp[u][1]+=a;
                    cal[u][1]=1LL*cal[u][1]*c%MOD;
                    if(dp[u][1]>=0x3F3F3F3F)
                    {
                        dp[u][1]=0x3F3F3F3F;
                        break;
                    }
                }
        }
        else
            dp[u][1]=0x3F3F3F3F,cal[u][1]=0;
    }


public:
    int countMinSamples(vector<int> A,vector<int> B)
    {
        n=A.size()+1;
        m=0;
        for(int i=1;i<n;i++)
        {
            //cout<<i<<" "<<A[i-1]<<"\n";
            adj[i].push_back(A[i-1]);
            adj[A[i-1]].push_back(i);
            if(B[i-1]!=-1)
            {
                m+=(B[i-1]!=-1);
                sp.push_back(i);
            }
        }

        int best=0x3F3F3F3F,res=0;
        for(int s=0;s<(1<<m);s++)
        {
            fill(st,st+n,0);
            bool flag=true;
            for(int i=0;i<m;i++)
            {
                if(st[sp[i]]!=0&&st[sp[i]]!=((s>>i)&1)+1)
                {
                    flag=false;
                    break;
                }
                st[sp[i]]=((s>>i)&1)+1;
                if(st[sp[i]]==1)
                {
                    if(st[A[sp[i]-1]]!=0&&st[A[sp[i]-1]]!=2)
                    {
                        flag=false;
                        break;
                    }
                    st[A[sp[i]-1]]=2;
                    if(st[B[sp[i]-1]]!=0&&st[B[sp[i]-1]]!=2)
                    {
                        flag=false;
                        break;
                    }
                    st[B[sp[i]-1]]=2;
                }
            }
            if(!flag)
                continue;
            DP(0,-1);
            int a=dp[0][0],b=dp[0][1],c=cal[0][0],d=cal[0][1];
            if(a>b)
                swap(a,b),swap(c,d);
            if(a==b)
                c=(c+d)%MOD;
            if(a==best)
                res=(res+c)%MOD;
            if(a<best)
                best=a,res=c;
        }
        return res;
    }
};
