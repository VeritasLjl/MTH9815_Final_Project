//
//  bondpositionservice.h
//  Trading System
//
//  Created by 廖佳珑 on 12/23/22.
//

#ifndef bondpositionservice_h
#define bondpositionservice_h

#include "soa.hpp"
#include "positionservice.hpp"
#include "products.hpp"
#include "util.hpp"


class BondPositionService: public PositionService<Bond>{
public:
    
    BondPositionService();
    
    // Get data on our service given a key
    Position<Bond>& GetData(string key) override;

    // The callback that a Connector should invoke for any new or updated data
    void OnMessage(Position<Bond> &data) override;

    // Add a listener to the Service for callbacks on add, remove, and update events
    // for data to the Service.
    void AddListener(ServiceListener<Position<Bond>> *listener) override;

    // Get all listeners on the Service.
    const vector< ServiceListener<Position<Bond>>* >& GetListeners() const override;
    
    void AddTrade(const Trade<Bond> &trade) override;

private:
    map<string, Position<Bond>*> positionBook;
    vector<ServiceListener<Position<Bond>>*> listenerBook;
};

BondPositionService::BondPositionService(){
    positionBook = std::map<string, Position<Bond>*>();
    listenerBook = std::vector<ServiceListener<Position<Bond>>*>();
}

Position<Bond>& BondPositionService::GetData(string key) {
    return *positionBook[key];
}

void BondPositionService::OnMessage(Position<Bond> &data){
    // Use product id as the key for the getting data function
    string key = data.GetProduct().GetProductId();
    if(positionBook.find(key)==positionBook.end()){
        if(DEBUG) std::cout << "ERROR  " << data.GetProduct() << std::endl;
    }
    else{
        // modify data
        if(DEBUG) std::cout << "UPDATE  RISK: " << data.GetProduct() << std::endl;
        
        for(auto i = listenerBook.begin(); i!=listenerBook.end(); i++){
            (*i)->ProcessUpdate(data);
        }
    }
}

void BondPositionService::AddListener(ServiceListener<Position<Bond>> *listener){
    listenerBook.push_back(listener);
}

const vector<ServiceListener<Position<Bond>>*>& BondPositionService::GetListeners() const{
    return listenerBook;
}

void BondPositionService::AddTrade(const Trade<Bond> &trade){
    Position<Bond>* p;
    if(positionBook.find(trade.GetProduct().GetProductId())!=positionBook.end())
        p = positionBook[trade.GetProduct().GetProductId()];
    else{
        Position<Bond> pb = Position<Bond>(trade.GetProduct());
//        positionBook.insert(pair<string, Position<Bond>*>(trade.GetProduct().GetProductId(),&pb));
        positionBook[trade.GetProduct().GetProductId()] = new Position<Bond>(trade.GetProduct());
        p = positionBook[trade.GetProduct().GetProductId()];
    }
    if(trade.GetSide() == BUY){
        p->BuyTrade(trade.GetBook(), trade.GetQuantity());
    }
    else{
        p->SellTrade(trade.GetBook(), trade.GetQuantity());
    }
    OnMessage(*p);
}

#endif /* bondpositionservice_h */
