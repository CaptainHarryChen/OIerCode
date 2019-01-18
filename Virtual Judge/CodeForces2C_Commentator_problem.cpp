#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<algorithm>
using namespace std;
const int dir[4][2]={{0,-1},{1,0},{-1,0},{0,1}};

struct Point
{
    double x,y;
    Point(){}
    Point(double x,double y):x(x),y(y){}
};
struct Circle
{
    Point O;
    double r;
};

Circle C[3];
double dis(Point u,Point v)
{return sqrt((u.x-v.x)*(u.x-v.x)+(u.y-v.y)*(u.y-v.y));}
double Value(Point u)
{
    double ang[3],res=0;
    for(int i=0;i<3;i++)
        ang[i]=C[i].r/dis(u,C[i].O);
    for(int i=0;i<3;i++)
        res+=(ang[i]-ang[(i+1)%3])*(ang[i]-ang[(i+1)%3]);
    return res;
}
bool check(Point u)
{
    bool flag=true;
    for(int i=0;i<3;i++)
    {
        double x1=C[i].O.x-u.x,y1=C[i].O.y-u.y;
        double x2=C[(i+1)%3].O.x-u.x,y2=C[(i+1)%3].O.y-u.y;
        if(x1*y2-y1*x2>0)
        {flag=false;break;}
    }
    if(flag)return true;
    for(int i=0;i<3;i++)
    {
        double x1=C[i].O.x-u.x,y1=C[i].O.y-u.y;
        double x2=C[(i+1)%3].O.x-u.x,y2=C[(i+1)%3].O.y-u.y;
        if(x1*y2-y1*x2<0)
        {flag=false;break;}
    }
    return flag;
}

int main()
{
    srand(time(0));

    for(int i=0;i<3;i++)
        scanf("%lf%lf%lf",&C[i].O.x,&C[i].O.y,&C[i].r);

    Point u,v,ansP;
    double now,ans,T=2;
    //for(int i=0;i<3;i++)
   //     T=max(T,max(abs(C[i].O.x-C[(i+1)%3].O.x),abs(C[i].O.y-C[(i+1)%3].O.y)));
    u.x=(C[0].O.x+C[1].O.x+C[2].O.x)/3;
    u.y=(C[0].O.y+C[1].O.y+C[2].O.y)/3;
    now=ans=Value(u);ansP=u;
    check(u);
    int cnt=0;
    while(ans>1e-20)
    {
        //printf("%.30f\n",ans);
        cnt++;
        if(cnt>100000)
            break;
        for(int d=0;d<4;d++)
        {
            v.x=u.x+dir[d][0]*T;
            v.y=u.y+dir[d][1]*T;
            //if(!check(v))
            //    continue;
            double nans=Value(v),possibility=exp((now-nans)/T*1e20);
            if(rand()<=possibility*RAND_MAX)
            {
                u=v;
                now=nans;
                if(now<ans)
                    ans=now,ansP=u;
                break;
            }
        }
        T*=0.999;
    }

    if(ans<1e-20)
        printf("%.5f %.5f\n",ansP.x,ansP.y);

    return 0;
}
