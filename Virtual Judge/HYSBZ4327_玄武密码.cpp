#include<cstdio>
#include<cstring>
const int MAXN=10000005,MAXM=100005,MAXL=105,MAXCHAR=4;

int ID(char c)
{
    switch(c)
    {
        case 'N':return 0;
        case 'S':return 1;
        case 'W':return 2;
        case 'E':return 3;
    }
    return -1;
}

struct Node
{
    Node *son[MAXCHAR],*fail,*fa;
    int dep;
    bool vis;
};

struct ACautomation
{
    Node nodes[MAXN],*root,*nodes_it;

    Node *NewNode()
    {
        memset(nodes_it,0,sizeof(Node));
        return nodes_it++;
    }
    void Clear()
    {
        nodes_it=nodes;
        root=NewNode();
    }
    Node* Insert(const char *s)
    {
        Node *u=root;
        for(int i=0;s[i];i++)
        {
            Node *&v=u->son[ID(s[i])];
            if(v==NULL)
            {
                v=NewNode();
                //printf("(%d %d %d)\n",u-nodes,v-nodes,ID(s[i]));
                v->dep=u->dep+1;
                v->fa=u;
            }
            u=v;
        }
        return u;
    }
    void BuildFail()
    {
        static Node* Q[MAXN];
        static int l,r;
        l=1,r=1;Q[1]=root;
        while(l<=r)
        {
            Node *u=Q[l++];
            for(int c=0;c<MAXCHAR;c++)
                if(u->son[c])
                {
                    Node *v=u->son[c],*f=u->fail;
                    while(f&&f->son[c]==NULL)
                        f=f->fail;
                    if(f)
                        v->fail=f->son[c];
                    else
                        v->fail=root;
                    //printf("[%d %d]\n",v-nodes,v->fail-nodes);
                    Q[++r]=v;
                }
        }
    }
    void Mark(const char *S)
    {
        Node *u=root;
        for(int i=0;S[i];i++)
        {
            while(u!=root&&!u->son[ID(S[i])])
                u=u->fail;
            if(u->son[ID(S[i])])
            {
                u=u->son[ID(S[i])];
                for(Node *v=u;v&&!v->vis;v=v->fail)
                    v->vis=true;//printf("{%d}\n",v-nodes);
            }
        }
    }
};

int N,M;
char S[MAXN],str[MAXL];
Node *ed[MAXM];
ACautomation AC;

int main()
{
    scanf("%d%d%s",&N,&M,S);
    AC.Clear();
    for(int i=1;i<=M;i++)
    {
        scanf("%s",str);
        ed[i]=AC.Insert(str);
    }
    AC.BuildFail();
    AC.Mark(S);

    for(int i=1;i<=M;i++)
    {
        Node *u=ed[i];
        while(u!=AC.root&&!u->vis)
            u=u->fa;
        printf("%d\n",u->dep);
    }

    return 0;
}
