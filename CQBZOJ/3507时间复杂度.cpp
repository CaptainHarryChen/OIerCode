#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=105;

int stk[MAXN],comp[MAXN],tp;
bool useless[MAXN];
bool used[30];

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        tp=0;
        memset(stk,0,sizeof stk);
        memset(comp,0,sizeof comp);
        memset(useless,0,sizeof useless);
        memset(used,0,sizeof used);
        int n,ans=0,chk;
        bool flag=true;
        char str[10],a[10],b[10],c[10];
        scanf("%d%s",&n,str);
        if(strcmp(str,"O(1)")==0)
            chk=0;
        else
            sscanf(str+4,"%d",&chk);

        int O=0;
        tp=0;
        int nouse=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%s",str);
            if(str[0]=='F')
            {
                scanf("%s %s %s",c,a,b);
                if(!flag)
                    continue;
                if(used[c[0]-'a'])
                {
                    flag=false;
                    continue;
                }
                stk[++tp]=c[0]-'a';
                used[c[0]-'a']=true;
                if(a[0]=='n'&&b[0]=='n')
                    comp[tp]=0,useless[tp]=false;
                else if(a[0]=='n')
                    comp[tp]=0,useless[tp]=true,nouse++;
                else if(b[0]=='n')
                {
                    comp[tp]=nouse?0:1;
                    useless[tp]=false;
                    O+=comp[tp];
                    ans=max(ans,O);
                }
                else
                {
                    int x,y;
                    sscanf(a,"%d",&x);
                    sscanf(b,"%d",&y);
                    if(x>y)
                        comp[tp]=0,useless[tp]=true,nouse++;
                    else
                        comp[tp]=0,useless[tp]=false;
                }
            }
            else
            {
                if(!flag)
                    continue;
                if(tp==0)
                {
                    flag=false;
                    continue;
                }
                used[stk[tp]]=false;
                nouse-=useless[tp];
                O-=comp[tp];
                tp--;
            }
        }
        if(tp!=0)
            flag=false;

        if(!flag)
            puts("ERR");
        else if(ans==chk)
            puts("Yes");
        else
            puts("No");
    }

    return 0;
}
