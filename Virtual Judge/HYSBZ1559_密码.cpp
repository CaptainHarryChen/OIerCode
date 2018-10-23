#include<cstring>
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=13,MAXL=28,MAXCHAR=26,MAXNODE=105,MAXS=1024+10;

struct Node
{
    Node *son[MAXCHAR],*fail;
    int dep,st;
    char c;
};

struct ACautomation
{
    Node nodes[MAXNODE],*root,*nodes_it;

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
            Node *&v=u->son[s[i]-'a'];
            if(v==NULL)
            {
                v=NewNode();
                v->c=s[i];
                v->dep=u->dep+1;
                //printf("(%d %d %c)\n",u-nodes,v-nodes,s[i]);
            }
            u=v;
        }
        return u;
    }
    void BuildFail()
    {
        static Node* Q[MAXNODE];
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
                    v->st|=v->fail->st;
                    //printf("[%d %d]\n",v-nodes,v->fail-nodes);
                    Q[++r]=v;
                }
        }
    }
};

ACautomation AC;
int L,N,M;
string str[MAXN];

int id[MAXN];
int len[MAXN][MAXN];
long long dp[2][MAXNODE][MAXS];

vector<string> pw;

bool cmpstr(const string &a,const string &b)
{return a.length()>b.length();}

int main()
{
    cin>>L>>N;
    AC.Clear();
    for(int i=1;i<=N;i++)
        cin>>str[i];
    sort(str+1,str+N+1,cmpstr);
    for(int i=1;i<=N;i++)
    {
        //cout<<"\'"+str[i]+"\'"<<endl;
        for(int j=i+1;j<=N;j++)
            if(str[i].find(str[j])!=string::npos)
            {
                swap(str[j],str[N]);
                N--;
                j--;
            }
    }
    for(int i=1;i<=N;i++)
        AC.Insert(str[i].c_str())->st|=(1<<(i-1));
    M=AC.nodes_it-AC.nodes;
    AC.BuildFail();

    dp[0][0][0]=1;
    for(int i=0;i<L;i++)
    {
        for(int j=0;j<M;j++)
            for(int s=0;s<(1<<N);s++)
                if(dp[i&1][j][s])
                {
                    //cout<<"dp["+to_string(i)+"]["+to_string(j)+"]["+to_string(s)+"]="+to_string(dp[i&1][j][s])<<endl;
                    Node *u=AC.nodes+j;
                    for(int c=0;c<MAXCHAR;c++)
                    {
                        Node *v=u;
                        while(v!=AC.root&&v->son[c]==NULL)
                            v=v->fail;
                        if(v->son[c])
                            v=v->son[c];
                        int id=v-AC.nodes;
                        dp[(i+1)&1][id][s|v->st]+=dp[i&1][j][s];
                    }
                }
        memset(dp[i&1],0,sizeof dp[i&1]);
    }

    long long ans=0;
    for(int j=0;j<M;j++)
        ans+=dp[L&1][j][(1<<N)-1];
    cout<<ans<<endl;

    if(ans<=42)
    {
        for(int i=1;i<=N;i++)
            for(int j=1;j<=N;j++)
                if(i!=j)
                {
                    int l1=str[i].length(),l2=str[j].length();
                    for(int k=1;k<=l1&&k<=l2;k++)
                    {
                        bool flag=true;
                        for(int p=0;p<k&&flag;p++)
                            flag=(str[i][l1-k+p]==str[j][p]);
                        if(flag)
                            len[i][j]=k;
                    }
                }
        for(int i=1;i<=N;i++)
            id[i]=i;
        do
        {
            int a=str[id[1]].length();
            string tmp=str[id[1]];
            for(int i=2;i<=N;i++)
            {
                a+=str[id[i]].length()-len[id[i-1]][id[i]];
                tmp+=str[id[i]].substr(len[id[i-1]][id[i]],str[id[i]].length()-len[id[i-1]][id[i]]);
            }
            if(a==L)
                pw.push_back(tmp);
        }while(next_permutation(id+1,id+N+1));
        sort(pw.begin(),pw.end());
        for(int i=0;i<(int)pw.size();i++)
            cout<<pw[i]<<endl;
    }

    return 0;
}
