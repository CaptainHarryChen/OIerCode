#include<cstdio>
#include<cmath>

int main()
{
    int T,ans;
    double a,b,c,x,y,sn,cs,tn;
    double vx,vy,tx,ty,t,v,ang;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lf%lf%lf%lf",&a,&b,&x,&y);
        c=sqrt(a*a+b*b);
        sn=b/c;cs=a/c;tn=b/a;
        
        ans=0;
        tx=x;
        ty=-x/a*b;
        vx=0;
        vy=sqrt(2.0*9.8*(y-ty));
        
        vx+=vy*2.0*sn*cs;
        vy=-vy*(cs*cs-sn*sn);
        
        x=tx;y=ty;
        
        while(x<0.0)
        {
            ans++;
            #ifdef DEBUG
            fprintf(stderr,"The %dth bounce: pos:(%lf , %lf) , speed(%lf , %lf)\n",ans,x,y,vx,vy);
            #endif
            t=(2.0*vx*b-2.0*vy*a)/(9.8*a);
            #ifdef DEBUG
            //fprintf(stderr,"Check equation:%lf\n",(vy+9.8/2*t)/vx);
            fprintf(stderr,"time:%lf\n",t);
            #endif
            tx=vx*t;
            ty=vy*t+9.8*t*t/2.0;
            
            vx=vx;
            vy+=9.8*t;
            
            v=sqrt(vx*vx+vy*vy);
            ang=atan(vy/vx);
            ang=ang-2.0*atan(b/a);
            vx=v*cos(ang);
            vy=-v*sin(ang);
            /*
            vx+=vy*2.0*sn*cs;
            vy=-vy*(cs*cs-sn*sn);
            */
            x+=tx;
            y-=ty;
        }
        
        printf("%d\n",ans);
    }
    return 0;
}