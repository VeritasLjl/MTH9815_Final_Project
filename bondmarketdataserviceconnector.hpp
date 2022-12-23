//
//  bondmarketdataserviceconnector.h
//  Trading System
//
//  Created by 廖佳珑 on 12/23/22.
//

#ifndef bondmarketdataserviceconnector_h
#define bondmarketdataserviceconnector_h

#include "soa.hpp"
#include "util.hpp"
#include "marketdataservice.hpp"

class BondMarketDataServiceConnector:public Connector<Bond>{
    BondMarketDataService* bps;
public:
    BondMarketDataServiceConnector(BondMarketDataService* _bps):bps(_bps){}
    void Publish(Bond& data) override;
    void Subscribe(string filename);
};

void BondMarketDataServiceConnector::Publish(Bond &data){
    std::cout<< data.GetProductId() <<endl;
}

void BondMarketDataServiceConnector::Subscribe(string filename = "marketdata.txt"){
    string s = PATH + filename;
    ifstream input;
    input.open(s);
    
    string product1,price1,bo1,qty1,product2,price2,bo2,qty2;
    while(true){
        input>>product1>>price1>>bo1>>qty1;
        input>>product2>>price2>>bo2>>qty2;
        assert(product1 == product2);
        if(input.eof())break;
        SECURITY sec = SecurityFromStr(product1);
        Bond b = Bond(Security(sec), CUSIP, "T", bondCoupon[NumFromSecurity(sec)], bondMaturity[NumFromSecurity(sec)]);
        Order data1 = Order(FracData(price1), stoi(qty1), (bo1=="BID")?BID:OFFER);
        Order data2 = Order(FracData(price2), stoi(qty2), (bo2=="BID")?BID:OFFER);
        vector<Order> bs{(bo1=="BID")?data1:data2};
        vector<Order> os{(bo1=="OFFER")?data1:data2};
        auto ob = OrderBook<Bond>(b,bs,os);
        bps->OnMessage(ob);
    }
    input.close();
}

#endif /* bondmarketdataserviceconnector_h */
