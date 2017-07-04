#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n;
char s[105];
int d[105][105];
bool match(char ch1,char ch2)
{
    if((ch1=='['&&ch2==']')||(ch1=='('&&ch2==')'))
        return true;
    return false;
}
void dp()
{
    for(int i=0;i<n;i++)
    {
        d[i+1][i]=0;
        d[i][i]=1;
    }
    for(int i=n-2;i>=0;i--)
    {
        for(int j=i+1;j<n;j++)
        {
            d[i][j]=n;
            if(match(s[i],s[j])) d[i][j]=min(d[i][j],d[i+1][j-1]);
            for(int k=i;k<j;k++)
                d[i][j]=min(d[i][j],d[i][k]+d[k+1][j]);
        }
    }
}
void print(int i,int j)
{
    if(i > j) return;
    if(i == j)
    {
        if(s[i]=='('||s[j]==')') printf("()");
        else printf("[]");
        return;
    }
    int ans = d[i][j];
    if(match(s[i],s[j])&&ans==d[i+1][j-1])
    {
        printf("%c",s[i]);
        print(i+1,j-1);
        printf("%c",s[j]);
        return;
    }
    for(int k=i;k<j;k++)
    {
        if(ans==d[i][k]+d[k+1][j])
        {
            print(i,k);
            print(k+1,j);
            return;
        }
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    getchar();
    for(int kase=1;kase<=t;kase++)
    {
        gets(s);
        gets(s);
        n = strlen(s);
        if(n==0){
            printf("\n");
            if(kase!=t) printf("\n");
            continue;
        }
        dp();
        print(0,n-1);
        printf("\n");
        if(kase!=t) printf("\n");
    }
    return 0;
}