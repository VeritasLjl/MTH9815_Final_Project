//
//  bondalgoexecutionservice.h
//  Trading System
//
//  Created by 廖佳珑 on 12/23/22.
//

#ifndef bondalgoexecutionservice_h
#define bondalgoexecutionservice_h

#include "util.hpp"
#include "soa.hpp"
#include "products.hpp"
#include "executionservice.hpp"

template<typename T>
class AlgoExecution{
public:
    ExecutionOrder<T>& GetExecutionOrder()const{
        return executionOrder;
    }
    string GetOrderID() const{
        return orderId;
    }
    AlgoExecution(string _orderId, ExecutionOrder<T> _executionOrder):orderId(_orderId), executionOrder(_executionOrder){}
private:
    string orderId;
    ExecutionOrder<T> executionOrder;
};

class BondAlgoExecutionService:public Service<string, ExecutionOrder<Bond>>{
public:
    // Get data on our service given a key
    ExecutionOrder<Bond>& GetData(string key) override;

    // The callback that a Connector should invoke for any new or updated data
    void OnMessage(ExecutionOrder<Bond> &data) override;

    // Add a listener to the Service for callbacks on add, remove, and update events
    // for data to the Service.
    void AddListener(ServiceListener<ExecutionOrder<Bond>> *listener) override;

    // Get all listeners on the Service.
    const vector< ServiceListener<ExecutionOrder<Bond>>* >& GetListeners() const override;
    
    void Cross(OrderBook<Bond>& data);
    
private:
    map<string,ExecutionOrder<Bond>*> bondAlgoExecutionBook;
    vector<ServiceListener<ExecutionOrder<Bond>>*> listenerBook;
};

ExecutionOrder<Bond>& BondAlgoExecutionService::GetData(string key) {
    return *bondAlgoExecutionBook[key];
}

void BondAlgoExecutionService::OnMessage(ExecutionOrder<Bond> &data){
    // Use product id as the key for the getting data function
    string key = data.GetOrderId();
    for(auto i = listenerBook.begin(); i!=listenerBook.end(); i++){
        (*i)->ProcessUpdate(data);
    }
}

void BondAlgoExecutionService::AddListener(ServiceListener<ExecutionOrder<Bond>> *listener){
    listenerBook.push_back(listener);
}

const vector<ServiceListener<ExecutionOrder<Bond>>*>& BondAlgoExecutionService::GetListeners() const{
    return listenerBook;
}

void BondAlgoExecutionService::Cross(OrderBook<Bond>& data){
    if(data.GetBidStack()[0].GetPrice()<data.GetOfferStack()[0].GetPrice())
        return;
    else{
        string orderId = GetOrderId();
        double price = data.GetBidStack()[0].GetPrice();
        double qty = MIN(data.GetBidStack()[0].GetQuantity(),data.GetBidStack()[1].GetQuantity());
        bondAlgoExecutionBook[orderId] = new ExecutionOrder<Bond>(data.GetProduct(), BID, orderId, FOK, price, qty, 0, "", false);
        OnMessage(*bondAlgoExecutionBook[orderId]);
    }
}
#endif /* bondalgoexecutionservice_h */
