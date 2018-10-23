#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=1000005;

class BIT
{
    int val[MAXN];
public:
    void Clear()
    {memset(val,0,sizeof val);}
    BIT(){Clear();}

    void Add(int x,int v)
    {
        while(x<MAXN)
        {
            val[x]+=v;
            x+=x&(-x);
        }
    }
    int Query(int x)
    {
        int res=0;
        while(x)
        {
            res+=val[x];
            x-=x&(-x);
        }
        return res;
    }
};

BIT cnt;
int N,M;
int A[MAXN],B[MAXN],temp[MAXN];
int fail[MAXN];
int val[MAXN],valc;
vector<int> ans;

int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1,x;i<=N;i++)
    {
        scanf("%d",&x);
        A[x]=i;
    }

    cnt.Clear();
    for(int i=1;i<=N;i++)
    {
        temp[i]=cnt.Query(A[i]);
        cnt.Add(A[i],1);
    }

    for(int i=1;i<=M;i++)
    {
        scanf("%d",&B[i]);
        val[++valc]=B[i];
    }

    sort(val+1,val+valc+1);
    valc=unique(val+1,val+valc+1)-val-1;
    for(int i=1;i<=M;i++)
        B[i]=lower_bound(val+1,val+valc+1,B[i])-val;

    cnt.Clear();
    fail[0]=-1;
    for(int i=1,j=0;i<=N;i++)
    {
        j=fail[i-1];
        while(j!=-1&&cnt.Query(A[i])!=temp[j+1])
        {
            for(int k=i-j;k<i-fail[j];k++)
                cnt.Add(A[k],-1);
            j=fail[j];
        }
        fail[i]=j+1;
        if(fail[i]!=0)
            cnt.Add(A[i],1);
    }

    cnt.Clear();
    for(int i=1,j=0;i<=M;i++)
    {
        while((j!=-1&&cnt.Query(B[i])!=temp[j+1])||j==N)
        {
            for(int k=i-j;k<i-fail[j];k++)
                cnt.Add(B[k],-1);
            j=fail[j];
        }
        j++;
        if(j!=0)
            cnt.Add(B[i],1);
        if(j==N)
            ans.push_back(i-N+1);
    }
    printf("%u\n",ans.size());
    for(int i=0;i<(int)ans.size();i++)
        printf("%d%c",ans[i]," \n"[i==(int)ans.size()-1]);

    return 0;
}
