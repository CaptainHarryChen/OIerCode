#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class SimilarNames
{
    static const int MAXN=53,MAXS=65540,MOD=1000000007;

    int n,q,m;
    vector<int> son[MAXN];
    vector<int> st,subst[MAXS];
    bool valid[MAXS];

    int que[MAXN];
    int dp[MAXN][MAXS],tmp[MAXS];

    void MakeTree(vector<string> &str)
    {
        sort(str.begin(),str.end(),[](const string &a,const string &b){return a.length()>b.length();});
        for(int i=0;i<n;i++)
        {
            bool flag=false;
            for(int j=i+1;j<n;j++)
                if(str[i].substr(0,str[j].length())==str[j])
                {
                    son[j].push_back(i);
                    flag=true;
                    break;
                }
            if(!flag)
                son[n].push_back(i);
        }
    }
    void Discretization(vector<int> &A,vector<int> &B)
    {
        q=0;
        for(int i=0;i<m;i++)
        {
            que[q++]=A[i];
            que[q++]=B[i];
        }
        sort(que,que+q);
        q=unique(que,que+q)-que;
        for(int i=0;i<m;i++)
        {
            A[i]=lower_bound(que,que+q,A[i])-que;
            B[i]=lower_bound(que,que+q,B[i])-que;
        }
    }
    void PreprocessState(const vector<int> &A,const vector<int> &B)
    {
        for(int s=0;s<(1<<q);s++)
        {
            bool flag=true;
            for(int i=0;i<m&&flag;i++)
                if(((s>>A[i])&1)!=0&&((s>>B[i])&1)==0)
                    flag=false;
            if(flag)
            {
                st.push_back(s);
                valid[s]=true;
            }
        }
        for(auto s:st)
        {
            for(int ss=s;ss;ss=(ss-1)&s)
                if(valid[ss]&&valid[s^ss])
                    subst[s].push_back(ss);
            subst[s].push_back(0);
        }
    }
    void DP(int u)
    {
        dp[u][0]=1;
        for(auto v:son[u])
        {
            DP(v);
            copy(dp[u],dp[u]+(1<<q),tmp);
            fill(dp[u],dp[u]+(1<<q),0);
            for(auto s:st)
                for(auto ss:subst[s])
                    dp[u][s]=(dp[u][s]+1LL*tmp[s^ss]*dp[v][ss]%MOD)%MOD;
        }
        if(u!=n)
        {
            copy(dp[u],dp[u]+(1<<q),tmp);
            fill(dp[u],dp[u]+(1<<q),0);
            for(auto s:st)
            {
                dp[u][s]=tmp[s];
                for(int t=s;t;t-=t&(-t))
                    if(valid[s^(t&(-t))])
                        dp[u][s]=(dp[u][s]+tmp[s^(t&(-t))])%MOD;
            }
        }
    }

public:
    int count(vector<string> str,vector<int> A,vector<int> B)
    {
        m=A.size();
        n=str.size();

        MakeTree(str);
        Discretization(A,B);
        PreprocessState(A,B);

        DP(n);

        int ans=dp[n][(1<<q)-1];
        for(int i=1;i<=n-q;i++)
            ans=1LL*ans*i%MOD;
        return ans;
    }
};
