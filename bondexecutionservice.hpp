//
//  bondexecutionservice.h
//  Trading System
//
//  Created by 廖佳珑 on 12/23/22.
//

#ifndef bondexecutionservice_h
#define bondexecutionservice_h

#include <string>
#include "soa.hpp"
#include "data.hpp"
#include "executionservice.hpp"
#include "bondtradebookingservice.hpp"
#include "util.hpp"

class BondExecutionService:public Service<string, Trade<Bond>>{
public:
    // Get data on our service given a key
    Trade<Bond>& GetData(string key) override;

    // The callback that a Connector should invoke for any new or updated data
    void OnMessage(Trade<Bond> &data) override;

    // Add a listener to the Service for callbacks on add, remove, and update events
    // for data to the Service.
    void AddListener(ServiceListener<Trade<Bond>> *listener) override;

    // Get all listeners on the Service.
    const vector< ServiceListener<Trade<Bond>>* >& GetListeners() const override;
    
    void AddExecution(ExecutionOrder<Bond>& data);
private:
    map<string, Trade<Bond>*> executionBook;
    vector<ServiceListener<Trade<Bond>>*> listenerBook;
};

void BondExecutionService::AddExecution(ExecutionOrder<Bond> &data){
    string tid = "TRD"+to_string(GetTradeID());
    string book = "TRSY1";
    auto t1 = Trade<Bond>(data.GetProduct(),tid , data.GetPrice(), book, data.GetVisibleQuantity(), BUY);
    OnMessage(t1);
    
    auto t2 = Trade<Bond>(data.GetProduct(),tid , data.GetPrice(), (string)"TRSY2", data.GetVisibleQuantity(), BUY);
    OnMessage(t2);
    
    auto t3 = Trade<Bond>(data.GetProduct(),tid , data.GetPrice(), (string)"TRSY3", data.GetVisibleQuantity(), SELL);
    OnMessage(t3);
}

Trade<Bond>& BondExecutionService::GetData(string key) {
    return *executionBook[key];
}

void BondExecutionService::OnMessage(Trade<Bond> &data){
    // Use product id as the key for the getting data function
    for(auto i = listenerBook.begin(); i!=listenerBook.end(); i++){
        (*i)->ProcessUpdate(data);
    }
}

void BondExecutionService::AddListener(ServiceListener<Trade<Bond>> *listener){
    listenerBook.push_back(listener);
}

const vector<ServiceListener<Trade<Bond>>*>& BondExecutionService::GetListeners() const{
    return listenerBook;
}


#endif /* bondexecutionservice_h */
