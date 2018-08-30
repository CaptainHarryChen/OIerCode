#include<cstdio>
#include<cstring>
const int MAXN=1005;

int n,m,k;
int G[MAXN][MAXN];
int nxt[MAXN];
bool vis[MAXN];
int X[MAXN],Y[MAXN];
int s1[MAXN],s2[MAXN],tot1,tot2;

bool dfs(int u)
{
    for(int i=1;i<=k;i++)
        if(G[u][i]&&vis[i]==false)
        {
            vis[i]=true;
            if(nxt[i]==0||dfs(nxt[i]))
            {
                nxt[i]=u;
                return true;
            }
        }
    return false;
}

int main()
{
    scanf("%d%d%d",&n,&m,&k);
    char a[6],b[6];
    for(int i=1;i<=k;i++)
    {
        scanf("%s%s",a,b);
        sscanf(a+1,"%d",&X[i]);
        sscanf(b+1,"%d",&Y[i]);
        if(a[0]=='C')
            s1[++tot1]=i;
        else
            s2[++tot2]=i;
    }

    for(int i=1;i<=tot1;i++)
        for(int j=1;j<=tot2;j++)
            if(X[s1[i]]==Y[s2[j]]||Y[s1[i]]==X[s2[j]])
                G[s1[i]][s2[j]]=1;

    int ans=k;
    for(int i=1;i<=k;i++)
    {
        memset(vis,0,sizeof vis);
        ans-=dfs(i);
    }
    printf("%d\n",ans);

    return 0;
}
