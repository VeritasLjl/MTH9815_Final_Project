//
//  util.h
//  Trading System
//
//  Created by 廖佳珑 on 12/22/22.
//

#ifndef util_h
#define util_h

#include <vector>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <math.h>
#include <iostream>
#include <fstream>

#define MAX(a,b) ((a<b)?b:a)
#define MIN(a,b) ((a<b)?a:b)
#define AVG(a,b) ((a+b)/2)
#define DEBUG 1 // 0 for RUN, 1 for DEBUG
#define SECURITYNUM 7
#define PATH "/Users/liaojialong/Desktop/Baruch/LEARNING/2022FALL/MTH9815 Software Engineering for Finance/tradingsystem/Trading System/Trading System/"
#define d32 (1.0/32)
#define d256 (1.0/256)

enum SECURITY{Y2,Y3,Y5,Y7,Y10,Y20,Y30};

void init(){
    std::cout << fixed << setprecision(8);
}

SECURITY SecurityFromStr(string s){
    if(s=="2Y")return Y2;
    if(s=="3Y")return Y3;
    if(s=="5Y")return Y5;
    if(s=="7Y")return Y7;
    if(s=="10Y")return Y10;
    if(s=="20Y")return Y20;
    if(s=="30Y")return Y30;
    return Y2;
}

SECURITY SecurityFromNum(int s){
    switch(s){
        case 0:return Y2;break;
        case 1:return Y3;break;
        case 2:return Y5;break;
        case 3:return Y7;break;
        case 4:return Y10;break;
        case 5:return Y20;break;
        case 6:return Y30;break;
    }
    return Y2;
}

int NumFromSecurity(SECURITY s){
    switch(s){
        case 0:return Y2;break;
        case 1:return Y3;break;
        case 2:return Y5;break;
        case 3:return Y7;break;
        case 4:return Y10;break;
        case 5:return Y20;break;
        case 6:return Y30;break;
    }
    return -1;
}

string Security(SECURITY s){
    switch(s){
        case Y2:return "2Y";break;
        case Y3:return "3Y";break;
        case Y5:return "5Y";break;
        case Y7:return "7Y";break;
        case Y10:return "10Y";break;
        case Y20:return "20Y";break;
        case Y30:return "30Y";break;
    }
}

double FracData(string s){
    int a = (int)(s[0]-'0') * 100 + (int)(s[1]-'0') * 10 + (int)(s[2]-'0') * 1;
    int b = (int)(s[4]-'0') * 10 + (int)(s[5]-'0') * 1;
    int c = (int)(s[6]-'0') * 1;
    if(s[6]=='+')
        c = 4;
    double rst = a+b*d32+c*d256;
    return rst;
}

string GetOrderId(){
    static int c = 0;
    c++;
    return "ORD"+to_string(c);
}

#endif /* util_h */
