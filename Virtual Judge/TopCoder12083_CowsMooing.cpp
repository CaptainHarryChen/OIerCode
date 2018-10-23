#include<cstring>
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
const int MOD=10007;

class CowsMooing
{
    static const int MAXN=53,MAXC=32*27*25;
    int n;
    int cnt[MAXN][MAXN],len[MAXN],pro[MAXN],pro1[MAXN],pro2[MAXN];
    bool del[MAXN];

    int PowMod(int a,int b)
    {
        int res=1;
        while(b)
        {
            if(b&1)
                res=1LL*res*a%MOD;
            b>>=1;
            a=1LL*a*a%MOD;
        }
        return res;
    }

public:
    vector<int> getDistribution(vector<string> patterns)
    {
        n=patterns.size();
        vector<int> ans(n+1,0);

        for(int c=0;c<MAXC;c++)
        {
            memset(cnt,0,sizeof cnt);
            for(int i=0;i<n;i++)
            {
                int s=patterns[i].size();
                len[i]=s/__gcd(MAXC,s);
                if(len[i]==7)
                    len[i]=49;
                for(int j=0;j<len[i];j++)
                    cnt[i][j]=(patterns[i][(j*MAXC+c)%s]=='M');
            }
            memset(del,0,sizeof del);
            for(int i=0;i<n;i++)
                if(!del[i])
                {
                    for(int j=i+1;j<n;j++)
                        if(len[j]==len[i])
                        {
                            del[j]=true;
                            for(int k=0;k<len[j];k++)
                                cnt[i][k]+=cnt[j][k];
                        }
                }
            int L=1;
            memset(pro,0,sizeof pro);
            pro[0]=1;
            for(int i=0;i<n;i++)
                if(!del[i])
                {
                    memset(pro1,0,sizeof pro1);
                    memset(pro2,0,sizeof pro2);
                    for(int j=0;j<len[i];j++)
                        pro1[cnt[i][j]]++;
                    for(int a=0;a<=n;a++)
                        for(int b=0;a+b<=n;b++)
                            pro2[a+b]=(pro2[a+b]+(pro[a]*pro1[b])%MOD)%MOD;
                    L=L*len[i]%MOD;
                    memcpy(pro,pro2,sizeof pro);
                }
            for(int i=0;i<=n;i++)
            {
                int tmp=3235*PowMod(MAXC,MOD-2)%MOD;
                tmp=pro[i]*tmp%MOD;
                tmp=tmp*PowMod(L,MOD-2)%MOD;
                ans[i]=(ans[i]+tmp)%MOD;
            }
        }
        return ans;
    }
};
