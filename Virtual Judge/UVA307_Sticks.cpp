#include<cstdio>
#include<cstring>
#include<functional>
#include<algorithm>
using namespace std;
const int MAXN=105;

int n,A[MAXN],len,cnt;
bool used[MAXN];

bool dfs(int id,int r,int s)
{
    if(id>cnt)
        return true;
    int last=-1;
    for(int i=r;i<=n;i++)
        if(!used[i])
        {
            if(s+A[i]<len&&A[i]!=last)
            {
                used[i]=true;
                if(dfs(id,i+1,s+A[i]))
                    return true;
                used[i]=false;
                last=A[i];
            }
            else if(s+A[i]==len)
            {
                used[i]=true;
                if(dfs(id+1,1,0))
                    return true;
                used[i]=false;
                return false;
            }
            if(s==0)
                return false;
        }
    return false;
}

int main()
{
    //freopen("data.txt","r",stdin);
    for(;;)
    {
        scanf("%d",&n);
        if(n==0)
            break;
        int sum=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&A[i]);
            sum+=A[i];
        }
        sort(A+1,A+n+1,greater<int>());
        memset(used,0,sizeof used);
        for(len=A[1];len<=sum;len++)
            if(sum%len==0)
            {
                cnt=sum/len;
                if(dfs(1,1,0))
                {
                    printf("%d\n",len);
                    break;
                }
            }
    }
    return 0;
}
