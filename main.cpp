#include "cacheLRU.h"
#include <ctime>
#include <climits>
#include <iostream>
using namespace std;

int main()
{
    srand(time(NULL));
    int len=10000;
    cacheLRU<int,int> big(1024);
    for(int i=0;i<len;i++)
    {
        int rn=rand()%INT_MAX;
        big.put(make_pair(rn,rn));
    }
    cout<<"big size:"<<len<<"\t\tcapacity:"<<big.getCapa()<<"\t\tdel times:"<<big.getTimsDel()<<"\t\t"<<"rotations time:"<<big.getTimesLeftRotation()+big.getTimesRightRotation()<<"\t\taver rotation each item:"<<(double)(big.getTimesLeftRotation()+big.getTimesRightRotation())/len<<endl;
    srand(time(NULL));
    len=1000;
    cacheLRU<int,int> med0(128);
    for(int i=0;i<len;i++)
    {
        int rn=rand()%INT_MAX;
        med0.put(make_pair(rn,rn));
    }
    cout<<"med0 size:"<<len<<"\t\tcapacity:"<<med0.getCapa()<<"\t\tdel times:"<<med0.getTimsDel()<<"\t\t"<<"rotations time:"<<med0.getTimesLeftRotation()+med0.getTimesRightRotation()<<"\t\taver rotation each item:"<<(double)(med0.getTimesLeftRotation()+med0.getTimesRightRotation())/len<<endl;
    srand(time(NULL));
    len=1000;
    cacheLRU<int,int> med1(128);
    for(int i=0;i<len;i++)
    {
        int rn=rand()%CHAR_MAX;
        med1.put(make_pair(rn,rn));
    }
    cout<<"med1 size:"<<len<<"\t\tcapacity:"<<med1.getCapa()<<"\t\tdel times:"<<med1.getTimsDel()<<"\t\t"<<"rotations time:"<<med1.getTimesLeftRotation()+med1.getTimesRightRotation()<<"\t\taver rotation each item:"<<(double)(med1.getTimesLeftRotation()+med1.getTimesRightRotation())/len<<endl;
    return 0;
}
