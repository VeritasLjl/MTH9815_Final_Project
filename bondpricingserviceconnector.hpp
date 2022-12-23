//
//  bondpricingserviceconnector.h
//  Trading System
//
//  Created by 廖佳珑 on 12/23/22.
//

#ifndef bondpricingserviceconnector_h
#define bondpricingserviceconnector_h

#include "soa.hpp"
#include "util.hpp"
#include "bondpricingservice.hpp"

class BondPricingSerciveConnector:public Connector<Bond>{
    BondPricingService* bps;
public:
    BondPricingSerciveConnector(BondPricingService* _bps):bps(_bps){}
    void Publish(Bond& data) override;
    void Subscribe(string filename);
};

void BondPricingSerciveConnector::Publish(Bond &data){
    std::cout<<bps->GetData(data.GetProductId()).GetMid()<<"    " << bps->GetData(data.GetProductId()).GetBidOfferSpread() <<endl;
}

void BondPricingSerciveConnector::Subscribe(string filename = "prices.txt"){
    string s = PATH + filename;
    ifstream input;
    input.open(s);
    
    string product,price,spread;
    while(true){
        input>>product>>price>>spread;
        if(input.eof())break;
        SECURITY sec = SecurityFromStr(product);
        Bond b = Bond(Security(sec), CUSIP, "T", bondCoupon[NumFromSecurity(sec)], bondMaturity[NumFromSecurity(sec)]);
        Price<Bond> data = Price<Bond>(b, FracData(price), FracData(spread));
        bps->OnMessage(data);
    }
    input.close();
}

#endif /* bondpricingserviceconnector_h */
