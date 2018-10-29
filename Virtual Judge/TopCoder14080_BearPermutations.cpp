#include<iostream>
using namespace std;

class BearPermutations
{
    static const int MAXN=105;

    int C[MAXN][MAXN];
    int dp[MAXN][MAXN][3];

public:
    int countPermutations(int N,int S,int MOD)
    {
        C[0][0]=1;
        for(int i=1;i<=N;i++)
        {
            C[i][0]=1;
            for(int j=1;j<=i;j++)
                C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
        }
        for(int n=1;n<=N;n++)
            for(int s=0;s<=S;s++)
                for(int c=0;c<3;c++)
                    for(int pos=0;pos<n;pos++)
                    {
                        int add=0;
                        if(c==1)
                            add=pos+1;
                        if(c==2)
                            add=n-pos;
                        if(add>s)
                            continue;
                        for(int s1=0,s2;s1<=s-add;s1++)
                        {
                            s2=s-add-s1;
                            if(pos==0&&s1)
                                continue;
                            if(pos==n-1&&s2)
                                continue;
                            int tmp=C[n-1][pos];
                            if(pos>0)
                                tmp=1LL*tmp*dp[pos][s1][pos==n-1?0:2]%MOD;
                            if(pos<n-1)
                                tmp=1LL*tmp*dp[n-1-pos][s2][pos==0?0:1]%MOD;
                            dp[n][s][c]=(dp[n][s][c]+tmp)%MOD;
                        }
                    }
        int ans=0;
        for(int s=0;s<=S;s++)
            ans=(ans+dp[N][s][0])%MOD;
        return ans;
    }
};
