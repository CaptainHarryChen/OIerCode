#include<cstdio> 
#include<iostream> 
#include<cstring> 
#include<queue> 
#define MAXM 205 
#define INF 2139062143 
using namespace std; 
queue<int>myq; 
int net[MAXM][MAXM],N,M,d[MAXM],vd[MAXM],flow;  
int aug(int i,int augco) 
{ 
    int j,augc=augco,mind=M-1,delta; 
    if(i==M) 
        return augc; 
    for(j=1;j<=M;j++) 
        if(net[i][j]) 
        { 
			if(d[i]==d[j]+1) 
			{ 
				delta=min(augc,net[i][j]); 
				delta=aug(j,delta); 
				net[i][j]-=delta; 
				net[j][i]+=delta; 
				augc-=delta; 
				if(d[1]>=M) 
					return augco-augc; 
				if(augc==0) 
					break; 
			} 
			if(mind>d[j]) 
				mind=d[j]; 
        } 
    if(augco==augc) 
    { 
        vd[d[i]]--; 
        if(vd[d[i]]==0) 
            d[1]=M; 
        d[i]=mind+1; 
        vd[d[i]]++; 
    } 
    return augco-augc; 
} 
int main() 
{ 
    int a,b,c; 
    scanf("%d%d",&N,&M); 
    for(int i=1;i<=N;i++) 
    { 
        scanf("%d%d%d",&a,&b,&c); 
        net[a][b]+=c; 
    } 
    vd[0]=M; 
    while(d[1]<M) 
        flow+=aug(1,INF); 
    printf("%d\n",flow); 
    return 0; 
} 
  