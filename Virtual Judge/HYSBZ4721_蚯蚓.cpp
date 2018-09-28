#include<cstdio>
#include<cstring>
#include<functional>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXM=8000005;

template<class T> void Read(T &n)
{
    char c;
    while(c=getchar(),c!=EOF)
    {
        if(c>='0'&&c<='9')
        {
            n=c-'0';
            while(c=getchar(),c>='0'&&c<='9')
                n=n*10+c-'0';
            return;
        }
    }
}
template<class T> void Print(T n)
{
    static char str[20];
    static int len;
    if(n==0)
    {
        putchar('0');
        return;
    }
    len=0;
    while(n)
        str[len++]=n%10+'0',n/=10;
    len--;
    while(len>=0)
        putchar(str[len--]);
}

int n,m,q,u,v,t;
long long A[3][MAXM],hd[3],tl[3];

int main()
{
    Read(n);Read(m);Read(q);Read(u);Read(v);Read(t);
    for(int i=1;i<=n;i++)
        Read(A[0][i]);
    sort(A[0]+1,A[0]+n+1,greater<long long>());
    tl[0]=n;
    hd[0]=hd[1]=hd[2]=1;
    tl[1]=tl[2]=0;
    for(int i=1,j=1%t;i<=m;i++)
    {
        int id;
        long long mx=-0x7FFFFFFFFFFFFFFFLL;
        for(int j=0;j<3;j++)
            if(hd[j]<=tl[j])
            {
                if(A[j][hd[j]]>mx)
                    mx=A[j][hd[j]],id=j;
            }
        hd[id]++;
        long long len=mx+1LL*(i-1)*q;
        long long a=len*u/v,b=len-a;
        if(a<b)
            swap(a,b);
        A[1][++tl[1]]=a-1LL*i*q;
        A[2][++tl[2]]=b-1LL*i*q;
        if(j==0)
            Print(len),putchar(' ');
        j=j==t-1?0:j+1;
    }
    putchar('\n');
    for(int j=1%t;hd[0]<=tl[0]||hd[1]<=tl[1]||hd[2]<=tl[2];j=j==t-1?0:j+1)
    {
        int id;
        long long mx=-0x7FFFFFFFFFFFFFFFLL;
        for(int j=0;j<3;j++)
            if(hd[j]<=tl[j])
            {
                if(A[j][hd[j]]>mx)
                    mx=A[j][hd[j]],id=j;
            }
        hd[id]++;
        if(j==0)
            Print(mx+1LL*m*q),putchar(' ');
    }
    putchar('\n');

    return 0;
}
