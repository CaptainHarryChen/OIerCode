#include<cstdio>
#include<cstring>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=200005;

int N,M,A[MAXN],B[MAXN];
map<int,int> cnt;

int val[MAXN];

int fa[MAXN],sz[MAXN];
int Root(int x)
{
    if(fa[x]==0)
        return x;
    return fa[x]=Root(fa[x]);
}
void Union(int x,int y)
{
    int r1=Root(x),r2=Root(y);
    if(r1==r2)
        return;
    fa[r1]=r2;
    sz[r2]+=sz[r1];
}

int main()
{
    int sum=0,tmp=0;
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
    {
        scanf("%d",&A[i]);
        cnt[A[i]]++;
        sum^=A[i];
    }
    cnt[sum]++;
    A[N+1]=sum;
    for(int i=1;i<=N;i++)
    {
        scanf("%d",&B[i]);
        tmp^=B[i];
    }
    B[N+1]=tmp^sum;
    for(int i=1;i<=N;i++)
    {
        if(cnt[B[i]]==0)
        {
            puts("-1");
            return 0;
        }
        cnt[B[i]]--;
    }
    for(int i=1;i<=N+1;i++)
    {
        val[i*2-1]=A[i];
        val[i*2]=B[i];
    }
    sort(val+1,val+(N+1)*2+1);
    M=unique(val+1,val+(N+1)*2+1)-val-1;
    for(int i=1;i<=N+1;i++)
    {
        A[i]=lower_bound(val+1,val+M+1,A[i])-val;
        B[i]=lower_bound(val+1,val+M+1,B[i])-val;
    }
    sum=find(val+1,val+M+1,sum)-val;

    fill(sz+1,sz+M+1,1);

    int ans=0;
    for(int i=1;i<=N;i++)
        if(A[i]!=B[i])
        {
            Union(A[i],B[i]);
            ans++;
        }
    for(int i=1;i<=M;i++)
        if(Root(i)==i&&sz[i]>1)
            ans++;
    if(Root(sum)!=sum||sz[sum]>1)
        ans--;
    printf("%d\n",ans);

    return 0;
}
