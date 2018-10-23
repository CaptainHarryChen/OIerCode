#include<cstdio>
#include<cstring>
const int MAXN=1000005,MOD=1000000007;

int n;
char s[MAXN];
int fail[MAXN],dep[MAXN],fail2[MAXN];

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",s+1);
        n=strlen(s+1);
        fail[0]=-1;
        for(int i=1;i<=n;i++)
        {
            int u=fail[i-1];
            while(u!=-1&&s[u+1]!=s[i])
                u=fail[u];
            fail2[i]=fail[i]=u+1;
            dep[i]=dep[u+1]+1;
        }
        int ans=1;
        for(int i=1,j=0;i<=n;i++)
        {
            while(j!=-1&&s[j+1]!=s[i])
                j=fail[j];
            j++;
            while(j!=-1&&j>i/2)
                j=fail[j];
            if(j!=-1)
                ans=1LL*ans*(dep[j]+1)%MOD;
        }
        printf("%d\n",ans);
    }

    return 0;
}
