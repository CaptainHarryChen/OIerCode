#include<cstdio>
#include<unordered_set>
#include<algorithm>
using namespace std;
const int MAXN=10;
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};

int ans[MAXN+1][MAXN+1][MAXN+1];

struct Block
{
    int n,x[MAXN],y[MAXN];
    bool operator == (const Block &b)const
    {
        if(n!=b.n)
            return false;
        for(int i=0;i<n;i++)
            if(x[i]!=b.x[i]||y[i]!=b.y[i])
                return false;
        return true;
    }
    void Sort()
    {
        pair<int,int> s[MAXN];
        for(int i=0;i<n;i++)
            s[i].first=x[i],s[i].second=y[i];
        sort(s,s+n);
        for(int i=0;i<n;i++)
            x[i]=s[i].first,y[i]=s[i].second;
    }
    void Translate(int d,int t)
    {
        for(int i=0;i<n;i++)
        {
            x[i]+=dir[d][0]*t;
            y[i]+=dir[d][1]*t;
        }
    }
    void TranslateToUpLeft()
    {
        int mnx=20,mny=20;
        for(int i=0;i<n;i++)
        {
            mnx=min(mnx,x[i]);
            mny=min(mny,y[i]);
        }
        Translate(0,mnx);
        Translate(3,mny);
    }
    void Rotate()
    {
        for(int i=0;i<n;i++)
        {
            int tx=x[i],ty=y[i];
            x[i]=ty;
            y[i]=-tx;
        }
        TranslateToUpLeft();
    }
    void Flip()
    {
        for(int i=0;i<n;i++)
            x[i]=-x[i];
        TranslateToUpLeft();
    }
    void print()
    {
        char s[MAXN+1][MAXN+1]={0};
        printf("--DEBUG--\n");
        for(int i=0;i<10;i++)
            for(int j=0;j<10;j++)
                s[i][j]='.';
        for(int i=0;i<n;i++)
            s[x[i]][y[i]]='#';
        for(int i=0;i<10;i++)
            puts(s[i]);
    }
};
struct Hash
{
    size_t operator () (const Block &a)const
    {
        size_t res=0;
        for(int i=0;i<a.n;i++)
            res=res*100u+(a.x[i]*10u+a.y[i]);
        return res;
    }
};

unordered_set<Block,Hash> have;

Block A,B;
bool used[MAXN*2+2][MAXN*2+2];

bool check()
{
    B=A;
    B.TranslateToUpLeft();
    for(int i=0;i<4;i++)
    {
        B.Sort();
        if(have.count(B))
            return false;
        B.Rotate();
    }
    B.Flip();
    for(int i=0;i<4;i++)
    {
        B.Sort();
        if(have.count(B))
            return false;
        B.Rotate();
    }
    B.Sort();
    have.insert(B);
    int mxx=-1,mxy=-1;
    for(int i=0;i<B.n;i++)
    {
        mxx=max(mxx,B.x[i]);
        mxy=max(mxy,B.y[i]);
    }
    if(mxx>mxy)
        swap(mxx,mxy);
    ans[B.n][mxx+1][mxy+1]++;
    return true;
}

void dfs(int step)
{
    A.n=step;
    if(step&&!check())
        return;
    if(step==10)
        return;
    if(step==0)
        for(int i=0;i<10;i++)
            for(int j=0;j<10;j++)
            {
                used[i+10][j+10]=true;
                A.x[step]=i;A.y[step]=j;
                dfs(step+1);
                used[i+10][j+10]=false;
            }
    short vis[MAXN*2+2]={0};
    for(int i=0;i<step;i++)
        for(int d=0;d<4;d++)
        {
            int x=A.x[i]+dir[d][0],y=A.y[i]+dir[d][1];
            if(used[x+10][y+10]||((vis[x+10]>>(y+10))&1))
                continue;
            vis[x+10]|=(1<<(y+10));
            used[x+10][y+10]=true;
            A.x[step]=x;A.y[step]=y;
            dfs(step+1);
            used[x+10][y+10]=false;
        }
}

int main()
{
    //freopen("data.out","w",stdout);
    dfs(0);
    for(int k=1;k<=10;k++)
        for(int i=1;i<=10;i++)
            for(int j=1;j<=10;j++)
                ans[k][i][j]+=ans[k][i-1][j]+ans[k][i][j-1]-ans[k][i-1][j-1];

    int n,w,h;
    while(scanf("%d%d%d",&n,&w,&h)!=EOF)
    {
        if(w>h)
            swap(w,h);
        printf("%d\n",ans[n][w][h]);
    }

    return 0;
}
