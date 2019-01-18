#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=2019;

namespace SAM
{
    struct Node
    {
        Node *son[26],*fail;
        int len;
    }nodes[MAXN*2],*rt=nodes,*last=nodes,*ndit=nodes+1;

    int ID(Node *u)
    {return u-nodes+1;}
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
                nq->len=p->len+1;
                np->fail=q->fail=nq;
                for(;p&&p->son[c]==q;p=p->fail)
                    p->son[c]=nq;
            }
        }
        last=np;
    }

    int M;
    Node *pos[MAXN*2];
    int mn[MAXN*2];

    void Insert(char *s)
    {
        int n=0;
        for(n=0;s[n];n++)
            Extend(s[n]-'a');
        static int cnt[MAXN*2];
        for(int i=0;i<=n;i++)cnt[i]=0;
        M=ndit-nodes;
        for(Node *u=nodes;u<ndit;u++)
            cnt[u->len]++;
        for(int i=1;i<=n;i++)
            cnt[i]+=cnt[i-1];
        for(Node *u=nodes;u<ndit;u++)
            pos[cnt[u->len]--]=u;
    }
    void Match(char *s)
    {
        static int mat[MAXN*2];
        int n=strlen(s);
        for(int i=1;i<=M;i++)mat[i]=0;
        Node *u=rt;
        int now=0;
        for(int i=0;i<n;i++)
        {
            while(u!=rt&&u->son[s[i]-'a']==NULL)
                u=u->fail,now=u->len;
            if(u->son[s[i]-'a'])
                u=u->son[s[i]-'a'],now++;
            mat[ID(u)]=max(mat[ID(u)],now);
        }
        for(int i=1;i<=M;i++)
        {
            if(pos[i]->fail)
                mat[ID(pos[i])]=max(mat[ID(pos[i])],mat[ID(pos[i]->fail)]);
            mn[ID(pos[i])]=min(mn[ID(pos[i])],mat[ID(pos[i])]);
        }
    }
}

int n;
char s[MAXN];

int main()
{
    scanf("%d%s",&n,s);
    if(n==1)
    {
        printf("%d\n",strlen(s));
        return 0;
    }
    SAM::Insert(s);
    memset(SAM::mn,0x3F,sizeof SAM::mn);
    for(int i=2;i<=n;i++)
    {
        scanf("%s",s);
        SAM::Match(s);
    }
    int ans=0;
    for(int i=1;i<=SAM::M;i++)
        ans=max(ans,SAM::mn[i]);
    printf("%d\n",ans);

    return 0;
}
