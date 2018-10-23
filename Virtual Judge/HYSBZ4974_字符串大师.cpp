#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005;

int n;
int fail[MAXN];
char s[MAXN];
bool vis[26];

int main()
{
    scanf("%d",&n);
    fail[0]=-1;
    for(int i=1,x;i<=n;i++)
    {
        scanf("%d",&x);
        fail[i]=i-x;
    }
    for(int i=1;i<=n;i++)
        if(fail[i])
            s[i]=s[fail[i]];
        else
        {
            fill(vis,vis+26,0);
            int u=fail[i-1];
            while(u!=-1)
            {
                vis[s[u+1]-'a']=1;
                u=fail[u];
            }
            s[i]='a';
            while(vis[s[i]-'a'])
                s[i]++;
        }
    puts(s+1);

    return 0;
}
