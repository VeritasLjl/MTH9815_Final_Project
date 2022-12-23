//
//  bondstreamingservicelistener.h
//  Trading System
//
//  Created by 廖佳珑 on 12/23/22.
//

#ifndef bondstreamingservicelistener_h
#define bondstreamingservicelistener_h

#include "soa.hpp"
#include "util.hpp"
#include "products.hpp"
#include "bondstreamingservice.hpp"

class BondStreamingServiceListener: public ServiceListener<AlgoStream<Bond>>{
public:
    BondStreamingServiceListener(BondStreamingService* _bps):bps(_bps){};
    
    // Listener callback to process an add event to the Service
    void ProcessAdd(AlgoStream<Bond> &data) override{}

    // Listener callback to process a remove event to the Service
    void ProcessRemove(AlgoStream<Bond> &data) override{}

    // Listener callback to process an update event to the Service
    void ProcessUpdate(AlgoStream<Bond> &data) override{
        bps->AddStream(data);
    }
private:
    BondStreamingService* bps;
};

#endif /* bondstreamingservicelistener_h */
