#include<iostream>
#include<string>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXL=1000006,MAXCHAR=26;

struct ACautomaton
{
	struct Node
	{
		int cnt;
		Node *son[MAXCHAR],*fail;
		void clear()
		{
			cnt=0;
			fill(son,son+MAXCHAR,(Node*)NULL);
			fail=NULL;
		}
	};
	
	Node nodes[MAXL],*root,*ncnt;
	void Init()
	{
		root=(&nodes[0]);
		root->clear();
		ncnt=nodes+1;
	}

	int id(Node *u)
	{return u-nodes;}
	void Insert(const string &str,int &ID)
	{
		Node *u=root;
		for(int i=0;i<(int)str.length();i++)
		{
			int c=str[i]-'a';
			if(u->son[c]==NULL)
			{
				u->son[c]=ncnt++;
				u->son[c]->clear();
			}
			u=u->son[c];
		}
		u->cnt++;
		ID=id(u);
	}
	void Build()
	{
		static queue<Node*> Q;
		for(int i=0;i<MAXCHAR;i++)
			if(root->son[i])
			{
				root->son[i]->fail=root;
				Q.push(root->son[i]);
			}
		while(!Q.empty())
		{
			Node *u=Q.front();
			Q.pop();
			for(int i=0;i<MAXCHAR;i++)
				if(u->son[i])
				{
					Node *v=u->son[i],*f=u->fail;
					Q.push(v);
					while(f&&f->son[i]==NULL)
						f=f->fail;
					if(f)
						v->fail=f->son[i];
					else
						v->fail=root;
				}
		}
	}
	int Match(const string &str);
};

struct BIT
{
	int sum[MAXL];
	void Add(int pos,int val)
	{
		for(;pos<MAXL;pos+=(pos&(-pos)))
			sum[pos]+=val;
	}
	int Get(int pos)
	{
		int ret=0;
		for(;pos>0;pos-=(pos&(-pos)))
			ret+=sum[pos];
		return ret;
	}
};

int n,k;
int st[MAXL],ed[MAXL],dfc;
int id[MAXN];
bool enable[MAXN];
vector<int> adj[MAXL];
string a[MAXN],s;
ACautomaton A;
BIT S;

int ACautomaton::Match(const string &str)
{
	int ans=0;
	Node *u=root;
	for(int i=0;i<(int)str.length();i++)
	{
		int c=str[i]-'a';
		while(u&&u->son[c]==NULL)
			u=u->fail;
		if(u)
		{
			u=u->son[c];
			ans+=S.Get(st[id(u)]);
		}
		else
			u=root;
	}
	return ans;
}

void dfs(int u)
{
	st[u]=++dfc;
	for(int i=0;i<(int)adj[u].size();i++)
		dfs(adj[u][i]);
	ed[u]=dfc;
	S.Add(st[u],A.nodes[u].cnt);
	S.Add(ed[u]+1,-A.nodes[u].cnt);
}

int main()
{
	A.Init();
	cin>>n>>k;
	for(int i=1;i<=k;i++)
	{
		cin>>a[i];
		A.Insert(a[i],id[i]);
		enable[i]=true;
	}
	A.Build();
	for(ACautomaton::Node *u=A.nodes+1;u<A.ncnt;u++)
		adj[A.id(u->fail)].push_back(A.id(u));
	dfs(0);
	for(int i=1;i<=n;i++)
	{
		cin>>s;
		if(s[0]=='?')
		{
			s=s.substr(1,s.length()-1);
			cout<<A.Match(s)<<endl;
		}
		else if(s[0]=='-')
		{
			int x=0;
			for(int i=1;i<(int)s.length();i++)
				x=x*10+s[i]-'0';
			if(enable[x])
			{
				S.Add(st[id[x]],-1);
				S.Add(ed[id[x]]+1,1);
				enable[x]=false;
			}
		}
		else if(s[0]=='+')
		{
			int x=0;
			for(int i=1;i<(int)s.length();i++)
				x=x*10+s[i]-'0';
			if(!enable[x])
			{
				S.Add(st[id[x]],1);
				S.Add(ed[id[x]]+1,-1);
				enable[x]=true;
			}
		}
	}
	
	return 0;
}
