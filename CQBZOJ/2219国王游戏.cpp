#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=1005;

//#define BigInteger long long

#ifndef BigInteger
class BigInteger
{
    static const int MAXLEN=1000;
    static const int BASE=100000000;

    int len;
    int A[MAXN];

public:
    BigInteger()
    {len=1;A[0]=0;}
    BigInteger(int x)
    {*this=x;}
    int & operator [] (int i)
    {return A[i];}
    void operator = (int x)
    {
        len=0;
        while(x)
        {
            A[len]=x%BASE;
            x/=BASE;
            len++;
        }
    }
    BigInteger operator * (int x)
    {
        BigInteger ret(1);
        int flag=0,i;
        for(i=0;i<len||flag;i++)
        {
            long long res=1LL*x*A[i]+flag;
            ret[i]=res%BASE;
            flag=res/BASE;
        }
        ret.len=i;
        return ret;
    }
    BigInteger operator / (int x)
    {
        BigInteger ret(0);
        long long tmp=0;
        for(int i=len-1;i>=0;i--)
        {
            tmp=tmp*BASE+A[i];
            ret[i]=tmp/x;
            tmp%=x;
        }
        ret.len=len;
        while(ret.len>0&&ret[ret.len-1]==0)
            ret.len--;
        if(ret.len==0)
            ret.len=1;
        return ret;
    }
    bool operator < (const BigInteger &B)const
    {
        if(len<B.len)
            return true;
        if(len>B.len)
            return false;
        for(int i=len-1;i>=0;i--)
        {
            if(A[i]<B.A[i])
                return true;
            if(A[i]>B.A[i])
                return false;
        }
        return false;
    }
    void print()
    {
        for(int i=len-1;i>=0;i--)
        {
            if(i==len-1)
                printf("%d",A[i]);
            else
                printf("%08d",A[i]);
        }
    }
};
#endif // BigInteger

int n;
pair<int,int> A[MAXN];
bool greedy(const pair<int,int> &a,const pair<int,int> &b)
{return a.first*a.second<b.first*b.second;}

BigInteger P,ans;

int main()
{
    scanf("%d",&n);
    for(int i=0;i<=n;i++)
        scanf("%d%d",&A[i].first,&A[i].second);
    sort(A+1,A+n+1,greedy);

    P=A[0].first;
    ans=0;
    for(int i=1;i<=n;i++)
    {
        ans=max(ans,P/A[i].second);
        P=P*A[i].first;
    }

    #ifdef BigInteger
        printf("%I64d\n",ans);
    #else
        ans.print();
        puts("");
    #endif // BigInteger

    return 0;
}
