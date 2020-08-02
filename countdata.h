#ifndef COUNTDATA_H
#define COUNTDATA_H
#include <iostream>
#include <QtDebug>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>

using namespace std;

int getStringtarget(string &a);//获取头数据
void cutData(string &a,int len,string &data);//剪
bool emtyData(string &a);//判断是否还有数据；
void cutOpera(string &a,string &op);//获取操作符
void CountMain(string &a,float &ret);//主计算
double retTem(double ret,double next,string a);//计算值
void CountMain(string &a,double &ret,int opnum)
{
    double data[opnum + 1];
    string op[opnum];
    string datatem;

    for(int i = 0;i<=opnum;i++)
    {
        int n = getStringtarget(a);
        cutData(a,n,datatem);
        data[i] = atof(datatem.c_str());


        if(i != opnum)
        {
            cutOpera(a,op[i]);
        }

    }

        for(int i =0;i<=opnum;i++)
        {
            qDebug()<<data[i];
        }

        for(int i =0;i<opnum;i++)
        {
            qDebug()<<QString::fromStdString(op[i]);
        }

        ret =data[0];
        for(int i = 0;i<opnum;i++)
        { ret = retTem(ret,data[i+1],op[i]);}



}

int getStringtarget(string &a) //获取头数据长度
{
   int i = 0;
   int c = 0;
   while(1)
   {
       if(i == 0 && a[i] < 48)
       {
           i++;
       }
       else if(a[i] > 48 )
       {
           i++;

       }
       else if(a[i] == '.')
       {
           i++;
       }
       else if(a[i] == '0')
       {
           i++;
       }
       else {
           break;
       }
   }
   return i;
}

void cutData(string &a, int len, string &data)//剪数据
{
    data = a.substr(0,len);
//    qDebug()<<"cut :"<<QString::fromStdString(data)<<"len"<<len;
    a.erase(0,len);
}

bool emtyData(string &a)
{
    if(a == "")
        return true;
    else {
        return false;
    }
}

void cutOpera(string &a,string &op)//获取操作符
{
    op = a.substr(0,1);
    a.erase(0,1);
}
double retTem(double ret,double next,string a)//计算值
{
    if(a == "+")
        return ret+next;
    else if(a == "-")
        return ret-next;
    else if(a == "*")
        return ret*next;
    else if(a == "/")
        return ret/next;
    else {
        return -1;
    }
}

#endif // COUNTDATA_H
