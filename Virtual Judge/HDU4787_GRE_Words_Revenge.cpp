#include<iostream>
#include<string>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXL=5000006,MAXCHAR=2;

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
	
	int size()
	{return ncnt-nodes;}
	void Insert(const string &str)
	{
		Node *u=root;
		for(int i=0;i<(int)str.length();i++)
		{
			int c=str[i]-'0';
			if(u->son[c]==NULL)
			{
				u->son[c]=ncnt++;
				u->son[c]->clear();
			}
			u=u->son[c];
		}
		u->cnt=1;
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
	void Merge(Node *a,Node *b) 
	{
		a->cnt|=b->cnt;
		for(int i=0;i<MAXCHAR;i++)
			if(b->son[i])
			{
				if(a->son[i]==NULL)
				{
					a->son[i]=ncnt++;
					a->son[i]->clear();
				}
				Merge(a->son[i],b->son[i]);
			}
	}
	void Merge(const ACautomaton &C)
	{
		Merge(root,C.root);
		Build();
	}
	int Match(const string &str)
	{
		int ans=0;
		Node *u=root;
		for(int i=0;i<(int)str.length();i++)
		{
			int c=str[i]-'0';
			while(u&&u->son[c]==NULL)
				u=u->fail;
			if(u)
			{
				u=u->son[c];
				for(Node *tmp=u;tmp;tmp=tmp->fail)
					ans+=tmp->cnt;
			}
			else
				u=root;
		}
		return ans;
	}
};

ACautomaton A,B;
string op;

int main()
{
	int T,n;
	cin>>T;
	for(int test=1;test<=T;test++)
	{
		cout<<"Case #"<<test<<":"<<endl;
		cin>>n;
		A.Init();
		B.Init();
		int last=0;
		for(int i=1;i<=n;i++)
		{
			cin>>op;
			if(op[0]=='+')
			{
				int tmp=last%(op.length()-1);
				op=op.substr(tmp+1,op.length()-tmp-1)+op.substr(1,tmp);
				//cerr<<"Add : "+op<<endl;
				B.Insert(op);
				B.Build();
				if(B.size()>1000)
				{
					A.Merge(B);
					B.Init();
				}
			}
			if(op[0]=='?')
			{
				int tmp=last%(op.length()-1);
				op=op.substr(tmp+1,op.length()-tmp-1)+op.substr(1,tmp);
				//cerr<<"Query : "+op<<endl;
				cout<<(last=A.Match(op)+B.Match(op))<<endl;
			}
		}
	}
	
	return 0;
}
