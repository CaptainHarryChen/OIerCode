#include<cstdio>
#include<cstring>
#define MAXN 1050
char s1[MAXN],s2[MAXN];
int T,n,r1,r2,p1,p2;
struct node
{
	char col;
	int ch[4];
}tr1[MAXN],tr2[MAXN];
int make_tree(int *u,int t,node tree[],char s[])
{
	*u=p1++;
	tree[*u].col=s[t];
	int p=t,mx=t;
	if(s[t]=='p')
		for(int i=0;i<4;i++)
		{
			p=make_tree(tree[*u].ch+i,p+1,tree,s);
			if(p>mx)
				mx=p;
		}
	return mx;
}
int count(int *u,int v,node tree[])
{
	if(tree[*u].col=='f')
		return v;
	if(tree[*u].col=='e')
		return 0;
	int cnt=0;
	for(int i=0;i<4;i++)
		cnt+=count(tree[*u].ch+i,v/4,tree);
	return cnt;
}
int count(int *u1,int *u2,int v)
{
	if(tr1[*u1].col=='f'||tr2[*u2].col=='f')
		return v;
	if(tr1[*u1].col=='e'&&tr2[*u2].col=='e')
		return 0;
	if(tr1[*u1].col=='e')
	{
		int cnt=0;
		for(int i=0;i<4;i++)
			cnt+=count(tr2[*u2].ch+i,v/4,tr2);
		return cnt;
	}
	if(tr2[*u2].col=='e')
	{
		int cnt=0;
		for(int i=0;i<4;i++)
			cnt+=count(tr1[*u1].ch+i,v/4,tr1);
		return cnt;
	}
	int cnt=0;
	for(int i=0;i<4;i++)
		cnt+=count(tr1[*u1].ch+i,tr2[*u2].ch+i,v/4);
	return cnt;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		p1=p2=1;
		memset(tr1,0,sizeof tr1);
		memset(tr2,0,sizeof tr2);
		scanf("%s%s",s1,s2);
		n=strlen(s1);
		make_tree(&r1,0,tr1,s1);
		make_tree(&r2,0,tr2,s2);
		printf("There are %d black pixels.\n",count(&r1,&r2,1024));
	}
	return 0;
}
