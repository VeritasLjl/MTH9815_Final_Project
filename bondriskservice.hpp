//
//  bondriskservice.h
//  Trading System
//
//  Created by 廖佳珑 on 12/23/22.
//

#ifndef bondriskservice_h
#define bondriskservice_h

#include "soa.hpp"
#include "riskservice.hpp"
#include "products.hpp"
#include "util.hpp"


class BondRiskService: public RiskService<Bond>{
public:
    
    BondRiskService();
    
    // Get data on our service given a key
    PV01<Bond>& GetData(string key) override;

    // The callback that a Connector should invoke for any new or updated data
    void OnMessage(PV01<Bond> &data) override;

    // Add a listener to the Service for callbacks on add, remove, and update events
    // for data to the Service.
    void AddListener(ServiceListener<PV01<Bond>> *listener) override;

    // Get all listeners on the Service.
    const vector< ServiceListener<PV01<Bond>>* >& GetListeners() const override;
    
    void AddPosition(Position<Bond> &position) override;
    
    const PV01< BucketedSector<Bond> >& GetBucketedRisk(const BucketedSector<Bond> &sector) const override;

private:
    
    map<string, PV01<Bond>*> riskBook;
    vector<ServiceListener<PV01<Bond>>*> listenerBook;
};

BondRiskService::BondRiskService(){
    riskBook = std::map<string, PV01<Bond>*>();
    listenerBook = std::vector<ServiceListener<PV01<Bond>>*>();
}

PV01<Bond>& BondRiskService::GetData(string key) {
    return *riskBook[key];
}

void BondRiskService::OnMessage(PV01<Bond> &data){
    // Use product id as the key for the getting data function
    string key = data.GetProduct().GetProductId();
    if(riskBook.find(key)==riskBook.end()){
        if(DEBUG) std::cout << "INSERT  " << data.GetProduct() << std::endl;
        riskBook.insert(pair<string,PV01<Bond>*>(key,new PV01<Bond>(data)));
        
        for(auto i = listenerBook.begin(); i!=listenerBook.end(); i++){
            (*i)->ProcessAdd(data);
        }
    }
    else{
        // modify data
        if(DEBUG) std::cout << "UPDATE  " << data.GetProduct() << std::endl;
        delete riskBook[key];
        riskBook[key] = new PV01<Bond>(data);
        
        for(auto i = listenerBook.begin(); i!=listenerBook.end(); i++){
            (*i)->ProcessUpdate(data);
        }
    }
}

void BondRiskService::AddListener(ServiceListener<PV01<Bond>> *listener){
    listenerBook.push_back(listener);
}

const vector<ServiceListener<PV01<Bond>>*>& BondRiskService::GetListeners() const{
    return listenerBook;
}

void BondRiskService::AddPosition(Position<Bond> &position){
    if(riskBook.count(position.GetProduct().GetProductId())==0){
        riskBook[position.GetProduct().GetProductId()] = new PV01<Bond>(position.GetProduct(),0,position.GetAggregatePosition());
        // temporarily use 0 to indicate calculated risk
    }
    else{
        delete riskBook[position.GetProduct().GetProductId()];
        riskBook[position.GetProduct().GetProductId()] = new PV01<Bond>(position.GetProduct(),0,position.GetAggregatePosition());
    }
    OnMessage(*riskBook[position.GetProduct().GetProductId()]);
}

const PV01< BucketedSector<Bond> >& BondRiskService::GetBucketedRisk(const BucketedSector<Bond> &sector) const{
    auto pdts = sector.GetProducts();
    double totalrisk = 0;
    long qty = 0;
    for(auto i=pdts.begin(); i!=pdts.end();i++){
        totalrisk += 0; // consider risk to be zero now
        qty += 0; //consider position to be zero now
    }
    return PV01<BucketedSector<Bond>>(sector, totalrisk, qty);
}

#endif /* bondriskservice_h */
