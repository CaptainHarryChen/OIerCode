#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=45,MAXS=2097200;

vector< pair<int,bool> > W[MAXS];
char str[MAXN];
int val[MAXN];
int stk[MAXS*2],top;
char s1[MAXN],s2[MAXN];

int main()
{
	int n;
	while(scanf("%d",&n)!=EOF)
	{
		if(n==0)break;
		while(top)
			W[stk[top--]].clear();
		scanf("%s",str+1);
		for(int i=1;i<=2*n;i++)
			scanf("%d",val+i);
		int a=0,b=0;
		for(int i=1;i<=2*n;i++)
		{
			a+=str[i]=='a';
			b+=str[i]=='b';
		}
		if(a%2==1||b%2==1)
		{
			puts("-1");
			continue;
		}
		for(int s=0;s<(1<<n);s++)//枚举T1前半截，且|T1|≤|T2|
		{
			if(__builtin_popcount(s)>n/2)
				continue;
			int diff=0,p=0,q=0;//diff差=Val(T1)-Val(T2)
			for(int i=1;i<=n;i++)
				if(s&(1<<(i-1)))
				{
					diff+=val[i];
					s1[p++]=str[i];
				}
				else
				{
					diff-=val[i];
					s2[q++]=str[i];
				}
			bool flag=true;
			for(int i=0;i<p&&flag;i++)
				if(s1[i]!=s2[i])
					flag=false;
			if(!flag)
				continue;
			int c=1;
			for(int r=p;r<q;r++)
			{
				c<<=1;
				c|=(s2[r]=='b');
			}
			if(W[c].size()==0)
				stk[++top]=c;
			W[c].push_back(make_pair(diff,false));
		}
		for(int s=0;s<(1<<n);s++)//枚举T1后半截，且|T1|>=|T2|
		{
			if(__builtin_popcount(s)<(n+1)/2)
				continue;
			int p=0,q=0,diff=0;//diff差=Val(T2)-Val(T1)
			for(int i=n+1;i<=2*n;i++)
				if(s&(1<<(i-n-1)))
				{
					diff-=val[i];
					s1[p++]=str[i];
				}
				else
				{
					diff+=val[i];
					s2[q++]=str[i];
				}
			bool flag=true;
			for(int i=1;i<=q&&flag;i++)
				if(s1[p-i]!=s2[q-i])
					flag=false;
			if(!flag)
				continue;
			int c=1;
			for(int r=p;r>q;r--)
			{
				c<<=1;
				c|=s1[p-r]=='b';
			}
			if(W[c].size()==0)
				stk[++top]=c;
			W[c].push_back(make_pair(diff,true));
		}
		
		int ans=0x7FFFFFFF;
		for(int c=0;c<(1<<(n+1));c++)
			if(W[c].size()>1)
			{
				sort(W[c].begin(),W[c].end());
				int p=-1,q=-1;
				for(int i=0;i<(int)W[c].size();i++)
				{
					if(W[c][i].second)
						p=i;
					else
						q=i;
					if(p!=-1&&q!=-1)
						ans=min(ans,abs(W[c][p].first-W[c][q].first));
				}
			}
		printf("%d\n",ans==0x7FFFFFFF?-1:ans);
	}
	return 0;
}
