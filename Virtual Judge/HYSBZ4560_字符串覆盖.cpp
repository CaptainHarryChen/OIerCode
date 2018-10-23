#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=5,MAXA=10005,MAXS=18,MAXL=1005;

template<int type> class BIT
{
    int val[MAXA];
public:
    void Clear()
    {
        if(type==1)
            fill(val,val+MAXA,0xC0C0C0C0);
        else
            fill(val,val+MAXA,0x3F3F3F3F);
    }
    BIT(){Clear();}

    void Update(int x,int v)
    {
        x++;
        while(x)
        {
            if(v*type>val[x]*type)
                val[x]=v;
            x-=x&(-x);
        }
    }
    int Query(int x)
    {
        int res=(type==1?0xC0C0C0C0:0x3F3F3F3F);
        x++;
        while(x<MAXA)
        {
            if(val[x]*type>res*type)
                res=val[x];
            x+=x&(-x);
        }
        return res;
    }
};

int N,M;
string S;
int st[MAXA];

string str[MAXN];
bool del[MAXN];
int len[MAXN];

int fail[MAXL];

BIT<1> s1[MAXS];
int f[MAXA][MAXS],sf[MAXA][MAXS];

BIT<-1> s2[MAXS];
int g[MAXA][MAXS],sg[MAXA][MAXS];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin>>T;
    while(T--)
    {
        fill(del,del+MAXN,false);
        fill(st,st+MAXA,0);

        cin>>S>>N;
        M=S.length();
        for(int i=1;i<=N;i++)
        {
            cin>>str[i];
            len[i]=str[i].length();
            fill(fail,fail+MAXL,0);
            fail[0]=-1;
            for(int j=1;j<=len[i];j++)
            {
                int u=fail[j-1];
                while(u!=-1&&str[i][u]!=str[i][j-1])
                    u=fail[u];
                fail[j]=u+1;
            }

            for(int j=0,k=0;j<M;j++)
            {
                while(k!=-1&&str[i][k]!=S[j])
                    k=fail[k];
                k++;
                if(k==len[i])
                    st[j-len[i]+2]|=(1<<(i-1));
            }
        }

        for(int i=1;i<=N;i++)
            for(int j=1;j<=N;j++)
                if(!del[i]&&!del[j]&&i!=j)
                    if(str[i].find(str[j])!=string::npos)
                        del[j]=true;

        for(int i=0;i<=M;i++)
        {
            fill(f[i],f[i]+(1<<N),0xC0C0C0C0);
            fill(sf[i],sf[i]+(1<<N),0xC0C0C0C0);
            fill(g[i],g[i]+(1<<N),0x3F3F3F3F);
            fill(sg[i],sg[i]+(1<<N),0x3F3F3F3F);
        }

        for(int s=0;s<(1<<N);s++)
        {
            s1[s].Clear();
            s2[s].Clear();
        }
        for(int i=0;i<=M;i++)
            for(int s=0;s<(1<<N);s++)
            {
                if(i==0)
                {
                    if(s==0)
                        f[i][s]=sf[i][s]=g[i][s]=sg[i][s]=0;
                    else
                    {
                        f[i][s]=s1[s].Query(i)+i;
                        g[i][s]=s2[s].Query(i)+i;
                    }
                }
                else
                {
                    sf[i][s]=max(sf[i][s],sf[i-1][s]);
                    f[i][s]=max(sf[i][s],s1[s].Query(i)+i);
                    sg[i][s]=min(sg[i][s],sg[i-1][s]);
                    g[i][s]=min(sg[i][s],s2[s].Query(i)+i);
                    //if(sf[i][s]>=0&&sf[i][s]<=M)cerr<<"sf["<<i<<"]["<<s<<"]="<<sf[i][s]<<"     ";
                    //if(f[i][s]>=0&&f[i][s]<=M)cerr<<"f["<<i<<"]["<<s<<"]="<<f[i][s]<<endl;
                    //if(sg[i][s]>=0&&sg[i][s]<=M)cerr<<"sg["<<i<<"]["<<s<<"]="<<sg[i][s]<<"     ";
                    //if(g[i][s]>=0&&g[i][s]<=M)cerr<<"g["<<i<<"]["<<s<<"]="<<g[i][s]<<endl;
                }
                for(int k=1;k<=N;k++)
                    if((st[i+1]&(1<<(k-1)))!=0&&(s&(1<<(k-1)))==0)
                    {
                        int ts=s|(1<<(k-1));
                        s1[ts].Update(i+len[k],f[i][s]-i);
                        sf[i+len[k]][ts]=max(sf[i+len[k]][ts],f[i][s]+len[k]);
                        if(!del[k])
                        {
                            s2[ts].Update(i+len[k],g[i][s]-i);
                            sg[i+len[k]][ts]=min(sg[i+len[k]][ts],g[i][s]+len[k]);
                        }
                    }
            }
        int edst=0;
        for(int i=1;i<=N;i++)
            if(!del[i])
                edst|=(1<<(i-1));
        int ans2=0,ans1=g[M][edst];
        for(int s=0;s<(1<<N);s++)
            if((s&(edst))==edst)
                ans2=max(ans2,f[M][s]);
        cout<<ans1<<' '<<ans2<<endl;
    }
    return 0;
}
