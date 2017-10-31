#include<cstdio>
#include<cstring>
const int MAXN=55,MAXM=1005;
int n,m;
char hid[MAXN];
char s[MAXN];
bool v[MAXM][MAXN];
int main()
{
	scanf("%d%s",&n,hid);
	scanf("%d",&m);
	memset(v[0],1,sizeof v[0]);
	for(int i=0;i<n;i++)
		if(hid[i]!='*')
			v[0][hid[i]-'a']=false;
	for(int i=1;i<=m;i++)
	{
		scanf("%s",s);
		bool flag=true;
		for(int j=0;j<n;j++)
			if((hid[j]=='*'&&!v[0][s[j]-'a'])||(hid[j]!='*'&&hid[j]!=s[j]))
			{flag=false;break;}
		if(!flag)
		{
			memset(v[i],1,sizeof v[i]);
			continue;
		}
		for(int j=0;j<n;j++)
			if(hid[j]=='*')
				v[i][s[j]-'a']=true;
	}
	for(int i=1;i<=m;i++)
		for(int j=0;j<26;j++)
			v[i][j]&=v[i-1][j];
	int ans=0;
	for(int i=0;i<26;i++)
		ans+=v[m][i];
	printf("%d\n",ans);
	return 0;
}
