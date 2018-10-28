#include<iostream>
#include<string>
#include<vector>
using namespace std;

class StringDecryption
{
    static const int MOD=1000000009;
    static const int MAXN=505,MAXDIG=11;

    int n;
    int dp[MAXN][MAXDIG][2];

public:
    int decrypt(vector<string> code)
    {
        string str="";
        for(const auto &s:code)
            str+=s;
        n=str.length();
        str=" "+str;
        dp[0][10][1]=1;
        for(int i=1;i<=n;i++)
        {
            int num=0,pw10=1;
            for(int j=i-2;j>=0;j--)
            {
                num=(num+1LL*pw10*(str[j+1]-'0')%MOD)%MOD;
                pw10=10LL*pw10%MOD;
                if(str[j+1]=='0')
                    continue;
                if(j>0&&str[j]==str[i])
                    continue;
                for(int d=0;d<11;d++)
                {
                    for(int f=0;f<2;f++)
                    {
                        if(dp[j][d][f]==0)
                            continue;
                        if(str[i]=='0'&&f)
                            continue;
                        dp[i][d][0]=(dp[i][d][0]+dp[j][d][f])%MOD;
                        if(str[i]-'0'!=d)
                        {
                            if(str[i]!='0'&&(j<i-2||num>1))
                                dp[i][str[i]-'0'][0]=(dp[i][str[i]-'0'][0]+1LL*dp[j][d][f]*(num-1-f+MOD)%MOD)%MOD;
                            if(j<i-2||num>1||f==0)
                                dp[i][str[i]-'0'][1]=(dp[i][str[i]-'0'][1]+1LL*dp[j][d][f])%MOD;
                        }
                    }
                }
            }
        }
        return dp[n][str[n]-'0'][1];
    }
};
