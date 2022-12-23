//
//  bondalgoexecutionservicelistener.h
//  Trading System
//
//  Created by 廖佳珑 on 12/23/22.
//

#ifndef bondalgoexecutionservicelistener_h
#define bondalgoexecutionservicelistener_h

#include "soa.hpp"
#include "util.hpp"
#include "products.hpp"
#include "bondalgoexecutionservice.hpp"

class BondAlgoExecutionServiceListener: public ServiceListener<OrderBook<Bond>>{
public:
    BondAlgoExecutionServiceListener(BondAlgoExecutionService* _bps):bps(_bps){};
    
    // Listener callback to process an add event to the Service
    void ProcessAdd(OrderBook<Bond> &data) override{}

    // Listener callback to process a remove event to the Service
    void ProcessRemove(OrderBook<Bond> &data) override{}

    // Listener callback to process an update event to the Service
    void ProcessUpdate(OrderBook<Bond> &data) override{
        bps->Cross(data);
    }
private:
    BondAlgoExecutionService* bps;
};
#endif /* bondalgoexecutionservicelistener_h */
