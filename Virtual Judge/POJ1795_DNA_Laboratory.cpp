#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN=17,MAXL=105,MAXS=1<<15;
int N;
string DNA[MAXN];
int dp[MAXS][MAXN],second[MAXS][MAXN];
int val[MAXN][MAXN],length[MAXN];
bool cmp(int i,int x,int j,int y)
{
	for(int p=x,q=y;p<length[i]&&q<length[j];p++,q++)
		if(DNA[i][p]>DNA[j][q])
			return 1;
		else if(DNA[i][p]<DNA[j][q])
			return 0;
	return 0;
}
int main()
{
	int T,maxs,n;
	scanf("%d",&T);
	for(int Case=1;Case<=T;Case++)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			cin>>DNA[i];
		N=n;
		for(int i=1;i<=n;i++)
		{
			if(DNA[i][0]=='z')
				continue;
			for(int j=1;j<=n;j++)
				if(i!=j&&DNA[j][0]!='z'&&DNA[i].find(DNA[j])!=string::npos)
				{
					DNA[j]="z"+DNA[j];
					N--;
				}
		}
		sort(DNA+1,DNA+n+1);
		for(int i=1;i<=n;i++)
			length[i]=DNA[i].length();
		maxs=1<<N;
		for(int i=1;i<=N;i++)
			for(int j=1;j<=N;j++)
			{
				int l1=length[i],l2=length[j];
				for(int k=min(l1,l2);k>=0;k--)
				{
					bool success=1;
					for(int p=0;p<k&&success;p++)
						if(DNA[i][l1-k+p]!=DNA[j][p])
							success=0;
					if(success)
					{
						val[i][j]=k;
						break;
					}
				}
			}
		memset(dp,0x7F,sizeof dp);
		for(int i=1;i<=N;i++)
			dp[1<<(i-1)][i]=length[i];
		for(int s=0;s<maxs;s++)
			for(int i=1;i<=N;i++)
				if(dp[s][i]!=0x7F7F7F7F)
					for(int j=1,bit=1;j<=N;j++,bit<<=1)
						if(i!=j&&(bit&s)==0)
						{
							int res=dp[s][i]+length[j]-val[j][i],&st=dp[s^bit][j];
							if(st>res||(st==res&&cmp(second[s^bit][j],val[j][second[s^bit][j]],i,val[j][i])))
							{
								st=res;
								second[s^bit][j]=i;
							}
						}
		string ans;
		int len=0x7F7F7F7F,cur,last=0,state=maxs-1,temp;
		for(int i=1;i<=N;i++)
			if(len>dp[state][i]||(len==dp[state][i]&&cmp(cur,0,i,0)))
			{
				len=dp[state][i];
				cur=i;
			}
		while(cur)
		{
			ans+=DNA[cur].substr(last,len-last);
			temp=second[state][cur];
			last=val[cur][temp];
			state^=1<<(cur-1);
			cur=temp;
		}
		printf("Scenario #%d:\n%s\n\n",Case,ans.c_str());
	}
	return 0;
}
