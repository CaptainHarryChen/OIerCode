#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 300005
int V[MAXN],ed[MAXN],nxt[MAXN],S[MAXN],nid[MAXN],tmp[MAXN],N,Q;
int input[MAXN][3];
int Root(int x){return S[x]==x?x:S[x]=Root(S[x]);}
void Input_Init()
{
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
		scanf("%d",&V[i]);
	for(int i=1;i<=N;i++)
		S[i]=nxt[i]=ed[i]=i;
	scanf("%d",&Q);
	char op[5];
	for(int i=1;i<=Q;i++)
	{
		scanf("%s",op);
		if(strcmp(op,"U")==0)
		{
			input[i][0]=0;
			scanf("%d%d",&input[i][1],&input[i][2]);
		}
		else if(strcmp(op,"A1")==0)
		{
			input[i][0]=1;
			scanf("%d%d",&input[i][1],&input[i][2]);
		}
		else if(strcmp(op,"A2")==0)
		{
			input[i][0]=2;
			scanf("%d%d",&input[i][1],&input[i][2]);
		}
		else if(strcmp(op,"A3")==0)
		{
			input[i][0]=3;
			scanf("%d",&input[i][1]);
		}
		else if(strcmp(op,"F1")==0)
		{
			input[i][0]=4;
			scanf("%d",&input[i][1]);
		}
		else if(strcmp(op,"F2")==0)
		{
			input[i][0]=5;
			scanf("%d",&input[i][1]);
		}
		else if(strcmp(op,"F3")==0)
			input[i][0]=6;
	}
	for(int i=1;i<=Q;i++)
		if(input[i][0]==0)
		{
			int x=Root(input[i][1]),y=Root(input[i][2]);
			if(x==y)continue;
			if(x>y)swap(x,y);
			S[y]=x;
			nxt[ed[x]]=y;
			ed[x]=ed[y];
		}
	memset(ed,0,sizeof ed);
	int id=0;
	for(int i=1;i<=N;i++)
	{
		int x=i;
		while(!ed[x])
		{
			nid[x]=++id;
			ed[x]=id;
			S[x]=x;
			x=nxt[x];
		}
	}
	memcpy(tmp,V,sizeof V);
	for(int i=1;i<=N;i++)
		V[nid[i]]=tmp[i];
}
int seg[MAXN*4],add[MAXN*4];
void InitST(int id,int l,int r)
{
	add[id]=0;
	if(l==r)
	{seg[id]=V[l];return;}
	InitST(id*2,l,(l+r)/2);
	InitST(id*2+1,(l+r)/2+1,r);
	seg[id]=max(seg[id*2],seg[id*2+1]);
}
void Update(int id,int L,int R,int l,int r,int ad)
{
	if(L>r||R<l)return;
	if(L>=l&&R<=r)
	{add[id]+=ad;return;}
	Update(id*2,L,(L+R)/2,l,r,ad);
	Update(id*2+1,(L+R)/2+1,R,l,r,ad);
	seg[id]=max(seg[id*2]+add[id*2],seg[id*2+1]+add[id*2+1]);
}
int Get(int id,int L,int R,int l,int r)
{
	if(L>r||R<l)return -90000000;
	if(L>=l&&R<=r)
		return seg[id]+add[id];
	return max(Get(id*2,L,(L+R)/2,l,r),Get(id*2+1,(L+R)/2+1,R,l,r))+add[id];
}
void RunSegTree()
{
	InitST(1,1,N);
	for(int i=1;i<=Q;i++)
	{
		if(input[i][0]==0)
		{
			int x=Root(input[i][1]),y=Root(input[i][2]);
			if(x==y)continue;
			if(x>y)swap(x,y);
			S[y]=x;
			ed[x]=ed[y];
		}
		else if(input[i][0]==1)
			Update(1,1,N,nid[input[i][1]],nid[input[i][1]],input[i][2]);
		else if(input[i][0]==2)
		{
			int x=Root(input[i][1]);
			Update(1,1,N,nid[x],ed[x],input[i][2]);
		}
		else if(input[i][0]==3)
			Update(1,1,N,1,N,input[i][1]);
		else if(input[i][0]==4)
			printf("%d\n",Get(1,1,N,nid[input[i][1]],nid[input[i][1]]));
		else if(input[i][0]==5)
		{
			int x=Root(input[i][1]);
			printf("%d\n",Get(1,1,N,nid[x],ed[x]));
		}
		else
			printf("%d\n",Get(1,1,N,1,N));
	}
}
int main()
{
	Input_Init();
	RunSegTree();
	return 0;
}
