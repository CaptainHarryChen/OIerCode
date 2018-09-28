#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=2005;

int N,x;
int A[MAXN];
int best[MAXN][MAXN];

int main()
{
    scanf("%d%d",&N,&x);
    for(int i=1;i<=N;i++)
        scanf("%d",&A[i]);
    for(int i=1;i<=N;i++)
    {
        best[i][0]=A[i];
        for(int k=1;k<N;k++)
            best[i][k]=min(best[i][k-1],A[(i-k+N-1)%N+1]);
    }
    long long ans=0x3F3F3F3F3F3F3F3FLL;
    for(int k=0;k<N;k++)
    {
        long long tmp=0;
        for(int i=1;i<=N;i++)
            tmp+=best[i][k];
        ans=min(ans,tmp+1LL*k*x);
    }
    printf("%lld\n",ans);

    fclose(stdin);
    fclose(stdout);
    return 0;
}
