#include<cstdio>
const int MAXN=100005;

int fa[MAXN],cnt[MAXN];
int Root(int x)
{
	if(fa[x]==0)
		return x;
	return fa[x]=Root(fa[x]);
}
void Union(int x,int y)
{
	int r1=Root(x),r2=Root(y);
	if(r1==r2)
		return;
	cnt[r2]+=cnt[r1];
	fa[r1]=r2;
}
bool check(const char *s)
{
	bool flag=true;
	for(int i=0;s[i];i++)
		if(s[i]!='7'&&s[i]!='4')
		{flag=false;break;}
	return flag;
}

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		cnt[i]=1;
	for(int i=1;i<n;i++)
	{
		int u,v;
		char s[12];
		scanf("%d%d%s",&u,&v,s);
		if(!check(s))
			Union(u,v);
	}
	long long s1=0,s2=0,s3=0,t2=0,t3=0;
	for(int i=1;i<=n;i++)
		if(fa[i]==0)
		{
			s1+=cnt[i];
			s2+=1LL*cnt[i]*cnt[i];
			s3+=1LL*cnt[i]*cnt[i]*cnt[i];
			t2+=1LL*cnt[i]*(cnt[i]-1);
			t3+=1LL*cnt[i]*cnt[i]*(cnt[i]-1);
		}
	long long ans=s1*s1*s1-3LL*s1*s2+2LL*s3+s1*t2-t3;
	printf("%lld\n",ans);
	
	return 0;
}
