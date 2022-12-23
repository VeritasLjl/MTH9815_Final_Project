//
//  bondriskservicelistener.h
//  Trading System
//
//  Created by 廖佳珑 on 12/23/22.
//

#ifndef bondriskservicelistener_h
#define bondriskservicelistener_h

#include "soa.hpp"
#include "util.hpp"
#include "products.hpp"
#include "bondriskservice.hpp"

class BondRiskServiceListener: public ServiceListener<Position<Bond>>{
public:
    BondRiskServiceListener(BondRiskService* _bps):bps(_bps){};
    
    // Listener callback to process an add event to the Service
    void ProcessAdd(Position<Bond> &data) override{}

    // Listener callback to process a remove event to the Service
    void ProcessRemove(Position<Bond> &data) override{}

    // Listener callback to process an update event to the Service
    void ProcessUpdate(Position<Bond> &data) override{
        bps->AddPosition(data);
    }
private:
    BondRiskService* bps;
};

#endif /* bondriskservicelistener_h */
