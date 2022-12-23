//
//  bondtradebookingserviceconnector.h
//  Trading System
//
//  Created by 廖佳珑 on 12/23/22.
//

#ifndef bondtradebookingserviceconnector_h
#define bondtradebookingserviceconnector_h

#include "soa.hpp"
#include "util.hpp"
#include "bondtradebookingservice.hpp"

class BondTradeBookingServiceConnector:public Connector<Bond>{
    BondTradeBookingService* btps;
public:
    BondTradeBookingServiceConnector(BondTradeBookingService* _btps):btps(_btps){}
    void Publish(Bond& data) override;
    void Subscribe(string filename);
};

void BondTradeBookingServiceConnector::Publish(Bond &data){
    std::cout<< btps->GetData(data.GetProductId()).GetTradeId() <<endl;
}



void BondTradeBookingServiceConnector::Subscribe(string filename = "trades.txt"){
    string s = PATH + filename;
    ifstream input;
    input.open(s);
    
    string product,tradeid,price,book,quantity,side;
    while(!input.eof()){
        input >> product >> tradeid >> price >> book >> quantity >> side;
        SECURITY sec = SecurityFromStr(product);
        Bond b = Bond(Security(sec), CUSIP, "T", bondCoupon[NumFromSecurity(sec)], bondMaturity[NumFromSecurity(sec)]);
        Side _side = (side=="BUY")?BUY:SELL;
        long qty = stoi(quantity);
        Trade<Bond> data = Trade<Bond>(b, tradeid, FracData(price), book, qty, _side);
        btps->BookTrade(data);
    }
    input.close();
}

#endif /* bondtradebookingserviceconnector_h */
