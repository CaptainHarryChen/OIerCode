#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
char a[10005][50],b[10005][50];
int main()
{
    int n,taila=0,tailb=0,heada=0,headb=0;
    while(1)
    {
        scanf("%s",a[taila++]);
		char c=getchar();
        if(c=='\r'||c=='\n')break;
    }
    n=0;
    while(1)
    {
        scanf("%s",b[tailb++]);
		char c=getchar();
        if(c=='\r'||c=='\n')break;
    }
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        printf("%s %s\n",a[heada],b[headb]);
        strcpy(a[taila++],a[heada++]);
        strcpy(b[tailb++],b[headb++]);
    }
    return 0;
}
