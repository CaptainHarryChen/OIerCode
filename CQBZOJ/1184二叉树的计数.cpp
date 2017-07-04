#include<cstdio>
#include<cstring>
using namespace std;
char s1[1000],s2[1000];
int cnt=1,n;
bool count(int l1,int r1,int l2,int r2)
{
    if(l1==r1)return 1;
    if(s1[l1]==s2[r2])
    {
        if(count(l1+1,r1,l2,r2-1))
            cnt*=2;
        return 1;
    }
    int x;
    for(x=l2;s2[x]!=s1[l1];x++);
    count(l1,l1+x-l2,l2,x);
    count(l1+x-l2+1,r1,x+1,r2);
    return 0;
}
int main()
{
    scanf("%s%s",s1,s2);
    n=strlen(s1);
    if(!count(0,n-1,0,n-1))
        cnt=0;
    printf("%d\n",cnt);
    return 0;
}