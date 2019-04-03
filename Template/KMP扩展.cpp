//CQBZOJ2293
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1000005;

int n,m;
char s1[MAXN],s2[MAXN];
int nxt[MAXN],ext[MAXN];

int main()
{
    scanf("%s%s",s1+1,s2+1);
    n=strlen(s1+1);
    m=strlen(s2+1);
    int id=0,mx=0;
    nxt[1]=m;
    for(int i=2;i<=m;i++)
    {
        if(i<=mx)
            nxt[i]=min(mx-i+1,nxt[i-id+1]);
        else
            nxt[i]=0;
        while(i+nxt[i]<=m&&s2[i+nxt[i]]==s2[1+nxt[i]])
            nxt[i]++;
        if(nxt[i]&&mx<i+nxt[i]-1)
            mx=i+nxt[i]-1,id=i;
    }
    id=0,mx=0;
    for(int i=1;i<=n;i++)
    {
        if(i<=mx)
            ext[i]=min(mx-i+1,nxt[i-id+1]);
        else
            ext[i]=0;
        while(i+ext[i]<=n&&1+ext[i]<=m&&s1[i+ext[i]]==s2[1+ext[i]])
            ext[i]++;
        if(ext[i]&&mx<i+ext[i]-1)
            mx=i+ext[i]-1,id=i;
    }
    for(int i=1;i<n;i++)
        printf("%d ",ext[i]);
    printf("%d",ext[n]);
    return 0;
}
