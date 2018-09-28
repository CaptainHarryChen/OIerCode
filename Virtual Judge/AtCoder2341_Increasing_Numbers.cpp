#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=500005;

int len;
char N[MAXN];
int cnt[15];

int main()
{
    scanf("%s",N);
    len=strlen(N);
    reverse(N,N+len);
    for(int i=0;i<len;i++)
    {
        N[i]-='0';
        cnt[N[i]]++;
    }
    int ans=0;
    int tmp=len;
    int num=-1,pos=-1;
    for(;;)
    {
        int i=len-1;
        if(N[i]==num)
            i=pos-1;
        else
            while(i>0&&N[i-1]>=N[i])
                i--;
        ans++;
        if(i==0||cnt[N[0]]==len)
            break;
        while(N[i]==N[i+1])
            i++;
        num=N[i],pos=i;
        for(int j=len-1;j>=i;j--)
            cnt[N[j]]--;
        len=i;
        N[len]=0;
        cnt[N[0]]--;
        N[0]++;
        cnt[N[0]]++;
        for(int j=0;N[j]==10;j++)
        {
            cnt[N[j]]--;cnt[N[j+1]]--;
            N[j]=0,N[j+1]++;
            cnt[N[j]]++;cnt[N[j+1]]++;
        }
        /*for(int j=len;j<tmp;j++)
            putchar(' ');
        for(int j=len-1;j>=0;j--)
            putchar(N[j]+'0');
        putchar('\n');*/
    }
    printf("%d\n",ans);

    return 0;
}
