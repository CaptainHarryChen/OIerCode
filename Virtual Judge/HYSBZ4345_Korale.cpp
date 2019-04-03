#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=1000005;

int N,K,cnt;
priority_queue<pair<long long,int>,vector<pair<long long,int> >,greater<pair<long long,int> > > Q;
int A[MAXN],B[MAXN];
long long ans[MAXN];

int mn[MAXN*4];
void Build(int L=1,int R=N,int u=1)
{
    if(L==R)
    {
        mn[u]=B[L];
        return;
    }
    int mid=(L+R)/2;
    Build(L,mid,u*2);
    Build(mid+1,R,u*2+1);
    mn[u]=min(mn[u*2],mn[u*2+1]);
}
int Query(int pos,long long val,int L=1,int R=N,int u=1)
{
    if(pos<=L&&mn[u]>val)
        return -1;
    if(L==R)
        return L;
    int mid=(L+R)/2,res=-1;
    if(pos<=mid)
    {
        res=Query(pos,val,L,mid,u*2);
        if(res!=-1)
            return res;
    }
    return Query(pos,val,mid+1,R,u*2+1);
}

int stk[MAXN],tp;
bool dfs(long long rest,int last=0)
{
    if(rest==0)
    {
        cnt--;
        if(cnt==0)
        {
            for(int i=1;i<=tp;i++)
                printf("%d%c",stk[i]," \n"[i==tp]);
            return true;
        }
        return false;
    }
    for(int i=last+1;i<=N;i++)
    {
        i=Query(i,rest);
        if(i!=-1)
        {
            stk[++tp]=i;
            if(dfs(rest-B[i],i))
                return true;
            tp--;
        }
        else
            break;
    }
    return false;
}

int main()
{
    scanf("%d%d",&N,&K);
    K--;
    if(K==0)
    {
        puts("0");
        return 0;
    }
    for(int i=1;i<=N;i++)
    {
        scanf("%d",&A[i]);
        B[i]=A[i];
    }
    sort(A+1,A+N+1);
    Q.push(make_pair(1LL*A[1],1));
    for(int i=1;i<=K;i++)
    {
        pair<long long,int> u=Q.top();
        Q.pop();
        ans[i]=u.first;
        if(i==K)break;
        if(u.second+1<=N)
        {
            u.second++;
            u.first+=A[u.second];
            Q.push(u);
            u.first-=A[u.second-1];
            Q.push(u);
        }
    }
    for(int i=K;i>0&&ans[i]==ans[K];i--)
        cnt++;
    printf("%lld\n",ans[K]);
    Build();
    dfs(ans[K]);

    return 0;
}
