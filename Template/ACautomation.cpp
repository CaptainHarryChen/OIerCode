//HDU2222 Keywords Search
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=1000005;

namespace ACautomation
{
    struct Node
    {
        Node *son[26],*fail;
        bool vis;
        int cnt;
    }nodes[MAXN],*it=nodes+1,*root=nodes;
    void Init()
    {
        it=nodes+1;
        root=nodes;
        memset(nodes,0,sizeof nodes);
    }
    void Insert(char str[])
    {
        Node *u=root;
        for(int i=0;str[i];i++)
        {
            int c=str[i]-'a';
            if(u->son[c]==NULL)
                u->son[c]=it++;
            u=u->son[c];
        }
        u->cnt++;
    }
    void Build()
    {
        static queue<Node*> Q;
        for(int i=0;i<26;i++)
            if(root->son[i])
            {
                Q.push(root->son[i]);
                root->son[i]->fail=root;
            }
        while(!Q.empty())
        {
            Node *u=Q.front();
            Q.pop();
            for(int i=0;i<26;i++)
                if(u->son[i])
                {
                    Node *v=u->son[i],*f=u->fail;
                    while(f&&f->son[i]==NULL)
                        f=f->fail;
                    if(f)
                        v->fail=f->son[i];
                    else
                        v->fail=root;
                    Q.push(v);
                }
        }
    }
    int Match(char str[])
    {
        int res=0;
        Node *u=root;
        for(int i=0;str[i];i++)
        {
            int c=str[i]-'a';
            while(u!=root&&u->son[c]==NULL)
                u=u->fail;
            if(u->son[c])
            {
                u=u->son[c];
                for(Node *v=u;v&&!v->vis;v=v->fail)
                {
                    res+=v->cnt;
                    v->vis=true;
                }
            }
        }
        return res;
    }
}

char s[MAXN];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        ACautomation::Init();
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%s",s);
            ACautomation::Insert(s);
        }
        ACautomation::Build();
        scanf("%s",s);
        printf("%d\n",ACautomation::Match(s));
    }
    return 0;
}
