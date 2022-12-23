//
//  data.h
//  Trading System
//
//  Created by 廖佳珑 on 12/22/22.
//

#ifndef data_h
#define data_h


#include "util.hpp"
#include <random>
#include <fstream>

using namespace std;

string randomPrice(){
    int a=0,b=0,c=0;
    int rdn = rand()%513;
    a = floor(rdn/256)+99;
    rdn -= (a-99)*256;
    b = floor(rdn/8);
    c = rdn - b*8;
    string rst = "000-xyz";
    rst[0] = char(floor(a/100)+'0');
    rst[1] = char(floor(floor(a%100)/10)+'0');
    rst[2] = char(floor(a%10)+'0');
    rst[4] = char(floor(b/10)+'0');
    rst[5] = char(floor(b%10)+'0');
    rst[6] = char(floor(c)+'0');
    return rst;
}

string randomBidOfferSpread(){
    int rdn = rand()%4+1;
    string rst = "000-000";
    rst[6] = char(rdn+'0');
    return rst;
}

void BondPriceGenerator(string filename="prices.txt", int N = 1000000){
    filename = PATH+filename;
    if(DEBUG) N = 1000;
    ofstream output;
    output.open(filename);
    for(int i=0;i<N;i++){
        for(int j=0; j<SECURITYNUM; j++){
            string s1 = Security(SecurityFromNum(j));
            string s2 = randomPrice();
            string s3 = randomBidOfferSpread();
            string s = s1+" "+s2+" "+s3+"\n";
            output << s;
            
        }
    }
    output.close();
}

string randomTransactionPrice(){
    int a=0,b=0,c=0;
    int rdn = rand()%257;
    a = floor(rdn/256)+99;
    rdn -= (a-99)*256;
    b = floor(rdn/8);
    c = rdn - b*8;
    string rst = "000-xyz";
    rst[0] = char(floor(a/100)+'0');
    rst[1] = char(floor(floor(a%100)/10)+'0');
    rst[2] = char(floor(a%10)+'0');
    rst[4] = char(floor(b/10)+'0');
    rst[5] = char(floor(b%10)+'0');
    rst[6] = char(floor(c)+'0');
    return rst;
}

int GetTradeID(){
    static int c=0;
    return c++;
}

void BondTradeGenerator(string filename="trades.txt", int N = 70){
    int cycle = 0;
    ofstream output;
    filename = PATH+filename;
    output.open(filename);
    
    for(int i=0; i<SECURITYNUM; i++){
        for(int j=0;j<10; j++){
            output << Security(SecurityFromNum(i)) << " ";
            output << "TRD" << GetTradeID() << "  "; // tradeid
            output << randomTransactionPrice() << "  ";
            switch(cycle%3){
                case 0: output << "TRSY1" << "  "; break;
                case 1: output << "TRSY2" << "  "; break;
                case 2: output << "TRSY3" << "  "; break;
            }
            output << (cycle%5+1)*1000000 << "  "; // quantity
            if(cycle%2) output << "BUY" << endl;
            else output << "SELL" << endl;
            cycle++;
        }
    }
    output.close();
}

string randomMarketData(int count){
    int a=0,b=0,c=0;
    int spread = (count%8) + 1;
    spread = MIN(spread,8-spread);
    int mid = count%512;
    mid = MIN(count,512-count);
    int rdn = (mid+spread)%256;
    rdn = (rdn+256)%256;
    a = floor(rdn/256)+99;
    rdn -= (a-99)*256;
    b = floor(rdn/8);
    c = rdn - b*8;
    string rst1 = "000-xyz";
    rst1[0] = char(floor(a/100)+'0');
    rst1[1] = char(floor(floor(a%100)/10)+'0');
    rst1[2] = char(floor(a%10)+'0');
    rst1[4] = char(floor(b/10)+'0');
    rst1[5] = char(floor(b%10)+'0');
    rst1[6] = char(floor(c)+'0');
    
    rdn = (mid-spread)%256;
    rdn = (rdn+256)%256;
    a = floor(rdn/256)+99;
    rdn -= (a-99)*256;
    b = floor(rdn/8);
    c = rdn - b*8;
    string rst2 = "000-xyz";
    rst2[0] = char(floor(a/100)+'0');
    rst2[1] = char(floor(floor(a%100)/10)+'0');
    rst2[2] = char(floor(a%10)+'0');
    rst2[4] = char(floor(b/10)+'0');
    rst2[5] = char(floor(b%10)+'0');
    rst2[6] = char(floor(c)+'0');
    return rst1+rst2+to_string(spread);
}

void BondMarketDateGenerator(string filename="marketdata.txt", int N = 1000000){
    if(DEBUG) N = 10000;
    ofstream output;
    filename = PATH+filename;
    output.open(filename);
    
    for(int i=0;i<N;i++){
        for(int j=0; j<SECURITYNUM; j++){
            string s1 = Security(SecurityFromNum(j));
            string s2 = randomMarketData(i);
            string s3 = "OFFER";
            string s4 = s2.substr(14,1)+"0000000";
            string s = s1+" "+s2.substr(0,7)+" "+s3+" "+s4+"\n";
            output << s;
            s3 = "BID";
            s = s1+" "+s2.substr(7,7)+" "+s3+" "+s4+"\n";
            output << s;
        }
    }
    output.close();
}

#endif /* data_h */
