#include<cstdio>
#include<cstring>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXLOG=18;

int N,H[MAXN];
set<pair<int,int> > cities;
int nxt[2][MAXN][MAXLOG];
long long dis[2][MAXN][MAXLOG][2];

void InitDoubling()
{
    memset(nxt,-1,sizeof nxt);
    cities.insert(make_pair(H[N],N));
    for(int i=N-1;i>0;i--)
    {
        set<pair<int,int> >::iterator u=cities.lower_bound(make_pair(H[i],0)),v;
        v=u;
        vector<pair<int,pair<int,int> > > tmp;
        for(int j=1;j<=2&&v!=cities.end();j++)
        {
            tmp.push_back(make_pair(abs(H[i]-v->first),*v));
            v++;
        }
        v=u;
        for(int j=1;j<=2&&v!=cities.begin();j++)
        {
            v--;
            tmp.push_back(make_pair(abs(H[i]-v->first),*v));
        }
        if(tmp.size()==1U)
        {
            nxt[0][i][0]=tmp[0].second.second;
            dis[0][i][0][0]=tmp[0].first;
            nxt[1][i][0]=-1;
        }
        else
        {
            sort(tmp.begin(),tmp.end());
            nxt[0][i][0]=tmp[0].second.second;
            dis[0][i][0][0]=tmp[0].first;
            nxt[1][i][0]=tmp[1].second.second;
            dis[1][i][0][1]=tmp[1].first;
        }
        cities.insert(make_pair(H[i],i));
    }
    for(int j=1;j<MAXLOG;j++)
        for(int k=0;k<2;k++)
            for(int i=1;i<=N;i++)
                if(nxt[k][i][j-1]!=-1)
                {
                    nxt[k][i][j]=nxt[k^(j==1)][nxt[k][i][j-1]][j-1];
                    if(nxt[k][i][j]!=-1)
                    {
                        dis[k][i][j][0]=dis[k][i][j-1][0]+dis[k^(j==1)][nxt[k][i][j-1]][j-1][0];
                        dis[k][i][j][1]=dis[k][i][j-1][1]+dis[k^(j==1)][nxt[k][i][j-1]][j-1][1];
                    }
                }
}

void GetDis(int s,int X,int &A,int &B)
{
    A=B=0;
    for(int j=MAXLOG-1;j>=0;j--)
        if(nxt[1][s][j]!=-1&&dis[1][s][j][0]+dis[1][s][j][1]<=X)
        {
            A+=dis[1][s][j][1];
            B+=dis[1][s][j][0];
            X-=dis[1][s][j][1]+dis[1][s][j][0];
            s=nxt[1][s][j];
        }

}
int cmp(int A1,int B1,int A2,int B2)
{
    if(B1==0&&B2!=0)
        return 1;
    if(B1!=0&&B2==0)
        return -1;
    if(B1==0&&B2==0)
        return 0;
    if(1LL*A1*B2==1LL*A2*B1)
        return 0;
    return (1LL*A1*B2<1LL*A2*B1)?-1:1;
}

void Solve1()
{
    int X0;
    scanf("%d",&X0);
    long long bestA=1,bestB=0;
    int bestID=0;
    for(int i=1;i<=N;i++)
    {
        int A,B;
        GetDis(i,X0,A,B);
        if(cmp(bestA,bestB,A,B)==1||(cmp(bestA,bestB,A,B)==0&&H[i]>H[bestID]))
        {
            bestID=i;
            bestA=A;
            bestB=B;
        }
    }
    printf("%d\n",bestID);
}
void Solve2()
{
    int M;
    scanf("%d",&M);
    while(M--)
    {
        int S,X;
        scanf("%d%d",&S,&X);
        int A,B;
        GetDis(S,X,A,B);
        printf("%d %d\n",A,B);
    }
}

int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
        scanf("%d",&H[i]);

    InitDoubling();
    Solve1();
    Solve2();
    
    return 0;
}
