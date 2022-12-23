//
//  bondstreamingservice.h
//  Trading System
//
//  Created by 廖佳珑 on 12/23/22.
//

#ifndef bondstreamingservice_h
#define bondstreamingservice_h

#include "soa.hpp"
#include "streamingservice.hpp"
#include "bondalgostreamingservice.hpp"
#include "products.hpp"
#include "util.hpp"


class BondStreamingService: public Service<string, AlgoStream<Bond>>{
public:
    
    // Get data on our service given a key
    AlgoStream<Bond>& GetData(string key) override;

    // The callback that a Connector should invoke for any new or updated data
    void OnMessage(AlgoStream<Bond> &data) override;

    // Add a listener to the Service for callbacks on add, remove, and update events
    // for data to the Service.
    void AddListener(ServiceListener<AlgoStream<Bond>> *listener) override;

    // Get all listeners on the Service.
    const vector< ServiceListener<AlgoStream<Bond>>* >& GetListeners() const override;

    void AddStream(AlgoStream<Bond> as);
    
private:
    
    map<string, AlgoStream<Bond>*> algoStreamBook;
    vector<ServiceListener<AlgoStream<Bond>>*> listenerBook;
};

AlgoStream<Bond>& BondStreamingService::GetData(string key) {
    return *algoStreamBook[key];
}

void BondStreamingService::OnMessage(AlgoStream<Bond> &data){
    // Use product id as the key for the getting data function
    
    for(auto i = listenerBook.begin(); i!=listenerBook.end(); i++){
        (*i)->ProcessUpdate(data);
    }
}

void BondStreamingService::AddListener(ServiceListener<AlgoStream<Bond>> *listener){
    listenerBook.push_back(listener);
}

const vector<ServiceListener<AlgoStream<Bond>>*>& BondStreamingService::GetListeners() const{
    return listenerBook;
}

void BondStreamingService::AddStream(AlgoStream<Bond> as){
    
}

#endif /* bondstreamingservice_h */
