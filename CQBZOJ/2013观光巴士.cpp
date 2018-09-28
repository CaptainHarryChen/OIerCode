#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=1005,MAXK=100005,MAXM=10005;

int N,M,K;
int D[MAXN];
int T[MAXM],A[MAXM],B[MAXM];
int latest[MAXN],off[MAXN],ti[MAXN],far[MAXN];
long long allD;

int main()
{
    scanf("%d%d%d",&N,&M,&K);
    for(int i=1;i<N;i++)
        scanf("%d",&D[i]),allD+=D[i];
    for(int i=1;i<=M;i++)
    {
        scanf("%d%d%d",&T[i],&A[i],&B[i]);
        latest[A[i]]=max(latest[A[i]],T[i]);
        off[B[i]]++;
    }
    for(int i=1;i<=N;i++)
        off[i]+=off[i-1];
    long long ans=0;
    ti[1]=0;
    for(int i=2;i<=N;i++)
        ti[i]=max(ti[i-1],latest[i-1])+D[i-1];
    for(int i=1;i<=M;i++)
        ans+=ti[B[i]]-T[i];
    while(K&&allD)
    {
        ti[1]=0;
        for(int i=2;i<=N;i++)
            ti[i]=max(ti[i-1],latest[i-1])+D[i-1];
        far[N]=far[N-1]=N;
        for(int i=N-2;i>0;i--)
            if(ti[i+1]<=latest[i+1])
                far[i]=i+1;
            else
                far[i]=far[i+1];
        int best=0,bestid;
        for(int i=1;i<N;i++)
            if(off[far[i]]-off[i]>best&&D[i])
            {
                best=off[far[i]]-off[i];
                bestid=i;
            }
        ans-=best;
        D[bestid]--;
        allD--;
        K--;
    }
    printf("%lld\n",ans);

    return 0;
}
