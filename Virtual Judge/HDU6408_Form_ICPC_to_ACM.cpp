#include<cstdio>
#include<set>
using namespace std;
const int MAXK=50005;

struct Plan
{
    long long val;
    mutable int num;
    Plan()=default;
    Plan(long long _val,int _num):val(_val),num(_num){}
    bool operator < (const Plan &t)const
    {return val<t.val;}
};

int k;
int c[MAXK],d[MAXK],m[MAXK],p[MAXK],e[MAXK],R[MAXK],E[MAXK];
long long sumR[MAXK],sumE[MAXK];
long long costC[MAXK];
multiset<Plan> warehouse;
int content;

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&k);
        for(int i=1;i<=k;i++)
            scanf("%d%d%d%d",&c[i],&d[i],&m[i],&p[i]);
        for(int i=1;i<k;i++)
        {
            scanf("%d%d%d",&e[i],&R[i],&E[i]);
            sumR[i+1]=sumR[i]+R[i];
            sumE[i+1]=sumE[i]+E[i];
        }

        long long mnC=c[1];
        for(int i=1;i<=k;i++)
        {
            mnC=min(mnC,c[i]-sumR[i]);
            costC[i]=mnC+sumR[i];
        }

        long long ans=0;
        bool success=true;
        content=0;
        warehouse.clear();
        for(int i=1;i<=k;i++)
        {
            warehouse.insert(Plan(costC[i]+m[i]-sumE[i],p[i]));
            content+=p[i];
            while(!warehouse.empty()&&d[i])
            {
                auto it=warehouse.begin();
                int delta=min(d[i],it->num);
                ans+=1LL*delta*(it->val+sumE[i]);
                it->num-=delta;
                d[i]-=delta;
                content-=delta;
                if(it->num==0)
                    warehouse.erase(it);
            }
            if(d[i])
            {
                success=false;
                break;
            }
            while(content>e[i])
            {
                auto it=warehouse.end();
                it--;
                int delta=min(it->num,content-e[i]);
                it->num-=delta;
                content-=delta;
                if(it->num==0)
                    warehouse.erase(it);
            }
        }
        if(!success)
            puts("-1");
        else
            printf("%I64d\n",ans);
    }

    return 0;
}
