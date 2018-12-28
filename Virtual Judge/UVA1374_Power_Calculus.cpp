#include<cstdio>
#include<cstring>
const int MAXN=1005;

int A[MAXN],cnt;
bool have[MAXN*10];

bool dfs(int step,int n)
{
    if(step==0)
    {
        if(have[n])
            return true;
        return false;
    }
    int mx=0;
    for(int i=1;i<=cnt;i++)
        mx=A[i]<mx?mx:A[i];
    if(mx*(1<<step)<n)
        return false;
    for(int i=cnt;i>=cnt;i--)
        for(int j=i;j>0;j--)
        {
            int x=A[i]+A[j];
            if(!have[x]&&x<=n*2)
            {
                A[++cnt]=x;
                have[x]=true;
                if(dfs(step-1,n))
                    return true;
                have[x]=false;
                cnt--;
            }
            if(i!=j)
            {
                x=A[i]>A[j]?A[i]-A[j]:A[j]-A[i];
                if(!have[x])
                {
                    A[++cnt]=x;
                    have[x]=true;
                    if(dfs(step-1,n))
                        return true;
                    have[x]=false;
                    cnt--;
                }
            }
        }
    return false;
}

int main()
{
    for(;;)
    {
        int n;
        scanf("%d",&n);
        if(n==0)
            break;
        for(int i=0;;i++)
        {
            A[cnt=1]=1;
            memset(have,0,sizeof have);
            have[1]=true;
            if(dfs(i,n))
            {
                printf("%d\n",i);
                break;
            }
        }
    }
    return 0;
}
