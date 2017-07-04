#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
int n,m,cnt;
char s[1005][1005],e[2];
bool f[1005][1005];
struct num
{
    int x,y;
    char a;
    num(){}
    num(int i,int j,char k)
    {x=i;y=j;a=k;}
};
queue<num>q;
bool f_(int x,int y)
{
    if(x>=0&&y>=0&&x<n&&y<m)return 1;
    return 0;
}
int main()
{
    int dd[4][2]={{-1,0},{0,-1},{1,0},{0,1}};
    cin>>n>>m;
	gets(e);
    for(int i=0;i<n;i++)
        gets(s[i]);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(f[i][j]==1||s[i][j]=='0')continue;
            num tt=num(i,j,s[i][j]);
            cnt++;
            f[i][j]=1;
            q.push(tt);
            while(!q.empty())
            {
                tt=q.front();
                q.pop();
                for(int k=0;k<4;k++)
                {
					num t=tt;
                    t.x=t.x+dd[k][0];
					t.y=t.y+dd[k][1];
					t.a=s[t.x][t.y];
                    if(f_(t.x,t.y)&&f[t.x][t.y]==0&&t.a==s[i][j])
                    {
                        f[t.x][t.y]=1;
                        q.push(t);
                    }
                }
            }
        }
    }
    cout<<cnt<<endl;
    return 0;
}
