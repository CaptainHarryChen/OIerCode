#include<cstdio>
const int MAXN=1005;

long long gcd(long long a,long long b)
{return b==0?a:gcd(b,a%b);}

int ans[MAXN],tmp[MAXN],c;

bool dfs(int step,int a,int b)
{
    if(step==0)
    {
        if(b==0)
        {
            bool flag=ans[c]==0||tmp[1]<ans[c];
            if(tmp[1]==ans[c])
            {
                for(int i=1;i<=c;i++)
                {
                    if(tmp[i]<ans[c-i+1])
                    {
                        flag=true;
                        break;
                    }
                    if(tmp[i]>ans[c-i+1])
                        break;
                }
            }
            if(flag)
                for(int i=1;i<=c;i++)
                    ans[c-i+1]=tmp[i];
            return true;
        }
        return false;
    }
    long long i=(a+b-1)/b;
    if(i<=tmp[step+1])
        i=tmp[step+1]+1;
    bool success=false;
    for(;;i++)
    {
        if(1LL*step*a<1LL*b*i)
            break;
        long long x=1LL*a*i;
        long long y=1LL*b*i-1LL*a;
        long long d=gcd(x,y);
        x/=d;y/=d;
        tmp[step]=i;
        if(dfs(step-1,x,y))
            success=true;
    }
    return success;
}

int main()
{
    int a,b;
    scanf("%d%d",&b,&a);
    for(int i=1;;i++)
    {
        c=i;
        if(dfs(i,a,b))
        {
            for(int j=1;j<=c;j++)
                printf("%d%c",ans[j]," \n"[j==c]);
            return 0;
        }
    }

    return 0;
}
