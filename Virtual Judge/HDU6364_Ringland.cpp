#include<cstdio>
#include<vector>
//#include<ctime>
using namespace std;
const int MAXN=500005,INF=0x3F3F3F3F;
const long long LLF=0x3F3F3F3F3F3F3F3FLL;

struct FastIO {
    static const int S = 1310720;
    int wpos;
    char wbuf[S];
    FastIO() : wpos(0) { }
    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len) pos = 0, len = fread(buf, 1, S, stdin);
        if (pos == len) return -1;
        return buf[pos++];
    }
    inline int xint() {
        int c = xchar(), x = 0, s = 1;
        while (c <= 32) c = xchar();
        if (c == '-') s = -1, c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x * s;
    }
    ~FastIO() {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;

int N,L;
long long a[MAXN],b[MAXN*3];
int l[MAXN],r[MAXN],rb[MAXN*3];
vector<long long> g[MAXN];

int main()
{
	//freopen("in","r",stdin);

	int T;
	T=io.xint();
	while(T--)
	{
		//clock_t st=clock();
		N=io.xint();L=io.xint();

		for(int i=1;i<=N;i++)
		{
			a[i]=io.xint();
			a[i]+=L;
		}
		for(int i=1;i<=N;i++)
			b[i]=io.xint();
		for(int i=N+1;i<=N*3;i++)
			b[i]=b[i-N]+L;

		for(int i=1;i<=N;i++)
		{
			l[i]=i==1?1:(l[i-1]+i-1);
			while(b[l[i]]<a[i]-L/2)
				l[i]++;
			l[i]-=i;
			r[i]=i==1?1:(r[i-1]+i-1);
			while(b[r[i]]<a[i]+1)
				r[i]++;
			r[i]-=i;
		}
		int bg=-INF,ed=INF;
		for(int i=1;i<=N;i++)
		{
			bg=max(bg,l[i]);
			ed=min(ed,l[i]+N);
		}

		for(int i=0;i<ed-bg;i++)
			g[i].clear();
		for(int i=1;i<=N;i++)
			g[0].push_back(a[i]);
		for(int i=1;i<=N;i++)
			if(r[i]<ed)
				g[max(0,r[i]-bg)].push_back(-2LL*a[i]);

		rb[bg]=a[1]<b[bg+1]?0:-1;
		for(int i=bg+1;i<3*N;i++)
		{
			rb[i]=rb[i-1];
			while(rb[i]<min(i-bg,N-1)&&a[rb[i]+2]<b[i+1])
				rb[i]++;
		}
		for(int i=bg;i<3*N;i++)
		{
			if(i-N+1<ed)
				g[max(i-N+1-bg,0)].push_back(-b[i+1]);
			if(rb[i]!=-1&&i-rb[i]<ed)
			{
				g[i-rb[i]-bg].push_back(2LL*b[i+1]);
				if(i+1<ed)
					g[i+1-bg].push_back(-b[i+1]);
			}
			else if(i+1<ed)
				g[i+1-bg].push_back(b[i+1]);
		}
		long long tmp=0,ans=LLF;
		for(int i=0;i<ed-bg;i++)
		{
			for(int j=0;j<(int)g[i].size();j++)
				tmp+=g[i][j];
			ans=min(ans,tmp);
		}
		printf("%I64d\n",ans);
		//printf("%dms\n",(int)(clock()-st));
	}

	return 0;
}
