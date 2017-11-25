#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXS=30;

namespace Trie
{
	struct Node
	{Node *ch[MAXS];};
	Node nodes[MAXN],*rt,*cur=nodes+1;
	void Insert(Node *&u,const char s[],int k)
	{
		if(u==NULL)
			u=cur++;
		if(s[k]==0)return;
		Insert(u->ch[s[k]-'a'],s,k+1);
	}
}

char str[MAXN];
bool DP1(Trie::Node *u)
{
	bool ret=false;
	for(int i=0;i<26;i++)
		if(u->ch[i])
			if(DP1(u->ch[i])==false)
				ret=true;
	return ret;
}
bool DP2(Trie::Node *u)
{
	bool ret=false,flag=true;
	for(int i=0;i<26;i++)
		if(u->ch[i])
		{
			flag=false;
			if(DP2(u->ch[i])==false)
				ret=true;
		}
	if(flag)ret=true;
	return ret;
}

int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",str);
		Trie::Insert(Trie::rt,str,0);
	}
	bool ans1,ans2;
	ans1=DP1(Trie::rt);
	ans2=DP2(Trie::rt);
	if(ans1)
	{
		if(ans2||k%2==1)
			puts("First");
		else
			puts("Second");
	}
	else
		puts("Second");
	return 0;
}
