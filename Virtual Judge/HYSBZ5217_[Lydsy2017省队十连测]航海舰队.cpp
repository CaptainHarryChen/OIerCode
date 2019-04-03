#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=705,MAXLEN=MAXN*MAXN*3;
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
const double PI=acos(-1);

struct cpx
{
    double r,i;
    cpx(){}
    cpx(double a,double b):r(a),i(b){}
    cpx operator + (const cpx &t)const
    {return cpx(r+t.r,i+t.i);}
    cpx operator - (const cpx &t)const
    {return cpx(r-t.r,i-t.i);}
    cpx operator * (const cpx &t)const
    {return cpx(r*t.r-i*t.i,r*t.i+i*t.r);}
    cpx operator / (double k)const
    {return cpx(r/k,i/k);}
};

void FFT(cpx A[],int n,int mode)
{
    for(int i=0,j=0;i<n;i++)
    {
        if(i<j)
            swap(A[i],A[j]);
        for(int k=n>>1;j^=k,~j&k;k>>=1);
    }
    for(int i=1;i<n;i<<=1)
    {
        cpx w1=cpx(cos(PI/i),mode*sin(PI/i));
        for(int j=0;j<n;j+=(i<<1))
        {
            cpx w=cpx(1,0);
            for(int l=j,r=j+i;l<j+i;l++,r++,w=w*w1)
            {
                cpx tmp=A[r]*w;
                A[r]=A[l]-tmp;
                A[l]=A[l]+tmp;
            }
        }
    }
    if(mode==-1)
        for(int i=0;i<n;i++)
            A[i]=A[i]/n;
}

int n,m,h,w,len;
int mnx,mny,mxx,mxy;
char mp[MAXN][MAXN];
bool vis[MAXN][MAXN];

cpx ree[MAXLEN],fle[MAXLEN],mov[MAXLEN];

void GetReef()
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(mp[i][j]=='#')
                ree[(n-i)*m+(m-j)].r=1;
    /*printf("Reef  :");
    for(int i=0;i<n*m;i++)
        printf("%2.0f%c",ree[i].r," \n"[i==n*m-1]);*/
}
void GetFleet()
{
    mnx=n+1,mny=m+1,mxx=0,mxy=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(mp[i][j]=='o')
            {
                mnx=min(mnx,i);
                mny=min(mny,j);
                mxx=max(mxx,i);
                mxy=max(mxy,j);
            }
    h=mxx-mnx+1;w=mxy-mny+1;
    for(int i=mnx;i<=mxx;i++)
        for(int j=mny;j<=mxy;j++)
            if(mp[i][j]=='o')
                fle[(i-mnx)*m+(j-mny)].r=1;
    /*printf("Fleet :");
    for(int i=0;i<n*m;i++)
        printf("%2.0f%c",fle[i].r," \n"[i==n*m-1]);*/
}
void BFS()
{
    static pair<int,int> q[MAXN*MAXN];
    static int hd,tl;
    hd=1;tl=0;
    q[++tl]=make_pair(mnx,mny);
    vis[mnx][mny]=true;
    while(hd<=tl)
    {
        pair<int,int> u=q[hd++];
        for(int d=0;d<4;d++)
        {
            pair<int,int> v=make_pair(u.first+dir[d][0],u.second+dir[d][1]);
            if(v.first<=0||v.second<=0||v.first+h-1>n||v.second+w-1>m||vis[v.first][v.second])
                continue;
            if((int)floor(ree[n*m-(v.first*m+v.second-m)].r+0.5)!=0)
                continue;
            vis[v.first][v.second]=true;
            q[++tl]=v;
        }
    }
}
void GetMove()
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(vis[i][j])
                mov[i*m+j-m-1].r=1;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%s",mp[i]+1);

    for(len=1;len<n*m*2-1;len<<=1);

    GetReef();
    GetFleet();

    FFT(ree,len,1);
    FFT(fle,len,1);
    for(int i=0;i<len;i++)
        ree[i]=ree[i]*fle[i];
    FFT(ree,len,-1);

    /*printf("Result:");
    for(int i=0;i<n*m*2-1;i++)
        printf("%2.0f%c",ree[i].r," \n"[i==n*m*2-2]);*/

    BFS();

    GetMove();

    FFT(mov,len,1);
    for(int i=0;i<len;i++)
        mov[i]=mov[i]*fle[i];
    FFT(mov,len,-1);

    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(mp[i][j]!='#'&&(int)floor(mov[i*m+j-m-1].r+0.5)!=0)
                ans++;
    printf("%d\n",ans);

    fclose(stdin);
    fclose(stdout);
    return 0;
}
