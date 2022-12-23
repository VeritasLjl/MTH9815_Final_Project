//
//  bondpositionservicelistener.h
//  Trading System
//
//  Created by 廖佳珑 on 12/23/22.
//

#ifndef bondpositionservicelistener_h
#define bondpositionservicelistener_h

#include "soa.hpp"
#include "util.hpp"
#include "products.hpp"
#include "bondpositionservice.hpp"

class BondPositionServiceListener: public ServiceListener<Trade<Bond>>{
public:
    BondPositionServiceListener(BondPositionService* _bps):bps(_bps){};
    
    // Listener callback to process an add event to the Service
    void ProcessAdd(Trade<Bond> &data) override{}

    // Listener callback to process a remove event to the Service
    void ProcessRemove(Trade<Bond> &data) override{}

    // Listener callback to process an update event to the Service
    void ProcessUpdate(Trade<Bond> &data) override{
        bps->AddTrade(data);
    }
private:
    BondPositionService* bps;
};

#endif /* bondpositionservicelistener_h */
