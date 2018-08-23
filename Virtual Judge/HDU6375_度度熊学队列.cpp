#include<cstdio>
#include<cstring>
#include<deque>
#include<algorithm>
using namespace std;
const int MAXN=150005,MAXQ=400005;

void read(int &x){
    char ch = getchar();x = 0;
    for (; ch < '0' || ch > '9'; ch = getchar());
    for (; ch >='0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
}

struct Node
{
    int val;
    Node *nxt,*pre;
};

class List
{
    static Node nodes[MAXQ],*ncnt;
    static Node* NewNode(int v)
    {
        ncnt->val=v;
        ncnt->nxt=ncnt->pre=NULL;
        return ncnt++;
    }
    
    Node *head,*tail;
    int sz;
    bool rev;
    
public:
    static void Clear(){ncnt=nodes;}
    List(){head=tail=NULL;sz=rev=0;}
    
    void clear(){head=tail=NULL;sz=rev=0;}
    int Size(){return sz;}
    void Reverse(){rev^=1;}
    void Push(Node *u,int dir)
    {
        if(sz==0)
        {
            head=tail=u;
            sz++;
            return;
        }
        dir^=rev;
        if(dir==0)
        {
            head->pre=u;
            u->nxt=head;
            head=u;
        }
        else
        {
            tail->nxt=u;
            u->pre=tail;
            tail=u;
        }
        sz++;
    }
    void Push(int val,int dir)
    {Node *u=NewNode(val);Push(u,dir);}
    void Pop(int dir)
    {
        if(sz==1)
        {
            head=tail=NULL;
            sz--;
            return;
        }
        dir^=rev;
        if(dir==0)
            head=head->nxt,head->pre=NULL;
        else
            tail=tail->pre,tail->nxt=NULL;
        sz--;
    }
    Node *Get(int dir)
    {
        dir^=rev;
        if(dir==0)
            return head;
        return tail;
    }
};
Node List::nodes[MAXQ],*List::ncnt;

int N,Q;
int id[MAXN];
List dq[MAXN];

int main()
{
    int op,u,v,val,w;
    while(scanf("%d%d",&N,&Q)!=EOF)
    {
        List::Clear();
        
        for(int i=1;i<=N;i++)
            id[i]=i,dq[i].clear();
        for(int i=1;i<=Q;i++)
        {
            read(op);
            if(op==1)
            {
                read(u);read(w);read(val);
                u=id[u];
                dq[u].Push(val,w);
            }
            else if(op==2)
            {
                read(u);read(w);
                u=id[u];
                if(dq[u].Size()==0)
                    printf("-1\n");
                else
                {
                    printf("%d\n",dq[u].Get(w)->val);
                    dq[u].Pop(w);
                }
            }
            else
            {
                read(u);read(v);read(w);
                int tu=u,tv=v;
                u=id[u];v=id[v];
                if(w==1)
                    dq[v].Reverse();
                if(dq[u].Size()>dq[v].Size())
                {
                    while(dq[v].Size())
                    {
                        Node *t=dq[v].Get(0);
                        dq[v].Pop(0);
                        t->nxt=t->pre=NULL;
                        dq[u].Push(t,1);
                    }
                }
                else
                {
                    while(dq[u].Size())
                    {
                        Node *t=dq[u].Get(1);
                        dq[u].Pop(1);
                        t->nxt=t->pre=NULL;
                        dq[v].Push(t,0);
                    }
                    id[tu]=v;id[tv]=u;
                }
            }
        }
    }
    
    return 0;
}
