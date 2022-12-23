//
//  bondtradebookingservice.h
//  Trading System
//
//  Created by 廖佳珑 on 12/22/22.
//

#ifndef bondtradebookingservice_h
#define bondtradebookingservice_h

#include "util.hpp"
#include "tradebookingservice.hpp"
#include "soa.hpp"
#include "products.hpp"

class BondTradeBookingService:public TradeBookingService<Bond>{
public:
    BondTradeBookingService();
    
    void BookTrade(Trade<Bond> &data) override;
    
    // Get data on our service given a key
    Trade<Bond>& GetData(string key) override;

    // The callback that a Connector should invoke for any new or updated data
    void OnMessage(Trade<Bond> &data) override;

    // Add a listener to the Service for callbacks on add, remove, and update events
    // for data to the Service.
    void AddListener(ServiceListener<Trade<Bond>> *listener) override;

    // Get all listeners on the Service.
    const vector< ServiceListener<Trade<Bond>>* >& GetListeners() const override;
    
private:
    std::map<string,Trade<Bond>*> tradeBook;
    std::vector<ServiceListener<Trade<Bond>>*> listenerBook;
};

BondTradeBookingService::BondTradeBookingService(){
    tradeBook = std::map<string,Trade<Bond>*>();
    listenerBook = std::vector<ServiceListener<Trade<Bond>>*>();
}

void BondTradeBookingService::BookTrade(Trade<Bond> &data){
    string key = data.GetTradeId();
    tradeBook[key] = new Trade<Bond>(data);
    OnMessage(*tradeBook[key]);
}

Trade<Bond>& BondTradeBookingService::GetData(string key) {
    return *tradeBook[key];
}

void BondTradeBookingService::OnMessage(Trade<Bond> &data){
    // Use product id as the key for the getting data function
    for(auto i = listenerBook.begin(); i!=listenerBook.end(); i++){
        (*i)->ProcessUpdate(data);
    }
}

void BondTradeBookingService::AddListener(ServiceListener<Trade<Bond>> *listener){
    listenerBook.push_back(listener);
}

const vector<ServiceListener<Trade<Bond>>*>& BondTradeBookingService::GetListeners() const{
    return listenerBook;
}

#endif /* bondtradebookingservice_h */
