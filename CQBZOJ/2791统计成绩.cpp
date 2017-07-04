#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int putname[1005];
double score[1005][1005];
char name[1005][100];
int f(int n,int m,int r)
{
    int k=0;
    double s=-99999;
    if(r==2)
    {
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                if(score[i][j]>s)
                    s=score[i][j];
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                if(score[i][j]==s)
                {putname[k++]=i;break;}
        return k;
    }
    double sum[1005]={0};
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            sum[i]+=score[i][j];
    if(r==1)
    {
        s=99999999;
        for(int i=0;i<n;i++)
            if(s>sum[i])
                s=sum[i];
    }
    else
    {
        s=-99999;
        for(int i=0;i<n;i++)
            if(s<sum[i])
                s=sum[i];
    }
    for(int i=0;i<n;i++)
        if(sum[i]==s)
            putname[k++]=i;
    return k;
}
int main()
{
    int t,n,m,r;
    scanf("%d",&t);
    for(int iii=1;iii<=t;iii++)
    {
        scanf("%d%d%d",&n,&m,&r);
        for(int i=0;i<n;i++)
        {
            scanf("%s",name[i]);
            for(int j=0;j<m;j++)
                scanf("%lf",&score[i][j]);
        }
        int a=f(n,m,r);
        for(int i=0;i<a;i++)
            printf("%s\n",name[putname[i]]);
        memset(putname,0,sizeof(putname));
        memset(name,0,sizeof(name));
        memset(score,0,sizeof(score));
    }
    return 0;
}
