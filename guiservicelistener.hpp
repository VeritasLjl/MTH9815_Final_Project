//
//  guiservicelistener.h
//  Trading System
//
//  Created by 廖佳珑 on 12/23/22.
//

#ifndef guiservicelistener_h
#define guiservicelistener_h
#include "soa.hpp"
#include "util.hpp"
#include "products.hpp"
#include "guiservice.hpp"

template<typename T>
class GUIServiceListener: public ServiceListener<Price<T>>{
public:
    GUIServiceListener(GUIService<T>* _bps):bps(_bps){};
    
    // Listener callback to process an add event to the Service
    void ProcessAdd(Price<T> &data) override{}

    // Listener callback to process a remove event to the Service
    void ProcessRemove(Price<T> &data) override{}

    // Listener callback to process an update event to the Service
    void ProcessUpdate(Price<T> &data) override{
        bps->Throettle(data);
    }
private:
    GUIService<T>* bps;
};

#endif /* guiservicelistener_h */
