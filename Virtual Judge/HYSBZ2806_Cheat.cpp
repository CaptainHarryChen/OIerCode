#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1100005;

namespace SAM
{
    struct Node
    {
        Node *son[2],*fail;
        int len;
    }nodes[MAXN*2],*rt=nodes,*last=rt,*ndit=nodes+1;

    void Extend(int c)
    {
        Node *p=last,*np=ndit++;
        np->len=last->len+1;
        for(;p&&p->son[c]==NULL;p=p->fail)
            p->son[c]=np;
        if(p==NULL)
            np->fail=rt;
        else
        {
            Node *q=p->son[c];
            if(q->len==p->len+1)
                np->fail=q;
            else
            {
                Node *nq=ndit++;
                memcpy(nq,q,sizeof(Node));
                q->fail=np->fail=nq;
                nq->len=p->len+1;
                for(;p&&p->son[c]==q;p=p->fail)
                    p->son[c]=nq;
            }
        }
        last=np;
    }
    void Insert(char *s)
    {
        last=rt;
        for(int i=1;s[i];i++)
            Extend(s[i]-'0');
    }
    void Match(char *s,int res[])
    {
        Node *u=rt;
        int l=0;
        for(int i=1;s[i];i++)
        {
            while(u!=rt&&u->son[s[i]-'0']==NULL)
                u=u->fail,l=u->len;
            if(u->son[s[i]-'0'])
                u=u->son[s[i]-'0'],l++;
            res[i]=l;
        }
    }
}

int N,M;
char s[MAXN];
int len[MAXN];
int dp[MAXN];

int DP(int L0,int n)
{
    static int q[MAXN],hd,tl;
    for(int i=0;i<=L0-1;i++)
        dp[i]=0;
    hd=1;tl=0;
    for(int i=L0;i<=n;i++)
    {
        while(hd<=tl&&dp[q[tl]]-q[tl]<=dp[i-L0]-(i-L0))
            tl--;
        q[++tl]=i-L0;
        while(hd<=tl&&q[hd]<i-len[i])
            hd++;
        dp[i]=max(dp[i-1],hd<=tl?dp[q[hd]]-q[hd]+i:0);
    }
    return dp[n];
}
int Solve(int n)
{
    int L=1,R=n,res=0;
    while(L<=R)
    {
        int mid=(L+R)/2;
        if(DP(mid,n)*10>=n*9)
            res=mid,L=mid+1;
        else
            R=mid-1;
    }
    return res;
}

int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<=M;i++)
    {
        scanf("%s",s+1);
        SAM::Insert(s);
    }
    while(N--)
    {
        scanf("%s",s+1);
        SAM::Match(s,len);
        printf("%d\n",Solve(strlen(s+1)));
    }
    return 0;
}
