//
//  bondmarketdataservice.h
//  Trading System
//
//  Created by 廖佳珑 on 12/23/22.
//

#ifndef bondmarketdataservice_h
#define bondmarketdataservice_h

#include "soa.hpp"
#include "marketdataservice.hpp"
#include "products.hpp"
#include "util.hpp"


class BondMarketDataService: public MarketDataService<Bond>{
public:
    
    BondMarketDataService();
    
    // Get data on our service given a key
    OrderBook<Bond>& GetData(string key) override;

    // The callback that a Connector should invoke for any new or updated data
    void OnMessage(OrderBook<Bond> &data) override;

    // Add a listener to the Service for callbacks on add, remove, and update events
    // for data to the Service.
    void AddListener(ServiceListener<OrderBook<Bond>> *listener) override;

    // Get all listeners on the Service.
    const vector< ServiceListener<OrderBook<Bond>>* >& GetListeners() const override;
    
    // Get the best bid/offer order
    const BidOffer& GetBestBidOffer(const string &productId) override;

    // Aggregate the order book
    const OrderBook<Bond>& AggregateDepth(const string &productId) override;

private:
    map<string, OrderBook<Bond>*> marketDataBook;
    vector<ServiceListener<OrderBook<Bond>>*> listenerBook;
};

BondMarketDataService::BondMarketDataService(){
    marketDataBook = std::map<string, OrderBook<Bond>*>();
    listenerBook = std::vector<ServiceListener<OrderBook<Bond>>*>();
}

OrderBook<Bond>& BondMarketDataService::GetData(string key) {
    return *marketDataBook[key];
}

void BondMarketDataService::OnMessage(OrderBook<Bond> &data){
    // Use product id as the key for the getting data function
    string key = data.GetProduct().GetProductId();
    if(marketDataBook.find(key)==marketDataBook.end()){
        marketDataBook[key] = new OrderBook<Bond>(data.GetProduct(),data.GetBidStack(),data.GetOfferStack());
    }
    else{
        marketDataBook[key]->expand(data);
        for(auto i = listenerBook.begin(); i!=listenerBook.end(); i++){
            (*i)->ProcessUpdate(data);
        }
    }
}

void BondMarketDataService::AddListener(ServiceListener<OrderBook<Bond>> *listener){
    listenerBook.push_back(listener);
}

const vector<ServiceListener<OrderBook<Bond>>*>& BondMarketDataService::GetListeners() const{
    return listenerBook;
}

// Get the best bid/offer order
const BidOffer& BondMarketDataService::GetBestBidOffer(const string &productId) {
    OrderBook<Bond>*  ob = marketDataBook[productId];
    return BidOffer(ob->GetBidStack()[0], ob->GetOfferStack()[0]);
}

// Aggregate the order book
const OrderBook<Bond>& BondMarketDataService::AggregateDepth(const string &productId) {
    return *marketDataBook[productId];
}

#endif /* bondmarketdataservice_h */
