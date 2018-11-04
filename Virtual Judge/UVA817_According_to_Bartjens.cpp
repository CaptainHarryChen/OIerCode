#include<cstdio>
#include<cstring>
const int MAXN=12;

int n;
char str[MAXN*2];
int stk[MAXN*2],tp;
long long stk2[MAXN*2],tp2;
bool flag;

bool check()
{
    stk2[tp2=1]=stk[1];
    long long res=0;
    for(int i=2;i<=tp;i+=2)
    {
        if(stk[i]==-1)
            stk2[tp2]*=stk[i+1];
        else if(stk[i]==-2)
            stk2[++tp2]=-2,stk2[++tp2]=stk[i+1];
        else if(stk[i]==-3)
            stk2[++tp2]=-3,stk2[++tp2]=stk[i+1];
    }
    res=stk2[1];
    for(int i=2;i<=tp2;i+=2)
    {
        if(stk2[i]==-2)
            res+=stk2[i+1];
        if(stk2[i]==-3)
            res-=stk2[i+1];
    }
    return res==2000;
}
void print()
{
    printf("  ");
    for(int i=1;i<=tp;i++)
    {
        if(stk[i]==-1)
            putchar('*');
        else if(stk[i]==-2)
            putchar('+');
        else if(stk[i]==-3)
            putchar('-');
        else
            printf("%d",stk[i]);
    }
    puts("=");
}

void dfs(int p,int num=0,bool zero=false)
{
    if(num>=100000)
        return;
    if(p>=n)
    {
        stk[++tp]=num;
        if(check())
        {
            print();
            flag=true;
        }
        tp--;
        return;
    }
    stk[++tp]=num;
    stk[++tp]=-1;
    dfs(p+1,str[p]-'0',str[p]=='0');
    stk[tp]=-2;
    dfs(p+1,str[p]-'0',str[p]=='0');
    stk[tp]=-3;
    dfs(p+1,str[p]-'0',str[p]=='0');
    tp--;
    tp--;
    if(!zero)
        dfs(p+1,num*10+str[p]-'0',false);
}

int main()
{
    int test=0;
    while(scanf("%s",str)!=EOF)
    {
        test++;
        n=strlen(str);
        if(n==1)
            break;
        n--;
        flag=false;
        printf("Problem %d\n",test);
        if(strcmp(str,"2000=")!=0)
            dfs(1,str[0]-'0',str[0]=='0');
        if(!flag)
            puts("  IMPOSSIBLE");
    }
    return 0;
}
