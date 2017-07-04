#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
char stack[10000][7];
int p=-1;
int main()
{
    int m;
    cin>>m;
    char e[10];
    for(int i=0;i<m;i++)
    {
        scanf("%s",e);
        if(strcmp(e,"out")==0)
        {
            for(int j=0;stack[p][j]!=0;j++)
                stack[p][j]=0;
            p--;
        }
        else if(strcmp(e,"in")==0)
            scanf("%s",stack[++p]);
        else
        {
			if(stack[0][0]==0)continue;
            printf("%s",stack[0]);
            for(int j=1;j<=p;j++)
                printf(" %s",stack[j]);
            printf("\n");
        }
    }
    return 0;
}
