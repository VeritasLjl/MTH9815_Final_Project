//
//  bondhistoricaldataservice.h
//  Trading System
//
//  Created by 廖佳珑 on 12/23/22.
//

#ifndef bondhistoricaldataservice_h
#define bondhistoricaldataservice_h

#include "soa.hpp"
#include "historicaldataservice.hpp"
#include "products.hpp"
#include "util.hpp"


class BondHistoricalDataService: public HistoricalDataService<Bond>{
public:
    
    BondHistoricalDataService();
    
    // Get data on our service given a key
    Bond& GetData(string key) override;

    // The callback that a Connector should invoke for any new or updated data
    void OnMessage(Bond &data) override;

    // Add a listener to the Service for callbacks on add, remove, and update events
    // for data to the Service.
    void AddListener(ServiceListener<Bond> *listener) override;

    // Get all listeners on the Service.
    const vector< ServiceListener<Bond>* >& GetListeners() const override;
    
    // Persist data to a store
    void PersistData(string persistKey, const Bond& data)override{}

private:
    
    map<string, Bond*> bondBook;
    vector<ServiceListener<Bond>*> listenerBook;
};

BondHistoricalDataService::BondHistoricalDataService(){
    bondBook = std::map<string, Bond*>();
    listenerBook = std::vector<ServiceListener<Bond>*>();
}

Bond& BondHistoricalDataService::GetData(string key) {
    return *bondBook[key];
}

void BondHistoricalDataService::OnMessage(Bond &data){
    // Use product id as the key for the getting data function
   for(auto i = listenerBook.begin(); i!=listenerBook.end(); i++){
        (*i)->ProcessUpdate(data);
    }
}

void BondHistoricalDataService::AddListener(ServiceListener<Bond> *listener){
    listenerBook.push_back(listener);
}

const vector<ServiceListener<Bond>*>& BondHistoricalDataService::GetListeners() const{
    return listenerBook;
}

#endif /* bondhistoricaldataservice_h */
