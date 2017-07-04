#include<cstdio>
#include<iostream>
using namespace std;
char s[7][7];
bool f[7][7];
int n,dd[4][2]={{1,0},{0,1},{-1,0},{0,-1}},cnt=1,ss,z=1;
bool ff(int a,int b,int i,int j)
{
	if(a<0||b<0||a>=n||b>=n)return 0;
	if(i<0||j<0||i>=n||j>=n)return 0;
	if(f[i][j]==1)return 0;
	return 1;
}
void dfs(int a,int b)
{
    int ii,jj;
    for(int i=0;i<4;i++)
    {
        ii=a+dd[i][0];
        jj=b+dd[i][1];
		if(!ff(a,b,ii,jj))continue;
		if(s[ii][jj]=='(')
		{
			if(s[a][b]==')')continue;
			f[ii][jj]=1;
			cnt++;
			z++;
			dfs(ii,jj);
			cnt--;
			z--;
			f[ii][jj]=0;
		}
		else
		{
			if(z<=0)continue;
			f[ii][jj]=1;
			cnt++;
			z--;
			dfs(ii,jj);
			cnt--;
			z++;
			f[ii][jj]=0;
		}
    }
    if(cnt>ss&&z==0)
        ss=cnt;
}
int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
        scanf("%s",s[i]);
	if(s[0][0]==')'){printf("0\n");return 0;}
    f[0][0]=1;
    dfs(0,0);
    printf("%d\n",ss);
    return 0;
}
