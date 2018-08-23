#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1005;

int n;
int A[MAXN];

int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=1;i<=n;i++)
            scanf("%d",&A[i]);
        sort(A+1,A+n+1);
        bool flag=false;
        for(int i=n;i>=3;i--)
            if(A[i-2]+A[i-1]>A[i])
            {
                printf("%d\n",A[i]+A[i-1]+A[i-2]);
                flag=true;
                break;
            }
        if(!flag)
            puts("-1");
    }
    
    return 0;
}
