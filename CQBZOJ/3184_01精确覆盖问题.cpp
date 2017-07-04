#include<cstdio>
#define MAXN 1005
#define MAXLEN MAXN*MAXN
int N,M;
int U[MAXLEN],D[MAXLEN],L[MAXLEN],R[MAXLEN];
int cntc[MAXN],cntl[MAXN];
int col[MAXLEN],line[MAXLEN];
int head,_new,ans;
void remove(int c)
{
	R[L[c]]=R[c];
	L[R[c]]=L[c];
	
	for(int i=D[c];i!=c;i=D[i])
		for(int j=R[i];j!=i;j=R[j])
		{
			U[D[j]]=U[j];
			D[U[j]]=D[j];
			cntc[col[j]]--;
		}
}
void resume(int c)
{
	for(int i=U[c];i!=c;i=U[i])
		for(int j=L[i];j!=i;j=L[j])
		{
			U[D[j]]=j;
			D[U[j]]=j;
			cntc[col[j]]++;
		}
	
	L[R[c]]=c;
	R[L[c]]=c;
}
void dfs()
{
	if(R[head]==head)
	{ans++;return;}
	
	int min_cnt=0x7FFFFFFF,c;
	for(int i=R[head];i!=head;i=R[i])
		if(cntc[i]<min_cnt)
		{c=i;min_cnt=cntc[i];}
	remove(c);
	
	for(int i=D[c];i!=c;i=D[i])
	{
		for(int j=R[i];j!=i;j=R[j])
			remove(col[j]);
		dfs();
		for(int j=L[i];j!=i;j=L[j])
			resume(col[j]);
	}
	
	resume(c);
}
int main()
{
	scanf("%d%d",&N,&M);
	for(int i=0;i<=M;i++)
	{
		L[i]=i-1;
		R[i]=i+1;
		U[i]=i;
		D[i]=i;
		cntc[i]=0;
	}
	_new=M+1;
	L[head]=M;
	R[M]=head;
	for(int i=1,l_begin,l_end;i<=N;i++)
	{
		l_begin=l_end=_new;
		for(int j=1,k;j<=M;j++)
		{
			scanf("%1d",&k);
			if(!k)continue;
			col[_new]=j;
			line[_new]=i;
			cntl[i]++;
			cntc[j]++;
			
			U[_new]=j;
			D[_new]=D[j];
			D[j]=_new;
			U[D[_new]]=_new;
			
			L[_new]=l_begin;
			R[l_begin]=_new;
			R[_new]=l_end;
			L[l_end]=_new;
			l_end=_new;
			
			_new++;
		}
	}
	for(int i=1;i<=M;i++)
		if(cntc[i]==0)
		{printf("0\n");return 0;}
	dfs();
	printf("%d\n",ans);
	return 0;
}
