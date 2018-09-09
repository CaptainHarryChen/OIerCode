#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=500005;

int N,X;

int main()
{
    scanf("%d%d",&N,&X);
    int now=0,L=0,R=0;
    bool flag=true;
    for(int i=1;i<=N;i++)
    {
        int x,a,b;
        scanf("%d%d%d",&x,&a,&b);
        R+=x-now;
        now=x;
        int l=(x+a)/2+1,r=x-(x-b)/2-1;
        if(a<-x)l=-0x7FFFFFFF;
        if(b>x)r=0x7FFFFFFF;
        if(R<l||r<L||l>r)
        {
            //printf("[%d]",i);
            flag=false;
            puts("NIE");
            break;
        }
        L=max(L,l);
        R=min(R,r);
    }
    if(flag)
        printf("%d\n",L);
    return 0;
}
