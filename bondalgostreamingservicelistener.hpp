//
//  bondalgostreamingservicelistener.h
//  Trading System
//
//  Created by 廖佳珑 on 12/23/22.
//

#ifndef bondalgostreamingservicelistener_h
#define bondalgostreamingservicelistener_h

#include "soa.hpp"
#include "util.hpp"
#include "products.hpp"
#include "bondalgostreamingservice.hpp"

class BondAlgoStreamingServiceListener: public ServiceListener<Price<Bond>>{
public:
    BondAlgoStreamingServiceListener(BondAlgoStreamingService* _bps):bps(_bps){};
    
    // Listener callback to process an add event to the Service
    void ProcessAdd(Price<Bond> &data) override{}

    // Listener callback to process a remove event to the Service
    void ProcessRemove(Price<Bond> &data) override{}

    // Listener callback to process an update event to the Service
    void ProcessUpdate(Price<Bond> &data) override{
        bps->AddPrice(data);
    }
private:
    BondAlgoStreamingService* bps;
};
#endif /* bondalgostreamingservicelistener_h */
