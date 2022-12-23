//
//  bondexecutionservicelistener.h
//  Trading System
//
//  Created by 廖佳珑 on 12/23/22.
//

#ifndef bondexecutionservicelistener_h
#define bondexecutionservicelistener_h

#include "soa.hpp"
#include "util.hpp"
#include "products.hpp"
#include "bondexecutionservice.hpp"


class BondExecutionServiceListener: public ServiceListener<ExecutionOrder<Bond>>{
public:
    BondExecutionServiceListener(BondExecutionService* _bps):bps(_bps){};
    
    // Listener callback to process an add event to the Service
    void ProcessAdd(ExecutionOrder<Bond> &data) override{}

    // Listener callback to process a remove event to the Service
    void ProcessRemove(ExecutionOrder<Bond> &data) override{}

    // Listener callback to process an update event to the Service
    void ProcessUpdate(ExecutionOrder<Bond> &data) override{
        bps->AddExecution(data);
    }
private:
    BondExecutionService* bps;
};

#endif /* bondexecutionservicelistener_h */
