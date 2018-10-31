#include<cstdio>
#include<cstring>
//#include<vector>
const int MAXN=6;

int n,ans;
bool del[MAXN*MAXN*3];
int eid[MAXN][MAXN][4];

//vector<int> adj[MAXN*MAXN*MAXN];
bool G[66][66];
int deg[66],fdeg[66],id;

void dfs(int step)
{
    if(step>=ans)
        return;
    int k;
    for(k=1;k<=id;k++)
        if(deg[k]==fdeg[k])
            break;
    if(k>id)
    {
        ans=step;
        return;
    }
    for(int i=1;i<=2*n*(n+1);i++)
        if(G[k][i])
        {
            for(int j=1;j<=id;j++)
                if(G[j][i])
                    deg[j]--;
            dfs(step+1);
            for(int j=1;j<=id;j++)
                if(G[j][i])
                    deg[j]++;
        }
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        int k;
        scanf("%d",&k);
        memset(del,0,sizeof del);
        memset(G,0,sizeof G);
        memset(deg,0,sizeof deg);
        memset(fdeg,0,sizeof fdeg);
        for(int i=1;i<=k;i++)
        {
            int x;
            scanf("%d",&x);
            del[x]=true;
        }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                eid[i][j][0]=(i-1)*(2*n+1)+j;
                eid[i][j][1]=(i-1)*(2*n+1)+n+1+j;
                eid[i][j][2]=eid[i][j][0]+2*n+1;
                eid[i][j][3]=eid[i][j][1]-1;
            }
        id=0;
        for(int l=1;l<=n;l++)
            for(int i=1;i+l-1<=n;i++)
                for(int j=1;j+l-1<=n;j++)
                {
                    id++;
                    fdeg[id]=l*4;
                    for(int k=j;k<j+l;k++)
                    {
                        G[id][eid[i][k][0]]=true;
                        if(!del[eid[i][k][0]])
                            deg[id]++;
                    }
                    for(int k=j;k<j+l;k++)
                    {
                        G[id][eid[i+l-1][k][2]]=true;
                        if(!del[eid[i+l-1][k][2]])
                            deg[id]++;
                    }
                    for(int k=i;k<i+l;k++)
                    {
                        G[id][eid[k][j][3]]=true;
                        if(!del[eid[k][j][3]])
                            deg[id]++;
                    }
                    for(int k=i;k<i+l;k++)
                    {
                        G[id][eid[k][j+l-1][1]]=true;
                        if(!del[eid[k][j+l-1][1]])
                            deg[id]++;
                    }
                }
        ans=0x3F3F3F3F;
        dfs(0);
        printf("%d\n",ans);
    }

    return 0;
}
