#include<cstdio>
#include<ctime>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=105;
const int dir[4][2]={{0,1},{1,0},{-1,0},{0,-1}};
const double EPS=1e-3;

struct Point
{
    double x,y;
};

int n;
Point P[MAXN];

double Anneal()
{
    double dis=0,ans;
    Point u=P[rand()%n+1],v;
    for(int i=1;i<=n;i++)
        dis+=sqrt((u.x-P[i].x)*(u.x-P[i].x)+(u.y-P[i].y)*(u.y-P[i].y));
    ans=dis;
    double t=5000;
    while(t>EPS)
    {
        for(int d=0;d<4;d++)
        {
            v.x=u.x+dir[d][0]*t;
            v.y=u.y+dir[d][1]*t;
            double sum=0;
            for(int i=1;i<=n;i++)
                sum+=sqrt((v.x-P[i].x)*(v.x-P[i].x)+(v.y-P[i].y)*(v.y-P[i].y));
            double posibility=exp((dis-sum)*t);
            //if(posibility>1.0)
            //printf("Mush happened: (%.0f,%.0f)->(%.0f,%.0f)  dis:%.0f->%.0f\n",u.x,u.y,v.x,v.y,dis,sum);
            if(rand()%100000<=posibility*100000)
            {
                ans=min(ans,sum);
                dis=sum;
                u=v;
                break;
            }
        }
        t*=0.98;
    }
    return ans;
}

int main()
{
    srand(time(0));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lf%lf",&P[i].x,&P[i].y);
    double ans=1e100;
    for(int i=1;i<=100;i++)
        ans=min(ans,Anneal());
    printf("%.0f\n",ans);

    return 0;
}
