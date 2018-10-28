#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class EllysString
{
    static const int MAXN=2505,MAXCHAR=26;

    int si[MAXN],ti[MAXN];
    int dp[MAXN];
    int cnt[MAXCHAR];

public:
    int theMin(vector<string> s,vector<string> t)
    {
        string S="",T="";
        for(const auto &str:s)
            S+=str;
        for(const auto &str:t)
            T+=str;
        int n=S.length();
        for(int i=0;i<n;i++)
        {
            si[i]=S[i]-'a';
            ti[i]=T[i]-'a';
        }
        fill(dp,dp+n+1,n+1);
        dp[0]=0;
        for(int i=0;i<n;i++)
            if(si[i]==ti[i])
                dp[i+1]=min(dp[i+1],dp[i]);
            else
            {
                dp[i+1]=min(dp[i+1],dp[i]+1);
                fill(cnt,cnt+MAXCHAR,0);
                cnt[si[i]]++;
                cnt[ti[i]]--;
                bool flag=false;
                int j;
                for(j=i+1;j<n&&!flag;j++)
                {
                    if(si[j]==ti[j])
                        break;
                    else
                    {
                        cnt[si[j]]++;
                        cnt[ti[j]]--;
                        if(cnt[si[j]]&&cnt[ti[j]])
                            break;
                        else if(cnt[si[j]]==0&&cnt[ti[j]]==0)
                        {
                            flag=true;
                            break;
                        }
                    }
                }
                if(flag)
                    dp[j+1]=min(dp[j+1],dp[i]+j-i);
            }
        return dp[n];
    }
};

vector<string> a,b;
string s;
EllysString solver;

int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>s;
        a.push_back(s);
    }
    for(int i=1;i<=m;i++)
    {
        cin>>s;
        b.push_back(s);
    }
    cout<<solver.theMin(a,b)<<endl;

    return 0;
}
