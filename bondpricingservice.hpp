//
//  bondpricingservice.h
//  Trading System
//
//  Created by 廖佳珑 on 12/22/22.
//

#ifndef bondpricingservice_h
#define bondpricingservice_h

#include "soa.hpp"
#include "pricingservice.hpp"
#include "products.hpp"
#include "util.hpp"


class BondPricingService: public PricingService<Bond>{
public:
    
    BondPricingService();
    
    // Get data on our service given a key
    Price<Bond>& GetData(string key) override;

    // The callback that a Connector should invoke for any new or updated data
    void OnMessage(Price<Bond> &data) override;

    // Add a listener to the Service for callbacks on add, remove, and update events
    // for data to the Service.
    void AddListener(ServiceListener<Price<Bond>> *listener) override;

    // Get all listeners on the Service.
    const vector< ServiceListener<Price<Bond>>* >& GetListeners() const override;

private:
    
    map<string, Price<Bond>*> priceBook;
    vector<ServiceListener<Price<Bond>>*> listenerBook;
};

BondPricingService::BondPricingService(){
    priceBook = std::map<string, Price<Bond>*>();
    listenerBook = std::vector<ServiceListener<Price<Bond>>*>();
}

Price<Bond>& BondPricingService::GetData(string key) {
    return *priceBook[key];
}

void BondPricingService::OnMessage(Price<Bond> &data){
    // Use product id as the key for the getting data function
    string key = data.GetProduct().GetProductId();
    if(priceBook.find(key)==priceBook.end()){
        if(DEBUG) std::cout << "INSERT  " << data.GetProduct().GetProductId() << "  "<< data.GetMid()
            << "  " << data.GetBidOfferSpread() << std::endl;
        priceBook.insert(pair<string,Price<Bond>*>(key,new Price<Bond>(data)));
        
        for(auto i = listenerBook.begin(); i!=listenerBook.end(); i++){
            (*i)->ProcessUpdate(data);
        }
    }
    else if(data.GetMid()==0){
        // delete data
        if(DEBUG) std::cout << "DELETE  " << data.GetProduct().GetProductId() << "  "<< data.GetMid()
            << "  "<< data.GetBidOfferSpread() << std::endl;
        delete priceBook[key];
        priceBook.erase(key);
        
        for(auto i = listenerBook.begin(); i!=listenerBook.end(); i++){
            (*i)->ProcessUpdate(data);
        }
    }
    else{
        // modify data
        if(DEBUG) std::cout << "MODIFY  " << data.GetProduct().GetProductId() << "  "<< data.GetMid()
            << "  "<< data.GetBidOfferSpread() << std::endl;
        delete priceBook[key];
        priceBook[key] = new Price<Bond>(data);
        
        for(auto i = listenerBook.begin(); i!=listenerBook.end(); i++){
            (*i)->ProcessUpdate(data);
        }
    }
}

void BondPricingService::AddListener(ServiceListener<Price<Bond>> *listener){
    listenerBook.push_back(listener);
}

const vector<ServiceListener<Price<Bond>>*>& BondPricingService::GetListeners() const{
    return listenerBook;
}

#endif /* bondpricingservice_h */
