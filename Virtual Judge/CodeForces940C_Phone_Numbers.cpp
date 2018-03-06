#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=100005;

int n,m,id[30],letcnt;
char str[MAXN],let[30];
bool used[30];

int main()
{
	scanf("%d%d%s",&n,&m,str+1);
	for(int i=1;i<=n;i++)
		used[str[i]-'a']=true;
	for(int i=0;i<26;i++)
		if(used[i])
		{
			let[++letcnt]=i+'a';
			id[i]=letcnt;
		}
	if(m>n)
	{
		printf("%s",str+1);
		for(int i=n+1;i<=m;i++)
			putchar(let[1]);
		puts("");
		return 0;
	}
	str[m+1]=0;
	for(int i=m;i>0;i--)
	{
		int c=id[str[i]-'a'];
		if(c<letcnt)
		{
			str[i]=let[c+1];
			break;
		}
		else
			str[i]=let[1];
	}
	printf("%s\n",str+1);
	return 0;
}