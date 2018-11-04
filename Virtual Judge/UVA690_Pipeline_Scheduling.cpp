#include<cstdio>
#include<cstring>

int n,ans;
char sc[5][22];
long long ti[5],st[5];

int mov[22],mc;

void dfs(int step,int delta=0)
{
    if(delta+(10-step)*mov[1]+n>=ans)
        return;
    if(step>=10)
    {
        ans=delta+n;
        return;
    }
    long long bkup[5];
    memcpy(bkup,st,sizeof st);
    for(int i=1;i<=mc;i++)
    {
        memcpy(st,bkup,sizeof st);
        int d=mov[i];
        bool flag=true;
        for(int j=0;j<5;j++)
            if((st[j]>>d)&ti[j])
            {
                flag=false;
                break;
            }
        if(!flag)
            continue;
        for(int j=0;j<5;j++)
            st[j]=((st[j]>>d)^ti[j]);
        dfs(step+1,d+delta);
    }
}

int main()
{
    for(;;)
    {
        scanf("%d",&n);
        if(n==0)
            break;
        for(int i=0;i<5;i++)
        {
            scanf("%s",sc[i]);
            ti[i]=0;
            for(int j=0;j<n;j++)
                if(sc[i][j]=='X')
                    ti[i]|=1<<j;
            st[i]=ti[i];
        }
        mc=0;
        for(int i=1;i<n;i++)
        {
            bool flag=true;
            for(int j=0;j<5;j++)
                if(ti[j]&(ti[j]>>i))
                {
                    flag=false;
                    break;
                }
            if(flag)
                mov[++mc]=i;
        }
        mov[++mc]=n;
        ans=0x3F3F3F3F;
        dfs(1);
        printf("%d\n",ans);
    }
    return 0;
}
