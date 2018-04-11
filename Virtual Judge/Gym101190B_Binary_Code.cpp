#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
using namespace std;
const int MAXN=500010,MAXNODE=MAXN*10,MAXEDGE=MAXNODE*2;

namespace SAT
{
	struct Edge
	{
		int v;
		Edge *nxt;
	}E[MAXEDGE],*etop=E,*adj[MAXNODE];
	void AddEdge(int u,int v)
	{
		//cerr<<"Add edge : "<<u<<"  ->  "<<v<<endl;
		etop->v=v;
		etop->nxt=adj[u];
		adj[u]=etop++;
	}
	int dfn[MAXNODE],low[MAXNODE],dfc;
	int stk[MAXNODE],top;
	bool ind[MAXNODE];
	int blkid[MAXNODE],blkc;
	void tarjan(int u)
	{
		dfn[u]=++dfc;
		low[u]=dfn[u];
		stk[++top]=u;
		ind[u]=true;
		for(Edge *p=adj[u];p;p=p->nxt)
		{
			if(!dfn[p->v])
			{
				tarjan(p->v);
				low[u]=min(low[u],low[p->v]);
			}
			else if(ind[p->v])
				low[u]=min(low[u],dfn[p->v]);
		}
		if(dfn[u]==low[u])
		{
			blkc++;
			do
			{
				ind[stk[top]]=false;
				blkid[stk[top]]=blkc;
			}while(stk[top--]!=u);
		}
	}
	bool solve(int num,int N)
	{
		for(int i=0;i<num;i++)
			if(!dfn[i])
				tarjan(i);
		for(int i=0;i<N*2;i++)
			if(blkid[i]==blkid[i^1])
				return false;
		return true;
	}
}

namespace Trie
{
	struct Node
	{
		Node *son[2],*fa;
		vector<int> ter;
		int id[2];
	};
	Node nodes[MAXN*2],*ntop=nodes,*root;
	Node *Insert(const string &s,int n,int id)
	{
		if(root==NULL)
			root=ntop++;
		Node *u=root;
		for(int i=0;i<n;i++)
		{
			if(u->son[s[i]-'0']==NULL)
			{
				u->son[s[i]-'0']=ntop++;
				u->son[s[i]-'0']->fa=u;
			}
			u=u->son[s[i]-'0'];
		}
		u->ter.push_back(id);
		return u;
	}
	void SAT_AddEdge(int &num)
	{
		for(Node *i=nodes;i<ntop;i++)
			i->id[0]=num++,i->id[1]=num++;
		for(Node *i=nodes;i<ntop;i++)
		{
			if(i->fa)
			{
				SAT::AddEdge(i->id[0],i->fa->id[0]);
				SAT::AddEdge(i->fa->id[1],i->id[1]);
			}
		}
	}
	void ProcessTerminal(int &num)
	{
		for(Node *i=nodes;i<ntop;i++)
			if(i->ter.size())
			{
				int last0=num++,last1=num++;
				SAT::AddEdge(last0,i->ter[0]^1);
				SAT::AddEdge(i->ter[0],last1);
				for(int j=1;j<(int)i->ter.size();j++)
				{
					int f0=num++,f1=num++;
					SAT::AddEdge(f0,last0);
					SAT::AddEdge(last1,f1);
					SAT::AddEdge(i->ter[j],last0);
					SAT::AddEdge(i->ter[j],f1);
					SAT::AddEdge(f0,i->ter[j]^1);
					SAT::AddEdge(last1,i->ter[j]^1);
					last0=f0;last1=f1;
				}
			}
	}
}

int N;
string str[MAXN];
int satId[MAXN][2];
Trie::Node *trId[MAXN];
int pos[MAXN];
int num;

int main()
{
	freopen("binary.in","r",stdin);
	freopen("binary.out","w",stdout);
	cin>>N;
	num=0;
	for(int i=1;i<=N;i++)
	{
		int f0,f1;
		f0=satId[i][0]=num++;
		f1=satId[i][1]=num++;
		cin>>str[i];
		int len=str[i].length();
		for(pos[i]=0;pos[i]<len&&str[i][pos[i]]!='?';pos[i]++);
		if(pos[i]==len)
		{
			pos[i]=-1;
			SAT::AddEdge(f0,f1);
			trId[f0]=trId[f1]=Trie::Insert(str[i],len,f1);
		}
		else
		{
			str[i][pos[i]]='0';
			trId[f0]=Trie::Insert(str[i],len,f0);
			str[i][pos[i]]='1';
			trId[f1]=Trie::Insert(str[i],len,f1);
		}
	}
	
	Trie::SAT_AddEdge(num);
	
	for(int i=0;i<N*2;i++)
	{
		Trie::Node *u=trId[i];
		if(u->son[0])
			SAT::AddEdge(i,u->son[0]->id[1]);
		if(u->son[1])
			SAT::AddEdge(i,u->son[1]->id[1]);
		if(u->fa)
			SAT::AddEdge(i,u->fa->id[0]);
		SAT::AddEdge(u->id[0],i^1);
		SAT::AddEdge(u->id[1],i^1);
	}
	
	Trie::ProcessTerminal(num);
	
	if(SAT::solve(num,N))
	{
		cout<<"YES"<<endl;
		for(int i=1;i<=N;i++)
		{
			if(pos[i]!=-1)
				str[i][pos[i]]=SAT::blkid[satId[i][0]]<SAT::blkid[satId[i][1]]?'0':'1';
			cout<<str[i]<<endl;
		}
	}
	else
		cout<<"NO"<<endl;
	
	return 0;
}
