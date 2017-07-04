#include<cstdio>
#include<cstring>
#include<set>
using namespace std;
#define MAXN 100005
const int dd[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
char str[MAXN];
int n,tx,ty,d[MAXN],X[MAXN],Y[MAXN];
struct state
{
	int x,y;
	state(){}
	state(int a,int b):x(a),y(b){}
	bool operator<(state t)const
	{return x<t.x||(x==t.x&&y<t.y);}
	bool operator>(state t)const
	{return x>t.x||(x==t.x&&y>t.y);}
};
set<state>S;
void change1(int k)
{
	if(str[k]=='F')return;
	tx=X[n+1],ty=Y[n+1];
	int ttx,tty;
	if(str[k]=='R') 
	{
		ttx=X[k]+ty-Y[k];
		tty=Y[k]-tx+X[k];
	}
	else
	{
		ttx=X[k]-ty+Y[k];
		tty=Y[k]+tx-X[k];
	}
	ttx+=dd[d[k]][0],tty+=dd[d[k]][1];
	if(!S.count(state(ttx,tty)))
		S.insert(state(ttx,tty));
}
void change2(int k)
{
	if(str[k]=='L')return;
	tx=X[n+1],ty=Y[n+1];
	int ttx,tty;
	if(str[k]=='F')
	{
		tx-=dd[d[k]][0];ty-=dd[d[k]][1];
		ttx=X[k]-ty+Y[k];
		tty=Y[k]+tx-X[k];
	}
	else
	{
		ttx=X[k]-tx+X[k];
		tty=Y[k]-ty+Y[k];
	}
	if(!S.count(state(ttx,tty)))
		S.insert(state(ttx,tty));
}
void change3(int k)
{
	if(str[k]=='R')return;
	tx=X[n+1],ty=Y[n+1];
	int ttx,tty;
	if(str[k]=='F')
	{
		tx-=dd[d[k]][0];ty-=dd[d[k]][1];
		ttx=X[k]+ty-Y[k];
		tty=Y[k]-tx+X[k];
	}
	else
	{
		ttx=X[k]-tx+X[k];
		tty=Y[k]-ty+Y[k];
	}
	if(!S.count(state(ttx,tty)))
		S.insert(state(ttx,tty));
}
int main()
{
	scanf("%s",str+1);
	n=strlen(str+1);
	for(int i=1;i<=n;i++)
		switch(str[i])
		{
			case 'F':{d[i+1]=d[i];X[i+1]=X[i]+dd[d[i]][0],Y[i+1]=Y[i]+dd[d[i]][1];break;}
			case 'L':{d[i+1]=(d[i]+1)%4;X[i+1]=X[i];Y[i+1]=Y[i];break;}
			case 'R':{d[i+1]=(d[i]+3)%4;X[i+1]=X[i];Y[i+1]=Y[i];break;}
		}
	for(int i=1;i<=n;i++)
	{
		change1(i);
		change2(i);
		change3(i);
	}
	printf("%d\n",S.size());
	return 0;
}
