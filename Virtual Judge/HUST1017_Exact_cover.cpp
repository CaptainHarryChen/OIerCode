#include<cstdio>
#define MAXN 1005
#define MAXLEN MAXN*MAXN
#define INF 0x3FFFFFFF
int N, M;						//行数、列数
int row[MAXLEN];			    //各结点的行标号表
int cntr[MAXN];					//行结点记数器
int cntc[MAXN];					//列结点记数器
int L[MAXLEN], R[MAXLEN];		//行链表
int U[MAXLEN], D[MAXLEN]; 		//列链表
int C[MAXLEN];					//链表中各结点指向列表头
int O[MAXN];					//存结果
int head = 0;					//列表头指针
int deep;
void remove(const int &c)
{
	L[R[c]]=L[c];
	R[L[c]]=R[c];
	
	for(int i=D[c];i!=c;i=D[i])
		for(int j=R[i];j!=i;j=R[j])
		{
			U[D[j]]=U[j];
			D[U[j]]=D[j];
			cntc[C[j]]--;
		}
}
void resume(const int &c)
{
	for(int i=U[c];i!=c;i=U[i])
		for(int j=L[i];j!=i;j=L[j])
		{
			cntc[C[j]]++;
			U[D[j]]=j;
			D[U[j]]=j;
		}
		
	L[R[c]]=c;
	R[L[c]]=c;
}
bool dfs()
{
	if(R[head]==head)return 1;
	int min=INF,c;
	for(int i=R[head];i!=head;i=R[i])
		if(cntc[i]<min)
		{
			min=cntc[i];
			c=i;
		}
	remove(c);
	
	for(int i=D[c];i!=c;i=D[i])
	{
		O[deep++]=row[i];
		
		for(int j=R[i];j!=i;j=R[j])
			remove(C[j]);
		
		if(dfs())return 1;
		
		for(int j=L[i];j!=i;j=L[j])
				resume(C[j]);
		
		deep--;
	}
	resume(c);
	return 0;
}
int main()
{
	int begin,end,size;
	while(~scanf("%d%d",&N,&M))
	{
		for(int i=0;i<=M;i++)
		{
			cntc[i]=0;
			L[i]=i-1;
			R[i]=i+1;
			U[i]=D[i]=i;
		}
		L[0]=M;
		R[M]=0;
		size=M+1;
		for(int i=1;i<=N;i++)
		{
			scanf("%d",&cntr[i]);
			begin=end=size;
			for(int j=1,k;j<=cntr[i];j++)
			{
				scanf("%d",&k);
				cntc[k]++;
				C[size]=k;
				row[size]=i;
				
				U[D[k]]=size;
				D[size]=D[k];
				U[size]=k;
				D[k]=size;
				
				L[size]=end;
				R[end]=size;
				R[size]=begin;
				L[begin]=size;
				end=size;
				
				size++;
			}
		}
		bool flag=0;
		for(int i=1;i<=M;i++)
			if(cntc[i]==0)
			{flag=1;break;}
		if(flag){puts("NO");continue;}
		deep=0;
		if(dfs())
		{
			printf("%d",deep);
			for(int i=0;i<deep;i++)
				printf(" %d",O[i]);
			puts("");
		}
		else
			printf("NO\n");
	}
	return 0;
}
