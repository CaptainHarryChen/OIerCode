#include<cstdio>
#include<cstring>
const int MAXN=105;

int GetAnswer(const char tmp[])
{
	if(tmp[2]=='n')
	{
		int res;
		sscanf(tmp+4,"%d",&res);
		return res;
	}
	return 0;
}
int GetComplexity(const char A[],const char B[])
{
	if(A[0]=='n'&&B[0]=='n')
		return 0;
	if(A[0]=='n'&&B[0]!='n')
		return -1;
	if(A[0]!='n'&&B[0]=='n')
		return 1;
	int a,b;
	sscanf(A,"%d",&a);
	sscanf(B,"%d",&b);
	if(a<=b)
		return 0;
	return -1;
}

struct for_data
{
	char var;
	int add;
	for_data(){}
	for_data(char _v,int _a)
	{var=_v;add=_a;}
};

bool used[MAXN];
for_data stk[MAXN];
int tp;

char tmp[MAXN],A[MAXN],B[MAXN];

void Quit(int x)
{
	while(x--)
	{
		scanf("%s",tmp);
		if(tmp[0]=='F')
			scanf("%s%s%s",tmp,tmp,tmp);
	}
}

int main()
{
	int T,N;
	scanf("%d",&T);
	
	int ans,myans,nowcp,last;
	
	while(T--)
	{
		scanf("%d%s",&N,tmp);
		ans=GetAnswer(tmp);
		
		tp=0;
		myans=0;
		nowcp=0;
		last=-1;
		memset(used,0,sizeof used);
		bool error=false;
		for(int i=1;i<=N;i++)
		{
			scanf("%s",tmp);
			if(tmp[0]=='F')
			{
				scanf("%s",tmp);
				if(used[tmp[0]-'a'])
				{
					error=true;
					scanf("%s%s",tmp,tmp);
					Quit(N-i);
					break;
				}
				used[tmp[0]-'a']=true;
				
				scanf("%s%s",A,B);
				int cp=GetComplexity(A,B);
				
				for_data delta=for_data(tmp[0],0);
				
				if(cp==-1)
				{
					delta.add=0;
					if(last==-1)
						last=tp+1;
				}
				else
				{
					delta.add=0;
					if(last==-1)
					{
						nowcp+=cp;
						delta.add=cp;
					}
				}
				stk[++tp]=delta;
				
				if(myans<nowcp)
					myans=nowcp;
			}
			else
			{
				if(tp==0)
				{
					error=true;
					Quit(N-i);
					break;
				}
				if(last==tp)
					last=-1;
				used[stk[tp].var-'a']=false;
				nowcp-=stk[tp].add;
				tp--;
			}
		}
		if(tp!=0)
			error=true;
		
		if(error)
			puts("ERR");
		else if(myans==ans)
			puts("Yes");
		else
			puts("No");
	}
	
	return 0;
}
