#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;
const int MAXN=300005;

int n,A[MAXN],B[MAXN];

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&A[i]);
        B[i]=A[i];
    }
    sort(B+1,B+n+1);
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        A[i]=lower_bound(B+1,B+n+1,A[i])-B;
        ans+=(A[i]&1)!=(i&1);
    }
    ans/=2;
    printf("%d\n",ans);

    return 0;
}
