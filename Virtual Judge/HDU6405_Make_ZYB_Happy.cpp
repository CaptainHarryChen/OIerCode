#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXL=300005,MAXCHAR=26,MAXN=10005,MOD=1000000007;

int PowMod(int a,int b)
{
    int ret=1;
    while(b)
    {
        if(b&1)
            ret=(1LL*a*ret)%MOD;
        a=(1LL*a*a)%MOD;
        b>>=1;
    }
    return ret;
}

class SAM
{
public:
    struct Node
    {
        int len,val,flag;
        Node *son[MAXCHAR],*fail;
    };
    static Node nodes[MAXL*2],*ncnt;
    static int ID(Node *p)
    {return p-nodes;}

    Node *root,*last;
    void Init()
    {
        root=ncnt++;
        last=root;
    }
    void Extend(int c)
    {
        Node *np=ncnt++,*p=last;
        np->val=1;
        np->len=last->len+1;
        for(;p&&p->son[c]==NULL;p=p->fail)
            p->son[c]=np;
        if(p==NULL)
            np->fail=root;
        else
        {
            Node *q=p->son[c];
            if(q->len==p->len+1)
                np->fail=q;
            else
            {
                Node *nq=ncnt++;
                *nq=*q;
                nq->len=p->len+1;
                nq->val=1;
                q->fail=np->fail=nq;
                for(;p&&p->son[c]==q;p=p->fail)
                    p->son[c]=nq;
            }
        }
        last=np;
    }
    void Insert(const string &s)
    {
        last=root;
        for(auto c:s)
            Extend(c-'a');
    }
    void AddVal(const string &s,int v)
    {
        static int id=0;
        id++;
        Node *u=root;
        for(auto c:s)
        {
            u=u->son[c-'a'];
            for(Node *t=u;t&&t->flag!=id;t=t->fail)
            {
                t->val=(1LL*t->val*v)%MOD;
                t->flag=id;
            }
        }
    }
};
SAM::Node SAM::nodes[MAXL*2],*SAM::ncnt=SAM::nodes;

int n,h[MAXN],ans[MAXL],base[MAXL];
string str[MAXN];
SAM S;

void Work(SAM::Node *u)
{
    u->flag=n+1;
    if(u->fail)
    {
        (ans[u->fail->len+1]+=u->val)%=MOD;
        ans[u->len+1]=(ans[u->len+1]-u->val+MOD)%MOD;
    }
    for(int i=0;i<MAXCHAR;i++)
        if(u->son[i]&&u->son[i]->flag!=n+1)
            Work(u->son[i]);
}

int main()
{
    S.Init();
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>str[i];
        S.Insert(str[i]);
    }
    for(int i=1;i<=n;i++)
    {
        cin>>h[i];
        S.AddVal(str[i],h[i]);
    }
    Work(S.root);
    for(int i=1;i<MAXL;i++)
        ans[i]=(ans[i-1]+ans[i])%MOD;
    for(int i=1;i<MAXL;i++)
        ans[i]=(ans[i-1]+ans[i])%MOD;
    base[0]=1;
    for(int i=1;i<MAXL;i++)
        base[i]=(1LL*base[i-1]*26)%MOD;
    for(int i=2;i<MAXL;i++)
        base[i]=(base[i]+base[i-1])%MOD;
    for(int i=1;i<MAXL;i++)
        ans[i]=(1LL*ans[i]*PowMod(base[i],MOD-2))%MOD;
    int Q;
    cin>>Q;
    while(Q--)
    {
        int k;
        cin>>k;
        cout<<ans[k]<<endl;
    }

    return 0;
}
